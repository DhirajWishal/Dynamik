// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "Player.h"

void Player::onInitializePlayer()
{
	cameraModule = StaticAllocator<DMKCameraModule>::allocate();

	this->setPosition({ 0.0f, 0.0f, 0.0f });
	this->setCameraPosition({ 0.0f, 0.0f, 0.0f });
	this->setCameraAndWorldUp(VEC3(0.0f, -1.0f, 0.0f), VEC3(0.0f, -1.0f, 0.0f));
	this->getCameraModule()->setExposure(1.0f);
	this->getCameraModule()->setGamma(1.0f);
}

void Player::setupPlayerControls(DMKPlayerController* pPlayerController)
{
	pPlayerController->bindMovementControl(DMKMovementControlInstruction::DMK_MOVEMENT_CONTROL_INSTRUCTION_MOVE_FORWARD, TEXT("KeyW"), this, (DMKEventType)(DMK_EVENT_TYPE_REPEAT | DMK_EVENT_TYPE_PRESS));
	pPlayerController->bindMovementControl(DMKMovementControlInstruction::DMK_MOVEMENT_CONTROL_INSTRUCTION_MOVE_BACKWARD, TEXT("KeyS"), this, (DMKEventType)(DMK_EVENT_TYPE_REPEAT | DMK_EVENT_TYPE_PRESS));
	pPlayerController->bindMovementControl(DMKMovementControlInstruction::DMK_MOVEMENT_CONTROL_INSTRUCTION_MOVE_LEFT, TEXT("KeyA"), this, (DMKEventType)(DMK_EVENT_TYPE_REPEAT | DMK_EVENT_TYPE_PRESS));
	pPlayerController->bindMovementControl(DMKMovementControlInstruction::DMK_MOVEMENT_CONTROL_INSTRUCTION_MOVE_RIGHT, TEXT("KeyD"), this, (DMKEventType)(DMK_EVENT_TYPE_REPEAT | DMK_EVENT_TYPE_PRESS));
}

void Player::onMoveForward()
{
	addForwardVector(0.001f);
}

void Player::onMoveBackward()
{
	addBackwardVector(0.001f);
}

void Player::onMoveLeft()
{
	addRightVector(0.001f);
}

void Player::onMoveRight()
{
	addLeftVector(0.001f);
}
