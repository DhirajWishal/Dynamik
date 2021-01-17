// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Types/DataTypes.h"

namespace DMK
{
	namespace Random
	{
		/**
		 * Generate random once.
		 *
		 * @param lowerBound: The minimum bound of the random integer. Default is 0.
		 * @param upperBound: The maximum bound of the random integer. Default is the integer max of UI64.
		 * @return Unsigned 64 bit integer.
		 */
		UI64 GenerateRandom(UI64 lowerBound = 0, UI64 upperBound = std::numeric_limits<UI64>::max());
	}
}