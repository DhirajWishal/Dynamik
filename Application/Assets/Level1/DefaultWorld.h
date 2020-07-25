// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _APPLICATION_DEFAULT_WORLD_H
#define _APPLICATION_DEFAULT_WORLD_H

#include "GameLibrary/GameWorld.h"
using namespace Dynamik;

class DefaultWorld : public DMKGameWorld {
public:
	DefaultWorld() {}

	virtual void initialize() override final;
};

#endif // !_APPLICATION_DEFAULT_WORLD_H
