// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/Objects/VulkanBuffer.h"

#include "VulkanBackend/Common/VulkanDevice.h"

namespace DMK
{
	namespace GraphicsCore
	{
		namespace VulkanBackend
		{
			Buffer* VulkanDevice::CreateRawBuffer(UI64 size)
			{
				// Create the Vulkan buffer and set the parent pointer.
				VulkanBuffer* pBuffer = new VulkanBuffer();
				pBuffer->SetParent(this);

				// Return the casted buffer pointer.
				return dynamic_cast<Buffer*>(pBuffer);
			}

			void VulkanDevice::DestroyBuffer(Buffer* pBuffer)
			{
				// Destroy the buffer handle.
				vkDestroyBuffer(GetLogicalDevice(), pBuffer->Inherit<VulkanBuffer>()->GetBufferHandle(), nullptr);

				// Free the allocated buffer memory.
				vkFreeMemory(GetLogicalDevice(), pBuffer->Inherit<VulkanBuffer>()->GetBufferMemory(), nullptr);

				// Delete the allocated buffer.
				delete pBuffer;
			}
		}
	}
}