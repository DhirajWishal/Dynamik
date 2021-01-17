// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "Thread/Utilities.h"

#include <chrono>
#include <thread>

namespace DMK
{
	namespace Thread
	{
		namespace Utilities
		{
			void Sleep(UI64 duration)
			{
				std::this_thread::sleep_for(std::chrono::microseconds(duration));
			}
		}
	}
}