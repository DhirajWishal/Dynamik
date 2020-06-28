// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _APPLICATION_PLAYER_MOON_H
#define _APPLICATION_PLAYER_MOON_H

/*
 Author:	Dhiraj Wishal
 Date:		06/06/2020
*/
#include "GameLibrary/GameEntity.h"
using namespace Dynamik;

class PlayerMoon : public DMKGameEntity {
public:
	PlayerMoon() {}
	~PlayerMoon() {}

	virtual void initialize() override final;
};

#endif // !_APPLICATION_PLAYER_MOON_H