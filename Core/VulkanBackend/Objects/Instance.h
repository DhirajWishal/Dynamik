// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GraphicsCore/Backend/BackendHandles.h"
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
			std::vector<const char*> mValidationLayers;

			VkInstance vInstance = VK_NULL_HANDLE;
			VkDebugUtilsMessengerEXT vDebugMessenger = VK_NULL_HANDLE;

			static VulkanInstance Create(bool enableValidation);
			static void Destroy(const VulkanInstance& vInstance);
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
	}
}