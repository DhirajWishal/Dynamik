// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Types/DataTypes.h"

#define GET_NANOSECONDS_FROM_MILLISECONDS(x)			x * 1000
#define GET_NANOSECONDS_FROM_SECONDS(x)					x * 1000000

#define GET_MILLISECONDS_FROM_NANOSECONDS(x)			x / 1000
#define GET_MILLISECONDS_FROM_SECONDS(x)				x * 1000

#define GET_SECONDS_FROM_MILLISECONDS(x)				x / 1000
#define GET_SECONDS_FROM_NANOSECONDS(x)					x / 1000000

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