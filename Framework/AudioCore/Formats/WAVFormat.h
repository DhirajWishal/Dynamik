// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Types/DataTypes.h"

/**
 * Make a tag using 4 characters.
 * This is well defined in the MSDN documentation about XAudio2: https://docs.microsoft.com/en-us/windows/win32/xaudio2/how-to--load-audio-data-files-in-xaudio2
 */
#define MAKE_TAG(ch0, ch1, ch2, ch3)									\
				  (static_cast<UI32>(static_cast<UI8>(ch0))			\
				| (static_cast<UI32>(static_cast<UI8>(ch1)) << 8)	\
				| (static_cast<UI32>(static_cast<UI8>(ch2)) << 16)	\
				| (static_cast<UI32>(static_cast<UI8>(ch3)) << 24))

namespace DMK
{
	namespace AudioCore
	{
		/**
		 * WAV File Tag enum.
		 */
		enum class WAVFileTag : const UI32 {
			UNKNOWN = 0U,
			RIFF = MAKE_TAG('R', 'I', 'F', 'F'),
			FORMAT = MAKE_TAG('f', 'm', 't', ' '),
			DATA = MAKE_TAG('d', 'a', 't', 'a'),
			WAVE_FILE = MAKE_TAG('W', 'A', 'V', 'E'),
			XWMA_FILE = MAKE_TAG('X', 'W', 'M', 'A'),
			DLS_SAMPLE = MAKE_TAG('w', 's', 'm', 'p'),
			MIDI_SAMPLE = MAKE_TAG('s', 'm', 'p', 'l'),
			XWMA_DPDS = MAKE_TAG('d', 'p', 'd', 's'),
			XMA_SEEK = MAKE_TAG('s', 'e', 'e', 'k'),
		};

		/**
		 * WAV file format.
		 * This structure contains information about a single WAV file.
		 */
		struct WAVFormat {
			UI16 mFormatTag = 0;			// Format tag.
			UI16 mChannels = 0;				// The number of channels in the audio file.
			UI64 mSampleRate = 0;			// Sample rate of the audio.
			UI64 mAvgByteRate = 0;			// Averate number of bytes played per second.
			UI16 mBlockAlignment = 0;		// Alignment of the memory block.
			UI16 mBitsPerSample = 0;		// Number of bits per sample.
			UI16 mCBSize = 0;				// Size of the additional information.
		};

		/**
		 * WAV Data structure.
		 * This structure contains information about a single WAV file.
		 */
		struct WAVData {
			WAVFormat mWAVFormat = {};	// Wave format.
			const UI32* pSeek = nullptr;       // Note: XMA Seek data is Big-Endian
			const UI8* pStartAudio = nullptr;	// Audio playback starting point.
			UI32 mAudioBytes = 0;	// Number of audio bytes to play.
			UI32 mLoopStart = 0;	// Loop start index.
			UI32 mLoopLength = 0;	// The length of the loop.
			UI32 mSeekCount = 0;	// The seek count.
		};

#pragma pack(push, 1)
		/**
		 * RIFF Chunk structure.
		 * RIFF stands for Resource Interchange File Format (https://docs.microsoft.com/en-us/windows/win32/xaudio2/resource-interchange-file-format--riff-).
		 */
		struct RIFFChunk {
			WAVFileTag mTag = WAVFileTag::UNKNOWN;
			UI32 mSize = 0;
		};

		/**
		 * RIFF Chunk Header structure.
		 */
		struct RIFFChunkHeader {
			WAVFileTag mTag = WAVFileTag::UNKNOWN;
			UI32 mSize = 0;
			WAVFileTag mRiff = WAVFileTag::UNKNOWN;
		};

		/**
		 * DLS Loop structure.
		 */
		struct DLSLoop {
			static const UI32 Forward = 0x00000000;
			static const UI32 Release = 0x00000001;

			UI32 mSize = 0;
			UI32 mLoopType = 0;
			UI32 mLoopStart = 0;
			UI32 mLoopLength = 0;
		};

		/**
		 * RIFF DLS Sample structure.
		 */
		struct RIFFDLSSample {
			static const UI32 NoTruncation = 0x00000001;
			static const UI32 NoCompression = 0x00000002;

			UI32 mSize = 0;
			UI16 mUnityNote = 0;
			I16 mFineTune = 0;
			I32 mGain = 0;
			UI32 mOptions = 0;
			UI32 mLoopCount = 0;
		};

		/**
		 * MIDI Loop structure.
		 */
		struct MIDILoop {
			static const UI32 Forward = 0x00000000;
			static const UI32 Alternating = 0x00000001;
			static const UI32 Backward = 0x00000002;

			UI32 mCuePointId = 0;
			UI32 mType = 0;
			UI32 mStart = 0;
			UI32 mEnd = 0;
			UI32 mFraction = 0;
			UI32 mPlayCount = 0;
		};

		/**
		 * RIFF MIDI Sample structure.
		 */
		struct RIFFMIDISample {
			UI32 mManufacturerId = 0;
			UI32 mProductId = 0;
			UI32 mSamplePeriod = 0;
			UI32 mUnityNode = 0;
			UI32 mPitchFraction = 0;
			UI32 mSMPTEFormat = 0;
			UI32 mSMPTEOffset = 0;
			UI32 mLoopCount = 0;
			UI32 mSamplerData = 0;
		};
#pragma pack(pop)

		/**
		 * Check if the RIFF Chunk size is valid.
		 */
		static_assert(sizeof(RIFFChunk) == 8, "RIFFChunk structure size mismatch!");

		/**
		 * Check if the RIFF Chunk Header size is valid.
		 */
		static_assert(sizeof(RIFFChunkHeader) == 12, "RIFFChunkHeader structure size mismatch!");

		/**
		 * Check if the DLS Loop size is valid.
		 */
		static_assert(sizeof(DLSLoop) == 16, "DLSLoop structure size mismatch!");

		/**
		 * Check if the RIFF DLS Sample size is valid.
		 */
		static_assert(sizeof(RIFFDLSSample) == 20, "RIFFDLSSample structure size mismatch!");

		/**
		 * Check if the MIDI Loop size is valid.
		 */
		static_assert(sizeof(MIDILoop) == 24, "MIDILoop structure size mismatch!");

		/**
		 * Check if the RIFF MIDI Sample size is valid.
		 */
		static_assert(sizeof(RIFFMIDISample) == 36, "RIFFMIDISample structure size mismatch!");
	}
}