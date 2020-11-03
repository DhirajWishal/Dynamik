// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_BACKEND_BUFFER_H
#define _DYNAMIK_VULKAN_BACKEND_BUFFER_H

#include "VulkanBackend/Common/VulkanObject.h"

namespace DMK
{
	namespace GraphicsCore
	{
		namespace VulkanBackend
		{
			/**
			 * Vulkan Buffer object.
			 * This is the base class for all the buffers in Vulkan.
			 */
			class VulkanBuffer : public VulkanObject {
			public:
				/**
				 * Default constructor.
				 */
				VulkanBuffer() {}

				/**
				 * Default destructor.
				 */
				virtual ~VulkanBuffer() {}

				/**
				 * Set the buffer handle of the vertex buffer.
				 *
				 * @param vBuffer: The buffer handle to be set.
				 */
				void SetBufferHandle(VkBuffer vBuffer) { this->vBuffer = vBuffer; }

				/**
				 * Get the Vulkan buffer handle.
				 *
				 * @return: The Vulkan buffer handle.
				 */
				VkBuffer GetBufferHandle() const { return vBuffer; }

				/**
				 * Set the buffer memory of the vertex buffer.
				 *
				 * @param vDeviceMemory: The Vulkan device memory handle.
				 */
				void SetBufferMemory(VkDeviceMemory vDeviceMemory) { this->vDeviceMemory = vDeviceMemory; }

				/**
				 * Get the Vulkan buffer memory handle.
				 *
				 * @return: The Vulkan device memory handle.
				 */
				VkDeviceMemory GetBufferMemory() const { return vDeviceMemory; }

			private:
				VkBuffer vBuffer = VK_NULL_HANDLE;	// Vulkan buffer handle.
				VkDeviceMemory vDeviceMemory = VK_NULL_HANDLE;	// Vulkan device memory handle.
			};
		}
	}
}

#endif // !_DYNAMIK_VULKAN_BACKEND_BUFFER_H
