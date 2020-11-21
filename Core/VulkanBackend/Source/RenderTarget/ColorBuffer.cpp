// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/RenderTarget/ColorBuffer.h"
#include "VulkanBackend/RenderTarget/SwapChain.h"
#include "VulkanBackend/Common/VulkanDevice.h"
#include "VulkanBackend/Common/Utilities.h"

namespace DMK
{
	namespace VulkanBackend
	{
		ColorBufferHandle VulkanDevice::CreateColorBuffer(GraphicsCore::RenderTargetAttachmentSpecification spec)
		{
			// Create the color buffer object.
			ColorBuffer vColorBuffer = {};

			// Initialize the buffer.
			vColorBuffer.Initialize(*this, spec);

			// Insert it to the vector.
			vColorBuffers.insert(vColorBuffers.end(), std::move(vColorBuffer));

			return vColorBuffers.size() - 1;
		}

		void VulkanDevice::DestroyColorBuffer(ColorBufferHandle vColorBufferHandle)
		{
			// Get and terminate the color buffer.
			auto vColorBuffer = vColorBuffers.at(vColorBufferHandle);
			vColorBuffer.Terminate(*this);

			// Remove it from the vector.
			vColorBuffers.erase(vColorBuffers.begin() + vColorBufferHandle);
		}

		void VulkanDevice::DestroyAllColorBuffers()
		{
			// Terminate all the color buffers.
			for (auto itr = vColorBuffers.begin(); itr != vColorBuffers.end(); itr++)
				itr->Terminate(*this);

			vColorBuffers.clear();
		}

		namespace _Helpers
		{
			/**
			 * Create image memory for the Color Buffer.
			 * This creates one image memory block to fit all of the images.
			 *
			 * @param vImages: The images to be binded.
			 * @param vPhysicalDevice: The physical device in which the memory is allocated to.
			 * @param vLogicalDevice: The logical device to bind the memory to.
			 * @return The Vulkan Device Memory handle.
			 */
			VkDeviceMemory CreateImageMemory(const std::vector<VkImage>& vImages, VkPhysicalDevice vPhysicalDevice, VkDevice vLogicalDevice)
			{
				// Get memory requirements.
				VkMemoryRequirements memRequirements = {};
				vkGetImageMemoryRequirements(vLogicalDevice, vImages[0], &memRequirements);

				// Memory allocate info.
				VkMemoryAllocateInfo allocInfo = {};
				allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
				allocInfo.allocationSize = memRequirements.size * vImages.size();
				allocInfo.memoryTypeIndex = Utilities::FindMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vPhysicalDevice);

				// Allocate the image memory
				VkDeviceMemory vImageMemory = VK_NULL_HANDLE;
				DMK_VK_ASSERT(vkAllocateMemory(vLogicalDevice, &allocInfo, nullptr, &vImageMemory), "Failed to allocate image memory!");

				// Bind the image to the image memory.
				UI32 counter = 0;
				while (counter < vImages.size())
				{
					DMK_VK_ASSERT(vkBindImageMemory(vLogicalDevice, *(vImages.data() + counter), vImageMemory, memRequirements.size * counter), "Failed to bind image memory!");
					counter++;
				}

				return vImageMemory;
			}
		}

		void ColorBuffer::Initialize(const VulkanDevice& vDevice, const GraphicsCore::RenderTargetAttachmentSpecification& spec)
		{
			mSpecification = spec;

			// Get the swap chain support details.
			auto vSwapChainSupport = vDevice.GetSwapChainSupportDetails();
			vFormat = _Helpers::ChooseSwapSurfaceFormat(vSwapChainSupport.formats).format;

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
				DMK_VK_ASSERT(vkCreateImage(vDevice.GetLogicalDevice(), &createInfo, nullptr, &vImages.at(counter)), "Failed to create Vulkan Color Buffer image!");
				counter++;
			} while (counter != mBufferCount);

			// Create the buffer memory.
			vBufferMemory = _Helpers::CreateImageMemory(vImages, vDevice.GetPhysicalDevice(), vDevice.GetLogicalDevice());

			// Create the image views.
			vImageViews = std::move(_Helpers::CreateImageViews(vImages, vFormat, vDevice.GetLogicalDevice()));
		}

		void ColorBuffer::Terminate(const VulkanDevice& vDevice)
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