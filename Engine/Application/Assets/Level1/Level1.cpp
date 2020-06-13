// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "Level1.h"
#include "Player.h"

void Level1::onLoad()
{
	playerObject = (POINTER<DMKPlayerObject>)StaticAllocator<Player>::allocate();

	myMoon.setupCamera(playerObject->getCameraModule());

	myEntities.pushBack(&myMoon);
}
