// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "AutomatedMemoryManager.h"

#include "StaticAllocator.h"
#include <iostream>

namespace Dynamik
{
	DMKAutomatedMemoryManager::DMKAutomatedMemoryManager()
	{
	}

	DMKAutomatedMemoryManager::~DMKAutomatedMemoryManager()
	{

		for (auto _address : memoryMap)
		{
#ifdef DMK_DEBUG
			printf("Deleting 0x%p from the automated memory manager.\n", _address.second);

#endif // DMK_DEBUG
			StaticAllocator<BYTE>::rawDeallocate(_address.second, 0);
		}

	}

	UI64 DMKAutomatedMemoryManager::getAllocationCount()
	{
		return instance.memoryMap.size();
	}

	VPTR DMKAutomatedMemoryManager::allocateNew(UI64 size, UI64 offset, UI64 alignment)
	{
		VPTR _pointer = StaticAllocator<BYTE>::rawAllocate(size, alignment, offset);
		instance.memoryMap[(UI64)_pointer] = _pointer;

		return _pointer;
	}

	void DMKAutomatedMemoryManager::deallocate(VPTR location, UI64 size, UI64 offset, UI64 alignment)
	{
		StaticAllocator<BYTE>::rawDeallocate(location, size, alignment, offset);
		instance.memoryMap.erase((UI64)location);
	}

	DMKAutomatedMemoryManager DMKAutomatedMemoryManager::instance;
}
