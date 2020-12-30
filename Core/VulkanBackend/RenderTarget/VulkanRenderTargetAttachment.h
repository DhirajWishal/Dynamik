// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GraphicsCore/Backend/RenderTarget.h"
#include <vulkan/vulkan.h>

namespace DMK
{
	namespace VulkanBackend
	{
		class VulkanDevice;

		class VulkanRenderTargetAttachment {
		public:
			VulkanRenderTargetAttachment(UI8 flag) : mAttachmentFlag(flag) {}
			virtual ~VulkanRenderTargetAttachment() {}

			virtual void Initialize(VulkanDevice* pDevice, Vector2 extent, UI32 bufferCount) {}
			virtual void Terminate(VulkanDevice* pDevice) {}

			virtual VkAttachmentDescription GetAttachmentDescription() const { return VkAttachmentDescription(); }
			virtual VkImageLayout GetAttachmentLayout() const { return VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED; }

		public:
			UI8 GetAttachmentFlag() const { return mAttachmentFlag; }

		protected:
			std::vector<VkImage> vImages;
			std::vector<VkImageView> vImageViews;

			VkFormat vFormat = VkFormat::VK_FORMAT_UNDEFINED;

			UI8 mAttachmentFlag = 0;
		};
	}
}