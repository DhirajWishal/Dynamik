// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Types/DataTypes.h"

namespace DMK
{
	namespace AudioCore
	{
		/**
		 * Audio File Format enum.
		 * This defines which file contained the audio data.
		 */
		enum class AudioFileFormat : UI8 {
			UNDEFINED,
			WAV,
			MP3,
			OGG,
		};

		/**
		 * Audio Object Handle.
		 * This object shares the link to an audio object in a selected audio backend. Since the backend is designed
		 * to be data-oriented, the backends store their own audio object implementations. This class contains the
		 * link (one in two) to one of these audio objects.
		 */
		class AudioObjectHandle {
		public:
			AudioObjectHandle() {}
			~AudioObjectHandle() {}

			const char* GetName() const { return pName; }
			UI64 GetHandle() const { return mHandle; }
			UI64 GetLength() const { return mLength; }
			UI64 GetSampleRate() const { return mSampleRate; }
			UI64 GetBytesPerSecond() const { return mBytesPerSecond; }
			AudioFileFormat GetFormat() const { return mFormat; }

			const char* pName = nullptr;
			UI64 mHandle = 0;

			UI64 mLength = 0;
			UI64 mSampleRate = 0;
			UI64 mBytesPerSecond = 0;

			AudioFileFormat mFormat = AudioFileFormat::UNDEFINED;
		};

		/**
		 * Audio Object Cache type.
		 * This type holds the audio object cache which removes the need to process handles.
		 * Note that the cache might not be valid after adding more or removing an audio object from the backend.
		 */
		typedef void* AudioObjectCache;
	}
}