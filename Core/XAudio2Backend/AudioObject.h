// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "AudioCore/AudioObjectHandle.h"

#include <xaudio2.h>

namespace DMK
{
	namespace XAudio2Backend
	{
		/**
		 * Audio Object for the XAudio2 backend.
		 * This object stores information that is ready to be played using this backend.
		 */
		class AudioObject {
		public:
			/**
			 * Default constructor.
			 */
			AudioObject() {}

			/**
			 * Default destructor.
			 */
			~AudioObject() {}

			/**
			 * Terminate the object.
			 */
			void Terminate();

			/**
			 * Get source pointer.
			 *
			 * @return IXAudio2SourceVoice pointer.
			 */
			IXAudio2SourceVoice* GetSourcePointer() const { return pSourceData; }

			/**
			 * Get the address of the source voice structure.
			 *
			 * @return The IXAudio2SourceVoice pointer address.
			 */
			IXAudio2SourceVoice** GetSourceDataPointer() const { return const_cast<IXAudio2SourceVoice**>(&pSourceData); }

			/**
			 * Begin audio playback.
			 *
			 * @param pInstance: The IXAudio2 pointer.
			 */
			void BeginPlay(IXAudio2* pInstance);

			/**
			 * Updates play and returns true if audio is played.
			 *
			 * @return Boolean value.
			 */
			bool UpdatePlay();

			/**
			 * Play the audio once.
			 *
			 * @param pInstance: The IXAudio2 pointer.
			 */
			void PlayOnce(IXAudio2* pInstance);

			/**
			 * Get the buffer address.
			 *
			 * @return XAUDIO2_BUFFER pointer.
			 */
			XAUDIO2_BUFFER* GetBufferAddress() const { return const_cast<XAUDIO2_BUFFER*>(&mBuffer); }

			/**
			 * Get the XWMA buffer address.
			 *
			 * @return XAUDIO2_BUFFER pointer.
			 */
			XAUDIO2_BUFFER_WMA* GetBufferXWMAAddress() const { return const_cast<XAUDIO2_BUFFER_WMA*>(&mXWMABuffer); }

			/**
			 * Get the address of the Wave Format structure.
			 *
			 * @return WAVEFORMATEX pointer.
			 */
			WAVEFORMATEX* GetWaveFormatAddress() const { return const_cast<WAVEFORMATEX*>(&mWaveFromat); }

		private:
			IXAudio2SourceVoice* pSourceData = nullptr;	// Audio source data.
			XAUDIO2_BUFFER mBuffer = { 0 }; // Audio data buffer.
			XAUDIO2_BUFFER_WMA mXWMABuffer = { 0 };	// XWMA audio data buffer.
			WAVEFORMATEX mWaveFromat = {};	// The wave format.
		};
	}
}