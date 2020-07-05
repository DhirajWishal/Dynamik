// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_AUTOMATED_MEMORY_MANAGER_H
#define _DYNAMIK_AUTOMATED_MEMORY_MANAGER_H

#include "../Macros/Global.h"
#include <unordered_map>

namespace Dynamik
{
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
		using ADDRESS = VPTR;

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
		static VPTR allocateNew(UI64 size, UI64 offset, UI64 alignment);

		/*
		 Deallocate a allocated buffer
		*/
		static void deallocate(VPTR location, UI64 size, UI64 offset, UI64 alignment);

	private:
		std::unordered_map<INDEX, ADDRESS> memoryMap;
	};
}

#endif // !_DYNAMIK_AUTOMATED_MEMORY_MANAGER_H
