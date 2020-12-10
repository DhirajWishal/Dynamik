// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/Primitives/Buffers/VulkanBuffer.h"
#include "VulkanBackend/Common/VulkanDevice.h"
#include "VulkanBackend/Common/Utilities.h"

#include "VulkanBackend/Primitives/Buffers/StaggingBuffer.h"
#include "Core/Memory/Functions.h"

namespace DMK
{
	namespace VulkanBackend
	{
		void VulkanBuffer::Terminate(GraphicsCore::Device* pDevice)
		{
			vkDestroyBuffer(pDevice->Derive<VulkanDevice>()->GetLogicalDevice(), this->vBuffer, nullptr);
			vkFreeMemory(pDevice->Derive<VulkanDevice>()->GetLogicalDevice(), this->vBufferMemory, nullptr);
		}
		
		void VulkanBuffer::CopyBuffer(GraphicsCore::Device* pDevice, const Buffer* pBuffer)
		{
			// Check if the buffer is able to copy data to.
			if (this->mSize < pBuffer->mSize)
			{
				Logger::LogError(TEXT("The buffer size is not sufficient to copy data!"));
				return;
			}

			VkBufferCopy vCopy = {};
			vCopy.dstOffset = 0;
			vCopy.srcOffset = 0;
			vCopy.size = pBuffer->Size();

			auto vCommandBuffer = pDevice->Derive<VulkanDevice>()->CreateCommandBuffer();
			vCommandBuffer.CopyBuffer(pBuffer->Derive<VulkanBuffer>()->vBuffer, this->vBuffer, vCopy);
			pDevice->Derive<VulkanDevice>()->TerminateCommandBuffer(vCommandBuffer);
		}

		void VulkanBuffer::MoveBuffer(GraphicsCore::Device* pDevice, const Buffer* pBuffer)
		{
		}

		void VulkanBuffer::Extend(GraphicsCore::Device* pDevice, UI64 size)
		{
			// Check if the buffer was allocated before.
			if (mSize && vBuffer && vBufferMemory)
			{
				// Create the stagging buffer, initialize it and move data to it.
				StaggingBuffer vStaggingBuffer = {};
				vStaggingBuffer.Initialize(pDevice, mSize);
				vStaggingBuffer.MoveData(pDevice, this->MapMemory(pDevice, mSize, 0), mSize, 0);
				this->UnmapMemory(pDevice);

				// Terminate the old buffer.
				Terminate(pDevice);

				// Initialize the buffer to the new size.
				Initialize(pDevice, mSize + size);

				// Copy data from the stagging buffer to this buffer.
				MoveData(pDevice, vStaggingBuffer.MapMemory(pDevice, mSize, 0), mSize, 0);
				vStaggingBuffer.UnmapMemory(pDevice);

				// Terminate the stagging buffer.
				vStaggingBuffer.Terminate(pDevice);
			}
			else
			{
				// Terminate the old buffer.
				Terminate(pDevice);

				// Initialize the buffer to the new size.
				Initialize(pDevice, mSize + size);
			}

			mSize += size;
		}

		VkBuffer VulkanBuffer::CreateBuffer(VkDevice vDevice, UI64 size, VkBufferUsageFlags usageFlags)
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

		VkDeviceMemory VulkanBuffer::CreateBufferMemory(VkDevice vDevice, VkPhysicalDevice vPhysicalDevice, VkBuffer vBuffer, VkMemoryPropertyFlags memoryProperties)
		{
			VkMemoryRequirements memRequirements = {};
			vkGetBufferMemoryRequirements(vDevice, vBuffer, &memRequirements);

			VkMemoryAllocateInfo allocInfo = {};
			allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
			allocInfo.allocationSize = memRequirements.size;
			allocInfo.memoryTypeIndex = Utilities::FindMemoryType(memRequirements.memoryTypeBits, memoryProperties, vPhysicalDevice);

			VkDeviceMemory vBufferMemory = VK_NULL_HANDLE;
			DMK_VK_ASSERT(vkAllocateMemory(vDevice, &allocInfo, nullptr, &vBufferMemory), "Failed to allocate buffer memory!");

			DMK_VK_ASSERT(vkBindBufferMemory(vDevice, vBuffer, vBufferMemory, 0), "Failed to bind buffer memory!");

			return vBufferMemory;
		}
	}
}