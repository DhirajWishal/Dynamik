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
	playerObject->setPosition({ 0.0f, 0.0f, 0.0f });
	playerObject->setCameraPosition({0.0f, 0.0f, 0.0f});
	playerObject->setAspectRatio(1280.0f / 720.0f);

	myMoon.setupCamera(playerObject->getCameraModule());

	//entities.pushBack(&myMoon);

	auto entity = createHollowEntity();
	
	entity->addComponent<DMKMeshComponent>(DMKMeshFactory::createDefault(DMK_TEXT("E:/Projects/Dynamik Engine/Game Repository/assets/assets/moon/Moon 2K.fbx")));
	entity->setupCamera(playerObject->getCameraModule());
	
	entity->getComponent<DMKMeshComponent>(0)->addTexture(DMK_TEXT("E:/Projects/Dynamik Engine/Game Repository/assets/assets/moon/Diffuse_2K.png"), DMKTextureType::DMK_TEXTURE_TYPE_2D);
	
	entity->getComponent<DMKMeshComponent>(0)->translate(MAT4(1.0f), { 0.0f, 0.0f, -5.0f });

	/* Initialize Sky Box */
	//environmentMap = StaticAllocator<DMKEnvironmentMap>::allocate();

	ARRAY<STRING> texturePaths;
	texturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/right.jpg");
	texturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/left.jpg");
	texturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/top.jpg");
	texturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/bottom.jpg");
	texturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/front.jpg");
	texturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/back.jpg");

	//environmentMap->setSkyBox(DMKMeshFactory::createSkyBox(texturePaths));
}

void Level1::setupEventMap(DMKEventMap* pEventMap)
{
	pEventMap->addInstruction(DMKEvent::DMK_EVENT_KEY_W, DMKControlInstruction::DMK_CONTROL_INSTRUCTION_MOVE_FORWARD);
	pEventMap->addInstruction(DMKEvent::DMK_EVENT_KEY_S, DMKControlInstruction::DMK_CONTROL_INSTRUCTION_MOVE_BACKWARD);
	pEventMap->addInstruction(DMKEvent::DMK_EVENT_KEY_A, DMKControlInstruction::DMK_CONTROL_INSTRUCTION_MOVE_LEFT);
	pEventMap->addInstruction(DMKEvent::DMK_EVENT_KEY_D, DMKControlInstruction::DMK_CONTROL_INSTRUCTION_MOVE_RIGHT);
}

void Level1::onUpdate(const DMKEventBuffer& eventBuffer)
{
	//playerObject->addBackwardVector(0.0001f);
	//playerObject->addUpVector(0.0001f);
	playerObject->updateCamera();
}
