// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_ENGINE_SYSTEM_LOCATOR_H
#define _DYNAMIK_ENGINE_SYSTEM_LOCATOR_H

#include "Core/Types/DataTypes.h"

namespace DMK
{
	namespace Engine
	{
		/**
		 * System locator for the Dynamik Engine.
		 * This object keeps track on all the systems which are currently running and which can be accessed.
		 */
		class SystemLocator {
		public:
			SystemLocator() {}
			~SystemLocator() {}
		};
	}
}

#endif // !_DYNAMIK_ENGINE_SYSTEM_LOCATOR_H
