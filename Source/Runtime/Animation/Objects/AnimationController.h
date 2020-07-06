// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_ANIMATION_CONTROLLER_H
#define _DYNAMIK_ANIMATION_CONTROLLER_H

#include "GameLibrary/LevelComponent.h"

#include <functional>
#include <unordered_map>

namespace Dynamik
{
	/* Dynamik Animation Control Instruction */
	enum class DMK_API DMKAnimationControlInstruction {
		DMK_ANIMATION_CONTROL_INSTRUCTION_PAUSE,
		DMK_ANIMATION_CONTROL_INSTRUCTION_PLAY,
		DMK_ANIMATION_CONTROL_INSTRUCTION_RESTART,
	};

	/*
	 Dynamik Animation Controller
	*/
	class DMK_API DMKAnimationController {
		using TFunc = std::function<void()>;

		/* Animation Control Instruction */
		struct DMK_API AnimationControlInstruction {
			// DMKAnimationComponent component;
			DMKAnimationControlInstruction instruction = DMKAnimationControlInstruction::DMK_ANIMATION_CONTROL_INSTRUCTION_PAUSE;
			TFunc pfInvoke;
		};

	public:
		DMKAnimationController() {}
		~DMKAnimationController() {}

		void initialize();
		void update();

		void bindInstruction(STRING sEvent, DMKAnimationControlInstruction instruction, DMKLevelComponent* pLevelComponent, DMKEventType eventType);

	private:
		std::unordered_map<STRING, AnimationControlInstruction> instructionMap;
	};
}

#endif // !_DYNAMIK_ANIMATION_CONTROLLER_H
