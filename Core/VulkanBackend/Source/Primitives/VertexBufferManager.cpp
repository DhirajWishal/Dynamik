// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/Primitives/VertexBufferManager.h"
#include "VulkanBackend/Common/VulkanDevice.h"

namespace DMK
{
	namespace VulkanBackend
	{
		GraphicsCore::BufferHandle VertexBufferManager::TryCreateBuffer(const VulkanDevice& vDevice, GraphicsCore::VertexBufferObject&& vertexBuffer)
		{
			// Check if the buffer layout is available. If not, create a new buffer and register the layout.
			if (mBufferMap.find(vertexBuffer.LayoutHash()) != mBufferMap.end())
				return CreateNewBuffer(vDevice, std::move(vertexBuffer));
			else
				return ExtendInsert(vDevice, std::move(vertexBuffer), &mBufferMap[vertexBuffer.LayoutHash()]);

			return GraphicsCore::BufferHandle(GraphicsCore::BufferType::VERTEX, 0, 0);
		}

		GraphicsCore::BufferHandle VertexBufferManager::CreateNewBuffer(const VulkanDevice& vDevice, GraphicsCore::VertexBufferObject&& vertexBuffer)
		{
			auto hash = vertexBuffer.LayoutHash();
			auto size = vertexBuffer.Size();

			auto pBuffer = &mBufferMap[hash];
			pBuffer->Initialize(vDevice, size);
			pBuffer->MoveData(vDevice, vertexBuffer.Data(), pBuffer->Size());

			vertexBuffer.Terminate();

			return GraphicsCore::BufferHandle(GraphicsCore::BufferType::VERTEX, hash, size);
		}

		GraphicsCore::BufferHandle VertexBufferManager::ExtendInsert(const VulkanDevice& vDevice, GraphicsCore::VertexBufferObject&& vertexBuffer, VertexBuffer* pBuffer)
		{
			auto hash = vertexBuffer.LayoutHash();
			auto size = vertexBuffer.Size();
			auto oldSize = pBuffer->Size();

			pBuffer->Extend(vDevice, vertexBuffer.Size());
			pBuffer->MoveData(vDevice, vertexBuffer.Data(), size, oldSize);

			vertexBuffer.Terminate();

			return GraphicsCore::BufferHandle(GraphicsCore::BufferType::VERTEX, hash, size, oldSize);
		}
	}
}