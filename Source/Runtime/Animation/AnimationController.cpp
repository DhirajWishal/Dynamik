// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "AnimationController.h"

namespace Dynamik
{
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
		case Dynamik::DMKAnimationControlInstruction::DMK_ANIMATION_CONTROL_INSTRUCTION_PLAY:
			break;
		case Dynamik::DMKAnimationControlInstruction::DMK_ANIMATION_CONTROL_INSTRUCTION_PAUSE:
			break;
		case Dynamik::DMKAnimationControlInstruction::DMK_ANIMATION_CONTROL_INSTRUCTION_REPEAT:
			break;
		case Dynamik::DMKAnimationControlInstruction::DMK_ANIMATION_CONTROL_INSTRUCTION_RESTART:
			break;
		default:
			break;
		}

		eventList.pushBack(sEvent);
	}
}
