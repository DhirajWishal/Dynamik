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
			 * Load Audio From File command.
			 * This command loads audio data from a file and returns its handle to a defined pointer.
			 */
			struct LoadAudioFromFile {
				/**
				 * Construct the command using the asset path and the handle pointer.
				 *
				 * @param pAsset: The asset path.
				 * @param pHandle: The location to store the handle data to. Default is nullptr.
				 */
				LoadAudioFromFile(const wchar* pAsset, AudioObjectHandle* pHandle = nullptr)
					: pAsset(pAsset), pHandle(pHandle) {}

				const wchar* pAsset = nullptr;	// The asset path.
				AudioObjectHandle* pHandle = nullptr;	// The audio object handle pointer.
			};

			/**
			 * Get Audio Object Cache command.
			 * This command retrieves the cache of a given audio object handle.
			 */
			struct GetAudioObjectCache {
				/**
				 * Construct the command using the audio object handle and the audio cache pointer.
				 *
				 * @param mHandle: The audio object handle.
				 * @param pCache: The audio cache pointer.
				 */
				GetAudioObjectCache(const AudioObjectHandle& mHandle, AudioObjectCache* pCache)
					: mHandle(mHandle), pCache(pCache) {}

				AudioObjectHandle mHandle = {};	// Audio object handle.
				AudioObjectCache* pCache = { nullptr };	// Audio object cache pointer.
			};
		}
	}
}