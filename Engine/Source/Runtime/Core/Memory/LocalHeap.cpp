#include "dmkafx.h"
#include "LocalHeap.h"

#include "StaticAllocator.h"
#include "MemoryFunctions.h"

namespace Dynamik
{
	LocalHeap::LocalHeap()
	{
	}

	LocalHeap::~LocalHeap()
	{
		_terminateLocalBlock();

		myMemoryBlock = nullptr;
		myNextPtr = myMemoryBlock;
		myAllocationSize = 0;
	}

	void LocalHeap::allocate(UI32 byteSize)
	{
		if (byteSize)
		{
			/* Issue a warning. */;
			_terminateLocalBlock();
		}

		myMemoryBlock = StaticAllocator<UI32>::allocate(byteSize);
	}

	void LocalHeap::extend(UI32 additionalSize)
	{
		auto _newPool = StaticAllocator<UI32>::allocate(myAllocationSize + additionalSize);
		DMKMemoryFunctions::moveData(_newPool.get(), myMemoryBlock.get(), myAllocationSize);

		_terminateLocalBlock();

		UI64 _oldSize = myMemoryBlock - myNextPtr;

		myMemoryBlock = _newPool;
		myNextPtr = myMemoryBlock;

		myAllocationSize += additionalSize;
		DMKMemoryFunctions::moveData(myMemoryBlock.get(), _newPool.get(), myAllocationSize);
		myNextPtr += _oldSize;
	}

	void LocalHeap::clearPool()
	{
		DMKMemoryFunctions::setData(myMemoryBlock.get(), 0, myAllocationSize);
	}

	VPTR LocalHeap::addToStore(VPTR data, UI32 byteSize)
	{
		if (myNextPtr == myMemoryBlock)
		{
			/* Issue a warning. */
			extend(myAllocationSize + byteSize);
		}

		DMKMemoryFunctions::moveData(myNextPtr.get(), data, byteSize);

		auto _tmp = myNextPtr;
		myNextPtr += byteSize;

		return _tmp.get();
	}

	void LocalHeap::deleteFromStore(VPTR data, UI32 byteSize)
	{
		DMKMemoryFunctions::setData(data, 0, byteSize);
		myNextPtr -= byteSize;
	}

	void LocalHeap::_terminateLocalBlock()
	{
		StaticAllocator<UI32>::deallocate(myMemoryBlock, myAllocationSize);
	}

}