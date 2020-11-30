// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "XAudio2Backend/XAudio2BackendFunction.h"
#include "XAudio2Backend/XAudio2Instance.h"

#include "AudioCore/Commands/CoreCommands.h"
#include "AudioCore/Commands/AudioObjectCommands.h"
#include "AudioCore/Commands/PlaybackCommands.h"

namespace DMK
{
	namespace XAudio2Backend
	{
		void XAudio2BackendFunction(Thread::CommandQueue<THREAD_MAX_COMMAND_COUNT>* pCommandQueue)
		{
			// Create the instance object.
			XAudio2Instance mInstance = {};

			// Main loop state.
			bool bShouldRun = true;

			// Main execution loop.
			do {
				// Check if a command is present.
				if (pCommandQueue->Count())
				{
					// Get the first command.
					auto pCommand = pCommandQueue->GetAndPop();
					SET_COMMAND_PENDING(pCommand);

					// Check if the command is to initialize the backend.
					if (TYPE_NAME(AudioCore::Commands::InitializeBackend) == pCommand->GetCommandName())
					{
						SET_COMMAND_EXECUTING(pCommand);

						// Initialize the instance.
						mInstance.Initialize(pCommand->GetData<AudioCore::Commands::InitializeBackend>().enableDebugging);
						SET_COMMAND_SUCCESS(pCommand);

						DELETE_COMMAND(pCommand, AudioCore::Commands::InitializeBackend);
					}

					// Check if the command is to terminate the backend.
					else if (TYPE_NAME(AudioCore::Commands::TerminateBackend) == pCommand->GetCommandName())
					{
						SET_COMMAND_EXECUTING(pCommand);

						// Terminate the instance.
						mInstance.Terminate();
						SET_COMMAND_SUCCESS(pCommand);

						DELETE_COMMAND(pCommand, AudioCore::Commands::TerminateBackend);

						bShouldRun = false;
					}

					// Check if the command is to load audio data from a file.
					else if (TYPE_NAME(AudioCore::Commands::LoadAudioFromFile) == pCommand->GetCommandName())
					{
						SET_COMMAND_EXECUTING(pCommand);

						// Get the actual command.
						auto& mCommand = pCommand->GetData<AudioCore::Commands::LoadAudioFromFile>();

						// Check and execute if an asset path is set.
						if (mCommand.pAsset)
						{
							// Check and asign data to the pHandle after loading the data.
							if (mCommand.pHandle)
								*mCommand.pHandle = mInstance.CreateAudioObject(mCommand.pAsset);
							else
								mInstance.CreateAudioObject(mCommand.pAsset);

							SET_COMMAND_SUCCESS(pCommand);

							DELETE_COMMAND(pCommand, AudioCore::Commands::LoadAudioFromFile);
						}
					}

					// Check if the command is to get audio object cache.
					else if (TYPE_NAME(AudioCore::Commands::GetAudioObjectCache) == pCommand->GetCommandName())
					{
						SET_COMMAND_EXECUTING(pCommand);

						// Get the actual command.
						auto& mCommand = pCommand->GetData<AudioCore::Commands::GetAudioObjectCache>();

						// Check and complete if the cache pointer is valid.
						if (mCommand.pCache)
						{
							*mCommand.pCache = mInstance.GetAudioCache(mCommand.mHandle);
							SET_COMMAND_SUCCESS(pCommand);

							DELETE_COMMAND(pCommand, AudioCore::Commands::GetAudioObjectCache);
						}
					}

					// Check if the command is for direct playback.
					else if (TYPE_NAME(AudioCore::Commands::DirectPlayback) == pCommand->GetCommandName())
					{
						SET_COMMAND_EXECUTING(pCommand);

						// Get the actual command.
						auto& mCommand = pCommand->GetData<AudioCore::Commands::DirectPlayback>();

						// Check and complete if the cache pointer is valid.
						if (mCommand.pAsset)
						{
							// Play the audio track.
							mInstance.PlayLoop(mCommand.pAsset, mCommand.loopCount);
							SET_COMMAND_SUCCESS(pCommand);

							DELETE_COMMAND(pCommand, AudioCore::Commands::GetAudioObjectCache);
						}
					}

					// Check if the command is for buffered playback.
					else if (TYPE_NAME(AudioCore::Commands::BufferedPlayback) == pCommand->GetCommandName())
					{
						SET_COMMAND_EXECUTING(pCommand);

						// Get the actual command.
						auto& mCommand = pCommand->GetData<AudioCore::Commands::BufferedPlayback>();

						// Play if the cache is specified. Play using the handle if not.
						if (mCommand.mCache)
							mInstance.PlayLoop(mCommand.mCache, mCommand.loopCount);
						else
							mInstance.PlayLoop(mCommand.mHandle, mCommand.loopCount);

						SET_COMMAND_SUCCESS(pCommand);

						DELETE_COMMAND(pCommand, AudioCore::Commands::BufferedPlayback);
					}

					// If execution failed.
					if (pCommand)
					{
						SET_COMMAND_FAILED(pCommand);

						// Delete the command.
						delete pCommand;
					}
				}
			} while (bShouldRun);
		}
	}
}