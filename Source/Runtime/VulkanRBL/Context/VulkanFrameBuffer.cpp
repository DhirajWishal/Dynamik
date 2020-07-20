// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanFrameBuffer.h"

#include "Attachments/VulkanColorAttachment.h"
#include "Attachments/VulkanDepthAttachment.h"

#include "../VulkanUtilities.h"

namespace Dynamik
{
	namespace Backend
	{
		void VulkanFrameBuffer::initialize(RCoreObject* pCoreObject, RRenderPass* pRenderPass, DMKExtent2D frameExtent, UI32 bufferCount, ARRAY<ARRAY<RFrameBufferAttachment*>> pAttachments)
		{
			width = Cast<UI32>(frameExtent.width);
			height = Cast<UI32>(frameExtent.height);
			this->pAttachments = pAttachments;

			if (bufferCount < 1)
				DMK_ERROR("Requested frame buffer count is not a valid count!");

			if (pAttachments.size() != bufferCount)
				DMK_FATAL("Invalid buffer count or attachment count!");

			for (size_t i = 0; i < bufferCount; i++)
			{
				ARRAY<VkImageView> _attachments;

				for (auto pAttachment : pAttachments[i])
					_attachments.pushBack(Inherit<VulkanImageView>(Inherit<VulkanImage>(pAttachment->pImageAttachment)->pImageView)->imageView);

				VkFramebufferCreateInfo framebufferInfo = {};
				framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
				framebufferInfo.renderPass = InheritCast<VulkanRenderPass>(pRenderPass);
				framebufferInfo.attachmentCount = static_cast<UI32>(_attachments.size());
				framebufferInfo.pAttachments = _attachments.data();
				framebufferInfo.width = width;
				framebufferInfo.height = height;
				framebufferInfo.layers = 1;

				VkFramebuffer _buffer = VK_NULL_HANDLE;
				DMK_VULKAN_ASSERT(vkCreateFramebuffer(Inherit<VulkanCoreObject>(pCoreObject)->device, &framebufferInfo, nullptr, &_buffer), "Failed to create frame buffer!");

				buffers.pushBack(_buffer);
			}
		}

		void VulkanFrameBuffer::terminate(RCoreObject* pCoreObject)
		{
			/* Terminate attachments */
			for (auto container : pAttachments)
			{
				for (auto pAttachment : container)
				{
					pAttachment->terminate(pCoreObject);
					StaticAllocator<RFrameBufferAttachment>::rawDeallocate(pAttachment, 0);
				}
			}
			pAttachments.clear();

			/* Terminate frame buffers */
			for (auto buffer : buffers)
				vkDestroyFramebuffer(Inherit<VulkanCoreObject>(pCoreObject)->device, buffer, nullptr);
			buffers.clear();
		}

		const VkFramebuffer VulkanFrameBuffer::operator[](UI32 index) const
		{
			return this->buffers[index];
		}
	}
}