#pragma once
#ifndef _DYNAMIK_MEMORY_MANAGER_H
#define _DYNAMIK_MEMORY_MANAGER_H

/*
 Heap memory manager for the Dynamik Engine.
 This is a Singleton structure used to allocate and deallocate memory.
*/

#include "Pointer.h"
#include "Macros/Global.h"
#include "Macros/MemoryMacro.h"
#include "Object/Components/ManagerObject.h"

namespace Dynamik
{
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
	class DMK_API DMKMemoryManager : public DMKManagerObject {
		DMKMemoryManager() {}
		~DMKMemoryManager();

		DMK_CLASS_SINGLETON(DMKMemoryManager)

			static void deallocate(POINTER<UI32> address, UI32 byteSize);

		static DMKHeapContainer oneTimeAllocate(UI32 byteSize);
	};
}

#endif // !_DYNAMIK_MEMORY_MANAGER_H
