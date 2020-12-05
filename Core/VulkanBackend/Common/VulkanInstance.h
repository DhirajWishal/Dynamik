// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "VulkanDevice.h"

namespace DMK
{
	namespace VulkanBackend
	{
		/**
		 * Vulkan Instance object.
		 * This object stores information and the state of the Vulkan Instance along with its debuger.
		 */
		class VulkanInstance {
		public:
			VulkanInstance() {}
			~VulkanInstance() {}

			/**
			 * Initialize the backend instance.
			 */
			void Initialize(bool enableValidation);

			/**
			 * Terminate the backend instance.
			 */
			void Terminate();

		public:
			/**
			 * Get the Vulkan Instance.
			 *
			 * @return VkInstance handle.
			 */
			DMK_FORCEINLINE VkInstance GetInstance() const { return vInstance; }

			/**
			 * Get the Vulkan Debug Messenger.
			 *
			 * @return VkDebugUtilsMessengerEXT handle.
			 */
			DMK_FORCEINLINE VkDebugUtilsMessengerEXT GetDebugMessenger() const { return vDebugMessenger; }

			/**
			 * Get the validation layers used by the instance.
			 *
			 * @param: The vector containing the validation layers.
			 */
			DMK_FORCEINLINE const std::vector<const char*>& GetValidationLayers() const { return this->validationLayers; }

		private:
			/**
			 * Setup the GLFW instance.
			 */
			void SetupGLFW();

			/**
			 * Initialize the Vulkan Instance.
			 */
			void InitializeInstance();

			/**
			 * Terminate the Vulkan Instance.
			 */
			void TerminateInstance();

			/**
			 * Initialize the Vulkan Debugger.
			 */
			void InitializeDebugger();

			/**
			 * Terminate the Vulkan Debugger.
			 */
			void TeminateDebugger();

		public:
			std::vector<const char*> validationLayers;	// Validation layers.
			std::vector<const char*> instanceExtensions;	// Instance extensions.

			VkInstance vInstance = VK_NULL_HANDLE;	// Vulkan instance handle.
			VkDebugUtilsMessengerEXT vDebugMessenger = VK_NULL_HANDLE;	// Vulkan debug messenger handle.

			bool enableValidation = true;	// Boolean if to enable validation.
		};
	}
}
