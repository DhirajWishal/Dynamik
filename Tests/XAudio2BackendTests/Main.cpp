// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "XAudio2Backend/XAudio2Instance.h"

int main()
{
	DMK::XAudio2Backend::XAudio2Instance mInstance;
	mInstance.Initialize(true);

	//mBackend.PlayLoop(STRING("..\\..\\Assets\\Audio\\Gun+357+Magnum.wav"), 5);

	auto mHandle = mInstance.CreateAudioObject(TEXT("..\\..\\Assets\\Audio\\file_example_WAV_10MG.wav"));

	auto mCache = mInstance.BeginAudioPlay(mHandle);
	mInstance.SetVolume(mHandle, 5.0f / 10.0f);
	while (mInstance.Update(mCache));

	mInstance.Terminate();
}