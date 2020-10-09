// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "AnimationController.h"

void DMKAnimationController::initialize()
{
}

void DMKAnimationController::update()
{
}

void DMKAnimationController::bindInstruction(STRING sEvent, DMKAnimationControlInstruction instruction, DMKGameModule* pGameModule, DMKEventType eventType)
{
	switch (instruction)
	{
	case DMKAnimationControlInstruction::DMK_ANIMATION_CONTROL_INSTRUCTION_PLAY:
		break;
	case DMKAnimationControlInstruction::DMK_ANIMATION_CONTROL_INSTRUCTION_PAUSE:
		break;
	case DMKAnimationControlInstruction::DMK_ANIMATION_CONTROL_INSTRUCTION_REPEAT:
		break;
	case DMKAnimationControlInstruction::DMK_ANIMATION_CONTROL_INSTRUCTION_RESTART:
		break;
	default:
		break;
	}

	eventList.pushBack(sEvent);
}
