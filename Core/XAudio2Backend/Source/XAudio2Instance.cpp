// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "XAudio2Backend/XAudio2Instance.h"
#pragma comment(lib,"xaudio2.lib")

#include "Core/ErrorHandler/Logger.h"
#include "XAudio2Backend/Loaders/WAVLoader.h"
#include "XAudio2Backend/Utilities/Converters.h"
#include "XAudio2Backend/Utilities/ObjectCreators.h"

namespace DMK
{
	namespace XAudio2Backend
	{
		void XAudio2Instance::Initialize(bool enableDebugging)
		{
			// Initialize the COINIT.
			HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

			// Create the XAudio2 instance.
			if (FAILED(XAudio2Create(pXAudio2.GetAddressOf(), 0)))
			{
				Logger::LogError(TEXT("Failed to create the XAudio2 instance!"));
				CoUninitialize();
				return;
			}

			// Check and enable debugging.
			if (enableDebugging)
			{
				// Initailize the debugger.
				XAUDIO2_DEBUG_CONFIGURATION debug = { 0 };
				debug.TraceMask = XAUDIO2_LOG_ERRORS | XAUDIO2_LOG_WARNINGS;
				debug.BreakMask = XAUDIO2_LOG_ERRORS;
				pXAudio2->SetDebugConfiguration(&debug, 0);
			}

			// Create the XAudio2 mastering voice.
			if (FAILED(pXAudio2->CreateMasteringVoice(&pMasteringVoice)))
			{
				Logger::LogError(TEXT("Failed to create the XAudio2 mastering voice!"));
				CoUninitialize();
				return;
			}
		}

		void XAudio2Instance::Terminate()
		{
			mAudioObjects.clear();
			pMasteringVoice->DestroyVoice();
			pXAudio2.Reset();
			CoUninitialize();
		}

		void XAudio2Instance::SetGlobalVolume(float volumeFactor)
		{
			GetMasteringVoice()->SetVolume(volumeFactor);
		}

		AudioCore::AudioObjectHandle XAudio2Instance::CreateAudioObject(const wchar* pAsset)
		{
			// Create the handle instance.
			AudioCore::AudioObjectHandle mHandle = {};
			//mHandle.pFileName = pAsset;

			// Create the object from using the WAV format.
			if (WString(pAsset).find(TEXT(".wav")) != WString::npos)
				mAudioObjects.insert(mAudioObjects.end(), std::move(CreateFromWAV(pAsset, &mHandle)));

			// Get the handle and return it.
			mHandle.mHandle = mAudioObjects.size() - 1;
			return mHandle;
		}

		void XAudio2Instance::DestroyAudioObject(AudioCore::AudioObjectHandle mHandle)
		{
			mAudioObjects.at(mHandle.GetHandle()).Terminate();
		}

		AudioCore::AudioObjectCache XAudio2Instance::GetAudioCache(const AudioCore::AudioObjectHandle& mHandle)
		{
			return reinterpret_cast<AudioCore::AudioObjectCache>(GetAudioObject(mHandle.GetHandle()));
		}

		void XAudio2Instance::PlayAudioOnce(const wchar* pAsset)
		{
			// Create the object instance.
			AudioObject mObject = {};

			// Play the WAV file once.
			if (WString(pAsset).find(TEXT(".wav")) != WString::npos)
				mObject = std::move(CreateFromWAV(pAsset));

			// Play the audio.
			mObject.PlayOnce(GetInstance());

			// Terminate the object.
			mObject.Terminate();
		}

		void XAudio2Instance::PlayAudioOnce(const AudioCore::AudioObjectHandle& mHandle)
		{
			GetAudioObject(mHandle.GetHandle())->PlayOnce(GetInstance());
		}

		void XAudio2Instance::PlayLoop(const wchar* pAsset, UI64 loopCount)
		{
			// Create the object instance.
			AudioObject mObject = {};

			// Play the WAV file once.
			if (WString(pAsset).find(TEXT(".wav")) != WString::npos)
				mObject = std::move(CreateFromWAV(pAsset));

			// Play the audio.
			while (loopCount--)
				mObject.PlayOnce(GetInstance());

			// Terminate the object.
			mObject.Terminate();
		}

		void XAudio2Instance::PlayLoop(const AudioCore::AudioObjectHandle& mHandle, UI64 loopCount)
		{
			// Get the required audio object.
			auto pAudioObject = GetAudioObject(mHandle.GetHandle());

			// Play the audio file.
			while (loopCount--)
				pAudioObject->PlayOnce(GetInstance());
		}

		void XAudio2Instance::PlayLoop(const AudioCore::AudioObjectCache mCache, UI64 loopCount)
		{
			// Cast the required audio object.
			auto pAudioObject = reinterpret_cast<AudioObject*>(mCache);

			// Play the audio file.
			while (loopCount--)
				pAudioObject->PlayOnce(GetInstance());
		}

		AudioCore::AudioObjectCache XAudio2Instance::BeginAudioPlay(const AudioCore::AudioObjectHandle& mHandle)
		{
			AudioCore::AudioObjectCache mCache = GetAudioObject(mHandle.GetHandle());
			reinterpret_cast<AudioObject*>(mCache)->BeginPlay(GetInstance());

			return mCache;
		}

		bool XAudio2Instance::Update(AudioCore::AudioObjectCache mCache)
		{
			return reinterpret_cast<AudioObject*>(mCache)->UpdatePlay();
		}

		bool XAudio2Instance::Update()
		{
			bool isPlaying = false;
			for (auto itr = mAudioObjects.begin(); itr != mAudioObjects.end(); itr++)
				isPlaying = itr->UpdatePlay();

			return isPlaying;
		}

		void XAudio2Instance::SetVolume(const AudioCore::AudioObjectHandle& mHandle, float volumeFactor)
		{
			GetAudioObject(mHandle.GetHandle())->GetSourcePointer()->SetVolume(volumeFactor);
		}
	}
}