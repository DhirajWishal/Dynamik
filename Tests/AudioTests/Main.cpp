// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "Audio/Engine.h"
#include "AudioCore/Commands/PlaybackCommands.h"

int main()
{
	DMK::Audio::Engine mAudioEngine = {};
	mAudioEngine.Initialize(DMK::Audio::AudioBackendType::X_AUDIO_2);

	mAudioEngine.GetCommandQueue()->PushCommand<DMK::AudioCore::Commands::DirectPlayback>(DMK::AudioCore::Commands::DirectPlayback(TEXT("..\\..\\Assets\\Audio\\file_example_WAV_10MG.wav")));

	mAudioEngine.Terminate();
}