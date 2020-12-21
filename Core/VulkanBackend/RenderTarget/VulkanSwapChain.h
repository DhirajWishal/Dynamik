// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Maths/Vector/Vector2.h"
#include <vulkan/vulkan.h>

namespace DMK
{
	namespace VulkanBackend
	{
		class VulkanDevice;

		class VulkanSwapChain {
		public:
			VulkanSwapChain() {}
			~VulkanSwapChain() {}

			void Initialize(VulkanDevice* pDevice, Vector2 extent, UI32 bufferCount);
			void Terminate(VulkanDevice* pDevice);

		private:
			std::vector<VkImage> vImages;
			std::vector<VkImageView> vImageViews;

			VkSwapchainKHR vSwapChain = VK_NULL_HANDLE;
		};
	}
}