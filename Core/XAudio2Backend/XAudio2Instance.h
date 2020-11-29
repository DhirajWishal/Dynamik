// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "AudioObject.h"
//#include "XAudio2Device.h"
#include "Core/Types/DataTypes.h"

#include <wrl\client.h>

namespace DMK
{
	namespace XAudio2Backend
	{
		/**
		 * XAudio2 Instance object.
		 * This object is responsible of creating XAudio2 devices.
		 */
		class XAudio2Instance {
		public:
			/**
			 * Default constructor.
			 */
			XAudio2Instance() {}

			/**
			 * Default destructor.
			 */
			~XAudio2Instance() {}

			/**
			 * Get the XAudio2 instance pointer.
			 *
			 * @return THe IXAudio2 pointer.
			 */
			IXAudio2* GetInstance() const { return pXAudio2.Get(); }

			/**
			 * Get the mastering voice structure pointer.
			 *
			 * @return The IXAudio2MasteringVoice pointer.
			 */
			IXAudio2MasteringVoice* GetMasteringVoice() const { return pMasteringVoice; }

		public:
			/**
			 * Initialize the backend.
			 *
			 * @param enableDebugging: State whether to enable debigging.
			 */
			void Initialize(bool enableDebugging);

			/**
			 * Terminate the backend.
			 */
			void Terminate();

			/**
			 * Set the global volume of the backend.
			 * This method sets the global volume to a certain value which will be set to all audio object which use
			 * this backend.
			 *
			 * @param volumeFactor: The volume factor to be set.
			 */
			void SetGlobalVolume(float volumeFactor);

		public:
			/**
			 * Create a new audio object.
			 *
			 * @param pAsset: The asset path.
			 * @return Audio Object Handle.
			 */
			AudioCore::AudioObjectHandle CreateAudioObject(const wchar* pAsset);

			/**
			 * Destroy an audio object using its handle.
			 *
			 * @param mHandle: The handle of the audio object.
			 */
			void DestroyAudioObject(AudioCore::AudioObjectHandle mHandle);

			/**
			 * Get audio cache using its handle.
			 * 
			 * @param mHandle: The audio object handle.
			 */
			AudioCore::AudioObjectCache GetAudioCache(const AudioCore::AudioObjectHandle& mHandle);

		public:
			/**
			 * Play audio once directly from the file.
			 * Note that this does not stream data directly to the device!
			 *
			 * @param pAsset: The asset path.
			 */
			void PlayAudioOnce(const wchar* pAsset);

			/**
			 * Play audio once.
			 *
			 * @param mHandle: The audio object handle.
			 */
			void PlayAudioOnce(const AudioCore::AudioObjectHandle& mHandle);

			/**
			 * Loop the audio multiple times.
			 *
			 * @param pAsset: The asset path.
			 * @param loopCount: The number of times the audio should be played.
			 */
			void PlayLoop(const wchar* pAsset, UI64 loopCount);

			/**
			 * Loop the audio multiple times.
			 *
			 * @param mHandle: The audio object handle.
			 * @param loopCount: The number of times the audio should be played.
			 */
			void PlayLoop(const AudioCore::AudioObjectHandle& mHandle, UI64 loopCount);

			/**
			 * Loop the audio multiple times.
			 *
			 * @param mCache: The audio object cache.
			 * @param loopCount: The number of times the audio should be played.
			 */
			void PlayLoop(const AudioCore::AudioObjectCache mCache, UI64 loopCount);

		public:
			/**
			 * Begin to play an audio object.
			 *
			 * @param mHandle: The handle of the audio object.
			 * @return Audio Object Cache.
			 */
			AudioCore::AudioObjectCache BeginAudioPlay(const AudioCore::AudioObjectHandle& mHandle);

			/**
			 * Update the audio object using its cache.
			 *
			 * @param mCache: The audio object cache.
			 * @return Boolean value stating if the audio playback is complete.
			 */
			bool Update(AudioCore::AudioObjectCache mCache);

			/**
			 * Update all audio objects.
			 * This updates all the loaded audio objects even if its playing or not. This also returns if an audio
			 * object is still not yet finished playing.
			 *
			 * @return Boolean value.
			 */
			bool Update();

			/**
			 * Set the volume of a playing audio object.
			 * The volume is set as a factor where the default volume is multiplied by it.
			 *
			 * @param mHandle: The audio object handle.
			 * @param volumeFactor: The volume factor.
			 */
			void SetVolume(const AudioCore::AudioObjectHandle& mHandle, float volumeFactor);

		private:
			/**
			 * Get an audio object pointer from the store.
			 *
			 * @param index: The index of the audio object.
			 * @return The pointer of the object.
			 */
			AudioObject* GetAudioObject(UI64 index) const { return const_cast<AudioObject*>(mAudioObjects.data() + index); }

		private:
			Microsoft::WRL::ComPtr<IXAudio2> pXAudio2;	// XAudio2 instance.
			IXAudio2MasteringVoice* pMasteringVoice = nullptr;	// XAudio2 mastering voice pointer.
			std::vector<AudioObject> mAudioObjects;	// All the created audio objects.
		};
	}
}