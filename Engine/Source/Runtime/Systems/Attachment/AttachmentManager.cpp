#include "dmkafx.h"
#include "AttachmentManager.h"

namespace Dynamik
{
	DMKAttachmentManager::DMKAttachmentManager()
	{
		myMemoryBuffer = nullptr;
		myNextPtr = myMemoryBuffer;
		myAllocationSize = 0;
	}
	
	DMKAttachmentManager::~DMKAttachmentManager()
	{
		StaticAllocator<BYTE>::deallocate(myMemoryBuffer, 0);
	}
	
	inline void DMKAttachmentManager::_allocateHeap(UI32 byteSize)
	{
		if (myAllocationSize)
		{
			DMK_INFO("Extending the buffer by " + std::to_string(byteSize) + " Bytes.");

			auto _newBuffer = StaticAllocator<BYTE>::allocate(myAllocationSize + byteSize);
			MemoryFunctions::moveData(_newBuffer, myMemoryBuffer, myAllocationSize);

			StaticAllocator<BYTE>::deallocate(myMemoryBuffer, myAllocationSize);
			myMemoryBuffer = _newBuffer;
			myNextPtr = myMemoryBuffer;
			myNextPtr += myAllocationSize;
			myAllocationSize += byteSize;
		}
		else
		{
			myMemoryBuffer = StaticAllocator<BYTE>::allocate(byteSize);
			myNextPtr = myMemoryBuffer;
			myAllocationSize = byteSize;
		}
	}
}