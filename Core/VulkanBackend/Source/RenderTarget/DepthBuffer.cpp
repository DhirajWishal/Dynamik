// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/RenderTarget/DepthBuffer.h"
#include "VulkanBackend/Common/VulkanDevice.h"
#include "VulkanBackend/Common/Utilities.h"

namespace DMK
{
	namespace VulkanBackend
	{
		DepthBufferHandle VulkanDevice::CreateDepthBuffer(GraphicsCore::RenderTargetAttachmentSpecification spec)
		{
			// Create the depth buffer object.
			DepthBuffer vDepthBuffer = {};

			// Initialize the buffer.
			vDepthBuffer.Initialize(*this, spec);

			// Insert it to the vector.
			vDepthBuffers.insert(vDepthBuffers.end(), std::move(vDepthBuffer));

			return vDepthBuffers.size() - 1;
		}

		void VulkanDevice::DestroyDepthBuffer(DepthBufferHandle vDepthBufferHandle)
		{
			// Get and terminate the color buffer.
			auto vDepthBuffer = vDepthBuffers.at(vDepthBufferHandle);
			vDepthBuffer.Terminate(*this);

			// Remove it from the vector.
			vDepthBuffers.erase(vDepthBuffers.begin() + vDepthBufferHandle);
		}

		void VulkanDevice::DestroyAllDepthBuffers()
		{
			// Terminate all the depth buffers.
			for (auto itr = vDepthBuffers.begin(); itr != vDepthBuffers.end(); itr++)
				itr->Terminate(*this);

			vDepthBuffers.clear();
		}

		void DepthBuffer::Initialize(VulkanDevice& vDevice, const GraphicsCore::RenderTargetAttachmentSpecification& spec)
		{
			mSpecification = spec;
			vFormat = Utilities::FindDepthFormat(vDevice.GetPhysicalDevice());

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
			createInfo.usage = VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT | VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
			createInfo.samples = static_cast<VkSampleCountFlagBits>(vDevice.GetMsaaSamples());
			createInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
			createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

			// Get the swap chain support details.
			auto vSwapChainSupport = vDevice.GetSwapChainSupportDetails();
			mBufferCount = vSwapChainSupport.capabilities.minImageCount + 1;
			if (vSwapChainSupport.capabilities.maxImageCount > 0
				&& mBufferCount > vSwapChainSupport.capabilities.maxImageCount)
				mBufferCount = vSwapChainSupport.capabilities.maxImageCount;

			vImages.resize(mBufferCount);
			UI32 counter = 0;

			// Create the necessary color buffers.
			do {
				DMK_VK_ASSERT(vkCreateImage(vDevice.GetLogicalDevice(), &createInfo, nullptr, &vImages.at(counter)), "Failed to create Vulkan Color Buffer image!");
				counter++;
			} while (counter != mBufferCount);

			// Create the buffer memory.
			vBufferMemory = Utilities::CreateImageMemory(vImages, vDevice.GetPhysicalDevice(), vDevice.GetLogicalDevice());

			// Create the image views.
			vImageViews = std::move(Utilities::CreateImageViews(vImages, vFormat, vDevice.GetLogicalDevice()));

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
				vkDestroyImage(vDevice.GetLogicalDevice(), *itr, nullptr);

			// Free the device memory.
			vkFreeMemory(vDevice.GetLogicalDevice(), vBufferMemory, nullptr);

			// Destroy the image views.
			for (auto itr = vImageViews.begin(); itr != vImageViews.end(); itr++)
				vkDestroyImageView(vDevice.GetLogicalDevice(), *itr, nullptr);
		}
	}
}