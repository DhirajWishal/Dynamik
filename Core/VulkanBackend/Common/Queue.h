// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Macros/Global.h"
#include "Core/Types/DataTypes.h"

#include <optional>

#define VK_ENABLE_BETA_EXTENSIONS
#include <vulkan/vulkan.h>

namespace DMK
{
	namespace VulkanBackend
	{
		/**
		 * Vulkan Queue obect.
		 * Vulkan uses queues to perform tasks.
		 */
		class Queue {
		public:
			/**
			 * Default constructor.
			 */
			Queue() = default;

			/**
			 * Default destructor.
			 */
			~Queue() {}

			/**
			 * Find Vulkan Queue families.
			 *
			 * @param vPhysicalDevice: The physical device to find for.
			 * @param vSurface: The surface it is attached to.
			 */
			void FindQueueFamilies(VkPhysicalDevice vPhysicalDevice, VkSurfaceKHR vSurface);

			/**
			 * Check if the queues are completed.
			 *
			 * @return Boolean value.
			 */
			bool IsComplete();

			/**
			 * Get the graphics family queue.
			 *
			 * @return std::optional<UI32> object.
			 */
			DMK_FORCEINLINE std::optional<UI32> GetGraphicsFamily() const { return graphicsFamily; }

			/**
			 * Get the compute family queue.
			 *
			 * @return std::optional<UI32> object.
			 */
			DMK_FORCEINLINE std::optional<UI32> GetComputeFamily() const { return computeFamily; }

			/**
			 * Get the transfer family queue.
			 *
			 * @return std::optional<UI32> object.
			 */
			DMK_FORCEINLINE std::optional<UI32> GetTransferFamily() const { return transferFamily; }

			/**
			 * Get the graphcis queue.
			 *
			 * @return VkQueue handle.
			 */
			DMK_FORCEINLINE VkQueue GetGraphicsQueue() const { return vGraphicsQueue; }

			/**
			 * Get the compute queue.
			 *
			 * @return VkQueue handle.
			 */
			DMK_FORCEINLINE VkQueue GetComputeQueue() const { return vComputeQueue; }

			/**
			 * Get the transfer queue.
			 *
			 * @return VkQueue handle.
			 */
			DMK_FORCEINLINE VkQueue GetTransferQueue() const { return vTransferQueue; }

			std::optional<UI32> graphicsFamily;     // Graphics Family
			std::optional<UI32> computeFamily;  // Compute Family
			std::optional<UI32> transferFamily;     // Transfer Family

			VkQueue vGraphicsQueue = VK_NULL_HANDLE;	// Graphics queue handle.
			VkQueue vComputeQueue = VK_NULL_HANDLE;		// Compute queue handle.
			VkQueue vTransferQueue = VK_NULL_HANDLE;	// Transfer queue handle.
		};
	}
}