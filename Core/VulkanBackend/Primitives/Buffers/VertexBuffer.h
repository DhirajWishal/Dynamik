// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "VulkanBuffer.h"

namespace DMK
{
	namespace VulkanBackend
	{
		/**
		 * Vulkan Vertex Buffer object.
		 * This object stores vertex information.
		 */
		class VertexBuffer : public VulkanBuffer {
		public:
			VertexBuffer() : VulkanBuffer(GraphicsCore::BufferType::VERTEX) {}
			~VertexBuffer() {}

			virtual void Initialize(GraphicsCore::Device* pDevice, UI64 size) override final;

			virtual void* MapMemory(GraphicsCore::Device* pDevice, UI64 size, UI64 offset = 0) override final;
			virtual void UnmapMemory(GraphicsCore::Device* pDevice) override final;
		};
	}
}