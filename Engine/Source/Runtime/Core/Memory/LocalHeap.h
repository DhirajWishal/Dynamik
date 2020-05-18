#pragma once
#ifndef _DYNAMIK_LOCAL_HEAP_H
#define _DYNAMIK_LOCAL_HEAP_H

/*
 Local Heap object for the Dynamik Engine.

 Author:    Dhiraj Wishal
 Date:      13/05/2020
*/
#include "Pointer.h"
#include "Macros/MemoryMacro.h"
#include "Macros/Global.h"

namespace Dynamik
{
	/*
	 The local heap is used to allocate a block of memory for an object, preferably for a manager to store its
	 data on the heap.
	 This automatically deallocates its memory block when destroyed.
	*/
	class DMK_API LocalHeap {
	public:
		LocalHeap();
		~LocalHeap();

		/*
		 Allocate a new memory pool.

		 @param byteSize: Size of the allocation in bytes.

		 @warn: Reallocating or recalling this function while the a memory buffer is already allocated
				will result in an override allocation.
		*/
		void allocate(UI32 byteSize);

		/*
		 Extend the memory buffer.

		 @param newByteSize: The total size to be extended.
		*/
		void extend(UI32 additionalSize);

		/*
		 Clear all the values stored in the memory buffer to be 0.
		*/
		void clearPool();

		/*
		 Adds data to the memory buffer and return its address.

		 @param data: Data to be stored.
		 @param byteSize: Size of the storing data.

		 @warn: Extends the memory buffer and adds the new data to it. The extended size will be equal to
				the pre allocated size plus the size of the adding data.
		*/
		VPTR addToStore(VPTR data, UI32 byteSize);

		/*
		 Delete a value from the memory buffer.

		 @param data: Data location of the variable.
		 @param byteSize: Size of the stored data.
		*/
		void deleteFromStore(VPTR data, UI32 byteSize);

		UI32 getAllocationSize() { return myAllocationSize; }

	private:
		void _terminateLocalBlock();

		POINTER<UI32> myMemoryBlock;
		POINTER<UI32> myNextPtr = myMemoryBlock;
		UI32 myAllocationSize = 0;
	};
}

#endif // !_DYNAMIK_LOCAL_HEAP_H
