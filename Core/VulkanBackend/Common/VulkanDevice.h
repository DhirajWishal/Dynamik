// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Macros/Global.h"
#include "GraphicsCore/Backend/DeviceHandle.h"

#include "Macros.h"
#include "VulkanQueue.h"

#include <optional>
#include <GLFW/glfw3.h>

namespace DMK
{
	namespace VulkanBackend
	{
		class VulkanInstance;

		/**
		 * Structure containing support details for a Vulkan Swap Chain.
		 */
		struct VulkanSwapChainSupportDetails {
			VkSurfaceCapabilitiesKHR capabilities = {};		// Swap Chain capabilities.
			std::vector<VkSurfaceFormatKHR> formats = {};	// Swap Chain formats.
			std::vector<VkPresentModeKHR> presentModes = {};	// Swap Chain present modes.
		};

		/**
		 * Vulkan Device for Dynamik.
		 *
		 * This uses GLFW to create and manage the window and inputs.
		 */
		class VulkanDevice {
		public:
			/**
			 * Default constructor.
			 */
			VulkanDevice() {}

			/**
			 * Default destructor.
			 */
			~VulkanDevice() {}

			/**
			 * Initialize the device.
			 *
			 * @param initInfo: The DeviceInitInfo structure contining the initialization information.
			 * @param pInstance: The instance which the device belongs to.
			 */
			void Initialize(const GraphicsCore::DeviceInitInfo& initInfo, VulkanInstance* pInstance);

			/**
			 * Terminate the device.
			 */
			void Terminate();

			/**
			 * Begin a new frame.
			 *
			 * @return 8 bit integer representing the frame index. Returns -1 if an error has occured.
			 */
			I8 BeginFrame();

			/**
			 * End the new frame by execuring all the commands.
			 */
			void EndFrame();

		public:
			/**
			 * Get the GLFW window handle.
			 *
			 * @return GLFWwindow pointer.
			 */
			DMK_FORCEINLINE GLFWwindow* GetWindowHandle() const { return pWindowHandle; }

			/**
			 * Get the Vulkan surface.
			 *
			 * @return VkSurfaceKHR handle.
			 */
			DMK_FORCEINLINE VkSurfaceKHR GetSurface() const { return vSurface; }

			/**
			 * Get the Vulkan physical device.
			 *
			 * @return VkPhysicalDevice handle.
			 */
			DMK_FORCEINLINE VkPhysicalDevice GetPhysicalDevice() const { return vPhysicalDevice; }

			/**
			 * Get Vulkan logical device.
			 *
			 * @return VkDevice handle.
			 */
			DMK_FORCEINLINE VkDevice GetLogicalDevice() const { return vLogicalDevice; }

			/**
			 * Get the Vulkan Queues.
			 *
			 * @return VulkanQueue object.
			 */
			DMK_FORCEINLINE VulkanQueue GetQueue() const { return vQueue; }

			/**
			 * Get the init info of the device.
			 *
			 * @return DeviceInitInfo structure.
			 */
			DMK_FORCEINLINE GraphicsCore::DeviceInitInfo GetInitInfo() const { return initInfo; }

			/**
			 * Get the parent instance which the device is bound to.
			 *
			 * @return The VulkanInstance object.
			 */
			DMK_FORCEINLINE VulkanInstance* GetParentInstance() const { return pInstance; }

		private:
			/**
			 * Initialize the display object.
			 */
			void InitializeDisplay();

			/**
			 * Terminate the display object.
			 */
			void TerminateDisplay();

			/**
			 * Create the window surface.
			 */
			void CreateSurface();

			/**
			 * Destroy the window surface.
			 */
			void DestroySurface();

			/**
			 * Create the Vulkan Physical Device.
			 */
			void InitializePhysicalDevice();

			/**
			 * Terminate the Vulkan Physical Device.
			 */
			void TerminatePhysicalDevice();

			/**
			 * Initialize the Vulkan logical device.
			 */
			void InitializeLogicalDevice();

			/**
			 * Terminate the Vulkan logical device.
			 */
			void TerminateLogicalDevice();

		public:
			/**
			 * Get the physical device properties.
			 *
			 * @return VkPhysicalDeviceProperties structure.
			 */
			DMK_FORCEINLINE VkPhysicalDeviceProperties GetPhysicalDeviceProperties() const { return vPhysicalDeviceProperties; }

			/**
			 * Get the physical device ray tracing properties.
			 *
			 * @return VkPhysicalDeviceRayTracingPropertiesKHR structure.
			 */
			DMK_FORCEINLINE VkPhysicalDeviceRayTracingPropertiesKHR GetPhysicalDeviceRayTracingProperties() const { return vPhysicalDeviceRayTracingProperties; }

			/**
			 * Get the physical device ray tracing properties.
			 *
			 * @return VkPhysicalDeviceRayTracingFeaturesKHR structure.
			 */
			DMK_FORCEINLINE VkPhysicalDeviceRayTracingFeaturesKHR GetPhysicalDeviceRayTracingFeatures() const { return vPhysicalDeviceRayTracingFeatures; }

			/**
			 * Query swap chain support details for this device.
			 *
			 * @return VulkanSwapChainSupportDetails structure.
			 */
			VulkanSwapChainSupportDetails QuerySwapChainSupportDetails();

			VkPhysicalDeviceProperties vPhysicalDeviceProperties = {};	// Physical device properties.
			VkPhysicalDeviceRayTracingFeaturesKHR vPhysicalDeviceRayTracingFeatures = {};	// Ray tracing features.
			VkPhysicalDeviceRayTracingPropertiesKHR vPhysicalDeviceRayTracingProperties = {};	// Ray tracing properties.

		private:
			/**
			 * Check if a physical device is suitable to use.
			 *
			 * @param vDevice: The physical device to be checked.
			 * @return Boolean value.
			 */
			bool IsPhysicalDeviceSuitable(VkPhysicalDevice vDevice);

		private:
			VulkanQueue vQueue = {};	// Vulkan queue object.

			std::vector<const char*> instanceExtensions;	// Instance extensions.
			std::vector<const char*> deviceExtensions;	// Device extensions.

			GLFWwindow* pWindowHandle = nullptr;	// The GLFW window pointer.
			VkSurfaceKHR vSurface = VK_NULL_HANDLE;	// The display surface.

			VkPhysicalDevice vPhysicalDevice = VK_NULL_HANDLE;	// The physical device.
			VkDevice vLogicalDevice = VK_NULL_HANDLE;	// The logical device.

			VulkanInstance* pInstance = nullptr;	// The Vulkan instance pointer.

			GraphicsCore::DeviceInitInfo initInfo = {};	// Initialize information of the device.
			I8 frameIndex = 0;	// The current frame index.
		};
	}
}
