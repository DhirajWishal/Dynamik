// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/RenderTarget/VulkanSwapChain.h"
#include "VulkanBackend/Macros.h"
#include "VulkanBackend/VulkanDevice.h"
#include "VulkanBackend/VulkanDisplay.h"

namespace DMK
{
	namespace VulkanBackend
	{
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

			VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, UI32 width, UI32 height)
			{
				VkExtent2D actualExtent = {
					width,
					height
				};

				if ((width >= capabilities.maxImageExtent.width) || (width <= capabilities.minImageExtent.width))
					actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));

				if ((height >= capabilities.maxImageExtent.height) || (height <= capabilities.minImageExtent.height))
					actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));

				return actualExtent;
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

		void VulkanSwapChain::Initialize(VulkanDevice* pDevice, Vector2 extent, UI32 bufferCount)
		{
			SwapChainSupportDetails& vSupport = pDevice->GetSwapChainSupportDetails();
			VkSurfaceFormatKHR surfaceFormat = _Helpers::ChooseSwapSurfaceFormat(vSupport.formats);
			VkPresentModeKHR presentMode = _Helpers::ChooseSwapPresentMode(vSupport.presentModes);

			auto& vCapabilities = pDevice->GetSurfaceCapabilities();
			VkCompositeAlphaFlagBitsKHR surfaceComposite = static_cast<VkCompositeAlphaFlagBitsKHR>(vCapabilities.supportedCompositeAlpha);
			surfaceComposite = (surfaceComposite & VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR)
				? VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR
				: (surfaceComposite & VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR)
				? VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR
				: (surfaceComposite & VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR)
				? VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR
				: VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR;

			UI32 bufferCount = vCapabilities.minImageCount + 1;
			if (vCapabilities.maxImageCount > 0
				&& bufferCount > vCapabilities.maxImageCount)
				bufferCount = vCapabilities.maxImageCount;

			VkSwapchainCreateInfoKHR vCI = {};
			vCI.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
			vCI.flags = VK_NULL_HANDLE;
			vCI.pNext = VK_NULL_HANDLE;
			vCI.surface = pDevice->GetDisplay()->Derive<VulkanDisplay>()->GetSurface();
			vCI.minImageCount = bufferCount;
			vCI.imageFormat = surfaceFormat.format;
			vCI.imageColorSpace = surfaceFormat.colorSpace;
			vCI.imageExtent = { static_cast<UI32>(extent.x), static_cast<UI32>(extent.y) };
			vCI.imageArrayLayers = 1;
			vCI.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

			UI32 queueFamilyindices[2] = {
					pDevice->GetQueue().mGraphicsFamily.value(),
					pDevice->GetQueue().mTransferFamily.value()
			};

			if (pDevice->GetQueue().mGraphicsFamily != pDevice->GetQueue().mTransferFamily)
			{
				vCI.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
				vCI.queueFamilyIndexCount = 2;
				vCI.pQueueFamilyIndices = queueFamilyindices;
			}
			else
			{
				vCI.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
				vCI.queueFamilyIndexCount = 0;
				vCI.pQueueFamilyIndices = nullptr;
			}

			vCI.preTransform = vSupport.capabilities.currentTransform;
			vCI.compositeAlpha = surfaceComposite;
			vCI.presentMode = presentMode;
			vCI.clipped = VK_TRUE;
			vCI.oldSwapchain = VK_NULL_HANDLE;

			DMK_VK_ASSERT(vkCreateSwapchainKHR(pDevice->GetLogicalDevice(), &vCI, nullptr, &vSwapChain), "Failed to create the Vulkan Swap Chain!");

			vImages.resize(vCI.minImageCount);
			DMK_VK_ASSERT(vkGetSwapchainImagesKHR(pDevice->GetLogicalDevice(), vSwapChain, &vCI.minImageCount, vImages.data()), "Failed to get the Vulkan Swap Chain Images!");

			vImageViews = std::move(_Helpers::CreateImageViews(vImages, vCI.imageFormat, pDevice->GetLogicalDevice()));
		}

		void VulkanSwapChain::Terminate(VulkanDevice* pDevice)
		{
			// Terminate the image views.
			for (auto itr = vImageViews.begin(); itr != vImageViews.end(); itr++)
				vkDestroyImageView(pDevice->GetLogicalDevice(), *itr, nullptr);

			vImageViews.clear();

			// Terminate the Swap Chain.
			vkDestroySwapchainKHR(pDevice->GetLogicalDevice(), vSwapChain, nullptr);
			vSwapChain = VK_NULL_HANDLE;
			vImages.clear();
		}
	}
}