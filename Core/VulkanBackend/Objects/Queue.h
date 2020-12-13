// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Types/StaticSparseSet.h"
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
			using Index = UI8;
			using Store = StaticSparseSet<VulkanQueue, Index>;

			std::optional<UI32> mGraphicsFamily;		// Graphics Family
			std::optional<UI32> mComputeFamily;			// Compute Family
			std::optional<UI32> mTransferFamily;		// Transfer Family

			VkQueue vGraphicsQueue = VK_NULL_HANDLE;	// Graphics queue handle.
			VkQueue vComputeQueue = VK_NULL_HANDLE;		// Compute queue handle.
			VkQueue vTransferQueue = VK_NULL_HANDLE;	// Transfer queue handle.
		};

		/**
		 * Create a temporary queue structure.
		 *
		 * @param vPhysicalDevice: The physical device to create the queue.
		 * @return The Vulkan Queue structure.
		 */
		VulkanQueue CreateTempQueue(const VkPhysicalDevice& vPhysicalDevice);

		/**
		 * Create a new Vulkan Queue structure.
		 * 
		 * @param vPhysicalDevice: The physical device to create the queue.
		 * @return VulkanQueue index.
		 */
		VulkanQueue::Index CreateQueue(const VkPhysicalDevice& vPhysicalDevice);

		/**
		 * Check if a queue if complete.
		 * 
		 * @param vQueue: The queue to be checked with.
		 * @return Boolean value.
		 */
		bool IsQueueComplete(const VulkanQueue& vQueue);

		/**
		 * Check if a queue if complete.
		 *
		 * @param vIndex: The queue index to be checked with.
		 * @return Boolean value.
		 */
		bool IsQueueComplete(const VulkanQueue::Index& vIndex);
	}
}