// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Types/DataTypes.h"

namespace DMK
{
	/**
	 * The Automated Memory Manager.
	 * This structure keeps track on all the memory allocations done by the DMK and terminates all the memory blocks
	 * which were not deallocated in the runtime when the application is being terminated.
	 */
	class AutomatedMemoryManager {
		/**
		 * Constructor.
		 */
		AutomatedMemoryManager();

		/**
		 * Destructor.
		 */
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
		 * @return Unsigned 16 bit integer.
		 */
		static UI64 GetAllocationCount();

		/**
		 * Allocate a new buffer.
		 *
		 * @tparam Type: Data type of the block.
		 * @param size: Size of the block.
		 * @param offset: Offset of the block.
		 * @param alignment: Alignment of the block.
		 * @return Pointer to the allocated memory block.
		 */
		template<class Type>
		static Type* AllocateNew(UI64 size = sizeof(Type), UI64 offset = 0, UI64 alignment = 0)
		{
			Type* _pointer = StaticAllocator<Type>::RawAllocate(size, alignment, offset);
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
		std::unordered_map<INDEX, ADDRESS> memoryMap;	// Memory map containing the memory addresses.
	};
}
