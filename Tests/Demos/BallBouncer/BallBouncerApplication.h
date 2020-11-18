// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Engine/GameApplication.h"

class BallBouncerApplciation : public DMK::Engine::GameApplication {
public:
	BallBouncerApplciation() {}
	~BallBouncerApplciation() {}

	virtual DMK::Engine::ServiceInitializationFlags GetServiceInitializationFlags() const;
	virtual DMK::Engine::SystemInitializationFlags GetSystemInitializationFlags() const;

	virtual void InitializeGame();
};