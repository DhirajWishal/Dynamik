// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/Common/VulkanMemoryHandle.h"
#include "VulkanBackend/Common/Assert.h"

namespace DMK
{
	namespace VulkanBackend
	{
		void* VulkanMemoryHandle::MapToLocal(UI64 size, UI64 offset)
		{
			// Check if the size or the offset is valid. 
			if (!size || (offset > byteSize))
			{
				ErrorHandler::Logger::LogError(TEXT("Invalid size or offset to map device memory!"));
				return nullptr;
			}

			// Map the memory to the local address space. 
			void* pData = nullptr;
			DMK_VULKAN_ASSERT(vkMapMemory(GetDevice(), GetDeviceMemory(), offset, size, 0, &pData), "Failed to map device memory!");

			return pData;
		}

		void VulkanMemoryHandle::UnmapMemory()
		{
			// Unmap the mapped memory. 
			vkUnmapMemory(GetDevice(), GetDeviceMemory());
		}
	}
}