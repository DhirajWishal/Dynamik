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
	playerObject->setCameraPosition({ 0.0f, 0.0f, 0.0f });
	playerObject->setAspectRatio(1280.0f / 720.0f);
	playerObject->setCameraAndWorldUp(VEC3(0.0f, -1.0f, 0.0f), VEC3(0.0f, -1.0f, 0.0f));

	auto entity = createHollowEntity();

	entity->addComponent<DMKMeshComponent>(DMKMeshFactory::createDefault(DMK_TEXT("E:/Projects/Dynamik Engine/Game Repository/assets/assets/moon/Moon 2K.fbx")));
	entity->setupCamera(playerObject->getCameraModule());

	entity->getComponent<DMKMeshComponent>(0)->addTexture(DMK_TEXT("E:/Projects/Dynamik Engine/Game Repository/assets/assets/moon/Diffuse_2K.png"), DMKTextureType::DMK_TEXTURE_TYPE_2D);

	entity->getComponent<DMKMeshComponent>(0)->translate(MAT4(1.0f), { 0.0f, 0.0f, -5.0f });

	/* Initialize Sky Box */
	ARRAY<STRING> texturePaths;
	texturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/right.jpg");
	texturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/left.jpg");
	texturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/top.jpg");
	texturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/bottom.jpg");
	texturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/front.jpg");
	texturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/back.jpg");

	environmentMap = StaticAllocator<DMKEnvironmentMap>::allocate();
	environmentMap->setSkyBox(DMKMeshFactory::createSkyBox(texturePaths));
}

void Level1::onUpdate(const DMKEventPool* pEventPool)
{
	static B1 refresh = false;

	if (DMKEventPool::MouseButtonLeft.isPressed())
	{
		playerObject->processMouseInput(DMKEventPool::getMousePosition(), 0.1f, refresh, true);
		refresh = false;
	}
	if (DMKEventPool::MouseButtonLeft.isReleased())
		refresh = true;

	playerObject->updateCamera();
}

void Level1::setupPlayerControls(DMKPlayerController* pController)
{
	pController->bindMovementControl(DMKMovementControlInstruction::DMK_MOVEMENT_CONTROL_INSTRUCTION_MOVE_FORWARD, DMK_TEXT("KeyW"), this, (DMKEventType)(DMK_EVENT_TYPE_REPEAT | DMK_EVENT_TYPE_PRESS));
	pController->bindMovementControl(DMKMovementControlInstruction::DMK_MOVEMENT_CONTROL_INSTRUCTION_MOVE_BACKWARD, DMK_TEXT("KeyS"), this, (DMKEventType)(DMK_EVENT_TYPE_REPEAT | DMK_EVENT_TYPE_PRESS));
	pController->bindMovementControl(DMKMovementControlInstruction::DMK_MOVEMENT_CONTROL_INSTRUCTION_MOVE_LEFT, DMK_TEXT("KeyA"), this, (DMKEventType)(DMK_EVENT_TYPE_REPEAT | DMK_EVENT_TYPE_PRESS));
	pController->bindMovementControl(DMKMovementControlInstruction::DMK_MOVEMENT_CONTROL_INSTRUCTION_MOVE_RIGHT, DMK_TEXT("KeyD"), this, (DMKEventType)(DMK_EVENT_TYPE_REPEAT | DMK_EVENT_TYPE_PRESS));
}

void Level1::onPlayerMoveForward()
{
	playerObject->addForwardVector(movementBias);
}

void Level1::onPlayerMoveBackward()
{
	playerObject->addBackwardVector(movementBias);
}

void Level1::onPlayerMoveLeft()
{
	playerObject->addRightVector(movementBias);
}

void Level1::onPlayerMoveRight()
{
	playerObject->addLeftVector(movementBias);
}
