// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "XAudio2Backend/Utilities/ObjectCreators.h"
#include "XAudio2Backend/Utilities/Converters.h"
#include "XAudio2Backend/Loaders/WAVLoader.h"

#include "Core/ErrorHandler/Logger.h"

#define WIN32_MEAN_AND_LEAN
#include <Windows.h>

namespace DMK
{
	namespace XAudio2Backend
	{
		AudioObject CreateFromWAV(const wchar* pAsset, AudioCore::AudioObjectHandle* pHandle)
		{
			// Setup objects and pointers.
			AudioObject mObject = {};
			AudioCore::WAVData wavData = {};
			UI8* pData = nullptr;

			// Load audio data.
			if (FAILED(LoadWAVAudioFromFileEx(pAsset, &pData, wavData)))
				Logger::LogError(TEXT("Failed to load the WAV file!"));

			// Set handle data if needed.
			if (pHandle)
			{
				pHandle->mFormat = AudioCore::AudioFileFormat::WAV;
				pHandle->mBytesPerSecond = wavData.mWAVFormat.mAvgByteRate;
				pHandle->mLength = wavData.mLoopLength;
				pHandle->mSampleRate = wavData.mWAVFormat.mSampleRate;
			}

			// Create source voice.
			*mObject.GetWaveFormatAddress() = WAVFormatToWAVEFORMATEX(wavData.mWAVFormat);
			mObject.GetBufferAddress()->pAudioData = wavData.pStartAudio;
			mObject.GetBufferAddress()->Flags = XAUDIO2_END_OF_STREAM;  // tell the source voice not to expect any data after this buffer
			mObject.GetBufferAddress()->AudioBytes = wavData.mAudioBytes;

			// Setup loop data.
			if (wavData.mLoopLength > 0)
			{
				mObject.GetBufferAddress()->LoopBegin = wavData.mLoopStart;
				mObject.GetBufferAddress()->LoopLength = wavData.mLoopLength;
				mObject.GetBufferAddress()->LoopCount = 1; // We'll just assume we play the loop twice
			}

			// Setup seek data.
			if (wavData.pSeek)
			{
				mObject.GetBufferXWMAAddress()->pDecodedPacketCumulativeBytes = wavData.pSeek;
				mObject.GetBufferXWMAAddress()->PacketCount = wavData.mSeekCount;
			}

			return mObject;
		}
	}
}