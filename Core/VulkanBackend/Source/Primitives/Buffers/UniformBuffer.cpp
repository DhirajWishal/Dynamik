// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/Primitives/Buffers/UniformBuffer.h"
#include "VulkanBackend/Common/VulkanDevice.h"

namespace DMK
{
	namespace VulkanBackend
	{
		void UniformBuffer::Initialize(const VulkanDevice& vDevice, UI64 size)
		{
			vBuffer = CreateBuffer(vDevice, size, VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT);
			vBufferMemory = CreateBufferMemory(vDevice, vBuffer, VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
		}

		void* UniformBuffer::MapMemory(const VulkanDevice& vDevice, UI64 size, UI64 offset)
		{
			// Check if the size and/ or offset is valid.
			if (size >= mSize || (size + offset) >= mSize)
			{
				Logger::LogError(TEXT("Invalid size or offset to map buffer memory!"));
				return nullptr;
			}

			void* pData = nullptr;
			DMK_VK_ASSERT(vkMapMemory(vDevice, vBufferMemory, offset, size, 0, &pData), "Failed to map buffer memory!");

			return pData;
		}

		void UniformBuffer::UnmapMemory(const VulkanDevice& vDevice)
		{
			vkUnmapMemory(vDevice, vBufferMemory);
		}
	}
}