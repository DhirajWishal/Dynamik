// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "VulkanSwapChain.h"

namespace DMK
{
	namespace VulkanBackend
	{
		class VulkanFrameBuffer {
		public:
			VulkanFrameBuffer() {}
			~VulkanFrameBuffer() {}

			void Initiallize(VulkanDevice* pDevice, Vector2 extent, std::vector<VulkanRenderTargetAttachment*> pAttachments, UI32 bufferCount);
			void Terminate(VulkanDevice* pDevice);

		private:
			void CreateRenderPass();
			void DestroyRenderPass();

			void CreateFrameBuffers();
			void DestroyFrameBuffers();

		private:
			std::vector<VkFramebuffer> vFrameBuffers;
			VkRenderPass vRenderPass = VK_NULL_HANDLE;
		};
	}
}