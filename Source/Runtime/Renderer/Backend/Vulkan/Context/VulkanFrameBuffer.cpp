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
		void VulkanFrameBuffer::initialize(RCoreObject* pCoreObject, RRenderPass* pRenderPass, RSwapChain* pSwapChain)
		{
			width = pSwapChain->extent.width;
			height = pSwapChain->extent.height;

			VulkanColorAttachment colorAttachment;
			B1 isColorAttachmentInitialized = false;
			VulkanDepthAttachment depthAttachment;
			B1 isDepthAttachmentInitialized = false;

			for (size_t i = 0; i < pSwapChain->bufferCount; i++)
			{
				ARRAY<VkImageView> _attachments;

				for (auto _subpass : pRenderPass->subPasses)
				{
					switch (_subpass)
					{
					case Dynamik::RSubPasses::SUBPASSES_SWAPCHAIN:
						_attachments.pushBack(((VulkanImageView*)InheritCast<VulkanSwapChain>(pSwapChain).imageViews[i])->imageView);
						break;
					case Dynamik::RSubPasses::SUBPASSES_DEPTH:
					{
						if (!isDepthAttachmentInitialized)
						{
							VulkanFrameBufferAttachmentInitInfo attachmentInfo;
							attachmentInfo.format = (DMKFormat)VulkanUtilities::findDepthFormat(Inherit<VulkanCoreObject>(pCoreObject)->device);
							attachmentInfo.imageWidth = width;
							attachmentInfo.imageHeight = height;
							attachmentInfo.msaaSamples = pCoreObject->sampleCount;

							depthAttachment.initialize(pCoreObject, attachmentInfo);
							isDepthAttachmentInitialized = true;

							attachmentImages.pushBack(depthAttachment.image);
							attachmentViews.pushBack(depthAttachment.imageView);
						}

						_attachments.pushBack(depthAttachment.imageView);
					}
					break;
					case Dynamik::RSubPasses::SUBPASSES_COLOR:
					{
						if (!isColorAttachmentInitialized)
						{
							VulkanFrameBufferAttachmentInitInfo attachmentInfo;
							attachmentInfo.format = (DMKFormat)InheritCast<VulkanSwapChain>(pSwapChain).format;
							attachmentInfo.imageWidth = width;
							attachmentInfo.imageHeight = height;
							attachmentInfo.msaaSamples = pCoreObject->sampleCount;

							colorAttachment.initialize(pCoreObject, attachmentInfo);
							isColorAttachmentInitialized = true;

							attachmentImages.pushBack(colorAttachment.image);
							attachmentViews.pushBack(colorAttachment.imageView);
						}

						_attachments.pushBack(colorAttachment.imageView);
					}
					break;
					case Dynamik::RSubPasses::SUBPASSES_OVERLAY:
						break;
					default:
						break;
					}
				}

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
			/* Terminate attachment images */
			for (auto image : attachmentImages)
				image.terminate(pCoreObject);

			/* Terminate attachment image views */
			for (auto imageView : attachmentViews)
				imageView.terminate(pCoreObject);

			/* Terminate frame buffers */
			for (auto buffer : buffers)
				vkDestroyFramebuffer(Inherit<VulkanCoreObject>(pCoreObject)->device, buffer, nullptr);
		}

		const VkFramebuffer VulkanFrameBuffer::operator[](UI32 index) const
		{
			return this->buffers[index];
		}
	}
}