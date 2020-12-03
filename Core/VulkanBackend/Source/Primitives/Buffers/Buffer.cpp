// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/Primitives/Buffers/Buffer.h"
#include "VulkanBackend/Common/VulkanDevice.h"
#include "VulkanBackend/Common/Utilities.h"

#include "VulkanBackend/Primitives/Buffers/StaggingBuffer.h"
#include "Core/Memory/Functions.h"

namespace DMK
{
	namespace VulkanBackend
	{
		void Buffer::Terminate(const VulkanDevice& vDevice)
		{
			// Check if the size, buffer and buffer memory are valid.
			if (!mSize || vBuffer == VK_NULL_HANDLE || vBufferMemory == VK_NULL_HANDLE)
				return;

			vkDestroyBuffer(vDevice, vBuffer, nullptr);
			vkFreeMemory(vDevice, vBufferMemory, nullptr);
		}

		void Buffer::CopyData(const VulkanDevice& vDevice, const void* pData, UI64 size, UI64 offset)
		{
			// Check if the size, buffer and buffer memory are valid.
			if (!mSize || !size || (size + offset) > mSize || !vBuffer || !vBufferMemory)
				return;

			auto pDataStore = MapMemory(vDevice, size, offset);
			MemoryFunctions::CopyData(pDataStore, pData, size);
			UnmapMemory(vDevice);
		}

		void Buffer::MoveData(const VulkanDevice& vDevice, const void* pData, UI64 size, UI64 offset)
		{
			// Check if the size, buffer and buffer memory are valid.
			if (!mSize || !size || (size + offset) > mSize || !vBuffer || !vBufferMemory)
				return;

			auto pDataStore = MapMemory(vDevice, size, offset);
			MemoryFunctions::MoveData(pDataStore, pData, size);
			UnmapMemory(vDevice);
		}

		void Buffer::Extend(const VulkanDevice& vDevice, UI64 size)
		{
			// Check if the buffer was allocated before.
			if (mSize && vBuffer && vBufferMemory)
			{
				// Create the stagging buffer, initialize it and move data to it.
				StaggingBuffer vStaggingBuffer = {};
				vStaggingBuffer.Initialize(vDevice, mSize);
				vStaggingBuffer.MoveData(vDevice, this->MapMemory(vDevice, mSize, 0), mSize, 0);
				this->UnmapMemory(vDevice);

				// Terminate the old buffer.
				Terminate(vDevice);

				// Initialize the buffer to the new size.
				Initialize(vDevice, mSize + size);

				// Copy data from the stagging buffer to this buffer.
				MoveData(vDevice, vStaggingBuffer.MapMemory(vDevice, mSize, 0), mSize, 0);
				vStaggingBuffer.UnmapMemory(vDevice);

				// Terminate the stagging buffer.
				vStaggingBuffer.Terminate(vDevice);
			}
			else
			{
				// Terminate the old buffer.
				Terminate(vDevice);

				// Initialize the buffer to the new size.
				Initialize(vDevice, mSize + size);
			}

			mSize += size;
		}

		VkBuffer Buffer::CreateBuffer(const VulkanDevice& vDevice, UI64 size, VkBufferUsageFlags usageFlags)
		{
			// Check if the size is valid.
			if (!size)
			{
				Logger::LogError(TEXT("Invalid size submitted to create the buffer!"));
				return VkBuffer();
			}

			VkBufferCreateInfo vBufferCI = {};
			vBufferCI.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
			vBufferCI.flags = VK_NULL_HANDLE;
			vBufferCI.pNext = VK_NULL_HANDLE;
			vBufferCI.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
			vBufferCI.size = static_cast<UI32>(size);
			vBufferCI.usage = usageFlags;

			VkBuffer vBuffer = VK_NULL_HANDLE;
			DMK_VK_ASSERT(vkCreateBuffer(vDevice, &vBufferCI, nullptr, &vBuffer), "Failed to create Vulkan Buffer!");

			return vBuffer;
		}

		VkDeviceMemory Buffer::CreateBufferMemory(const VulkanDevice& vDevice, VkBuffer vBuffer, VkMemoryPropertyFlags memoryProperties)
		{
			VkMemoryRequirements memRequirements = {};
			vkGetBufferMemoryRequirements(vDevice, vBuffer, &memRequirements);

			VkMemoryAllocateInfo allocInfo = {};
			allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
			allocInfo.allocationSize = memRequirements.size;
			allocInfo.memoryTypeIndex = Utilities::FindMemoryType(memRequirements.memoryTypeBits, memoryProperties, vDevice);

			VkDeviceMemory vBufferMemory = VK_NULL_HANDLE;
			DMK_VK_ASSERT(vkAllocateMemory(vDevice, &allocInfo, nullptr, &vBufferMemory), "Failed to allocate buffer memory!");

			DMK_VK_ASSERT(vkBindBufferMemory(vDevice, vBuffer, vBufferMemory, 0), "Failed to bind buffer memory!");

			return vBufferMemory;
		}
	}
}