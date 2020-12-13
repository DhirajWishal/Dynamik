// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Inputs/InputCenter.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Device Handle object.
		 * This object stores information about a single graphics device.
		 */
		class DeviceHandle {
		public:
			DeviceHandle(UI64 handle = 0) : mHandle(handle) {}
			~DeviceHandle() {}

			UI64 mHandle = 0;
		};
	}
}