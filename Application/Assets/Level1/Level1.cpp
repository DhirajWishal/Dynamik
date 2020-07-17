// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "Level1.h"
#include "Player.h"
#include "DefaultWorld.h"
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

	/* Create Basic World */
	createUserGameWorld<DefaultWorld>();
	pCurrentGameWorld->setCamera(playerObject->getCameraModule());

	movementBias = 0.1f;
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

	if (DMKEventPool::KeyUp.isPressed() || DMKEventPool::KeyUp.isOnRepeat())
		playerObject->addUpVector(movementBias);

	if (DMKEventPool::KeyDown.isPressed() || DMKEventPool::KeyDown.isOnRepeat())
		playerObject->addDownVector(movementBias);

	playerObject->updateCamera();
}

void Level1::setupPlayerControls(DMKPlayerController* pController)
{
	pController->bindMovementControl(DMKMovementControlInstruction::DMK_MOVEMENT_CONTROL_INSTRUCTION_MOVE_FORWARD, TEXT("KeyW"), this, (DMKEventType)(DMK_EVENT_TYPE_REPEAT | DMK_EVENT_TYPE_PRESS));
	pController->bindMovementControl(DMKMovementControlInstruction::DMK_MOVEMENT_CONTROL_INSTRUCTION_MOVE_BACKWARD, TEXT("KeyS"), this, (DMKEventType)(DMK_EVENT_TYPE_REPEAT | DMK_EVENT_TYPE_PRESS));
	pController->bindMovementControl(DMKMovementControlInstruction::DMK_MOVEMENT_CONTROL_INSTRUCTION_MOVE_LEFT, TEXT("KeyA"), this, (DMKEventType)(DMK_EVENT_TYPE_REPEAT | DMK_EVENT_TYPE_PRESS));
	pController->bindMovementControl(DMKMovementControlInstruction::DMK_MOVEMENT_CONTROL_INSTRUCTION_MOVE_RIGHT, TEXT("KeyD"), this, (DMKEventType)(DMK_EVENT_TYPE_REPEAT | DMK_EVENT_TYPE_PRESS));
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
