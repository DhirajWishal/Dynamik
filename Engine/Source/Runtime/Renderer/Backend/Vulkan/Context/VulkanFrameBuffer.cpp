#include "dmkafx.h"
#include "VulkanFrameBuffer.h"

namespace Dynamik
{
	namespace Backend
	{
		void VulkanFrameBuffer::initialize(
			const VulkanDevice& vDevice,
			UI32 bufferCount,
			const VulkanRenderPass& vRenderPass,
			const ARRAY<VulkanImageView>& attachments,
			UI32 width, UI32 height)
		{
			frameHeight = height;
			frameWidth = width;

			for (size_t i = 0; i < bufferCount; i++)
			{
				std::vector<VkImageView> attachments;
				for (VkImageView _imageView : attachments)
					attachments.push_back(_imageView);

				VkFramebufferCreateInfo framebufferInfo = {};
				framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
				framebufferInfo.renderPass = vRenderPass;
				framebufferInfo.attachmentCount = static_cast<UI32>(attachments.size());
				framebufferInfo.pAttachments = attachments.data();
				framebufferInfo.width = width;
				framebufferInfo.height = height;
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
		
		const VkFramebuffer VulkanFrameBuffer::operator[](UI32 index)
		{
			return this->buffers[index];
		}
	}
}