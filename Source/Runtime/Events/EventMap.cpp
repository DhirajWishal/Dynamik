// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "EventMap.h"

namespace Dynamik
{
	void DMKEventMap::addInstruction(const DMKEvent& eEvent, const DMKControlInstruction& eInstruction, const F32& actionRate)
	{
		DMKControlStructure constrolStruct = { eInstruction, actionRate };

		instructionMap[eEvent] = constrolStruct;
	}

	const DMKControlStructure DMKEventMap::getInstruction(const DMKEvent& eEvent) const
	{
		if (instructionMap.count(eEvent))
			return instructionMap[eEvent];

		return DMKControlStructure();
	}
}
