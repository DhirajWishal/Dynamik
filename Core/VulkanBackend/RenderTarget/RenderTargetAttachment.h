// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GraphicsCore/Backend/RenderTargetHandle.h"

#include <vulkan/vulkan.h>
#include <vector>

namespace DMK
{
	namespace VulkanBackend
	{
		class VulkanDevice;

		/**
		 * Render Target Attachment object.
		 * This object is the base class for all the render target attachments.
		 */
		class RenderTargetAttachment {
		public:
			/**
			 * Default constructor.
			 */
			RenderTargetAttachment() {}

			/**
			 * Default destructor.
			 */
			virtual ~RenderTargetAttachment() {}

			/**
			 * Initialize the attachment.
			 *
			 * @param vDevice: The device in which to initialize.
			 * @param spec: The render target attachment specification.
			 */
			virtual void Initialize(VulkanDevice& vDevice, const GraphicsCore::RenderTargetAttachmentSpecification& spec) {}

			/**
			 * Terminate the render target attachment.
			 *
			 * @param vDevice: The device in which to initialize.
			 */
			virtual void Terminate(const VulkanDevice& vDevice) {}

			GraphicsCore::RenderTargetAttachmentSpecification mSpecification = {};	// Attachment specification.

			std::vector<VkImage> vImages;	// Vulkan Image handles.
			std::vector<VkImageView> vImageViews;	// Vulkan Image Views.

			VkFormat vFormat = VkFormat::VK_FORMAT_UNDEFINED;	// Format of the render target image.
			UI32 mBufferCount = 0;	// The number of elements in the buffer.
		};
	}
}