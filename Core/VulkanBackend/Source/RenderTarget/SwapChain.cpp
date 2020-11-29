// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/RenderTarget/SwapChain.h"
#include "VulkanBackend/Common/VulkanDevice.h"
#include "VulkanBackend/Common/Utilities.h"

namespace DMK
{
	namespace VulkanBackend
	{
		GraphicsCore::RenderTargetAttachmentHandle VulkanDevice::CreateSwapChain(GraphicsCore::RenderTargetAttachmentSpecification spec)
		{
			// Create the swap chain object.
			SwapChain vSwapChain = {};

			// Initialize the swap chain.
			vSwapChain.Initialize(*this, spec);

			// Add the swapchain to the store.
			vSwapChains.insert(vSwapChains.end(), std::move(vSwapChain));

			return GraphicsCore::RenderTargetAttachmentHandle(vSwapChains.size() - 1, GraphicsCore::RenderTargetAttachmentType::SWAP_CHAIN);
		}

		void VulkanDevice::DestroySwapChain(GraphicsCore::RenderTargetAttachmentHandle vSwapChainHandle)
		{
			// get and terminate the swap chain.
			(vSwapChains.data() + vSwapChainHandle.mHandle)->Terminate(*this);

			// Remove it from the vector.
			vSwapChains.erase(vSwapChains.begin() + vSwapChainHandle.mHandle);
		}

		void VulkanDevice::DestroyAllSwapChains()
		{
			// Terminate all the swap chains.
			for (auto itr = vSwapChains.begin(); itr != vSwapChains.end(); itr++)
				itr->Terminate(*this);

			vSwapChains.clear();
		}

		void SwapChain::Initialize(VulkanDevice& vDevice, const GraphicsCore::RenderTargetAttachmentSpecification& spec)
		{
			mSpecification = spec;
			vSampleCount = vDevice.GetMsaaSamples();

			// Get the swap chain support details.
			auto vSupport = vDevice.GetSwapChainSupportDetails();

			VkSurfaceFormatKHR surfaceFormat = Utilities::ChooseSwapSurfaceFormat(vSupport.formats);
			VkPresentModeKHR presentMode = Utilities::ChooseSwapPresentMode(vSupport.presentModes);
			VkExtent2D scExtent = Utilities::ChooseSwapExtent(vSupport.capabilities, static_cast<UI32>(spec.extent.width), static_cast<UI32>(spec.extent.height));

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
			DMK_VK_ASSERT(vkCreateSwapchainKHR(vDevice, &createInfo, nullptr, &vSwapChain), "Failed to create the Vulkan Swap Chain!");

			vImages.resize(mBufferCount);

			// Get the swap chain images.
			DMK_VK_ASSERT(vkGetSwapchainImagesKHR(vDevice, vSwapChain, &mBufferCount, vImages.data()), "Failed to get the Vulkan Swap Chain Images!");

			vFormat = surfaceFormat.format;
			vImageViews = std::move(Utilities::CreateImageViews(vImages, vFormat, vDevice));
		}

		void SwapChain::Terminate(const VulkanDevice& vDevice)
		{
			// Terminate the image views.
			for (auto itr = vImageViews.begin(); itr != vImageViews.end(); itr++)
				vkDestroyImageView(vDevice, *itr, nullptr);

			vImageViews.clear();

			// Terminate the Swap Chain.
			vkDestroySwapchainKHR(vDevice, vSwapChain, nullptr);
			vSwapChain = VK_NULL_HANDLE;
			vImages.clear();
		}

		VkAttachmentDescription SwapChain::GetAttachmentDescription() const
		{
			VkAttachmentDescription vDesc = {};
			vDesc.flags = VK_NULL_HANDLE;
			vDesc.format = vFormat;
			vDesc.samples = VK_SAMPLE_COUNT_1_BIT;
			vDesc.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			vDesc.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
			vDesc.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
			vDesc.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
			vDesc.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
			vDesc.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

			return vDesc;
		}

		VkImageLayout SwapChain::GetAttachmentLayout() const
		{
			return VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		}
	}
}