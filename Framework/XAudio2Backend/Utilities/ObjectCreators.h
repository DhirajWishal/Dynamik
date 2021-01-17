// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "XAudio2Backend/AudioObject.h"
#include "Core/Types/DataTypes.h"
#include "AudioCore/AudioObjectHandle.h"

namespace DMK
{
	namespace XAudio2Backend
	{
		/**
		 * Create an audio object using a WAV file.
		 *
		 * @param pAsset: The audio file path.
		 * @param pHandle: The Audio Object Handle object pointer. Default is nullptr.
		 */
		AudioObject CreateFromWAV(const wchar* pAsset, AudioCore::AudioObjectHandle* pHandle = nullptr);
	}
}