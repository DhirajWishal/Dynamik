#include "dmkafx.h"
#include "VulkanFrameBuffer.h"

namespace Dynamik
{
	namespace Backend
	{
		void VulkanFrameBuffer::initialize(
			const VulkanDevice& vDevice,
			const VulkanSwapChain& vSwapChain,
			const VulkanRenderPass& vRenderPass,
			const ARRAY<POINTER<VulkanFrameBufferAttachment>>& attachments)
		{
			frameWidth = vSwapChain.extent.width;
			frameHeight = vSwapChain.extent.height;

			for (size_t i = 0; i < vSwapChain.images.size(); i++)
			{
				ARRAY<VkImageView> _attachments;

				for (auto _attachment : attachments)
					_attachments.pushBack(_attachment->imageView);

				_attachments.pushBack(vSwapChain.imageViews[i]);

				VkFramebufferCreateInfo framebufferInfo = {};
				framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
				framebufferInfo.renderPass = vRenderPass;
				framebufferInfo.attachmentCount = static_cast<UI32>(_attachments.size());
				framebufferInfo.pAttachments = _attachments.data();
				framebufferInfo.width = frameWidth;
				framebufferInfo.height = frameHeight;
				framebufferInfo.layers = 1;

				VkFramebuffer _buffer = VK_NULL_HANDLE;
				DMK_VULKAN_ASSERT(vkCreateFramebuffer(vDevice, &framebufferInfo, nullptr, &_buffer), "Failed to create frame buffer!");

				buffers.pushBack(_buffer);
			}
		}
		
		void VulkanFrameBuffer::terminate(const VulkanDevice& vDevice)
		{
			for (auto buffer : buffers)
				vkDestroyFramebuffer(vDevice, buffer, nullptr);
		}
		
		const VkFramebuffer VulkanFrameBuffer::operator[](UI32 index) const
		{
			return this->buffers[index];
		}
	}
}