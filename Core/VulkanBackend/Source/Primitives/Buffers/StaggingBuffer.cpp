// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/Primitives/Buffers/StaggingBuffer.h"
#include "VulkanBackend/Common/VulkanDevice.h"

namespace DMK
{
	namespace VulkanBackend
	{
		void StaggingBuffer::Initialize(GraphicsCore::Device* pDevice, UI64 size)
		{
			vBuffer = CreateBuffer(pDevice->Derive<VulkanDevice>()->GetLogicalDevice(), size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT);
			vBufferMemory = CreateBufferMemory(pDevice->Derive<VulkanDevice>()->GetLogicalDevice(), pDevice->Derive<VulkanDevice>()->GetPhysicalDevice(), vBuffer, VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
		}

		void* StaggingBuffer::MapMemory(GraphicsCore::Device* pDevice, UI64 size, UI64 offset)
		{
			// Check if the size and/ or offset is valid.
			if (size >= mSize || (size + offset) >= mSize)
			{
				Logger::LogError(TEXT("Invalid size or offset to map buffer memory!"));
				return nullptr;
			}

			void* pData = nullptr;
			DMK_VK_ASSERT(vkMapMemory(pDevice->Derive<VulkanDevice>()->GetLogicalDevice(), vBufferMemory, offset, size, 0, &pData), "Failed to map buffer memory!");

			return pData;
		}

		void StaggingBuffer::UnmapMemory(GraphicsCore::Device* pDevice)
		{
			vkUnmapMemory(pDevice->Derive<VulkanDevice>()->GetLogicalDevice(), vBufferMemory);
		}
	}
}