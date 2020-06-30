// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "Level1.h"
#include "Player.h"
#include "Core/Math/MathFunctions.h"
using namespace Dynamik;

void Level1::onLoad()
{
	playerObject = createUserPlayer<Player>();

	playerObject->cameraModule = StaticAllocator<DMKCameraModule>::allocate();
	playerObject->setCameraPosition({0.0f, 1.0f, 0.0f});

	myMoon.setupCamera(playerObject->getCameraModule());

	//entities.pushBack(&myMoon);

	auto entity = createHollowEntity();
	
	entity->addComponent<DMKMeshComponent>(DMKMeshFactory::createDefault(DMK_TEXT("E:/Projects/Dynamik Engine/Game Repository/assets/assets/chalet/chalet.obj")));
	entity->setupCamera(playerObject->getCameraModule());

	entity->getComponent<DMKMeshComponent>(0)->addTexture(DMK_TEXT("E:/Projects/Dynamik Engine/Game Repository/assets/assets/chalet/chalet.jpg"), DMKTextureType::DMK_TEXTURE_TYPE_2D);

	entity->getComponent<DMKMeshComponent>(0)->translate(MAT4(1.0f), { 0.0f, -3.0f, -3.0f });
	entity->getComponent<DMKMeshComponent>(0)->rotate({ 0.0f, 0.0f, 1.0f }, DMKMathFunctions::radians(90.0f));
}
