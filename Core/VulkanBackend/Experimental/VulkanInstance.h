// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GraphicsCore/Experimental/Instance.h"

#include <vulkan/vulkan.h>

namespace DMK
{
	namespace VulkanBackend
	{
		/**
		 * Vulkan Instance object.
		 */
		class VulkanInstance : public GraphicsCore::Instance {
		public:
			VulkanInstance() {}
			~VulkanInstance() {}

			/**
			 * Initialize the instance.
			 *
			 * @param enableValidation: Boolean whether to enable API validation.
			 */
			virtual void Initialize(bool enableValidation) override final;

			/**
			 * Terminate the instance.
			 */
			virtual void Terminate() override final;

			/**
			 * Create a new device.
			 *
			 * @param initInfo: The device initialization information.
			 */
			virtual GraphicsCore::Device* CreateDevice(const GraphicsCore::DeviceInitInfo& initInfo) override final;

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