// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "Core/Random/OneTimeGenerator.h"
#include "Core/Hash/Hasher.h"

#include <chrono>

namespace DMK
{
	namespace Random
	{
		UI64 GenerateRandom(UI64 lowerBound, UI64 upperBound)
		{
			UI64 currentTime = static_cast<UI64>(std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count());
			UI64 hashData[2] = { currentTime, reinterpret_cast<UI64>(&currentTime) };

			return currentTime;
		}
	}
}