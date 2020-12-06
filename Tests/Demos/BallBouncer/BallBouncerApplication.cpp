// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "BallBouncerApplication.h"

DMK::Engine::ServiceInitializationFlags BallBouncerApplciation::GetServiceInitializationFlags() const
{
	return DMK::Engine::ServiceInitializationFlags::ASSET_STORE;
}

DMK::Engine::SystemInitializationFlags BallBouncerApplciation::GetSystemInitializationFlags() const
{
	return DMK::Engine::SystemInitializationFlags::GRAPHICS | DMK::Engine::SystemInitializationFlags::AUDIO;
}

void BallBouncerApplciation::InitializeGame()
{
}

// Setup the entry point
SETUP_GAME_APPLICATION(BallBouncerApplciation)