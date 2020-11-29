// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "Audio/Engine.h"
#include "Core/ErrorHandler/Logger.h"

#include "XAudio2Backend/XAudio2BackendFunction.h"

#include "AudioCore/Commands/CoreCommands.h"

namespace DMK
{
	namespace Audio
	{
		void Engine::Initialize(AudioBackendType mBackendType)
		{
			this->mBackendType = mBackendType;

			switch (mBackendType)
			{
			case DMK::Audio::AudioBackendType::X_AUDIO_2:
				mBackendThread.swap(std::thread(XAudio2Backend::XAudio2BackendFunction, &mCommandQueue));
				break;
			default:
				Logger::LogError(TEXT("Invalid Audio Backend Type!"));
				break;
			}

#ifdef DMK_DEBUG
			GetCommandQueue()->PushCommand<AudioCore::Commands::InitializeBackend>(AudioCore::Commands::InitializeBackend(true));

#else 
			GetCommandQueue()->PushCommand<AudioCore::Commands::InitializeBackend>(AudioCore::Commands::InitializeBackend(false));

#endif	// DMK_DEBUG
		}

		void Engine::Terminate()
		{
			GetCommandQueue()->PushCommand<AudioCore::Commands::TerminateBackend>();
			mBackendThread.join();
		}
	}
}