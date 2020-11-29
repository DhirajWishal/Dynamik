// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "XAudio2Backend/Utilities/Converters.h"

namespace DMK
{
	namespace XAudio2Backend
	{
		WAVEFORMATEX WAVFormatToWAVEFORMATEX(const AudioCore::WAVFormat& mFormat)
		{
			WAVEFORMATEX mWaveFormat = {};
			mWaveFormat.wFormatTag = mFormat.mFormatTag;
			mWaveFormat.nChannels = mFormat.mChannels;
			mWaveFormat.nSamplesPerSec = static_cast<UI32>(mFormat.mSampleRate);
			mWaveFormat.nAvgBytesPerSec = static_cast<UI32>(mFormat.mAvgByteRate);
			mWaveFormat.nBlockAlign = mFormat.mBlockAlignment;
			mWaveFormat.wBitsPerSample = mFormat.mBitsPerSample;
			mWaveFormat.cbSize = mFormat.mCBSize;

			return mWaveFormat;
		}
	}
}