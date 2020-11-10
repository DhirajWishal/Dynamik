// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_BACKEND_DEVICE_H
#define _DYNAMIK_VULKAN_BACKEND_DEVICE_H

#include "GraphicsCore/Backend/Common/GDevice.h"
#include "Macros.h"

#include <optional>

#define VK_ENABLE_BETA_EXTENSIONS
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

namespace DMK
{
	namespace GraphicsCore
	{
		namespace VulkanBackend
		{
			class VulkanBackendInstance;

			/**
			 * Vulkan Queue obect.
			 * Vulkan uses queues to perform tasks.
			 */
			class VulkanQueue {
			public:
				/**
				 * Default constructor.
				 */
				VulkanQueue() = default;

				/**
				 * Default destructor.
				 */
				~VulkanQueue() {}

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
			class VulkanDevice final : public GDevice {
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
				 */
				virtual void Initialize(const DeviceInitInfo& initInfo) override final;

				/**
				 * Terminate the device.
				 */
				virtual void Terminate() override final;

				/**
				 * Begin a new frame.
				 *
				 * @return 8 bit integer representing the frame index. Returns -1 if an error has occured.
				 */
				virtual I8 BeginFrame() override final;

				/**
				 * End the new frame by execuring all the commands.
				 */
				virtual void EndFrame() override final;

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
			};
		}
	}
}

#endif // !_DYNAMIK_VULKAN_BACKEND_DEVICE_H
