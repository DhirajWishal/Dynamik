// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "Level1.h"
#include "Player.h"

void Level1::onLoad()
{
	playerObject = createUserPlayer<Player>();

	myMoon.setupCamera(playerObject->getCameraModule());

	//entities.pushBack(&myMoon);

	auto entity = createHollowEntity();
	
	entity->addComponent<DMKMeshComponent>(DMKMeshFactory::createDefault(DMK_TEXT("E:/Projects/Dynamik Engine/Game Repository/assets/assets/moon/Moon 2K.fbx")));
	entity->setupCamera(playerObject->getCameraModule());

	entity->getComponent<DMKMeshComponent>(0)->addTexture(DMK_TEXT("E:/Projects/Dynamik Engine/Game Repository/assets/assets/moon/Diffuse_2K.png"), DMKTextureType::DMK_TEXTURE_TYPE_2D);
}
