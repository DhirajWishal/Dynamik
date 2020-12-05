// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Buffers/IndexBuffer.h"
#include "Buffers/UniformBuffer.h"
#include "Buffers/StaggingBuffer.h"

namespace DMK
{
	namespace VulkanBackend
	{
		/**
		 * Vulkan Buffer Manager object.
		 * This object is responsible for managing buffers created by the device. The main purpose of this is to manage
		 * index buffer data, vertex buffer data and to create other buffers such as Stagging and Uniform.
		 */
		class BufferManager {
		public:
			BufferManager() {}
			~BufferManager() {}
		};
	}
}