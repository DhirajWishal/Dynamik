// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/RenderTarget/ColorBuffer.h"
#include "VulkanBackend/Common/VulkanDevice.h"
#include "VulkanBackend/Common/Utilities.h"

namespace DMK
{
	namespace VulkanBackend
	{
		GraphicsCore::RenderTargetAttachmentHandle VulkanDevice::CreateColorBuffer(GraphicsCore::RenderTargetAttachmentSpecification spec)
		{
			// Create the color buffer object.
			ColorBuffer vColorBuffer = {};

			// Initialize the buffer.
			vColorBuffer.Initialize(*this, spec);

			// Insert it to the vector.
			vColorBuffers.insert(vColorBuffers.end(), std::move(vColorBuffer));

			return GraphicsCore::RenderTargetAttachmentHandle(vColorBuffers.size() - 1, GraphicsCore::RenderTargetAttachmentType::COLOR_BUFFER);
		}

		void VulkanDevice::DestroyColorBuffer(GraphicsCore::RenderTargetAttachmentHandle vColorBufferHandle)
		{
			// Get and terminate the color buffer.
			(vColorBuffers.data() + vColorBufferHandle.mHandle)->Terminate(*this);

			// Remove it from the vector.
			vColorBuffers.erase(vColorBuffers.begin() + vColorBufferHandle.mHandle);
		}

		void VulkanDevice::DestroyAllColorBuffers()
		{
			// Terminate all the color buffers.
			for (auto itr = vColorBuffers.begin(); itr != vColorBuffers.end(); itr++)
				itr->Terminate(*this);

			vColorBuffers.clear();
		}

		void ColorBuffer::Initialize(VulkanDevice& vDevice, const GraphicsCore::RenderTargetAttachmentSpecification& spec)
		{
			mSpecification = spec;
			vSampleCount = vDevice.GetMsaaSamples();

			// Get the swap chain support details.
			auto vSwapChainSupport = vDevice.GetSwapChainSupportDetails();
			vFormat = Utilities::ChooseSwapSurfaceFormat(vSwapChainSupport.formats).format;

			// Image create info structure.
			VkImageCreateInfo createInfo = {};
			createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
			createInfo.flags = VK_NULL_HANDLE;
			createInfo.pNext = VK_NULL_HANDLE;
			createInfo.arrayLayers = 1;
			createInfo.extent.width = static_cast<UI32>(spec.extent.width);
			createInfo.extent.depth = static_cast<UI32>(spec.extent.depth);
			createInfo.extent.height = static_cast<UI32>(spec.extent.height);
			createInfo.format = vFormat;
			createInfo.arrayLayers = 1;
			createInfo.imageType = VK_IMAGE_TYPE_2D;
			createInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			createInfo.mipLevels = 1;
			createInfo.usage = VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
			createInfo.samples = static_cast<VkSampleCountFlagBits>(vDevice.GetMsaaSamples());
			createInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
			createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

			mBufferCount = vSwapChainSupport.capabilities.minImageCount + 1;
			if (vSwapChainSupport.capabilities.maxImageCount > 0
				&& mBufferCount > vSwapChainSupport.capabilities.maxImageCount)
				mBufferCount = vSwapChainSupport.capabilities.maxImageCount;

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

		void ColorBuffer::Terminate(const VulkanDevice& vDevice)
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

		VkAttachmentDescription ColorBuffer::GetAttachmentDescription() const
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

		VkImageLayout ColorBuffer::GetAttachmentLayout() const
		{
			return VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		}
	}
}