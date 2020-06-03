#include "dmkafx.h"
#include "AttachmentManager.h"

#include "GameLibrary/Attachments/BasicAttachments.h"

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
		UI32 _attachmentSize = 0;
		switch (attachment->attachmentType)
		{
		case Dynamik::DMKGameAssetAttachmentType::DMK_GAME_ASSET_ATTACHMENT_TYPE_TRANSFORM:
			_attachmentSize = sizeof(TransformAttachment);
			break;
		case Dynamik::DMKGameAssetAttachmentType::DMK_GAME_ASSET_ATTACHMENT_TYPE_SCALE:
			_attachmentSize = sizeof(ScaleAttachment);
			break;
		case Dynamik::DMKGameAssetAttachmentType::DMK_GAME_ASSET_ATTACHMENT_TYPE_MATERIAL:
			break;
			_attachmentSize = sizeof(MaterialAttachment);
		default:
			DMK_ERROR_BOX("Invalid Game Asset Attachment Type!");
			break;
		}

		_allocateHeap(_attachmentSize);

		DMKAttachmentMap _newMap;
		_newMap.type = attachment->attachmentType;
		_newMap.location = myNextPtr.get();
		_newMap.byteSize = _attachmentSize;
		myAttachmentMapping.pushBack(_newMap);

		MemoryFunctions::moveData(myNextPtr.get(), attachment.get(), _attachmentSize);
		myNextPtr += _attachmentSize;
	}

	const VPTR DMKAttachmentManager::getBuffer() const
	{
		return myMemoryBuffer;
	}

	const ARRAY<DMKAttachmentMap> DMKAttachmentManager::getAttachments() const
	{
		return myAttachmentMapping;
	}

	const POINTER<DMKAttachmentMap> DMKAttachmentManager::begin() const noexcept
	{
		return myAttachmentMapping.begin();
	}

	const POINTER<DMKAttachmentMap> DMKAttachmentManager::end() const noexcept
	{
		return myAttachmentMapping.end();
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
			myAllocationSize += byteSize;

			_recreateMappings();
		}
		else
		{
			myMemoryBuffer = StaticAllocator<BYTE>::allocate(byteSize);
			myNextPtr = myMemoryBuffer;
			myAllocationSize = byteSize;
		}
	}

	inline void DMKAttachmentManager::_recreateMappings()
	{
		for (UI32 i = 0; i < myAttachmentMapping.size(); i++)
		{
			myAttachmentMapping[i].location = myNextPtr.get();
			myNextPtr += myAttachmentMapping[i].byteSize;
		}
	}
}