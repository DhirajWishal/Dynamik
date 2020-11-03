// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_CORE_MEMORY_STATIC_ALLOCATOR_H
#define _DYNAMIK_CORE_MEMORY_STATIC_ALLOCATOR_H

/**
 * Static Memory Allocator for Dynamik
 */

#include "Core/ErrorHandler/Logger.h"
#include "AutomatedMemoryManager.h"
#include "Core/Types/Utilities.h"
#include "Core/Macros/Global.h"
#include "Defines.h"

#include <memory>

namespace DMK
{
	/**
	 * Dynamik Static Allocator class
	 * The static allocator is used to allocate a buffer in heap.It does not manage its deletion automatically but
	 * needs to be explicitly deleted.
	 *
	 * @tparam Type: Output type.
	 */
	template<class Type, UI64 DefaultAligment = DMK_ALIGNMENT>
	class StaticAllocator
	{
		using PTR = Type*;

		/**
		 * Constructor.
		 */
		StaticAllocator() {}

		/**
		 * Destructor.
		 */
		~StaticAllocator() {}
	public:

		/**
		 * Allocates a block of memory and return its address.
		 *
		 * @param byteSize: Size of the memory block in bytes. Default is the size of the type.
		 * @param alignment: Alignment of the allocated memory. Default is 0.
		 * @param offset: Memory offset of the allocated memory block. Default is 0.
		 * @return: The newly allocated block.
		 */
		DMK_FORCEINLINE static PTR RawAllocate(UI64 byteSize = sizeof(Type), UI64 alignment = DefaultAligment, UI64 offset = 0)
		{
			PTR _ptr = RawAllocation(byteSize, alignment, offset);
			Set(_ptr, Type());

			return _ptr;
		}

		/**
		 * Allocates a block of memory and return its address.
		 * This type of allocation is slow.
		 *
		 * @param byteSize: Size of the memory block in bytes. Default is the size of the type.
		 * @param alignment: Alignment of the allocated memory. Default is 0.
		 * @param offset: Memory offset of the allocated memory block. Default is 0.
		 * @return: The newly allocated block.
		 */
		DMK_FORCEINLINE static PTR Allocate(UI64 byteSize = sizeof(Type), UI64 alignment = DefaultAligment, UI64 offset = 0)
		{
			PTR _ptr = AutomatedMemoryManager::AllocateNew<Type>(byteSize, offset, alignment);

			return _ptr;
		}

		/**
		 * Allocates a block of memory and return its address.
		 *
		 * @param initData: Data to be initialized with.
		 * @param byteSize: Size of the memory block in bytes. Default is the size of the type.
		 * @param alignment: Alignment of the allocated memory. Default is 0.
		 * @param offset: Memory offset of the allocated memory block. Default is 0.
		 * @return: The newly allocated block.
		 */
		DMK_FORCEINLINE static PTR AllocateInit(const Type& initData, UI64 byteSize = sizeof(Type), UI64 alignment = DefaultAligment, UI64 offset = 0)
		{
			PTR _ptr = RawAllocation(byteSize, alignment, offset);
			Set(_ptr, static_cast<Type&&>(initData));

			return _ptr;
		}

		/**
		 * Deallocates the previously allocated block of memory.
		 *
		 * @param location: Address of the memory block.
		 * @param byteSize: Size of the memory block. Default is the size of type. If size is unknown, enter 0.
		 * @param alignment: Alignment of the memory block. Default is 0.
		 * @param offset: Offset of the memory block. Default is 0.
		 * @return: The newly allocated block.
		 */
		DMK_FORCEINLINE static void RawDeallocate(PTR location, UI64 byteSize = sizeof(Type), UI64 alignment = DefaultAligment, UI64 offset = 0)
		{
			if (byteSize)
				operator delete (location, byteSize, std::align_val_t{ alignment });
			else
				operator delete (location, std::align_val_t{ alignment });
		}

		/**
		 * Deallocates the previously allocated block of memory.
		 *
		 * @param location: Address of the memory block.
		 * @param byteSize: Size of the memory block. Default is the size of type. If size is unknown, enter 0.
		 * @param alignment: Alignment of the memory block. Default is 0.
		 * @param offset: Offset of the memory block. Default is 0.
		 * @return: The newly allocated block.
		 */
		DMK_FORCEINLINE static void Deallocate(PTR location, UI64 byteSize = sizeof(Type), UI64 alignment = DefaultAligment, UI64 offset = 0)
		{
			AutomatedMemoryManager::Deallocate(location, byteSize, offset, alignment);
		}

		/**
		 * Deallocates the previously allocated block of memory.
		 *
		 * @param begin: Begin address of the memory.
		 * @param end: Final address of the memory.
		 * @return: The newly allocated block.
		 */
		DMK_FORCEINLINE static void DeallocateRange(PTR begin, PTR end)
		{
			operator delete(begin, end);
		}

		/**
		 * Allocates a block of memory as an array and return its address.
		 *
		 * @param byteSize: Size of the memory block in bytes. Default is the size of the type.
		 * @param alignment: Alignment of the allocated memory. Default is 0.
		 * @param offset: Memory offset of the allocated memory block. Default is 0.
		 * @return: The newly allocated block.
		 */
		DMK_FORCEINLINE static PTR AllocateArr(UI64 byteSize = sizeof(Type), UI64 alignment = DefaultAligment, UI64 offset = 0)
		{
			PTR _ptr = RawAllocationArr(byteSize, alignment, offset);
			Set(_ptr, Type());

			return _ptr;
		}

		/**
		 * Deallocates the previously allocated block of memory. The allocation must be an array type.
		 *
		 * @param location: Address of the memory block.
		 * @param byteSize: Size of the memory block. Default is the size of type.
		 * @param alignment: Alignment of the memory block. Default is 0.
		 * @param offset: Offset of the memory block. Default is 0.
		 * @return: The newly allocated block.
		 */
		DMK_FORCEINLINE static void DeallocateArr(PTR location, UI64 byteSize = sizeof(Type), UI64 alignment = DefaultAligment, UI64 offset = 0)
		{
			if (byteSize)
				operator delete[](location, byteSize, std::align_val_t{ alignment });
			else
				delete[] location;
		}

		/**
		 * Deallocates the previously allocated block of memory. The allocation must be an array type.
		 *
		 * @param begin: Begin address of the memory.
		 * @param end: Final address of the memory.
		 * @return: The newly allocated block.
		 */
		DMK_FORCEINLINE static void DeallocateArrRange(PTR begin, PTR end)
		{
			operator delete[](begin, end);
		}

		/**
		 * Sets a value to a given location.
		 *
		 * @param location: Memory address of the block.
		 * @param value: Value to be initialized with.
		 */
		static void Set(PTR location, Type&& value)
		{
			new (static_cast<void*>(location)) (Type)(static_cast<Type&&>(value));
		}

	private:
		/**
		 * Allocate memory and check if the allocation was successful.
		 *
		 * @param byteSize: Size of the block.
		 * @param alignment: Alignment of the block.
		 * @param offset: Offset of the block.
		 * @return: The newly allocated block.
		 */
		DMK_FORCEINLINE static PTR RawAllocation(UI64 byteSize, UI64 alignment, UI64 offset)
		{
			try
			{
				auto __newAddr = operator new (byteSize, std::align_val_t{ alignment });

				if (!__newAddr)
				{
					Logger::LogError(TEXT("Unable to allocate memory!"));

#ifdef DMK_DEBUG
					__debugbreak();

#endif
				}

				return static_cast<PTR>(__newAddr);
			}
			catch (const std::exception&)
			{
				Logger::LogError(TEXT("Unable to allocate memory!"));

#ifdef DMK_DEBUG
				__debugbreak();

#endif

				return nullptr;
			}
		}

		/**
		 * Allocate memory as an array and check if the allocation was successful.
		 *
		 * @param byteSize: Size of the block.
		 * @param alignment: Alignment of the block.
		 * @param offset: Offset of the block.
		 * @return: The newly allocated block.
		 */
		DMK_FORCEINLINE static PTR RawAllocationArr(UI64 byteSize, UI64 alignment, UI64 offset)
		{
			try
			{
				auto __newAddr = operator new[](byteSize, std::align_val_t{ alignment });

				if (!__newAddr)
				{
					Logger::LogError(TEXT("Unable to allocate memory!"));

#ifdef DMK_DEBUG
					__debugbreak();

#endif
				}

				return static_cast<PTR>(__newAddr);
			}
			catch (const std::exception&)
			{
				Logger::LogError(TEXT("Unable to allocate memory!"));

#ifdef DMK_DEBUG
				__debugbreak();

#endif

				return nullptr;
			}
		}
	};
}

#endif // !_DYNAMIK_CORE_MEMORY_STATIC_ALLOCATOR_H