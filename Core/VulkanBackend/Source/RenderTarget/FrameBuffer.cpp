// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/RenderTarget/FrameBuffer.h"
#include "VulkanBackend/Common/VulkanDevice.h"
#include "Core/ErrorHandler/Logger.h"

namespace DMK
{
	namespace VulkanBackend
	{
		FrameBufferHandle VulkanDevice::CreateFrameBuffer(const RenderPassHandle& mRenderPassHandle, const std::vector<GraphicsCore::RenderTargetAttachmentHandle>& mAttachments, UI64 bufferCount, VkExtent2D vExtent)
		{
			// Create the frame buffer object.
			FrameBuffer vFrameBuffer = {};

			// Initialize the buffer.
			vFrameBuffer.Initialize(*this, mRenderPassHandle, mAttachments, bufferCount, vExtent);

			// Add the frame buffer to the vector and return its handle.
			vFrameBuffers.insert(vFrameBuffers.end(), std::move(vFrameBuffer));
			return vFrameBuffers.size() - 1;
		}

		void VulkanDevice::DestroyFrameBuffer(const FrameBufferHandle& mHandle)
		{
			// Get and terminate the frame buffer.
			(vFrameBuffers.data() + mHandle)->Terminate(*this);

			// Remove it from the vector.
			vFrameBuffers.erase(vFrameBuffers.begin() + mHandle);
		}

		void VulkanDevice::DestroyAllFrameBuffers()
		{
			// Iterate through and terminate all the frame buffers.
			for (auto itr = vFrameBuffers.begin(); itr != vFrameBuffers.end(); itr++)
				itr->Terminate(*this);

			// Clear the vector.
			vFrameBuffers.clear();
		}

		void FrameBuffer::Initialize(const VulkanDevice& vDevice, const RenderPassHandle& mRenderPassHandle, const std::vector<GraphicsCore::RenderTargetAttachmentHandle>& mAttachments)
		{
			this->vExtent = vExtent;
			UI64 bufferCount = 0;

			// Check if the frame buffer count is valid.
			if (!bufferCount)
			{
				Logger::LogError(TEXT("Invalid frame buffer count!"));
				return;
			}

			auto pBegin = mAttachments.begin();
			auto pEnd = mAttachments.end();
			UI64 index = 0;

			VkFramebufferCreateInfo vFBCreate = {};
			vFBCreate.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			vFBCreate.flags = VK_NULL_HANDLE;
			vFBCreate.pNext = VK_NULL_HANDLE;
			vFBCreate.layers = 1;
			vFBCreate.renderPass = *(vDevice.vRenderPasses.data() + mRenderPassHandle);
			vFBCreate.attachmentCount = bufferCount;
			vFBCreate.width = vExtent.width;
			vFBCreate.height = vExtent.height;

			// Iterate through and create the frame buffers.
			while (bufferCount--)
			{
				std::vector<VkImageView> vImageViews;

				// Resolve attachments.
				auto itr = pBegin;
				while (itr != pEnd)
				{
					switch (itr->mType)
					{
					case DMK::GraphicsCore::RenderTargetAttachmentType::SWAP_CHAIN:
						vImageViews.insert(vImageViews.end(), *((vDevice.vSwapChains.data() + itr->mHandle)->vImageViews.data() + index));
						break;
					case DMK::GraphicsCore::RenderTargetAttachmentType::COLOR_BUFFER:
						vImageViews.insert(vImageViews.end(), *((vDevice.vColorBuffers.data() + itr->mHandle)->vImageViews.data() + index));
						break;
					case DMK::GraphicsCore::RenderTargetAttachmentType::DEPTH_BUFFER:
						vImageViews.insert(vImageViews.end(), *((vDevice.vDepthBuffers.data() + itr->mHandle)->vImageViews.data() + index));
						break;
					default:
						Logger::LogError(TEXT("Invalid Render Target Attachment Type submitted to create the Frame Buffer!"));
						break;
					}

					itr++;
				}

				vFBCreate.pAttachments = vImageViews.data();

				VkFramebuffer vFrameBuffer = VK_NULL_HANDLE;
				DMK_VK_ASSERT(vkCreateFramebuffer(vDevice, &vFBCreate, nullptr, &vFrameBuffer), "Failed to create Vulkan Frame Buffer!");
				vFrameBuffers.insert(vFrameBuffers.end(), vFrameBuffer);

				index++;
			}
		}

		void FrameBuffer::Terminate(const VulkanDevice& vDevice)
		{
			// Destroy all the frame buffers.
			for (auto itr = vFrameBuffers.begin(); itr != vFrameBuffers.end(); itr++)
				vkDestroyFramebuffer(vDevice, *itr, nullptr);

			vFrameBuffers.clear();
		}
	}
}