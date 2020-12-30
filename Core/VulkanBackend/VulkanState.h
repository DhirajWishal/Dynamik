// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace DMK
{
	namespace VulkanBackend
	{
		/**
		 * Vulkan State structure.
		 * This structure holds state information about a single Vulkan backend state.
		 */
		struct VulkanInstanceState {
			VkInstance vInstance = VK_NULL_HANDLE;
			VkDebugUtilsMessengerEXT vDebugMessenger = VK_NULL_HANDLE;
		};
	}
}