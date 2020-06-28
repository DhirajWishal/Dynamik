// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "ComponentManager.h"

namespace Dynamik
{
	DMKComponentManager::~DMKComponentManager()
	{
		for (auto _component : components)
			StaticAllocator<I_ComponentArray>::deallocate(_component.second, 0);
	}
}
