// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "XAudio2Backend/AudioObject.h"
#include "Core/ErrorHandler/Logger.h"

namespace DMK
{
	namespace XAudio2Backend
	{
		void AudioObject::Terminate()
		{
		}

		void AudioObject::BeginPlay(IXAudio2* pInstance)
		{
			// Create the source voice structure.
			pInstance->CreateSourceVoice(GetSourceDataPointer(), &mWaveFromat);

			// Submit buffers.
			if (GetBufferXWMAAddress()->pDecodedPacketCumulativeBytes)
			{
				if (FAILED(GetSourcePointer()->SubmitSourceBuffer(GetBufferAddress(), GetBufferXWMAAddress())))
				{
					DMK_LOG_ERROR(TEXT("Failed to submit audio data to the buffer!"));
					GetSourcePointer()->DestroyVoice();
					return;
				}
			}
			else
			{
				if (FAILED(GetSourcePointer()->SubmitSourceBuffer(GetBufferAddress())))
				{
					DMK_LOG_ERROR(TEXT("Failed to submit audio data to the buffer!"));
					GetSourcePointer()->DestroyVoice();
					return;
				}
			}

			// Start playing.
			GetSourcePointer()->Start(0);
		}

		bool AudioObject::UpdatePlay()
		{
			XAUDIO2_VOICE_STATE state = {};
			GetSourcePointer()->GetState(&state);
			return (state.BuffersQueued > 0) != 0;
		}

		void AudioObject::PlayOnce(IXAudio2* pInstance)
		{
			// Begin play.
			BeginPlay(pInstance);

			// Let the sound play
			while (UpdatePlay()) Sleep(10);

			// Terminate the voice.
			GetSourcePointer()->DestroyVoice();
		}
	}
}