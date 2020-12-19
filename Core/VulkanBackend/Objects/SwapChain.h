// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Device.h"
#include "GraphicsCore/Backend/ViewPort.h"

namespace DMK
{
	namespace VulkanBackend
	{
		/**
		 * Vulkan Swap Chain structure.
		 */
		struct VulkanSwapChain {
			std::vector<VkImage> mImages;
			std::vector<VkImageView> mImageViews;

			VkSwapchainKHR vSwapChain = VK_NULL_HANDLE;

			static VulkanSwapChain Create(const VulkanDevice& vDevice, const GraphicsCore::ViewPort& viewPort);
			static void Destroy(const VulkanDevice& vDevice, const VulkanSwapChain& vSwapChain);
		};
	}
}