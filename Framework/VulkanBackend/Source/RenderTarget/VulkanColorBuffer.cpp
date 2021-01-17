// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/RenderTarget/VulkanColorBuffer.h"

namespace DMK
{
	namespace VulkanBackend
	{
		void VulkanColorBuffer::Initialize(VulkanDevice* pDevice, Vector2 extent, UI32 bufferCount)
		{
		}

		void VulkanColorBuffer::Terminate(VulkanDevice* pDevice)
		{
		}

		VkAttachmentDescription VulkanColorBuffer::GetAttachmentDescription() const
		{
			VkAttachmentDescription vDesc = {};
			vDesc.flags = VK_NULL_HANDLE;
			vDesc.format = vFormat;
			vDesc.samples = static_cast<VkSampleCountFlagBits>(vSampleCount);
			vDesc.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			vDesc.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
			vDesc.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
			vDesc.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
			vDesc.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
			vDesc.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

			return vDesc;
		}

		VkImageLayout VulkanColorBuffer::GetAttachmentLayout() const
		{
			return VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		}
	}
}