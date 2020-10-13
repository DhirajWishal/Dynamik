// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_MEMORY_MANAGER_H
#define _DYNAMIK_MEMORY_MANAGER_H

/*
 Heap memory manager for the Dynamik Engine.
*/

#include "Core/Types/Pointer.h"
#include "Core/Macros/Global.h"
#include "Core/Macros/MemoryMacro.h"

/*
 Dynamik Heap Container structure.
 This automatically deallocates memory upon destruction.
 address stored in this structure can be allocated externally but deallocation of memory uses the
 Memory manager.
*/
struct DMK_API DMKHeapContainer {
	DMKHeapContainer() {}
	~DMKHeapContainer();

	POINTER<UI32> address;
	UI32 byteSize = 0;
};

/*
 Memory Manager for the Dynamik Engine.
 There are 2 main types of allocations supported by the manager.
 * One time allocation (automatically clears the memory)
 * Heap pool allocation (double buffered stack allocation)
*/
class DMK_API DMKMemoryManager {
	DMKMemoryManager() {}
	~DMKMemoryManager();
public:
	static void deallocate(UI32* address, UI32 byteSize);

	static DMKHeapContainer oneTimeAllocate(UI32 byteSize);
};

#endif // !_DYNAMIK_MEMORY_MANAGER_H