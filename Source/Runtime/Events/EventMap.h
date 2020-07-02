// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_EVENT_MAP_H
#define _DYNAMIK_EVENT_MAP_H

/*
 Author:	Dhiraj Wishal
 Date:		02/07/2020
*/
#include "Core/Macros/Global.h"
#include "Event/KeyCodes.h"
#include "EventHandler.h"
#include <unordered_map>

namespace Dynamik
{
	/*
	 Dynamik Control Instruction
	 These instructions are what is used by the camera controller to control the camera.
	*/
	enum class DMK_API DMKControlInstruction : UI32 {
		DMK_CONTROL_INSTRUCTION_UNKNOWN			= 0,

		DMK_CONTROL_INSTRUCTION_MOVE_FORWARD	= BIT_SHIFT(0),
		DMK_CONTROL_INSTRUCTION_MOVE_BACKWARD	= BIT_SHIFT(1),
		DMK_CONTROL_INSTRUCTION_MOVE_LEFT		= BIT_SHIFT(2),
		DMK_CONTROL_INSTRUCTION_MOVE_RIGHT		= BIT_SHIFT(3),

		DMK_CONTROL_INSTRUCTION_JUMP			= BIT_SHIFT(4),
		DMK_CONTROL_INSTRUCTION_CROUCH			= BIT_SHIFT(5),
		DMK_CONTROL_INSTRUCTION_SPRINT			= BIT_SHIFT(6),
		DMK_CONTROL_INSTRUCTION_SLIDE			= BIT_SHIFT(7),

		DMK_CONTROL_INSTRUCTION_TRIGGER			= BIT_SHIFT(8),
		DMK_CONTROL_INSTRUCTION_RELOAD			= BIT_SHIFT(9),
		DMK_CONTROL_INSTRUCTION_AIM				= BIT_SHIFT(10),
		DMK_CONTROL_INSTRUCTION_VIEW			= BIT_SHIFT(11),
		DMK_CONTROL_INSTRUCTION_LOOK			= BIT_SHIFT(12),
	};

	/*
	 Dynamik Control Structure
	*/
	struct DMK_API DMKControlStructure {
		DMKControlInstruction instruction = DMKControlInstruction::DMK_CONTROL_INSTRUCTION_UNKNOWN;
		F32 actionRate = 1.0f;
	};

	/*
	 Dynamik Event Map
	 This component describes which events are used in the update function.
	*/
	class DMK_API DMKEventMap {
	public:
		DMKEventMap() {}
		~DMKEventMap() {}

		/*
		 Add an instruction to the map.

		 @param eEvent: The event.
		 @param eInstruction: The instruction bound to the given event.
		 @param actionRate: The action rate of the instruction. Default is 1.0f.
		*/
		void addInstruction(const DMKEvent& eEvent, const DMKControlInstruction& eInstruction, const F32& actionRate = 1.0f);

		/*
		 Get instruction associated to a given event.
		 Returns DMK_CONTROL_INSTRUCTION_UNKNOWN if an instruction is not bound to that event.

		 @param eEvent: The event.
		*/
		const DMKControlStructure getInstruction(const DMKEvent& eEvent) const;

	private:
		mutable std::unordered_map<DMKEvent, DMKControlStructure> instructionMap;
	};
}

#endif // !_DYNAMIK_EVENT_MAP_H
