// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "VulkanRenderTargetAttachment.h"

namespace DMK
{
	namespace VulkanBackend
	{
		class VulkanDevice;

		class VulkanSwapChain final : public VulkanRenderTargetAttachment {
		public:
			VulkanSwapChain() : VulkanRenderTargetAttachment(DMK_RT_SWAP_CHAIN_ATTACHMENT) {}
			~VulkanSwapChain() {}

			virtual void Initialize(VulkanDevice* pDevice, Vector2 extent, UI32 bufferCount) override final;
			virtual void Terminate(VulkanDevice* pDevice) override final;

			virtual VkAttachmentDescription GetAttachmentDescription() const override final;
			virtual VkImageLayout GetAttachmentLayout() const override final;

		private:
			VkSwapchainKHR vSwapChain = VK_NULL_HANDLE;
		};
	}
}