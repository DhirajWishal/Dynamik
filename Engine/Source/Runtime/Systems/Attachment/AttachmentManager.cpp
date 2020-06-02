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

	void DMKAttachmentManager::addAttachment(POINTER<DMKGameAssetAttachment> attachment)
	{
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

			_recreateReferenceTable();
		}
		else
		{
			myMemoryBuffer = StaticAllocator<BYTE>::allocate(byteSize);
			myNextPtr = myMemoryBuffer;
			myAllocationSize = byteSize;
		}
	}

	inline void DMKAttachmentManager::_recreateReferenceTable()
	{
		UI64 _oldAddress = 0;
		POINTER<BYTE> _newLocation = myMemoryBuffer;
		for (auto _elem : myReferenceTable)
		{
			if (_oldAddress)
			{
				UI64 _newOffset = _elem.second.getAddressAsInteger() - _oldAddress;
				_oldAddress = _elem.second.getAddressAsInteger();
				_newLocation += _newOffset;
			}

			myReferenceTable.try_emplace(_elem.first, _newLocation);
		}
	}
}