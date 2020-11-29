// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "RenderTargetAttachment.h"

namespace DMK
{
	namespace VulkanBackend
	{
		/**
		 * Color Buffer object.
		 * This obect stores color images for the render target.
		 */
		class ColorBuffer : public RenderTargetAttachment {
		public:
			/**
			 * Default constructor.
			 */
			ColorBuffer() {}

			/**
			 * Default destructor.
			 */
			~ColorBuffer() {}

			/**
			 * Initialize the attachment.
			 *
			 * @param vDevice: The device in which to initialize.
			 * @param spec: The render target attachment specification.
			 */
			virtual void Initialize(VulkanDevice& vDevice, const GraphicsCore::RenderTargetAttachmentSpecification& spec) override final;

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