// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "AudioCore/AudioObjectHandle.h"

namespace DMK
{
	namespace AudioCore
	{
		namespace Commands
		{
			/**
			 * Direct Playback command.
			 * This command send the audio file path and the backend will load the audio data and play is for
			 * how long the user states.
			 * This method of audio playback is somewhat slow as the audio data are loaded to memory from the file
			 * each time this command is sent. Looping takes a default time as audio data are not required to loaded
			 * again from memory.
			 */
			struct DirectPlayback {
				/**
				 * Construct the command using the asset path and loop count.
				 *
				 * @param pAsset: The asset path.
				 * @param loopCount: The number of times to loop the audio track. Default is 1.
				 * @param volumeFactor: The volume of the audio playback. Default is 1.0f.
				 */
				DirectPlayback(const wchar* pAsset, UI32 loopCount = 1, float volumeFactor = 1.0f)
					: pAsset(pAsset), loopCount(loopCount), volumeFactor(volumeFactor) {}

				const wchar* pAsset = nullptr;	// Audio asset path.
				UI64 loopCount = 1;	// Loop count.
				float volumeFactor = 1.0f;	// Volume of the playback.
			};

			/**
			 * Buffered Playback command.
			 * This is the fastest playback and the audio data is to be first loaded to the memory (buffered)
			 * prior to playback.
			 * For this command, providing either one of the handle or cache is enough to play the track but if
			 * better speed is required, we recommend providing the cache.
			 */
			struct BufferedPlayback {
				/**
				 * Construct the command using the handle, cache and loop count.
				 *
				 * @param mHandle: The audio object handle.
				 * @param mCache: The audio object cache. Default is nullptr.
				 * @param loopCount: The number of times the audio should be played. Default is 1.
				 * @param volumeFactor: The volume of the audio playback. Default is 1.0f.
				 */
				BufferedPlayback(const AudioObjectHandle& mHandle, AudioObjectCache mCache = nullptr, UI64 loopCount = 1, float volumeFactor = 1.0f)
					: mHandle(mHandle), mCache(mCache), loopCount(loopCount), volumeFactor(volumeFactor) {}

				AudioObjectHandle mHandle = {};	// The audio object handle.
				AudioObjectCache mCache = nullptr;	// The audio object cache.
				UI64 loopCount = 1;	// Loop count.
				float volumeFactor = 1.0f;	// Volume of the playback.
			};

			struct StreamedPlayback {};
		}
	}
}