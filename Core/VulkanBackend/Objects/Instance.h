// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Types/StaticSparseSet.h"
#include <vulkan/vulkan.h>

namespace DMK
{
	namespace VulkanBackend
	{
		/**
		 * Vulkan Instance structure.
		 * This structure stores the instance and the debugger.
		 */
		struct VulkanInstance {
			using Index = UI8;
			using Store = StaticSparseSet<VulkanInstance, Index>;

			std::vector<const char*> mValidationLayers;

			VkInstance vInstance = VK_NULL_HANDLE;
			VkDebugUtilsMessengerEXT vDebugMessenger = VK_NULL_HANDLE;
		};

		/**
		 * Initialize GLFW.
		 * This function should be called before calling any other Vulkan Backend based functions and should not be
		 * called multiple times.
		 */
		void InitializeGLFW();

		/**
		 * Terminate GLFW.
		 * This function should be called right after terminating the Vulkan Backend and the backend based displays.
		 */
		void TerminateGLFW();

		/**
		 * Create a new Vulkan Instance.
		 *
		 * @param enableValidation: Whether or not to enable validation.
		 * @return The instance index.
		 */
		VulkanInstance::Index CreateInstance(bool enableValidation);

		/**
		 * Destroy a created instance.
		 *
		 * @param vInstance: The instance handle.
		 */
		void DestroyInstance(const VulkanInstance::Index& vInstance);
	}
}