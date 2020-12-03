// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/Primitives/VertexBufferManager.h"
#include "VulkanBackend/Common/VulkanDevice.h"

namespace DMK
{
	namespace VulkanBackend
	{
		GraphicsCore::VertexBufferHandle VertexBufferManager::TryCreateBuffer(const VulkanDevice& vDevice, GraphicsCore::VertexBufferObject&& vertexBuffer)
		{
			return GraphicsCore::VertexBufferHandle();
		}
	}
}