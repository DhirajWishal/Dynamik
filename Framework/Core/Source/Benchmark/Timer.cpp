// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "Core/Benchmark/Timer.h"

#include <chrono>

namespace DMK
{
	namespace Benchmark
	{
		Timer::Timer()
			: pTimerName(nullptr),
			mStartTime(std::chrono::time_point_cast<std::chrono::microseconds>(
				std::chrono::high_resolution_clock::now()
				).time_since_epoch().count()) {}

		Timer::Timer(const wchar* pText)
			: pTimerName(pText),
			mStartTime(std::chrono::time_point_cast<std::chrono::microseconds>(
				std::chrono::high_resolution_clock::now()
				).time_since_epoch().count()) {}

		Timer::~Timer()
		{
			I64 endTime = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count();

			if (pTimerName)
				wprintf_s(TEXT("%s\n"), pTimerName);

			wprintf_s(TEXT("Time taken: %lld (microseconds)\n"), endTime - mStartTime);
		}
	}
}