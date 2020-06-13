// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanBuffer.h"

#include "../Common/VulkanUtilities.h"

namespace Dynamik
{
	namespace Backend
	{
		void VulkanBuffer::initialize(const VulkanDevice& vDevice, BufferType type, UI32 bufferSize, ResourceMemoryType memoryType)
		{
			size = bufferSize;
			VkBufferCreateInfo bufferInfo = {};
			bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
			bufferInfo.size = bufferSize;

			switch (type)
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

			DMK_VULKAN_ASSERT(vkCreateBuffer(vDevice, &bufferInfo, nullptr, &buffer), "Failed to create buffer!");

			VkMemoryRequirements memRequirements;
			vkGetBufferMemoryRequirements(vDevice, buffer, &memRequirements);

			VkMemoryAllocateInfo allocInfo = {};
			allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
			allocInfo.allocationSize = memRequirements.size;
			allocInfo.memoryTypeIndex = VulkanUtilities::findMemoryType(memRequirements.memoryTypeBits, (VkMemoryPropertyFlags)memoryType,
				vDevice);

			DMK_VULKAN_ASSERT(vkAllocateMemory(vDevice, &allocInfo, nullptr, &bufferMemory), "Failed to allocate buffer memory!");

			vkBindBufferMemory(vDevice, buffer, bufferMemory, 0);
		}

		void VulkanBuffer::terminate(const VulkanDevice& vDevice)
		{
			vkDestroyBuffer(vDevice, buffer, nullptr);
			vkFreeMemory(vDevice, bufferMemory, nullptr);
		}

		VPTR VulkanBuffer::mapMemory(const VulkanDevice& vDevice, UI32 offset)
		{
			VPTR data = nullptr;
			DMK_VULKAN_ASSERT(vkMapMemory(vDevice, bufferMemory, offset, size, VK_NULL_HANDLE, &data), "Unable to map the buffer memory!");
			return data;
		}

		void VulkanBuffer::unmapMemory(const VulkanDevice& vDevice)
		{
			vkUnmapMemory(vDevice, bufferMemory);
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