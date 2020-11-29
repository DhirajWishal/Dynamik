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
			/**
			 * Default constructor.
			 */
			AudioObjectHandle() {}

			/**
			 * Default destructor.
			 */
			~AudioObjectHandle() {}

			/**
			 * Get the name of the audio object.
			 *
			 * @return Const char pointer.
			 */
			const char* GetName() const { return pName; }

			/**
			 * Get the audio object handle.
			 *
			 * @return The handle unsigned integer.
			 */
			UI64 GetHandle() const { return mHandle; }

			/**
			 * Get the length of the audio.
			 *
			 * @return The length in miliseconds.
			 */
			UI64 GetLength() const { return mLength; }

			/**
			 * Get the sample rate.
			 *
			 * @return The sample rate in Hz.
			 */
			UI64 GetSampleRate() const { return mSampleRate; }

			/**
			 * Get the number of bytes played per second.
			 *
			 * @return The number of bytes per second.
			 */
			UI64 GetBytesPerSecond() const { return mBytesPerSecond; }

			/**
			 * Get the audio format.
			 *
			 * @return AudioFileFormat enum.
			 */
			AudioFileFormat GetFormat() const { return mFormat; }

			const char* pName = nullptr;	// The audio file name.
			UI64 mHandle = 0;	// Audio object handle.

			UI64 mLength = 0;	// Length of the audio.
			UI64 mSampleRate = 0;	// The sample rate of the audio.
			UI64 mBytesPerSecond = 0;	// The number of bytes played per second.

			AudioFileFormat mFormat = AudioFileFormat::UNDEFINED;	// Audio file format.
		};

		/**
		 * Audio Object Cache type.
		 * This type holds the audio object cache which removes the need to process handles.
		 * Note that the cache might not be valid after adding more or removing an audio object from the backend.
		 */
		typedef void* AudioObjectCache;
	}
}