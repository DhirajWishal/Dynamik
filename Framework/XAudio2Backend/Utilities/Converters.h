// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "AudioCore/Formats/WAVFormat.h"
#include <xaudio2.h>

namespace DMK
{
	namespace XAudio2Backend
	{
		/**
		 * Get WAVFormat data and insert it to the WAVEFORAMATEX structure.
		 *
		 * @param mFormat: The WAVFormat structure.
		 * @return WAVEFORMATEX structure.
		 */
		WAVEFORMATEX WAVFormatToWAVEFORMATEX(const AudioCore::WAVFormat& mFormat);
	}
}