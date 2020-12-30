// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "RenderTargetAttachment.h"

namespace DMK
{
	namespace VulkanBackend
	{
		/**
		 * Vulkan render pass object.
		 */
		class RenderPass {
		public:
			RenderPass() {}
			~RenderPass() {}

			/**
			 * Initialize the render pass.
			 *
			 * @param vDevice: The Vulkan Device object.
			 * @param mAttachments: The render target attachment handles.
			 */
			void Initialize(const VulkanDevice& vDevice, std::vector<GraphicsCore::RenderTargetAttachmentHandle> mAttachments, std::vector<VkSubpassDependency> vDependencies = { CreateDefaultSubpassDependency() });

			/**
			 * Terminate the render pass.
			 */
			void Terminate(const VulkanDevice& vDevice);

			/**
			 * VkRenderPass operator.
			 */
			operator VkRenderPass() const { return vRenderPass; }

		public:
			/**
			 * Create the default subpass dependency.
			 *
			 * @return VkSubpassDependency structure.
			 */
			static constexpr VkSubpassDependency CreateDefaultSubpassDependency()
			{
				VkSubpassDependency vDep = {};
				vDep.srcSubpass = VK_SUBPASS_EXTERNAL;
				vDep.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
				vDep.srcAccessMask = VK_NULL_HANDLE;
				vDep.dstSubpass = 0;
				vDep.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
				vDep.dstAccessMask = VkAccessFlagBits::VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VkAccessFlagBits::VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

				return vDep;
			}

		private:
			VkRenderPass vRenderPass = VK_NULL_HANDLE;	// Vulkan Render Pass handle.
		};

		/**
		 * Render Pass Handle type.
		 */
		typedef UI64 RenderPassHandle;
	}
}