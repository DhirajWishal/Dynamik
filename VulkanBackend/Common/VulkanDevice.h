// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_BACKEND_DEVICE_H
#define _DYNAMIK_VULKAN_BACKEND_DEVICE_H

#include "GraphicsCore/Backend/Common/GDevice.h"
#include "Macros.h"

#include <optional>

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_beta.h>
#include <GLFW/glfw3.h>

namespace DMK
{
	namespace GraphicsCore
	{
		namespace VulkanBackend
		{
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
				 * @return: Boolean value.
				 */
				bool IsComplete();

				/**
				 * Get the graphics family queue.
				 *
				 * @return: std::optional<UI32> object.
				 */
				DMK_FORCEINLINE std::optional<UI32> GetGraphicsFamily() const { return graphicsFamily; }

				/**
				 * Get the compute family queue.
				 *
				 * @return: std::optional<UI32> object.
				 */
				DMK_FORCEINLINE std::optional<UI32> GetComputeFamily() const { return computeFamily; }

				/**
				 * Get the transfer family queue.
				 *
				 * @return: std::optional<UI32> object.
				 */
				DMK_FORCEINLINE std::optional<UI32> GetTransferFamily() const { return transferFamily; }

				/**
				 * Get the graphcis queue.
				 *
				 * @return: VkQueue handle.
				 */
				DMK_FORCEINLINE VkQueue GetGraphicsQueue() const { return vGraphicsQueue; }

				/**
				 * Get the compute queue.
				 *
				 * @return: VkQueue handle.
				 */
				DMK_FORCEINLINE VkQueue GetComputeQueue() const { return vComputeQueue; }

				/**
				 * Get the transfer queue.
				 *
				 * @return: VkQueue handle.
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
				 * @return: 8 bit integer representing the frame index. Returns -1 if an error has occured.
				 */
				virtual I8 BeginFrame() override final;

				/**
				 * End the new frame by execuring all the commands.
				 */
				virtual void EndFrame() override final;

				/* Command Buffer creation */
			public:
				/**
				 * Create command buffers to record GPU bound commands.
				 *
				 * @param level: The level of the command buffer.
				 * @param bufferCount: The number of buffers to be created.
				 * @return: A vector of allocated command buffer object pointers.
				 */
				virtual std::vector<CommandBuffer*> CreateCommandBuffers(CommandBufferLevel level, UI32 bufferCount) override final;

				/**
				 * Submit commands to the device.
				 * This executes the commands recorded in the command buffers.
				 *
				 * @param pCommands: The command buffers to be submitted.
				 */
				virtual void SubmitCommands(std::vector<CommandBuffer*> pCommands) override final;

				/**
				 * Create one time command buffer.
				 * This command buffer is used for simple tasks.
				 *
				 * @return: Vulkan Command Buffer handle.
				 */
				VkCommandBuffer CreateOneTimeCommandBuffer();

				/**
				 * Submit the one time command buffer to the device to be executed.
				 *
				 * @param vCommandBuffer: The Vulkan Command Buffer handle.
				 */
				void SubmitOneTimeCommandBuffer(VkCommandBuffer vCommandBuffer);

				/* Buffer creation */
			public:
				/**
				 * Create a raw buffer.
				 *
				 * @param size: The size of the buffer in bytes.
				 * @return: The created raw buffer pointer.
				 */
				virtual Buffer* CreateRawBuffer(UI64 size) override final;

				/**
				 * Create a vertex buffer using the Vertex and the vertex count.
				 *
				 * @param vertex: The vertex structure defining the structure of a single vertex.
				 * @param vertexCount: The total number of vertexes that will be stored.
				 * @return: The created vertex buffer pointer.
				 */
				virtual VertexBuffer* CreateVertexBuffer(const Vertex& vertex, UI64 vertexCount) override final;

				/**
				 * Create an index buffer using the index size and the total number of indexes to be stored.
				 *
				 * @param indexSize: The size of the index in bytes.
				 * @param indexCount: The total number of indexes to be stored.
				 * @return: The created index buffer pointer.
				 */
				virtual IndexBuffer* CreateIndexBuffer(UI8 indexSize, UI64 indexCount) override final;

				/**
				 * Create a stagging buffer.
				 * These buffers does not contain any major usage unless moving data from the local address space to the
				 * device (GPU) address space.
				 *
				 * @param size: The size of the buffer in bytes.
				 * @return: The created stagging buffer pointer.
				 */
				virtual StaggingBuffer* CreateStaggingBuffer(UI64 size) override final;

				/**
				 * Destroy a created buffer object.
				 *
				 * @param pBuffer: The buffer to be destroyed.
				 */
				virtual void DestroyBuffer(Buffer* pBuffer) override final;

			public:
				/**
				 * Get the Vulkan Instance.
				 *
				 * @return: VkInstance handle.
				 */
				DMK_FORCEINLINE VkInstance GetInstance() const { return vInstance; }

				/**
				 * Get the Vulkan Debug Messenger.
				 *
				 * @return: VkDebugUtilsMessengerEXT handle.
				 */
				DMK_FORCEINLINE VkDebugUtilsMessengerEXT GetDebugMessenger() const { return vDebugMessenger; }

				/**
				 * Get the GLFW window handle.
				 *
				 * @return: GLFWwindow pointer.
				 */
				DMK_FORCEINLINE GLFWwindow* GetWindowHandle() const { return pWindowHandle; }

				/**
				 * Get the Vulkan surface.
				 *
				 * @return: VkSurfaceKHR handle.
				 */
				DMK_FORCEINLINE VkSurfaceKHR GetSurface() const { return vSurface; }

				/**
				 * Get the Vulkan physical device.
				 *
				 * @return: VkPhysicalDevice handle.
				 */
				DMK_FORCEINLINE VkPhysicalDevice GetPhysicalDevice() const { return vPhysicalDevice; }

				/**
				 * Get Vulkan logical device.
				 *
				 * @return: VkDevice handle.
				 */
				DMK_FORCEINLINE VkDevice GetLogicalDevice() const { return vLogicalDevice; }

				/**
				 * Get the Vulkan Queues.
				 *
				 * @return: VulkanQueue object.
				 */
				DMK_FORCEINLINE VulkanQueue GetQueue() const { return vQueue; }

			private:
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
				void TerminateDebugger();

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
				 * @return: VkPhysicalDeviceProperties structure.
				 */
				DMK_FORCEINLINE VkPhysicalDeviceProperties GetPhysicalDeviceProperties() const { return vPhysicalDeviceProperties; }

				/**
				 * Get the physical device ray tracing properties.
				 *
				 * @return: VkPhysicalDeviceRayTracingPropertiesKHR structure.
				 */
				DMK_FORCEINLINE VkPhysicalDeviceRayTracingPropertiesKHR GetPhysicalDeviceRayTracingProperties() const { return vPhysicalDeviceRayTracingProperties; }

				/**
				 * Get the physical device ray tracing properties.
				 *
				 * @return: VkPhysicalDeviceRayTracingFeaturesKHR structure.
				 */
				DMK_FORCEINLINE VkPhysicalDeviceRayTracingFeaturesKHR GetPhysicalDeviceRayTracingFeatures() const { return vPhysicalDeviceRayTracingFeatures; }

				/**
				 * Query swap chain support details for this device.
				 *
				 * @return: VulkanSwapChainSupportDetails structure.
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
				 * @return: Boolean value.
				 */
				bool IsPhysicalDeviceSuitable(VkPhysicalDevice vDevice);

			private:
				VulkanQueue vQueue = {};	// Vulkan queue object.

				std::vector<const char*> validationLayers;	// Validation layers.
				std::vector<const char*> instanceExtensions;	// Instance extensions.
				std::vector<const char*> deviceExtensions;	// Device extensions.

				VkInstance vInstance = VK_NULL_HANDLE;	// Vulkan instance handle.
				VkDebugUtilsMessengerEXT vDebugMessenger = VK_NULL_HANDLE;	// Vulkan debug messenger handle.

				GLFWwindow* pWindowHandle = nullptr;	// The GLFW window pointer.
				VkSurfaceKHR vSurface = VK_NULL_HANDLE;	// The display surface.

				VkPhysicalDevice vPhysicalDevice = VK_NULL_HANDLE;	// The physical device.
				VkDevice vLogicalDevice = VK_NULL_HANDLE;	// The logical device.
			};
		}
	}
}

#endif // !_DYNAMIK_VULKAN_BACKEND_DEVICE_H
