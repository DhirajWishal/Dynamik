// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanSwapChain.h"

#include "../VulkanUtilities.h"

namespace Backend
{
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const ARRAY<VkSurfaceFormatKHR>& availableFormats)
	{
		for (const auto& availableFormat : availableFormats)
			if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM
				&& availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
				return availableFormat;

		return ((ARRAY<VkSurfaceFormatKHR>)availableFormats)[0];
	}

	VkPresentModeKHR chooseSwapPresentMode(const ARRAY<VkPresentModeKHR>& availablePresentModes, RSwapChainPresentMode presentMode)
	{
		VkPresentModeKHR bestMode = VK_PRESENT_MODE_FIFO_KHR;

		for (const auto& availablePresentMode : availablePresentModes)
		{
			if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
				return availablePresentMode;
			else if (availablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR)
				bestMode = availablePresentMode;
			else if (availablePresentMode == VulkanUtilities::getPresentMode(presentMode))
				bestMode = availablePresentMode;
		}

		return bestMode;
	}

	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, UI32 width, UI32 height)
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

	VulkanSwapChainSupportDetails VulkanSwapChain::querySwapChainSupport(const VkPhysicalDevice& physicalDevice, const VkSurfaceKHR& surface)
	{
		VulkanSwapChainSupportDetails details;
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &details.capabilities);

		UI32 formatCount = 0;
		vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, nullptr);

		if (formatCount != 0)
		{
			details.formats.reserve(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, details.formats.data());
		}

		UI32 presentModeCount = 0;
		vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, nullptr);

		if (presentModeCount != 0)
		{
			details.presentModes.reserve(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, details.presentModes.data());
		}

		return details;
	}

	void VulkanSwapChain::initialize(RCoreObject* pCoreObject, DMKViewport viewport, RSwapChainPresentMode ePresentMode)
	{
		viewPort = viewport;
		VulkanSwapChainSupportDetails swapChainSupport = querySwapChainSupport(Inherit<VulkanCoreObject>(pCoreObject)->device, Inherit<VulkanCoreObject>(pCoreObject)->surface);

		VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
		VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes, ePresentMode);
		VkExtent2D scExtent = chooseSwapExtent(swapChainSupport.capabilities, viewPort.width, viewPort.width);

		/* TODO */
		viewPort.width = scExtent.width;
		viewPort.height = scExtent.height;

		VkCompositeAlphaFlagBitsKHR surfaceComposite =
			(Inherit<VulkanCoreObject>(pCoreObject)->surface.surfaceCapabilities.supportedCompositeAlpha & VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR)
			? VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR
			: (Inherit<VulkanCoreObject>(pCoreObject)->surface.surfaceCapabilities.supportedCompositeAlpha & VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR)
			? VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR
			: (Inherit<VulkanCoreObject>(pCoreObject)->surface.surfaceCapabilities.supportedCompositeAlpha & VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR)
			? VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR
			: VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR;

		bufferCount = swapChainSupport.capabilities.minImageCount + 1;
		if (swapChainSupport.capabilities.maxImageCount > 0
			&& bufferCount > swapChainSupport.capabilities.maxImageCount)
			bufferCount = swapChainSupport.capabilities.maxImageCount;

		VkSwapchainCreateInfoKHR createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = Inherit<VulkanCoreObject>(pCoreObject)->surface;
		createInfo.minImageCount = bufferCount;
		createInfo.imageFormat = surfaceFormat.format;
		createInfo.imageColorSpace = surfaceFormat.colorSpace;
		createInfo.imageExtent = scExtent;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		//createInfo.imageUsage = VK_IMAGE_USAGE_TRANSFER_DST_BIT;

		UI32 queueFamilyindices[] = {
			Inherit<VulkanCoreObject>(pCoreObject)->queues.processFamily.value(),
			Inherit<VulkanCoreObject>(pCoreObject)->queues.utilityFamily.value()
		};

		if (Inherit<VulkanCoreObject>(pCoreObject)->queues.processFamily != Inherit<VulkanCoreObject>(pCoreObject)->queues.utilityFamily)
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

		createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = presentMode;
		createInfo.clipped = VK_TRUE;
		createInfo.oldSwapchain = VK_NULL_HANDLE;

		if (vkCreateSwapchainKHR(Inherit<VulkanCoreObject>(pCoreObject)->device, &createInfo, nullptr, &swapChain))
			DMK_ERROR_BOX("Failed to create Swap Chain!");

		vkGetSwapchainImagesKHR(Inherit<VulkanCoreObject>(pCoreObject)->device, swapChain, &bufferCount, nullptr);
		ARRAY<VkImage> _images(bufferCount);
		vkGetSwapchainImagesKHR(Inherit<VulkanCoreObject>(pCoreObject)->device, swapChain, &bufferCount, _images.data());

		format = (DMKFormat)surfaceFormat.format;

		for (auto _image : _images)
		{
			VulkanImage* _vImage = StaticAllocator<VulkanImage>::rawAllocate();
			_vImage->image = _image;
			_vImage->format = format;
			_vImage->layers = 1;
			_vImage->mipLevel = 1;

			DMKTexture::TextureSwizzles _swizzles = {
				DMKTextureSwizzle::TEXTURE_SWIZZLE_IDENTITY,
				DMKTextureSwizzle::TEXTURE_SWIZZLE_IDENTITY,
				DMKTextureSwizzle::TEXTURE_SWIZZLE_IDENTITY,
				DMKTextureSwizzle::TEXTURE_SWIZZLE_IDENTITY };
			_vImage->createImageView(pCoreObject, _swizzles);
			images.pushBack(_vImage);
		}

		extent.width = Cast<F32>(scExtent.width);
		extent.height = Cast<F32>(scExtent.height);
	}

	void VulkanSwapChain::terminate(RCoreObject* pCoreObject)
	{
		for (auto image : images)
		{
			image->pImageView->terminate(pCoreObject);
			StaticAllocator<VulkanImageView>::rawDeallocate(image->pImageView);
			StaticAllocator<VulkanImage>::rawDeallocate(image);
		}
		images.clear();

		vkDestroySwapchainKHR(InheritCast<VulkanCoreObject>(pCoreObject).device, swapChain, nullptr);
	}

	VulkanSwapChain::operator VkSwapchainKHR() const
	{
		return this->swapChain;
	}
}
