// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_CORE_MEMORY_AUTOMATED_MEMORY_MANAGER_H
#define _DYNAMIK_CORE_MEMORY_AUTOMATED_MEMORY_MANAGER_H

#include "Core/Types/DataTypes.h"

namespace DMK
{
	/**
	 * The Automated Memory Manager. 
	 * This structure keeps track on all the memory allocations done by the DMK and terminates all the memory blocks
	 * which were not deallocated in the runtime when the application is being terminated.
	 */
	class AutomatedMemoryManager {
		AutomatedMemoryManager();
		~AutomatedMemoryManager();

		static AutomatedMemoryManager instance;

	private:
		using INDEX = UI64;
		using ADDRESS = void*;

	public:
		AutomatedMemoryManager(const AutomatedMemoryManager&) = delete;
		AutomatedMemoryManager(AutomatedMemoryManager&&) = delete;
		AutomatedMemoryManager& operator=(const AutomatedMemoryManager&) = delete;
		AutomatedMemoryManager& operator=(AutomatedMemoryManager&&) = delete;

		/**
		 * Get the number of allocations made.
		 *
		 * @return: Unsigned 16 bit integer.
		 */
		static UI64 GetAllocationCount();

		
		/**
		 * Allocate a new buffer. 
		 *
		 * @tparam TYPE: Data type of the block.
		 * @param size: Size of the block.
		 * @param offset: Offset of the block.
		 * @param alignment: Alignment of the block.
		 * @return: Pointer to the allocated memory block.
		 */
		template<class TYPE>
		static TYPE* AllocateNew(UI64 size = sizeof(TYPE), UI64 offset = 0, UI64 alignment = 0)
		{
			TYPE* _pointer = StaticAllocator<TYPE>::RawAllocate(size, alignment, offset);
			instance.memoryMap[(UI64)_pointer] = _pointer;

			return _pointer;
		}

		/**
		 * Deallocate a allocated buffer. 
		 *
		 * @param location: Location of the memory block.
		 * @param size: Size of the block.
		 * @param offset: Offset of the block.
		 * @param alignment: Alignment of the block.
		 */
		static void Deallocate(void* location, UI64 size, UI64 offset, UI64 alignment);

	private:
		std::unordered_map<INDEX, ADDRESS> memoryMap;
	};
}

#endif // !_DYNAMIK_CORE_MEMORY_AUTOMATED_MEMORY_MANAGER_H
