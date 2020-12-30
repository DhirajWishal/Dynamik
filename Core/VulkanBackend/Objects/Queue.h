// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Types/DataTypes.h"
#include <optional>
#include <vulkan/vulkan.h>

namespace DMK
{
	namespace VulkanBackend
	{
		struct VulkanDevice;

		/**
		 * Vulkan Queue structure.
		 */
		struct VulkanQueue {
			std::optional<UI32> mGraphicsFamily;		// Graphics Family
			std::optional<UI32> mComputeFamily;			// Compute Family
			std::optional<UI32> mTransferFamily;		// Transfer Family

			VkQueue vGraphicsQueue = VK_NULL_HANDLE;	// Graphics queue handle.
			VkQueue vComputeQueue = VK_NULL_HANDLE;		// Compute queue handle.
			VkQueue vTransferQueue = VK_NULL_HANDLE;	// Transfer queue handle.

			static VulkanQueue Create(const VkPhysicalDevice& vPhysicalDevice);
			static bool IsComplete(const VulkanQueue& vQueue);
		};
	}
}