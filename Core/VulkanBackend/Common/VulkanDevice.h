// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Macros/Global.h"
#include "GraphicsCore/Backend/DeviceHandle.h"

#include "Macros.h"
#include "Queue.h"

#include "VulkanBackend/RenderTarget/SwapChain.h"
#include "VulkanBackend/RenderTarget/ColorBuffer.h"

#include <optional>
#include <GLFW/glfw3.h>
#include <vulkan/vulkan_beta.h>

namespace DMK
{
	namespace VulkanBackend
	{
		class VulkanInstance;

		/**
		 * Structure containing support details for a Vulkan Swap Chain.
		 */
		struct SwapChainSupportDetails {
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
			 * This will terminate all the created resources and objects with it.
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
			 * @return Queue object.
			 */
			DMK_FORCEINLINE Queue GetQueue() const { return vQueue; }

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

			/**
			 * Get the Vulkan MSAA samples.
			 *
			 * @return VkSampleCountFlags enum.
			 */
			DMK_FORCEINLINE VkSampleCountFlags GetMsaaSamples() const { return vMsaaSamples; }

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
			 * Get the surface capabilities.
			 *
			 * @return VkSurfaceCapabilitiesKHR structure.
			 */
			DMK_FORCEINLINE VkSurfaceCapabilitiesKHR GetSurfaceCapabilities() const { return vSurfaceCapabilities; }

			/**
			 * Get the Swap Chain support details.
			 *
			 * @return SwapChainSupportDetails structure.
			 */
			DMK_FORCEINLINE SwapChainSupportDetails GetSwapChainSupportDetails() const { return vSwapChainSupportDetails; }

			VkPhysicalDeviceProperties vPhysicalDeviceProperties = {};	// Physical device properties.
			VkPhysicalDeviceRayTracingFeaturesKHR vPhysicalDeviceRayTracingFeatures = {};	// Ray tracing features.
			VkPhysicalDeviceRayTracingPropertiesKHR vPhysicalDeviceRayTracingProperties = {};	// Ray tracing properties.
			VkSurfaceCapabilitiesKHR vSurfaceCapabilities = {};	// Surface capabilities.
			SwapChainSupportDetails vSwapChainSupportDetails = {};	// Vulkan Swap Chain support details.

		private:
			/**
			 * Check if a physical device is suitable to use.
			 *
			 * @param vDevice: The physical device to be checked.
			 * @return Boolean value.
			 */
			bool IsPhysicalDeviceSuitable(VkPhysicalDevice vDevice);

			/* Render Target */
		public:
			/**
			 * Create a Swap Chain object.
			 *
			 * @param spec: The render target attachment specification.
			 * @return Vulkan Swap Chain handle.
			 */
			SwapChainHandle CreateSwapChain(GraphicsCore::RenderTargetAttachmentSpecification spec);

			/**
			 * Destroy a created swap chain.
			 *
			 * @param vSwapChainHandle: The swap chain object handle to be destroyed.
			 */
			void DestroySwapChain(SwapChainHandle vSwapChainHandle);

			/**
			 * This method destroys all the created swap chain objects.
			 */
			void DestroyAllSwapChains();

			std::vector<SwapChain> vSwapChains;	// All the created swap chains.

			/**
			 * Create a Color Buffer object.
			 *
			 * @param spec: The render target attachment specification.
			 * @return Vulkan Color Buffer handle.
			 */
			ColorBufferHandle CreateColorBuffer(GraphicsCore::RenderTargetAttachmentSpecification spec);

			/**
			 * Destroy a created Color Buffer object.
			 *
			 * @param vColorBufferHandle: The handle of the color buffer to be destroyed.
			 */
			void DestroyColorBuffer(ColorBufferHandle vColorBufferHandle);

			/**
			 * This method will destroy all the created color buffers in this device.
			 */
			void DestroyAllColorBuffers();

			std::vector<ColorBuffer> vColorBuffers;	// All the created color buffers.

		private:
			Queue vQueue = {};	// Vulkan queue object.

			std::vector<const char*> deviceExtensions;	// Device extensions.

			GLFWwindow* pWindowHandle = nullptr;	// The GLFW window pointer.
			VkSurfaceKHR vSurface = VK_NULL_HANDLE;	// The display surface.

			VkPhysicalDevice vPhysicalDevice = VK_NULL_HANDLE;	// The physical device.
			VkDevice vLogicalDevice = VK_NULL_HANDLE;	// The logical device.

			VulkanInstance* pInstance = nullptr;	// The Vulkan instance pointer.

			GraphicsCore::DeviceInitInfo initInfo = {};	// Initialize information of the device.

			VkSampleCountFlags vMsaaSamples = VK_SAMPLE_COUNT_1_BIT;	// Vulkan Multi Sampling Anti Aliasing bits.

			I8 frameIndex = 0;	// The current frame index.
		};
	}
}
