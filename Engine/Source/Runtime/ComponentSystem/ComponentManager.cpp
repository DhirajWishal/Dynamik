// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "ComponentManager.h"

namespace Dynamik
{
	DMKComponentManager::~DMKComponentManager()
	{
		for (auto _component : components)
			StaticAllocator<IComponentArray>::deallocate(_component.second, 0);
	}
}
