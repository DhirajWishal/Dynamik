// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "MemoryManager.h"

#include "StaticAllocator.h"

	/* Destructor */
DMKMemoryManager::~DMKMemoryManager()
{
}

void DMKMemoryManager::deallocate(UI32* address, UI32 byteSize)
{
	StaticAllocator<UI32>::deallocate(address, byteSize);
}

DMKHeapContainer DMKMemoryManager::oneTimeAllocate(UI32 byteSize)
{
	/* Create a new heap container and assign it a newly allocated block. */
	DMKHeapContainer _container;
	_container.address = StaticAllocator<UI32>::allocate(byteSize);
	_container.byteSize = byteSize;

	return _container;
}

DMKHeapContainer::~DMKHeapContainer()
{
	if (address.isValid())
		DMKMemoryManager::deallocate(address, byteSize);
	else
		/* Flag a warning. */;
}
