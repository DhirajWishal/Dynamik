// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "RenderTargetAttachment.h"

namespace DMK
{
	namespace VulkanBackend
	{
		/**
		 * Vulkan Depth Buffer object.
		 */
		class DepthBuffer : public RenderTargetAttachment {
		public:
			/**
			 * Default constructor.
			 */
			DepthBuffer() {}

			/**
			 * Default destructor.
			 */
			~DepthBuffer() {}

			/**
			 * Initialize the attachment.
			 *
			 * @param vDevice: The device in which to initialize.
			 * @param spec: The render target attachment specification.
			 * @param bufferCount: The number of images (buffers) to create.
			 * @param extent: The extent of the buffer.
			 */
			virtual void Initialize(VulkanDevice& vDevice, const GraphicsCore::RenderTargetAttachmentSpecification& spec, UI64 bufferCount, const VkExtent2D& extent) override final;

			/**
			 * Terminate the render target attachment.
			 *
			 * @param vDevice: The device in which to initialize.
			 */
			virtual void Terminate(const VulkanDevice& vDevice) override final;

			/**
			 * Get the attachment description of the attachment.
			 *
			 * @return VkAttachmentDescription structure.
			 */
			virtual VkAttachmentDescription GetAttachmentDescription() const override final;

			/**
			 * Get the attachment layout.
			 *
			 * @return VkImageLayout enum.
			 */
			virtual VkImageLayout GetAttachmentLayout() const override final;

		private:
			VkDeviceMemory vBufferMemory = VK_NULL_HANDLE;	// Vulkan buffer memory handle.
		};
	}
}