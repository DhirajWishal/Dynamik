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
			 * Get the render attachment type.
			 * 
			 * @return GraphicsCore::RenderTargetAttachmentType enum.
			 */
			GraphicsCore::RenderTargetAttachmentType GetAttachmentType() const { return mSpecification.type; }

			/**
			 * Initialize the attachment.
			 *
			 * @param vDevice: The device in which to initialize.
			 * @param spec: The render target attachment specification.
			 * @param bufferCount: The number of images (buffers) to create.
			 * @param extent: The extent of the buffer.
			 */
			virtual void Initialize(VulkanDevice& vDevice, const GraphicsCore::RenderTargetAttachmentSpecification& spec, UI64 bufferCount, const VkExtent2D& extent) {}

			/**
			 * Terminate the render target attachment.
			 *
			 * @param vDevice: The device in which to initialize.
			 */
			virtual void Terminate(const VulkanDevice& vDevice) {}

			/**
			 * Get the attachment description of the attachment.
			 *
			 * @return VkAttachmentDescription structure.
			 */
			virtual VkAttachmentDescription GetAttachmentDescription() const { return VkAttachmentDescription(); }

			/**
			 * Get the attachment layout.
			 *
			 * @return VkImageLayout enum.
			 */
			virtual VkImageLayout GetAttachmentLayout() const { return VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED; }

			GraphicsCore::RenderTargetAttachmentSpecification mSpecification = {};	// Attachment specification.

			std::vector<VkImage> vImages;	// Vulkan Image handles.
			std::vector<VkImageView> vImageViews;	// Vulkan Image Views.

			VkFormat vFormat = VkFormat::VK_FORMAT_UNDEFINED;	// Format of the render target image.
			VkSampleCountFlags vSampleCount = VK_SAMPLE_COUNT_64_BIT;	// MSAA sample count.
			UI32 mBufferCount = 0;	// The number of elements in the buffer.
		};
	}
}