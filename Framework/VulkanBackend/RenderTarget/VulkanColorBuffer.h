// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "VulkanRenderTargetAttachment.h"

namespace DMK
{
	namespace VulkanBackend
	{
		class VulkanColorBuffer final : public VulkanRenderTargetAttachment {
		public:
			VulkanColorBuffer() : VulkanRenderTargetAttachment(DMK_RT_COLOR_BUFFER_ATTACHMENT) {}
			~VulkanColorBuffer() {}

			virtual void Initialize(VulkanDevice* pDevice, Vector2 extent, UI32 bufferCount) override final;
			virtual void Terminate(VulkanDevice* pDevice) override final;

			virtual VkAttachmentDescription GetAttachmentDescription() const override final;
			virtual VkImageLayout GetAttachmentLayout() const override final;

		private:
			VkSampleCountFlags vSampleCount = VkSampleCountFlagBits::VK_SAMPLE_COUNT_64_BIT;
		};
	}
}