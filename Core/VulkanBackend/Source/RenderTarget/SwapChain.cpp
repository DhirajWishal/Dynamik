// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/RenderTarget/SwapChain.h"
#include "VulkanBackend/Common/VulkanDevice.h"

namespace DMK
{
	namespace VulkanBackend
	{
		SwapChainHandle VulkanDevice::CreateSwapChain(GraphicsCore::RenderTargetAttachmentSpecification spec)
		{
			// Create the swap chain object.
			SwapChain vSwapChain = {};

			// Initialize the swap chain.
			vSwapChain.Initialize(*this, spec);

			// Add the swapchain to the store.
			vSwapChains.insert(vSwapChains.end(), std::move(vSwapChain));

			return vSwapChains.size() - 1;
		}

		void VulkanDevice::DestroySwapChain(SwapChainHandle vSwapChainHandle)
		{
			// get and terminate the swap chain.
			auto vSwapChain = vSwapChains.at(vSwapChainHandle);
			vSwapChain.Terminate(*this);

			// Remove it from the vector.
			vSwapChains.erase(vSwapChains.begin() + vSwapChainHandle);
		}

		void VulkanDevice::DestroyAllSwapChains()
		{
			// Terminate all the swap chains.
			for (auto itr = vSwapChains.begin(); itr != vSwapChains.end(); itr++)
				itr->Terminate(*this);

			vSwapChains.clear();
		}

		namespace _Helpers
		{
			VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
			{
				for (const auto& availableFormat : availableFormats)
					if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM
						&& availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
						return availableFormat;

				return availableFormats[0];
			}

			/**
			 * Choose swap chain present mode.
			 * This describes how the swap chain images should be presented to the screen buffer.
			 *
			 * @param availablePresentModes: All the available present modes.
			 * @return VkPresentModeKHR enum.
			 */
			VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
			{
				VkPresentModeKHR bestMode = VK_PRESENT_MODE_FIFO_KHR;

				for (const auto& availablePresentMode : availablePresentModes)
				{
					if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
						return availablePresentMode;
					else if (availablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR)
						bestMode = availablePresentMode;
				}

				return bestMode;
			}

			/**
			 * Choose a swap chain extent.
			 * This defines the width and height of every swap chain image.
			 *
			 * @param capabilities: The surface capabilities.
			 * @param width: The prefered width of the image.
			 * @param height: The prefered height of the image.
			 * @return VkExtent2D structure.
			 */
			VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, UI32 width, UI32 height)
			{
				if (capabilities.currentExtent.width != std::numeric_limits<UI32>::max())
					return capabilities.currentExtent;
				else
				{
					VkExtent2D actualExtent = {
						width,
						height
					};

					if ((width >= capabilities.maxImageExtent.width) || (width <= capabilities.minImageExtent.width))
					{
						actualExtent.width = std::max(capabilities.minImageExtent.width,
							std::min(capabilities.maxImageExtent.width, actualExtent.width));
					}
					if ((height >= capabilities.maxImageExtent.height) || (height <= capabilities.minImageExtent.height))
					{
						actualExtent.height = std::max(capabilities.minImageExtent.height,
							std::min(capabilities.maxImageExtent.height, actualExtent.height));
					}

					return actualExtent;
				}
			}

			std::vector<VkImageView> CreateImageViews(const std::vector<VkImage>& vImages, VkFormat imageFormat, VkDevice vDevice)
			{
				VkImageViewCreateInfo createInfo = {};
				createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
				createInfo.flags = VK_NULL_HANDLE;
				createInfo.pNext = VK_NULL_HANDLE;
				createInfo.viewType = VkImageViewType::VK_IMAGE_VIEW_TYPE_2D;
				createInfo.format = imageFormat;

				VkImageSubresourceRange vSubRange = {};
				vSubRange.baseArrayLayer = 1;
				vSubRange.layerCount = 1;
				vSubRange.levelCount = 1;
				vSubRange.baseMipLevel = 0;

				createInfo.subresourceRange = vSubRange;

				std::vector<VkImageView> vImageViews(vImages.size());
				UI8 counter = 0;
				for (auto itr = vImages.begin(); itr != vImages.end(); itr++)
				{
					createInfo.image = *itr;
					DMK_VK_ASSERT(vkCreateImageView(vDevice, &createInfo, nullptr, vImageViews.data() + counter), "Failed to create Vulkan Image Views for the Swap Chain images!");
					counter++;
				}

				return vImageViews;
			}
		}

		void SwapChain::Initialize(const VulkanDevice& vDevice, const GraphicsCore::RenderTargetAttachmentSpecification& spec)
		{
			mSpecification = spec;

			// Get the swap chain support details.
			auto vSupport = vDevice.GetSwapChainSupportDetails();

			VkSurfaceFormatKHR surfaceFormat = _Helpers::ChooseSwapSurfaceFormat(vSupport.formats);
			VkPresentModeKHR presentMode = _Helpers::ChooseSwapPresentMode(vSupport.presentModes);
			VkExtent2D scExtent = _Helpers::ChooseSwapExtent(vSupport.capabilities, static_cast<UI32>(spec.extent.width), static_cast<UI32>(spec.extent.height));

			auto vCapabilities = vDevice.GetSurfaceCapabilities();

			VkCompositeAlphaFlagBitsKHR surfaceComposite =
				(vCapabilities.supportedCompositeAlpha & VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR)
				? VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR
				: (vCapabilities.supportedCompositeAlpha & VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR)
				? VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR
				: (vCapabilities.supportedCompositeAlpha & VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR)
				? VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR
				: VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR;

			mBufferCount = vSupport.capabilities.minImageCount + 1;
			if (vSupport.capabilities.maxImageCount > 0
				&& mBufferCount > vSupport.capabilities.maxImageCount)
				mBufferCount = vSupport.capabilities.maxImageCount;

			// Swap Chain create info.
			VkSwapchainCreateInfoKHR createInfo = {};
			createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
			createInfo.surface = vDevice.GetSurface();
			createInfo.minImageCount = mBufferCount;
			createInfo.imageFormat = surfaceFormat.format;
			createInfo.imageColorSpace = surfaceFormat.colorSpace;
			createInfo.imageExtent = scExtent;
			createInfo.imageArrayLayers = 1;
			createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
			//createInfo.imageUsage = VK_IMAGE_USAGE_TRANSFER_DST_BIT;

			UI32 queueFamilyindices[] = {
				vDevice.GetQueue().GetGraphicsFamily().value(),
				vDevice.GetQueue().GetTransferFamily().value()
			};

			if (vDevice.GetQueue().GetGraphicsFamily() != vDevice.GetQueue().GetTransferFamily())
			{
				createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
				createInfo.queueFamilyIndexCount = 2;
				createInfo.pQueueFamilyIndices = queueFamilyindices;
			}
			else
			{
				createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
				createInfo.queueFamilyIndexCount = 0;
				createInfo.pQueueFamilyIndices = nullptr;
			}

			createInfo.preTransform = vSupport.capabilities.currentTransform;
			createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
			createInfo.presentMode = presentMode;
			createInfo.clipped = VK_TRUE;
			createInfo.oldSwapchain = VK_NULL_HANDLE;

			// Create the Vulkan Swap Chain.
			DMK_VK_ASSERT(vkCreateSwapchainKHR(vDevice.GetLogicalDevice(), &createInfo, nullptr, &vSwapChain), "Failed to create the Vulkan Swap Chain!");

			vImages.resize(mBufferCount);

			// Get the swap chain images.
			DMK_VK_ASSERT(vkGetSwapchainImagesKHR(vDevice.GetLogicalDevice(), vSwapChain, &mBufferCount, vImages.data()), "Failed to get the Vulkan Swap Chain Images!");

			vFormat = surfaceFormat.format;
			vImageViews = std::move(_Helpers::CreateImageViews(vImages, vFormat, vDevice.GetLogicalDevice()));
		}

		void SwapChain::Terminate(const VulkanDevice& vDevice)
		{
			// Terminate the image views.
			for (auto itr = vImageViews.begin(); itr != vImageViews.end(); itr++)
				vkDestroyImageView(vDevice.GetLogicalDevice(), *itr, nullptr);

			vImageViews.clear();

			// Terminate the Swap Chain.
			vkDestroySwapchainKHR(vDevice.GetLogicalDevice(), GetSwapChain(), nullptr);
			vSwapChain = VK_NULL_HANDLE;
			vImages.clear();
		}
	}
}