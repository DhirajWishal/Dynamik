// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Types/DataTypes.h"
#include <vulkan/vulkan.h>

namespace DMK
{
	namespace VulkanBackend
	{
		class VulkanDevice;

		/**
		 * Vulkan Command Pool object.
		 */
		class CommandPool {
		public:
			CommandPool() {}
			~CommandPool() {}

			/**
			 * Initialize the command pool.
			 *
			 * @param vLogicalDevice: The Vulkan logical device handle.
			 */
			void Initialize(VkDevice vLogicalDevice);

			/**
			 * Terminate the command pool.
			 */
			void Terminate(VkDevice vLogicalDevice);

			VkCommandPool vCommandPool = VK_NULL_HANDLE;	// Vulkan command pool handle.
			UI64 allocatedCommandBufferCount = 0;	// The number of allocated command buffer count.
		};

		/**
		 * Command Buffer object.
		 * This object contains all the necessary functions a command buffer contains.
		 */
		class CommandBuffer {
		public:
			CommandBuffer() {}
			~CommandBuffer() {}

			/**
			 * Set the command buffer handle.
			 *
			 * @param vCommandBuffer: The command buffer handle.
			 */
			void SetBuffer(const VkCommandBuffer& vCommandBuffer) { this->vCommandBuffer = vCommandBuffer; }

			/**
			 * Begin recordning commands.
			 *
			 * @param vInheritanceInfo: The command buffer to inherit this buffer from.
			 */
			void BeginRecording(VkCommandBufferInheritanceInfo vInheritanceInfo = {});

			/**
			 * End command buffer recording.
			 */
			void EndRecording();

			/**
			 * Reset the commands recorded in this command buffer.
			 */
			void Reset();

			/**
			 * Set a new layout to a image.
			 *
			 * @param vImage: The image to set the layout.
			 * @param mipLevel: The mip map level.
			 * @param layerCount: The number of layers in the image.
			 * @param vFormat: The image format.
			 * @param vOldLayout: The old layout of the image.
			 * @param vNewLayout: The new layout to be set.
			 */
			void SetImageLayout(const VkImage& vImage, UI32 mipLevel, UI32 layerCount, VkFormat vFormat, VkImageLayout vOldLayout, VkImageLayout vNewLayout);

			/**
			 * Copy buffer data from source to destination.
			 *
			 * @param vSrcBuffer: The source buffer.
			 * @param vDstBuffer: The destination buffer.
			 * @param vBufferCopy: The buffer copy information structure.
			 */
			void CopyBuffer(const VkBuffer& vSrcBuffer, const VkBuffer& vDstBuffer, const VkBufferCopy& vBufferCopy);

			VkCommandBuffer vCommandBuffer = VK_NULL_HANDLE;	// Vulkan command buffer handle.
			UI64 commandPoolIndex = 0;	// The index of the command pool.
		};
	}
}