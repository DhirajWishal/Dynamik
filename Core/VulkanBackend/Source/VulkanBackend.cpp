// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/VulkanBackend.h"

namespace DMK
{
	namespace VulkanBackend
	{
		void VulkanBackend::Initialize(const BackendInitInfo& initInfo)
		{
		}

		void VulkanBackend::Terminate()
		{
		}

		MemoryHandle* VulkanBackend::AllocateMemory(UI64 size, MemoryProperty memoryProperty)
		{
			return nullptr;
		}

		void VulkanBackend::DeallocateMemory(MemoryHandle* pMemoryHandle)
		{
		}

		Buffer* VulkanBackend::CreateRawBuffer(UI64 size, MemoryProperty memoryProperty)
		{
			return nullptr;
		}

		void VulkanBackend::DestroyBuffer(Buffer* pBuffer)
		{
		}

		VertexBuffer* VulkanBackend::CreateVertexBuffer(UI64 stride, UI64 vertexCount, MemoryProperty memoryProperty)
		{
			return nullptr;
		}

		IndexBuffer* VulkanBackend::CreateIndexBuffer(UI64 stride, UI64 vertexCount, MemoryProperty memoryProperty)
		{
			return nullptr;
		}
	}
}