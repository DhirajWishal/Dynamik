// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "PlayerController.h"

#include "../GameModule.h"
#include "../Entities/PlayerEntity.h"

void DMKPlayerController::setEventPool(DMKEventPool* pEventPool)
{
	this->pEventPool = pEventPool;
}

void DMKPlayerController::executeMovements()
{
	for (auto control : movementControls)
		if (pEventPool->getComponent(control.first)->type & control.second.invokeCondition)
			control.second.function();
}

void DMKPlayerController::executeActions()
{
	for (auto control : actionControls)
		if (pEventPool->getComponent(control.first)->type & control.second.invokeCondition)
			control.second.function();
}

void DMKPlayerController::executeCameraControls()
{
	for (auto control : cameraControls)
		if (pEventPool->getComponent(control.first)->type & control.second.invokeCondition)
			control.second.function();
}

void DMKPlayerController::executeAll()
{
	executeMovements();
	executeActions();
	executeCameraControls();
}

void DMKPlayerController::reset()
{
	movementControls.clear();
	actionControls.clear();
	cameraControls.clear();
}

void DMKPlayerController::bindMovementControl(DMKMovementControlInstruction instruction, const STRING& sEvent, DMKPlayerEntity* pPlayer, DMKEventType eventType)
{
	switch (instruction)
	{
	case DMKMovementControlInstruction::DMK_MOVEMENT_CONTROL_INSTRUCTION_MOVE_FORWARD:
	{
		FunctionInvokeLevel level;
		level.function = [pPlayer]() { pPlayer->onMoveForward(); };
		level.invokeCondition = eventType;

		movementControls[sEvent] = level;
	}
	break;

	case DMKMovementControlInstruction::DMK_MOVEMENT_CONTROL_INSTRUCTION_MOVE_BACKWARD:
	{
		FunctionInvokeLevel level;
		level.function = [pPlayer]() { pPlayer->onMoveBackward(); };
		level.invokeCondition = eventType;

		movementControls[sEvent] = level;
	}
	break;

	case DMKMovementControlInstruction::DMK_MOVEMENT_CONTROL_INSTRUCTION_MOVE_LEFT:
	{
		FunctionInvokeLevel level;
		level.function = [pPlayer]() { pPlayer->onMoveLeft(); };
		level.invokeCondition = eventType;

		movementControls[sEvent] = level;
	}
	break;

	case DMKMovementControlInstruction::DMK_MOVEMENT_CONTROL_INSTRUCTION_MOVE_RIGHT:
	{
		FunctionInvokeLevel level;
		level.function = [pPlayer]() { pPlayer->onMoveRight(); };
		level.invokeCondition = eventType;

		movementControls[sEvent] = level;
	}
	break;

	case DMKMovementControlInstruction::DMK_MOVEMENT_CONTROL_INSTRUCTION_MOVE_CROUCH:
		break;
	case DMKMovementControlInstruction::DMK_MOVEMENT_CONTROL_INSTRUCTION_MOVE_JUMP:
		break;
	case DMKMovementControlInstruction::DMK_MOVEMENT_CONTROL_INSTRUCTION_MOVE_RUN:
		break;
	case DMKMovementControlInstruction::DMK_MOVEMENT_CONTROL_INSTRUCTION_MOVE_PEEK_LEFT:
		break;
	case DMKMovementControlInstruction::DMK_MOVEMENT_CONTROL_INSTRUCTION_MOVE_PEEK_RIGHT:
		break;
	case DMKMovementControlInstruction::DMK_MOVEMENT_CONTROL_INSTRUCTION_MOVE_SLIDE:
		break;
	default:
		break;
	}
}

void DMKPlayerController::bindActionControl(DMKActionControlInstruction instruction, const STRING& sEvent, DMKPlayerEntity* pPlayer, DMKEventType eventType)
{
	switch (instruction)
	{
	case DMKActionControlInstruction::DMK_ACTION_CONTROL_INSTRUCTION_AIM:
		break;
	case DMKActionControlInstruction::DMK_ACTION_CONTROL_INSTRUCTION_TRIGGER:
		break;
	case DMKActionControlInstruction::DMK_ACTION_CONTROL_INSTRUCTION_RELOAD:
		break;
	case DMKActionControlInstruction::DMK_ACTION_CONTROL_INSTRUCTION_LOOK_AT:
		break;
	case DMKActionControlInstruction::DMK_ACTION_CONTROL_INSTRUCTION_VIEW:
		break;
	default:
		break;
	}
}

void DMKPlayerController::bindCameraControl(DMKCameraControlInstruction instruction, const STRING& sEvent, DMKPlayerEntity* pPlayer, DMKEventType eventType)
{
	switch (instruction)
	{
	case DMKCameraControlInstruction::DMK_CAMERA_CONTROL_INSTRUCTION_MOVE_FORWARD:
		break;
	case DMKCameraControlInstruction::DMK_CAMERA_CONTROL_INSTRUCTION_MOVE_BACKWARD:
		break;
	case DMKCameraControlInstruction::DMK_CAMERA_CONTROL_INSTRUCTION_MOVE_LEFT:
		break;
	case DMKCameraControlInstruction::DMK_CAMERA_CONTROL_INSTRUCTION_MOVE_RIGHT:
		break;
	case DMKCameraControlInstruction::DMK_CAMERA_CONTROL_INSTRUCTION_MOVE_UP:
		break;
	case DMKCameraControlInstruction::DMK_CAMERA_CONTROL_INSTRUCTION_MOVE_DOWN:
		break;
	case DMKCameraControlInstruction::DMK_CAMERA_CONTROL_INSTRUCTION_ROTATE_X:
		break;
	case DMKCameraControlInstruction::DMK_CAMERA_CONTROL_INSTRUCTION_ROTATE_Y:
		break;
	case DMKCameraControlInstruction::DMK_CAMERA_CONTROL_INSTRUCTION_ROTATE_Z:
		break;
	default:
		break;
	}
}