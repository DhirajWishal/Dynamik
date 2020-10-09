// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GAME_EVENTS_H
#define _DYNAMIK_GAME_EVENTS_H

#include "Core/Macros/Global.h"
#include "Core/Types/DataTypes.h"

/*
 Game Event: Load next level
*/
struct DMK_API GELoadNextLevel {
	UI32 nextLevel = 0;
	B1 isActive = false;
};

/*
 Dynamik Game Events
 This object propagates all the game events which are required to be propagated to the engine.
*/
class DMK_API DMKGameEvents {
public:
	DMKGameEvents() = default;
	~DMKGameEvents() = default;

	static GELoadNextLevel loadLevel;
};

#endif // !_DYNAMIK_GAME_EVENTS_H
