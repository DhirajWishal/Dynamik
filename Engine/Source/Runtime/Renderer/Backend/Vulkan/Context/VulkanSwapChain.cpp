#include "dmkafx.h"
#include "VulkanSwapChain.h"

namespace Dynamik
{
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

		VkPresentModeKHR chooseSwapPresentMode(const ARRAY<VkPresentModeKHR>& availablePresentModes)
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
				details.formats.resize(formatCount);
				vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, details.formats.data());
			}

			UI32 presentModeCount = 0;
			vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, nullptr);

			if (presentModeCount != 0)
			{
				details.presentModes.resize(presentModeCount);
				vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, details.presentModes.data());
			}

			return details;
		}

		void VulkanSwapChain::initialize(const VulkanDevice& vDevice, const VulkanQueue& vQueue, VulkanViewport vViewport)
		{
			myViewport = vViewport;
			VulkanSwapChainSupportDetails swapChainSupport = querySwapChainSupport(vDevice, vViewport.surfacePtr.dereference());

			VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
			VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
			VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities, vViewport.width, vViewport.width);

			VkCompositeAlphaFlagBitsKHR surfaceComposite =
				(vViewport.surfacePtr->surfaceCapabilities.supportedCompositeAlpha & VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR)
				? VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR
				: (vViewport.surfacePtr->surfaceCapabilities.supportedCompositeAlpha & VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR)
				? VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR
				: (vViewport.surfacePtr->surfaceCapabilities.supportedCompositeAlpha & VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR)
				? VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR
				: VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR;

			UI32 imageCount = swapChainSupport.capabilities.minImageCount + 1;
			if (swapChainSupport.capabilities.maxImageCount > 0
				&& imageCount > swapChainSupport.capabilities.maxImageCount)
				imageCount = swapChainSupport.capabilities.maxImageCount;

			VkSwapchainCreateInfoKHR createInfo = {};
			createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
			createInfo.surface = vViewport.surfacePtr->surface;
			createInfo.minImageCount = imageCount;
			createInfo.imageFormat = surfaceFormat.format;
			createInfo.imageColorSpace = surfaceFormat.colorSpace;
			createInfo.imageExtent = extent;
			createInfo.imageArrayLayers = 1;
			createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
			//createInfo.imageUsage = VK_IMAGE_USAGE_TRANSFER_DST_BIT;

			UI32 queueFamilyindices[] = {
				vQueue.processFamily.value(),
				vQueue.utilityFamily.value()
			};

			if (vQueue.processFamily != vQueue.utilityFamily)
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

			if (vkCreateSwapchainKHR(vDevice, &createInfo, nullptr, &swapChain))
				DMK_ERROR_BOX("Failed to create Swap Chain!");

			vkGetSwapchainImagesKHR(vDevice, swapChain, &imageCount, nullptr);
			ARRAY<VkImage> _images(imageCount);
			vkGetSwapchainImagesKHR(vDevice, swapChain, &imageCount, _images.data());

			swapChainImageFormat = surfaceFormat.format;

			for (auto _image : _images)
			{
				VulkanImage _vImage;
				_vImage.image = _image;
				_vImage.imageFormat = swapChainImageFormat;
				_vImage.layers = 1;
				_vImage.mipLevel = 1;
				swapChainImages.pushBack(_vImage);
			}

			swapChainImageFormat = surfaceFormat.format;
			swapChainExtent = extent;

			_initializeImageViews(vDevice);
		}

		void VulkanSwapChain::terminate(const VulkanDevice& vDevice)
		{
		}

		VulkanSwapChain::operator VkSwapchainKHR() const
		{
			return this->swapChain;
		}

		void VulkanSwapChain::_initializeImageViews(const VulkanDevice& vDevice)
		{
			for (UI32 itr = 0; itr < swapChainImages.size(); itr++)
			{
				VulkanImageView _vView;
				_vView.initialize(vDevice, swapChainImages[itr]);
				swapChainImageViews.pushBack(_vView);
			}
		}
	}
}