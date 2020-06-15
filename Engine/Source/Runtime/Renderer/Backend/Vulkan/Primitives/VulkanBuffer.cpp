// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanBuffer.h"

#include "../VulkanUtilities.h"

namespace Dynamik
{
	namespace Backend
	{
		void VulkanBuffer::initialize(POINTER<RCoreObject> pCoreObject, BufferType eType, UI64 uSize, ResourceMemoryType memoryType)
		{
			size = uSize;
			VkBufferCreateInfo bufferInfo = {};
			bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
			bufferInfo.size = uSize;

			type = eType;
			switch (eType)
			{
			case Dynamik::BufferType::BUFFER_TYPE_STAGGING:
				bufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
				break;
			case Dynamik::BufferType::BUFFER_TYPE_VERTEX:
				bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
				break;
			case Dynamik::BufferType::BUFFER_TYPE_INDEX:
				bufferInfo.usage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
				break;
			case Dynamik::BufferType::BUFFER_TYPE_UNIFORM:
				bufferInfo.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
				break;
			case Dynamik::BufferType::BUFFER_TYPE_INDIRECT:
				bufferInfo.usage = VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT;
				break;
			case Dynamik::BufferType::BUFFER_TYPE_RAY_TRACING:
				bufferInfo.usage = VK_BUFFER_USAGE_RAY_TRACING_BIT_NV;
				break;
			default:
				DMK_ERROR_BOX("Invalid buffer type!");
				break;
			}

			bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

			DMK_VULKAN_ASSERT(vkCreateBuffer(InheritCast<VulkanCoreObject>(pCoreObject).device, &bufferInfo, nullptr, &buffer), "Failed to create buffer!");

			VkMemoryRequirements memRequirements;
			vkGetBufferMemoryRequirements(InheritCast<VulkanCoreObject>(pCoreObject).device, buffer, &memRequirements);

			VkMemoryAllocateInfo allocInfo = {};
			allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
			allocInfo.allocationSize = memRequirements.size;
			allocInfo.memoryTypeIndex = VulkanUtilities::findMemoryType(memRequirements.memoryTypeBits, (VkMemoryPropertyFlags)memoryType,
				InheritCast<VulkanCoreObject>(pCoreObject).device);

			DMK_VULKAN_ASSERT(vkAllocateMemory(InheritCast<VulkanCoreObject>(pCoreObject).device, &allocInfo, nullptr, &bufferMemory), "Failed to allocate buffer memory!");

			vkBindBufferMemory(InheritCast<VulkanCoreObject>(pCoreObject).device, buffer, bufferMemory, 0);
		}

		void VulkanBuffer::terminate(POINTER<RCoreObject> pCoreObject)
		{
			vkDestroyBuffer(InheritCast<VulkanCoreObject>(pCoreObject).device, buffer, nullptr);
			vkFreeMemory(InheritCast<VulkanCoreObject>(pCoreObject).device, bufferMemory, nullptr);
		}

		void VulkanBuffer::setData(POINTER<RCoreObject> pCoreObject, UI64 uSize, UI64 offset, VPTR data)
		{
			VPTR myData = getData(pCoreObject, uSize, offset);
			DMKMemoryFunctions::moveData(myData, data, uSize);
			unmapMemory(pCoreObject);
		}

		VPTR VulkanBuffer::getData(POINTER<RCoreObject> pCoreObject, UI64 size, UI64 offset)
		{
			VPTR data = nullptr;
			DMK_VULKAN_ASSERT(vkMapMemory(InheritCast<VulkanCoreObject>(pCoreObject).device, bufferMemory, offset, size, VK_NULL_HANDLE, &data), "Unable to map the buffer memory!");
			return data;
		}

		void VulkanBuffer::unmapMemory(POINTER<RCoreObject> pCoreObject)
		{
			vkUnmapMemory(InheritCast<VulkanCoreObject>(pCoreObject).device, bufferMemory);
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