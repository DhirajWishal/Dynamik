// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _APPLICATION_DEFAULT_WORLD_H
#define _APPLICATION_DEFAULT_WORLD_H

#include "GameLibrary/GameWorld.h"

class DefaultWorld final : public DMKGameWorld {
public:
	DefaultWorld() {}
	~DefaultWorld() {}

	virtual void initialize() override final;
	virtual void onUpdate(const F32 timeStep) override final;
	virtual void onMainWindowResize(DMKExtent2D newSize) override final;

	B1 areEntitiesInitialized = false;
};

#endif // !_APPLICATION_DEFAULT_WORLD_H
