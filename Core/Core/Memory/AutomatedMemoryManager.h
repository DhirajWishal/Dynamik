// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_AUTOMATED_MEMORY_MANAGER_H
#define _DYNAMIK_AUTOMATED_MEMORY_MANAGER_H

#include "../Macros/Global.h"
#include <unordered_map>

/*
 Dynamik Automated Memory Manager
 This is used to terminate all the heap allocated memory which was no freed explicitly by the runtime.
 This is done when the engine instance is terminated.
*/
class DMK_API DMKAutomatedMemoryManager {
	DMKAutomatedMemoryManager();
	~DMKAutomatedMemoryManager();

	static DMKAutomatedMemoryManager instance;

private:
	using INDEX = UI64;
	using ADDRESS = void*;

public:
	DMKAutomatedMemoryManager(const DMKAutomatedMemoryManager&) = delete;
	DMKAutomatedMemoryManager(DMKAutomatedMemoryManager&&) = delete;
	DMKAutomatedMemoryManager& operator=(const DMKAutomatedMemoryManager&) = delete;
	DMKAutomatedMemoryManager& operator=(DMKAutomatedMemoryManager&&) = delete;

	/*
	 Get the number of allocations made
	*/
	static UI64 getAllocationCount();

	/*
	 Allocate a new buffer
	*/
	template<class TYPE>
	static TYPE* allocateNew(UI64 size = sizeof(TYPE), UI64 offset = 0, UI64 alignment = 0)
	{
		TYPE* _pointer = StaticAllocator<TYPE>::rawAllocate(size, alignment, offset);
		instance.memoryMap[(UI64)_pointer] = _pointer;

		return _pointer;
	}

	/*
	 Deallocate a allocated buffer
	*/
	static void deallocate(void* location, UI64 size, UI64 offset, UI64 alignment);

private:
	std::unordered_map<INDEX, ADDRESS> memoryMap;
};

#endif // !_DYNAMIK_AUTOMATED_MEMORY_MANAGER_H
