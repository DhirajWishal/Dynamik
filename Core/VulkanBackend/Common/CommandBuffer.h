// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "VulkanDevice.h"

namespace DMK
{
	namespace VulkanBackend
	{
		/**
		 * Command Buffer object.
		 * This object contains all the necessary functions a command buffer contains.
		 */
		class CommandBuffer {
		public:
			/**
			 * Default constructor.
			 */
			CommandBuffer() {}

			/**
			 * Default destructor.
			 */
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

		private:
			VkCommandBuffer vCommandBuffer = VK_NULL_HANDLE;	// Vulkan command buffer handle.
		};
	}
}