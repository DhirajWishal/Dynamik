// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "VulkanBuffer.h"

namespace DMK
{
	namespace VulkanBackend
	{
		/**
		 * Vulkan Uniform Buffer object.
		 */
		class UniformBuffer : public VulkanBuffer {
		public:
			UniformBuffer() : VulkanBuffer(GraphicsCore::BufferType::UNIFORM_DATA) {}
			~UniformBuffer() {}

			virtual void Initialize(GraphicsCore::Device* pDevice, UI64 size) override final;

			virtual void* MapMemory(GraphicsCore::Device* pDevice, UI64 size, UI64 offset = 0) override final;
			virtual void UnmapMemory(GraphicsCore::Device* pDevice) override final;
		};
	}
}
