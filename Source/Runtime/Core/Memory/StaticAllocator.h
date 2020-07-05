// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_STATIC_ALLOCATOR_H
#define _DYNAMIK_STATIC_ALLOCATOR_H

/*
 Static Memory Allocator for the Dynamik Engine
*/

#include "Core/Types/Pointer.h"
#include "Core/Macros/MemoryMacro.h"
#include "Core/Macros/Global.h"
#include "Core/Error/ErrorManager.h"
#include "Core/Types/TypeTraits.h"
#include "AutomatedMemoryManager.h"

#include <memory>

namespace Dynamik
{
	/*
	 Dynamik Static Allocator class
	 The static allocator is used to allocate a buffer in heap. It does not manage its deletion automatically but
	 needs to be explicitly deleted.

	 @template param: Output type.
	 @template param: Default alignment type.
	*/
	template<class TYPE, UI64 DefaultAligment = DMK_ALIGNMENT>
	class DMK_API StaticAllocator
	{
		using PTR = POINTER<TYPE>;

		StaticAllocator() {}
		~StaticAllocator() {}
	public:

		/*
		 Allocates a block of memory and return its address.

		 @param byteSize: Size of the memory block in bytes. Default is the size of the type.
		 @param alignment: Alignment of the allocated memory. Default is 0.
		 @param offset: Memory offset of the allocated memory block. Default is 0;
		*/
		DMK_FORCEINLINE static PTR rawAllocate(UI64 byteSize = sizeof(TYPE), UI64 alignment = DefaultAligment, UI64 offset = 0)
		{
			PTR _ptr = _rawAllocation(byteSize, alignment, offset);
			set(_ptr, TYPE());

			return _ptr;
		}

		/*
		 Allocates a block of memory and return its address.
		 This type of allocation is slow.

		 @param byteSize: Size of the memory block in bytes. Default is the size of the type.
		 @param alignment: Alignment of the allocated memory. Default is 0.
		 @param offset: Memory offset of the allocated memory block. Default is 0;
		*/
		DMK_FORCEINLINE static PTR allocate(UI64 byteSize = sizeof(TYPE), UI64 alignment = DefaultAligment, UI64 offset = 0)
		{
			PTR _ptr = (PTR)DMKAutomatedMemoryManager::allocateNew(byteSize, offset, alignment);
			set(_ptr, TYPE());

			return _ptr;
		}

		/*
		 Allocates a block of memory and return its address.

		 @param byteSize: Size of the memory block in bytes. Default is the size of the type.
		 @param alignment: Alignment of the allocated memory. Default is 0.
		 @param offset: Memory offset of the allocated memory block. Default is 0;
		*/
		DMK_FORCEINLINE static PTR allocateInit(const TYPE& initData, UI64 byteSize = sizeof(TYPE), UI64 alignment = DefaultAligment, UI64 offset = 0)
		{
			PTR _ptr = _rawAllocation(byteSize, alignment, offset);
			set(_ptr, (TYPE&&)initData);

			return _ptr;
		}

		/*
		 Deallocates the previously allocated block of memory.

		 @param location: Address of the memory block.
		 @param byteSize: Size of the memory block. Default is the size of type. If size is unknown, enter 0.
		 @param alignment: Alignment of the memory block. Default is 0.
		 @param offset: Offset of the memory block. Default is 0.
		*/
		DMK_FORCEINLINE static void rawDeallocate(PTR location, UI64 byteSize = sizeof(TYPE), UI64 alignment = DefaultAligment, UI64 offset = 0)
		{
			if (byteSize)
				operator delete (location.get(), byteSize, std::align_val_t{ alignment });
			else
				delete location.get();
		}

		/*
		 Deallocates the previously allocated block of memory.

		 @param location: Address of the memory block.
		 @param byteSize: Size of the memory block. Default is the size of type. If size is unknown, enter 0.
		 @param alignment: Alignment of the memory block. Default is 0.
		 @param offset: Offset of the memory block. Default is 0.
		*/
		DMK_FORCEINLINE static void deallocate(PTR location, UI64 byteSize = sizeof(TYPE), UI64 alignment = DefaultAligment, UI64 offset = 0)
		{
			DMKAutomatedMemoryManager::deallocate(location, byteSize, offset, alignment);
		}

		/*
		 Deallocates the previously allocated block of memory.

		 @param begin: Begin address of the memory.
		 @param end: Final address of the memory.
		*/
		DMK_FORCEINLINE static void deallocateRange(PTR begin, PTR end)
		{
			operator delete(begin.get(), end.get());
		}

		/*
		 Allocates a block of memory as an array and return its address.

		 @param byteSize: Size of the memory block in bytes. Default is the size of the type.
		 @param alignment: Alignment of the allocated memory. Default is 0.
		 @param offset: Memory offset of the allocated memory block. Default is 0;
		*/
		DMK_FORCEINLINE static PTR allocateArr(UI64 byteSize = sizeof(TYPE), UI64 alignment = DefaultAligment, UI64 offset = 0)
		{
			PTR _ptr = _rawAllocationArr(byteSize, alignment, offset);
			set(_ptr, TYPE());

			return _ptr;
		}

		/*
		 Deallocates the previously allocated block of memory. The allocation must be an array type.

		 @param location: Address of the memory block.
		 @param byteSize: Size of the memory block. Default is the size of type.
		 @param alignment: Alignment of the memory block. Default is 0.
		 @param offset: Offset of the memory block. Default is 0.
		*/
		DMK_FORCEINLINE static void deallocateArr(PTR location, UI64 byteSize = sizeof(TYPE), UI64 alignment = DefaultAligment, UI64 offset = 0)
		{
			if (byteSize)
				operator delete[](location.get(), byteSize, std::align_val_t{ alignment });
			else
				delete[] location.get();
		}

		/*
		 Deallocates the previously allocated block of memory. The allocation must be an array type.

		 @param begin: Begin address of the memory.
		 @param end: Final address of the memory.
		*/
		DMK_FORCEINLINE static void deallocateArrRange(PTR begin, PTR end)
		{
			operator delete[](begin.get(), end.get());
		}

		/*
		 Sets a value to a given location.

		 @param location: Memory address of the block.
		 @param value: Value to be initialized with.
		*/
		static void set(PTR location, TYPE&& value)
		{
			new ((VPTR)location.get()) (TYPE)(removeReference<TYPE&&>(value));
		}

	private:
		/*
		 Allocate memory and check if the allocation was successful.
		*/
		DMK_FORCEINLINE static PTR _rawAllocation(UI64 byteSize, UI64 alignment, UI64 offset)
		{
			try
			{
				auto __newAddr = operator new (byteSize, std::align_val_t{ alignment });

				if (!__newAddr)
				{
					DMKErrorManager::issueErrorBox("Unable to allocate memory!");

#ifdef DMK_DEBUG
					__debugbreak();

#endif
				}

				return (PTR)__newAddr;
			}
			catch (const std::exception&)
			{
				DMKErrorManager::issueErrorBox("Unable to allocate memory!");

#ifdef DMK_DEBUG
				__debugbreak();

#endif

				return PTR();
			}
		}

		/*
		 Allocate memory as an array and check if the allocation was successful.
		*/
		DMK_FORCEINLINE static PTR _rawAllocationArr(UI64 byteSize, UI64 alignment, UI64 offset)
		{
			try
			{
				auto __newAddr = operator new[](byteSize, std::align_val_t{ alignment });

				if (!__newAddr)
				{
					DMKErrorManager::issueErrorBox("Unable to allocate memory!");

#ifdef DMK_DEBUG
					__debugbreak();

#endif
				}

				return (PTR)__newAddr;
			}
			catch (const std::exception&)
			{
				DMKErrorManager::issueErrorBox("Unable to allocate memory!");

#ifdef DMK_DEBUG
				__debugbreak();

#endif

				return PTR();
			}
		}
	};
}

#endif // !_DYNAMIK_STATIC_ALLOCATOR_H
