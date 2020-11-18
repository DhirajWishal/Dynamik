// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "BallBouncerApplication.h"

DMK::Engine::ServiceInitializationFlags BallBouncerApplciation::GetServiceInitializationFlags() const
{
	return DMK::Engine::ServiceInitializationFlags::SERVICE_INITIALIZEATION_FLAG_ASSET_STORE;
}

DMK::Engine::SystemInitializationFlags BallBouncerApplciation::GetSystemInitializationFlags() const
{
	return DMK::Engine::SystemInitializationFlags::SYSTEM_INITIALIZATION_FLAG_GRAPHICS;
}

void BallBouncerApplciation::InitializeGame()
{
}

// Setup the entry point
SETUP_GAME_APPLICATION(BallBouncerApplciation)