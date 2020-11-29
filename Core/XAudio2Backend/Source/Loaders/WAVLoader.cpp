// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "XAudio2Backend/Loaders/WAVLoader.h"

/**
 * Some of these files are from the DirectX XAudio2 examples @https://github.com/walbourn/directx-sdk-samples/blob/master/XAudio2/Common/WAVFileReader.cpp
 */

namespace DMK
{
	namespace XAudio2Backend
	{
		struct handle_closer { void operator()(HANDLE h) noexcept { if (h) CloseHandle(h); } };

		using ScopedHandle = std::unique_ptr<void, handle_closer>;

		inline HANDLE safe_handle(HANDLE h) noexcept { return (h == INVALID_HANDLE_VALUE) ? nullptr : h; }

		const AudioCore::RIFFChunk* FindChunk(const UI8* data, UI64 sizeBytes, AudioCore::WAVFileTag tag)
		{
			if (!data)
				return nullptr;

			const UI8* ptr = data;
			const UI8* end = data + sizeBytes;

			while (end > (ptr + sizeof(AudioCore::RIFFChunk)))
			{
				auto header = reinterpret_cast<const AudioCore::RIFFChunk*>(ptr);
				if (header->mTag == tag)
					return header;

				auto offset = header->mSize + sizeof(AudioCore::RIFFChunk);
				ptr += offset;
			}

			return nullptr;
		}

		HRESULT FindFormatAndData(const UI8* wavData, UI64 wavDataSize, AudioCore::WAVFormat* pwfx, const UI8** pdata, UI32* dataSize, bool& dpds, bool& seek)
		{
			if (!wavData || !pwfx)
				return E_POINTER;

			dpds = seek = false;

			if (wavDataSize < (sizeof(AudioCore::RIFFChunk) * 2 + sizeof(UI32) + sizeof(WAVEFORMAT)))
				return E_FAIL;

			const UI8* wavEnd = wavData + wavDataSize;

			// Locate RIFF 'WAVE'
			auto riffChunk = FindChunk(wavData, wavDataSize, AudioCore::WAVFileTag::RIFF);
			if (!riffChunk || riffChunk->mSize < 4)
				return E_FAIL;

			auto riffHeader = reinterpret_cast<const AudioCore::RIFFChunkHeader*>(riffChunk);
			if (riffHeader->mRiff != AudioCore::WAVFileTag::WAVE_FILE && riffHeader->mRiff != AudioCore::WAVFileTag::XWMA_FILE)
				return E_FAIL;

			// Locate 'fmt '
			auto ptr = reinterpret_cast<const UI8*>(riffHeader) + sizeof(AudioCore::RIFFChunkHeader);
			if ((ptr + sizeof(AudioCore::RIFFChunk)) > wavEnd)
				return HRESULT_FROM_WIN32(ERROR_HANDLE_EOF);

			auto fmtChunk = FindChunk(ptr, riffHeader->mSize, AudioCore::WAVFileTag::FORMAT);
			if (!fmtChunk || fmtChunk->mSize < sizeof(PCMWAVEFORMAT))
				return E_FAIL;

			ptr = reinterpret_cast<const UI8*>(fmtChunk) + sizeof(AudioCore::RIFFChunk);
			if (ptr + fmtChunk->mSize > wavEnd)
				return HRESULT_FROM_WIN32(ERROR_HANDLE_EOF);

			auto wf = reinterpret_cast<const WAVEFORMATEX*>(ptr);

			// Validate WAVEFORMAT (focused on chunk size and format tag, not other data that XAUDIO2 will validate)
			switch (wf->wFormatTag)
			{
			case WAVE_FORMAT_PCM:
			case WAVE_FORMAT_IEEE_FLOAT:
				// Can be a PCMWAVEFORMAT (16 bytes) or WAVEFORMATEX (18 bytes)
				// We validiated chunk as at least sizeof(PCMWAVEFORMAT) above
				break;

			default:
			{
				if (fmtChunk->mSize < sizeof(WAVEFORMATEX))
					return E_FAIL;

				auto wfx = reinterpret_cast<const WAVEFORMATEX*>(ptr);

				if (fmtChunk->mSize < (sizeof(WAVEFORMATEX) + wfx->cbSize))
					return E_FAIL;

				switch (wfx->wFormatTag)
				{
				case WAVE_FORMAT_WMAUDIO2:
				case WAVE_FORMAT_WMAUDIO3:
					dpds = true;
					break;

				case  0x166 /*WAVE_FORMAT_XMA2*/: // XMA2 is supported by Xbox One
					if ((fmtChunk->mSize < 52 /*sizeof(XMA2WAVEFORMATEX)*/) || (wfx->cbSize < 34 /*( sizeof(XMA2WAVEFORMATEX) - sizeof(WAVEFORMATEX) )*/))
						return E_FAIL;
					seek = true;
					break;

				case WAVE_FORMAT_ADPCM:
					if ((fmtChunk->mSize < (sizeof(WAVEFORMATEX) + 32)) || (wfx->cbSize < 32 /*MSADPCM_FORMAT_EXTRA_BYTES*/))
						return E_FAIL;
					break;

				case WAVE_FORMAT_EXTENSIBLE:
					if ((fmtChunk->mSize < sizeof(WAVEFORMATEXTENSIBLE)) || (wfx->cbSize < (sizeof(WAVEFORMATEXTENSIBLE) - sizeof(WAVEFORMATEX))))
						return E_FAIL;
					else
					{
						static const GUID s_wfexBase = { 0x00000000, 0x0000, 0x0010, { 0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71 } };

						auto wfex = reinterpret_cast<const WAVEFORMATEXTENSIBLE*>(ptr);

						if (memcmp(reinterpret_cast<const BYTE*>(&wfex->SubFormat) + sizeof(DWORD),
							reinterpret_cast<const BYTE*>(&s_wfexBase) + sizeof(DWORD), sizeof(GUID) - sizeof(DWORD)) != 0)
							return HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED);

						switch (wfex->SubFormat.Data1)
						{
						case WAVE_FORMAT_PCM:
						case WAVE_FORMAT_IEEE_FLOAT:
							break;

							// MS-ADPCM and XMA2 are not supported as WAVEFORMATEXTENSIBLE

						case WAVE_FORMAT_WMAUDIO2:
						case WAVE_FORMAT_WMAUDIO3:
							dpds = true;
							break;

						default:
							return HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED);
						}

					}
					break;

				default:
					return HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED);
				}
			}
			}

			// Locate 'data'
			ptr = reinterpret_cast<const UI8*>(riffHeader) + sizeof(AudioCore::RIFFChunkHeader);
			if ((ptr + sizeof(AudioCore::RIFFChunk)) > wavEnd)
				return HRESULT_FROM_WIN32(ERROR_HANDLE_EOF);

			auto dataChunk = FindChunk(ptr, riffChunk->mSize, AudioCore::WAVFileTag::DATA);
			if (!dataChunk || !dataChunk->mSize)
				return HRESULT_FROM_WIN32(ERROR_INVALID_DATA);

			ptr = reinterpret_cast<const UI8*>(dataChunk) + sizeof(AudioCore::RIFFChunk);
			if (ptr + dataChunk->mSize > wavEnd)
				return HRESULT_FROM_WIN32(ERROR_HANDLE_EOF);

			(*pwfx).mFormatTag = wf->wFormatTag;
			(*pwfx).mChannels = wf->nChannels;
			(*pwfx).mSampleRate = wf->nSamplesPerSec;
			(*pwfx).mAvgByteRate = wf->nAvgBytesPerSec;
			(*pwfx).mBlockAlignment = wf->nBlockAlign;
			(*pwfx).mBitsPerSample = wf->wBitsPerSample;
			(*pwfx).mCBSize = wf->cbSize;

			*pdata = ptr;
			*dataSize = dataChunk->mSize;
			return S_OK;
		}

		HRESULT FindLoopInfo(const UI8* wavData, UI64 wavDataSize, UI32* pLoopStart, UI32* pLoopLength)
		{
			if (!wavData || !pLoopStart || !pLoopLength)
				return E_POINTER;

			if (wavDataSize < (sizeof(AudioCore::RIFFChunk) + sizeof(UI32)))
				return E_FAIL;

			*pLoopStart = 0;
			*pLoopLength = 0;

			const UI8* wavEnd = wavData + wavDataSize;

			// Locate RIFF 'WAVE'
			auto riffChunk = FindChunk(wavData, wavDataSize, AudioCore::WAVFileTag::RIFF);
			if (!riffChunk || riffChunk->mSize < 4)
				return E_FAIL;

			auto riffHeader = reinterpret_cast<const AudioCore::RIFFChunkHeader*>(riffChunk);
			if (riffHeader->mRiff == AudioCore::WAVFileTag::XWMA_FILE)
				// xWMA files do not contain loop information
				return S_OK;

			if (riffHeader->mRiff != AudioCore::WAVFileTag::WAVE_FILE)
				return E_FAIL;

			// Locate 'wsmp' (DLS Chunk)
			auto ptr = reinterpret_cast<const UI8*>(riffHeader) + sizeof(AudioCore::RIFFChunkHeader);
			if ((ptr + sizeof(AudioCore::RIFFChunk)) > wavEnd)
				return HRESULT_FROM_WIN32(ERROR_HANDLE_EOF);

			auto dlsChunk = FindChunk(ptr, riffChunk->mSize, AudioCore::WAVFileTag::DLS_SAMPLE);
			if (dlsChunk)
			{
				ptr = reinterpret_cast<const UI8*>(dlsChunk) + sizeof(AudioCore::RIFFChunk);
				if (ptr + dlsChunk->mSize > wavEnd)
					return HRESULT_FROM_WIN32(ERROR_HANDLE_EOF);

				if (dlsChunk->mSize >= sizeof(AudioCore::RIFFDLSSample))
				{
					auto dlsSample = reinterpret_cast<const AudioCore::RIFFDLSSample*>(ptr);

					if (dlsChunk->mSize >= (dlsSample->mSize + dlsSample->mLoopCount * sizeof(AudioCore::DLSLoop)))
					{
						auto loops = reinterpret_cast<const AudioCore::DLSLoop*>(ptr + dlsSample->mSize);
						for (UI32 j = 0; j < dlsSample->mLoopCount; ++j)
						{
							if ((loops[j].mLoopType == AudioCore::DLSLoop::Forward || loops[j].mLoopType == AudioCore::DLSLoop::Release))
							{
								// Return 'forward' loop
								*pLoopStart = loops[j].mLoopStart;
								*pLoopLength = loops[j].mLoopLength;
								return S_OK;
							}
						}
					}
				}
			}

			// Locate 'smpl' (Sample Chunk)
			auto midiChunk = FindChunk(ptr, riffChunk->mSize, AudioCore::WAVFileTag::MIDI_SAMPLE);
			if (midiChunk)
			{
				ptr = reinterpret_cast<const UI8*>(midiChunk) + sizeof(AudioCore::RIFFChunk);
				if (ptr + midiChunk->mSize > wavEnd)
					return HRESULT_FROM_WIN32(ERROR_HANDLE_EOF);

				if (midiChunk->mSize >= sizeof(AudioCore::RIFFMIDISample))
				{
					auto midiSample = reinterpret_cast<const AudioCore::RIFFMIDISample*>(ptr);

					if (midiChunk->mSize >= (sizeof(AudioCore::RIFFMIDISample) + midiSample->mLoopCount * sizeof(AudioCore::MIDILoop)))
					{
						auto loops = reinterpret_cast<const AudioCore::MIDILoop*>(ptr + sizeof(AudioCore::RIFFMIDISample));
						for (UI32 j = 0; j < midiSample->mLoopCount; ++j)
						{
							if (loops[j].mType == AudioCore::MIDILoop::Forward)
							{
								// Return 'forward' loop
								*pLoopStart = loops[j].mStart;
								*pLoopLength = loops[j].mEnd - loops[j].mStart + 1;
								return S_OK;
							}
						}
					}
				}
			}

			return S_OK;
		}

		HRESULT FindTable(const UI8* wavData, UI64 wavDataSize, AudioCore::WAVFileTag tag, const UI32** pData, UI32* dataCount)
		{
			if (!wavData || !pData || !dataCount)
				return E_POINTER;

			if (wavDataSize < (sizeof(AudioCore::RIFFChunk) + sizeof(UI32)))
				return E_FAIL;

			*pData = nullptr;
			*dataCount = 0;

			const UI8* wavEnd = wavData + wavDataSize;

			// Locate RIFF 'WAVE'
			auto riffChunk = FindChunk(wavData, wavDataSize, AudioCore::WAVFileTag::RIFF);
			if (!riffChunk || riffChunk->mSize < 4)
				return E_FAIL;

			auto riffHeader = reinterpret_cast<const AudioCore::RIFFChunkHeader*>(riffChunk);
			if (riffHeader->mRiff != AudioCore::WAVFileTag::WAVE_FILE && riffHeader->mRiff != AudioCore::WAVFileTag::XWMA_FILE)
				return E_FAIL;

			// Locate tag
			auto ptr = reinterpret_cast<const UI8*>(riffHeader) + sizeof(AudioCore::RIFFChunkHeader);
			if ((ptr + sizeof(AudioCore::RIFFChunk)) > wavEnd)
				return HRESULT_FROM_WIN32(ERROR_HANDLE_EOF);

			auto tableChunk = FindChunk(ptr, riffChunk->mSize, tag);
			if (tableChunk)
			{
				ptr = reinterpret_cast<const UI8*>(tableChunk) + sizeof(AudioCore::RIFFChunk);
				if (ptr + tableChunk->mSize > wavEnd)
				{
					return HRESULT_FROM_WIN32(ERROR_HANDLE_EOF);
				}

				if ((tableChunk->mSize % sizeof(UI32)) != 0)
				{
					return E_FAIL;
				}

				*pData = reinterpret_cast<const UI32*>(ptr);
				*dataCount = tableChunk->mSize / 4;
			}

			return S_OK;
		}

#define RESET_POINTER(ptr) if(*ptr) delete[] *ptr

		HRESULT LoadAudioFromFile(const wchar* szFileName, UI8** wavData, DWORD* bytesRead)
		{
			if (!szFileName)
				return E_INVALIDARG;

			// open the file
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN8)
			ScopedHandle hFile(safe_handle(CreateFile2(szFileName,
				GENERIC_READ,
				FILE_SHARE_READ,
				OPEN_EXISTING,
				nullptr)));
#else
			ScopedHandle hFile(safe_handle(CreateFileW(szFileName,
				GENERIC_READ,
				FILE_SHARE_READ,
				nullptr,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				nullptr)));
#endif

			if (!hFile)
				return HRESULT_FROM_WIN32(GetLastError());

			// Get the file size
			FILE_STANDARD_INFO fileInfo;
			if (!GetFileInformationByHandleEx(hFile.get(), FileStandardInfo, &fileInfo, sizeof(fileInfo)))
				return HRESULT_FROM_WIN32(GetLastError());

			// File is too big for 32-bit allocation, so reject read
			if (fileInfo.EndOfFile.HighPart > 0)
				return E_FAIL;

			// Need at least enough data to have a valid minimal WAV file
			if (fileInfo.EndOfFile.LowPart < (sizeof(AudioCore::RIFFChunk) * 2 + sizeof(DWORD) + sizeof(WAVEFORMAT)))
				return E_FAIL;

			// Create enough space for the file data
			RESET_POINTER(wavData);
			*wavData = new (std::nothrow) UI8[fileInfo.EndOfFile.LowPart];
			if (!(*wavData))
				return E_OUTOFMEMORY;

			// read the data in
			if (!ReadFile(hFile.get(),
				*wavData,
				fileInfo.EndOfFile.LowPart,
				bytesRead,
				nullptr
			))
				return HRESULT_FROM_WIN32(GetLastError());

			return (*bytesRead < fileInfo.EndOfFile.LowPart) ? E_FAIL : S_OK;
		}

		HRESULT LoadWAVAudioInMemory(const UI8* wavData, UI64 wavDataSize, AudioCore::WAVFormat* wfx, const UI8** startAudio, UI32* audioBytes)
		{
			if (!wavData || !wfx || !startAudio || !audioBytes)
				return E_INVALIDARG;

			*wfx = {};
			*startAudio = nullptr;
			*audioBytes = 0;

			// Need at least enough data to have a valid minimal WAV file
			if (wavDataSize < (sizeof(AudioCore::RIFFChunk) * 2 + sizeof(DWORD) + sizeof(WAVEFORMAT)))
				return E_FAIL;

			bool dpds, seek;
			HRESULT hr = FindFormatAndData(wavData, wavDataSize, wfx, startAudio, audioBytes, dpds, seek);
			if (FAILED(hr))
				return hr;

			return (dpds || seek) ? E_FAIL : S_OK;
		}

		HRESULT LoadWAVAudioFromFile(const wchar* szFileName, UI8** wavData, AudioCore::WAVFormat* wfx, const UI8** startAudio, UI32* audioBytes)
		{
			if (!szFileName || !wfx || !startAudio || !audioBytes)
				return E_INVALIDARG;

			*wfx = {};
			*startAudio = nullptr;
			*audioBytes = 0;

			DWORD bytesRead = 0;
			HRESULT hr = LoadAudioFromFile(szFileName, wavData, &bytesRead);
			if (FAILED(hr))
				return hr;

			bool dpds, seek;
			hr = FindFormatAndData(*wavData, bytesRead, wfx, startAudio, audioBytes, dpds, seek);
			if (FAILED(hr))
				return hr;

			return (dpds || seek) ? E_FAIL : S_OK;
		}

		HRESULT LoadWAVAudioInMemoryEx(const UI8* wavData, UI64 wavDataSize, AudioCore::WAVData& result)
		{
			if (!wavData)
				return E_INVALIDARG;

			memset(&result, 0, sizeof(result));

			// Need at least enough data to have a valid minimal WAV file
			if (wavDataSize < (sizeof(AudioCore::RIFFChunk) * 2 + sizeof(DWORD) + sizeof(WAVEFORMAT)))
				return E_FAIL;

			bool dpds, seek;
			HRESULT hr = FindFormatAndData(wavData, wavDataSize, &result.mWAVFormat, &result.pStartAudio, &result.mAudioBytes, dpds, seek);
			if (FAILED(hr))
				return hr;

			hr = FindLoopInfo(wavData, wavDataSize, &result.mLoopStart, &result.mLoopLength);
			if (FAILED(hr))
				return hr;

			if (dpds)
			{
				hr = FindTable(wavData, wavDataSize, AudioCore::WAVFileTag::XWMA_DPDS, &result.pSeek, &result.mSeekCount);
				if (FAILED(hr))
					return hr;
			}
			else if (seek)
			{
				hr = FindTable(wavData, wavDataSize, AudioCore::WAVFileTag::XMA_SEEK, &result.pSeek, &result.mSeekCount);
				if (FAILED(hr))
					return hr;
			}

			return S_OK;
		}

		HRESULT LoadWAVAudioFromFileEx(const wchar* szFileName, UI8** wavData, AudioCore::WAVData& result)
		{
			if (!szFileName)
				return E_INVALIDARG;

			memset(&result, 0, sizeof(result));

			DWORD bytesRead = 0;
			HRESULT hr = LoadAudioFromFile(szFileName, wavData, &bytesRead);
			if (FAILED(hr))
				return hr;

			bool dpds, seek;
			hr = FindFormatAndData(*wavData, bytesRead, &result.mWAVFormat, &result.pStartAudio, &result.mAudioBytes, dpds, seek);
			if (FAILED(hr))
				return hr;

			hr = FindLoopInfo(*wavData, bytesRead, &result.mLoopStart, &result.mLoopLength);
			if (FAILED(hr))
				return hr;

			if (dpds)
			{
				hr = FindTable(*wavData, bytesRead, AudioCore::WAVFileTag::XWMA_DPDS, &result.pSeek, &result.mSeekCount);
				if (FAILED(hr))
					return hr;
			}
			else if (seek)
			{
				hr = FindTable(*wavData, bytesRead, AudioCore::WAVFileTag::XMA_SEEK, &result.pSeek, &result.mSeekCount);
				if (FAILED(hr))
					return hr;
			}

			return S_OK;
		}
	}
}