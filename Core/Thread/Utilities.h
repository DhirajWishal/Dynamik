// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Types/DataTypes.h"

namespace DMK
{
	namespace Thread
	{
		namespace Utilities
		{
			/**
			 * Sleep the thread for a specific duration.
			 *
			 * @param duration: The duration in microseconds.
			 */
			void Sleep(UI64 duration);
		}
	}
}