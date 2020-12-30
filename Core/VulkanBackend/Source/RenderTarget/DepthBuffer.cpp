// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/RenderTarget/DepthBuffer.h"
#include "VulkanBackend/Common/VulkanDevice.h"
#include "VulkanBackend/Common/Utilities.h"

namespace DMK
{
	namespace VulkanBackend
	{
		GraphicsCore::RenderTargetAttachmentHandle VulkanDevice::CreateDepthBuffer(UI64 bufferCount, GraphicsCore::RenderTargetAttachmentSpecification spec, const VkExtent2D& extent)
		{
			// Create the depth buffer object.
			DepthBuffer vDepthBuffer = {};

			// Initialize the buffer.
			vDepthBuffer.Initialize(*this, spec, bufferCount, extent);

			// Insert it to the vector.
			vDepthBuffers.insert(vDepthBuffers.end(), std::move(vDepthBuffer));

			return GraphicsCore::RenderTargetAttachmentHandle(vDepthBuffers.size() - 1, GraphicsCore::RenderTargetAttachmentType::DEPTH_BUFFER);
		}

		void VulkanDevice::DestroyDepthBuffer(GraphicsCore::RenderTargetAttachmentHandle vDepthBufferHandle)
		{
			// Get and terminate the color buffer.
			(vDepthBuffers.data() + vDepthBufferHandle.mHandle)->Terminate(*this);

			// Remove it from the vector.
			vDepthBuffers.erase(vDepthBuffers.begin() + vDepthBufferHandle.mHandle);
		}

		void VulkanDevice::DestroyAllDepthBuffers()
		{
			// Terminate all the depth buffers.
			for (auto itr = vDepthBuffers.begin(); itr != vDepthBuffers.end(); itr++)
				itr->Terminate(*this);

			vDepthBuffers.clear();
		}

		DepthBuffer* VulkanDevice::GetDepthBuffer(GraphicsCore::RenderTargetAttachmentHandle mHandle) const
		{
			return const_cast<DepthBuffer*>(vDepthBuffers.data() + mHandle.mHandle);
		}

		void DepthBuffer::Initialize(VulkanDevice& vDevice, const GraphicsCore::RenderTargetAttachmentSpecification& spec, UI64 bufferCount, const VkExtent2D& extent)
		{
			mSpecification = spec;
			vFormat = Utilities::FindDepthFormat(vDevice);

			// Image create info structure.
			VkImageCreateInfo createInfo = {};
			createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
			createInfo.flags = VK_NULL_HANDLE;
			createInfo.pNext = VK_NULL_HANDLE;
			createInfo.arrayLayers = 1;
			createInfo.extent.width = static_cast<UI32>(extent.width);
			createInfo.extent.height = static_cast<UI32>(extent.height);
			createInfo.extent.depth = 1;	// TODO
			createInfo.format = vFormat;
			createInfo.arrayLayers = 1;
			createInfo.imageType = VK_IMAGE_TYPE_2D;
			createInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			createInfo.mipLevels = 1;
			createInfo.usage = VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT | VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
			createInfo.samples = static_cast<VkSampleCountFlagBits>(vDevice.GetMsaaSamples());
			createInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
			createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

			mBufferCount = static_cast<UI32>(bufferCount);
			vImages.resize(mBufferCount);
			UI32 counter = 0;

			// Create the necessary color buffers.
			do {
				DMK_VK_ASSERT(vkCreateImage(vDevice, &createInfo, nullptr, &vImages.at(counter)), "Failed to create Vulkan Color Buffer image!");
				counter++;
			} while (counter != mBufferCount);

			// Create the buffer memory.
			vBufferMemory = Utilities::CreateImageMemory(vImages, vDevice, vDevice);

			// Create the image views.
			vImageViews = std::move(Utilities::CreateImageViews(vImages, vFormat, vDevice));

			// Set a new image layout.
			{
				// Create a new command buffer.
				auto vCommandBuffer = vDevice.CreateCommandBuffer();

				// Set image layout commands to all the images.
				for (auto itr = vImages.begin(); itr != vImages.end(); itr++)
					vCommandBuffer.SetImageLayout(*itr, 1, 1, vFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

				// Flush commands.
				vDevice.FlushCommands(vCommandBuffer);

				// Terminate the command buffer and the command pool.
				vDevice.TerminateCommandPool(vCommandBuffer.commandPoolIndex);
			}
		}

		void DepthBuffer::Terminate(const VulkanDevice& vDevice)
		{
			// Destroy the images.
			for (auto itr = vImages.begin(); itr != vImages.end(); itr++)
				vkDestroyImage(vDevice, *itr, nullptr);

			// Free the device memory.
			vkFreeMemory(vDevice, vBufferMemory, nullptr);

			// Destroy the image views.
			for (auto itr = vImageViews.begin(); itr != vImageViews.end(); itr++)
				vkDestroyImageView(vDevice, *itr, nullptr);
		}

		VkAttachmentDescription DepthBuffer::GetAttachmentDescription() const
		{
			VkAttachmentDescription vDesc = {};
			vDesc.flags = VK_NULL_HANDLE;
			vDesc.format = vFormat;
			vDesc.samples = static_cast<VkSampleCountFlagBits>(vSampleCount);
			vDesc.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			vDesc.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
			vDesc.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
			vDesc.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
			vDesc.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
			vDesc.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

			return vDesc;
		}

		VkImageLayout DepthBuffer::GetAttachmentLayout() const
		{
			return VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL;
		}
	}
}