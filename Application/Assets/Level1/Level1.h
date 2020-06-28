// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_LEVEL_1_H
#define _DYNAMIK_LEVEL_1_H

/*
 Author:	Dhiraj Wishal
 Date:		04/06/2020
*/
#include "GameLibrary/LevelComponent.h"
#include "Entities/PlayerMoon.h"
using namespace Dynamik;

class Level1 : public DMKLevelComponent {
public:
	Level1() {}
	~Level1() {}

	void onLoad() override;

private:
	PlayerMoon myMoon;
};

#endif // !_DYNAMIK_LEVEL_1_H
