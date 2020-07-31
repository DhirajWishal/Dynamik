// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanBuffer.h"

#include "../VulkanUtilities.h"
#include "../Common/VulkanOneTimeCommandBuffer.h"

namespace Dynamik
{
	namespace Backend
	{
		void VulkanBuffer::initialize(RCoreObject* pCoreObject, RBufferType eType, UI64 uSize, RResourceMemoryType memoryType)
		{
			size = uSize;
			type = eType;

			VkBufferCreateInfo bufferInfo = {};
			bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
			bufferInfo.size = uSize;

			switch (eType)
			{
			case Dynamik::RBufferType::BUFFER_TYPE_STAGGING:
				bufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
				break;
			case Dynamik::RBufferType::BUFFER_TYPE_VERTEX:
				bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
				break;
			case Dynamik::RBufferType::BUFFER_TYPE_INDEX:
				bufferInfo.usage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
				break;
			case Dynamik::RBufferType::BUFFER_TYPE_UNIFORM:
				bufferInfo.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
				break;
			case Dynamik::RBufferType::BUFFER_TYPE_INDIRECT:
				bufferInfo.usage = VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
				break;
			case Dynamik::RBufferType::BUFFER_TYPE_RAY_TRACING:
				bufferInfo.usage = VK_BUFFER_USAGE_RAY_TRACING_BIT_NV | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
				break;
			default:
				DMK_ERROR_BOX("Invalid buffer type!");
				break;
			}

			bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

			DMK_VULKAN_ASSERT(vkCreateBuffer(Inherit<VulkanCoreObject>(pCoreObject)->device, &bufferInfo, nullptr, &buffer), "Failed to create buffer!");

			VkMemoryRequirements memRequirements;
			vkGetBufferMemoryRequirements(Inherit<VulkanCoreObject>(pCoreObject)->device, buffer, &memRequirements);

			VkMemoryAllocateInfo allocInfo = {};
			allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
			allocInfo.allocationSize = memRequirements.size;
			allocInfo.memoryTypeIndex = VulkanUtilities::findMemoryType(memRequirements.memoryTypeBits, (VkMemoryPropertyFlags)memoryType,
				Inherit<VulkanCoreObject>(pCoreObject)->device);

			DMK_VULKAN_ASSERT(vkAllocateMemory(Inherit<VulkanCoreObject>(pCoreObject)->device, &allocInfo, nullptr, &bufferMemory), "Failed to allocate buffer memory!");

			vkBindBufferMemory(Inherit<VulkanCoreObject>(pCoreObject)->device, buffer, bufferMemory, 0);
		}

		void VulkanBuffer::terminate(RCoreObject* pCoreObject)
		{
			vkDestroyBuffer(Inherit<VulkanCoreObject>(pCoreObject)->device, buffer, nullptr);
			vkFreeMemory(Inherit<VulkanCoreObject>(pCoreObject)->device, bufferMemory, nullptr);
		}

		void VulkanBuffer::copy(RCoreObject* pCoreObject, RBuffer* pSrcBuffer, UI64 size, UI64 srcOffset, UI64 dstOffset)
		{
			if ((size > this->size) || (srcOffset > pSrcBuffer->getSize()) || (dstOffset > this->size))
			{
				DMK_ERROR("An argument submitted to copy a buffer is invalid!");
				return;
			}

			VulkanOneTimeCommandBuffer commandBuffer(pCoreObject);

			VkBufferCopy copyRegion = {};
			copyRegion.size = size;
			copyRegion.srcOffset = srcOffset;
			copyRegion.dstOffset = dstOffset;

			vkCmdCopyBuffer(commandBuffer, InheritCast<VulkanBuffer>(pSrcBuffer), buffer, 1, &copyRegion);
		}

		void VulkanBuffer::setData(RCoreObject* pCoreObject, UI64 uSize, UI64 offset, VPTR data)
		{
			if (uSize > size)
			{
				DMK_ERROR("The size submitted to update the buffer is larger than the allocated size!");
				return;
			}

			VPTR myData = getData(pCoreObject, uSize, offset);
			DMKMemoryFunctions::copyData(myData, data, uSize);
			unmapMemory(pCoreObject);
		}

		VPTR VulkanBuffer::getData(RCoreObject* pCoreObject, UI64 size, UI64 offset)
		{
			if (size > this->size)
			{
				DMK_ERROR("The size submitted to map the buffer is larger than the allocated size!");
				return nullptr;
			}

			VPTR data = nullptr;
			DMK_VULKAN_ASSERT(vkMapMemory(Inherit<VulkanCoreObject>(pCoreObject)->device, bufferMemory, offset, size, VK_NULL_HANDLE, &data), "Unable to map the buffer memory!");
			return data;
		}

		void VulkanBuffer::unmapMemory(RCoreObject* pCoreObject)
		{
			vkUnmapMemory(Inherit<VulkanCoreObject>(pCoreObject)->device, bufferMemory);
		}

		void VulkanBuffer::flushMemory(RCoreObject* pCoreObject)
		{
			if (!bufferMemory)
				return;

			VkMappedMemoryRange range = {};
			range.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
			range.pNext = VK_NULL_HANDLE;
			range.memory = bufferMemory;
			range.offset = 0;
			range.size = VK_WHOLE_SIZE;

			vkFlushMappedMemoryRanges(Inherit<VulkanCoreObject>(pCoreObject)->device, 1, &range);
		}

		VkDescriptorBufferInfo VulkanBuffer::createDescriptorInfo(UI32 offset)
		{
			VkDescriptorBufferInfo _info;
			_info.buffer = buffer;
			_info.range = size;
			_info.offset = offset;

			return _info;
		}

		VulkanBuffer::operator VkBuffer() const
		{
			return this->buffer;
		}

		VulkanBuffer::operator VkDeviceMemory() const
		{
			return this->bufferMemory;
		}
	}
}