// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/Objects/VulkanVertexBuffer.h"
#include "Core/ErrorHandler/Logger.h"
#include "VulkanBackend/Common/Macros.h"

#include "VulkanBackend/Common/VulkanDevice.h"

namespace DMK
{
	namespace GraphicsCore
	{
		namespace VulkanBackend
		{
			VertexBuffer* VulkanDevice::CreateVertexBuffer(const Vertex& vertex, UI64 vertexCount)
			{
				return nullptr;
			}

			void* VulkanVertexBuffer::MapToLocal(UI64 size, UI64 offset)
			{
				// Validate the mapping arguments.
				if (!size || (offset >= GetSize()))
				{
					Logger::LogError(TEXT("Invalid size or offset to map the Vertex Buffer!"));
					return nullptr;
				}

				// Map the buffer memory to the local address space.
				void* pLocalAddress = nullptr;
				DMK_VK_ASSERT(vkMapMemory(GetParent()->GetLogicalDevice(), GetBufferMemory(), offset, size, 0, &pLocalAddress), "Failed to map Vertex Buffer memory to the local address space!");

				return pLocalAddress;
			}

			void VulkanVertexBuffer::UnmapFromLocal()
			{
				vkUnmapMemory(GetParent()->GetLogicalDevice(), GetBufferMemory());
			}

			void VulkanVertexBuffer::CopyFrom(Buffer* pBuffer)
			{
				VkBufferCopy vCopy = {};
				vCopy.dstOffset = 0;
				vCopy.size = pBuffer->GetSize();
				vCopy.srcOffset = 0;

				// Copy the buffer.
				vkCmdCopyBuffer(GetParent()->CreateOneTimeCommandBuffer(), pBuffer->Inherit<VulkanVertexBuffer>()->GetBufferHandle(), GetBufferHandle(), 1, &vCopy);
			}

			void VulkanVertexBuffer::MoveFrom(Buffer* pBuffer)
			{
			}
		}
	}
}