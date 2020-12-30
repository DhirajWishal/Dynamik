// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "VulkanQueue.h"
#include "VulkanDisplay.h"

namespace DMK
{
	namespace VulkanBackend
	{
		/**
		 * Structure containing support details for a Vulkan Swap Chain.
		 */
		struct SwapChainSupportDetails {
			VkSurfaceCapabilitiesKHR capabilities = {};			// Swap Chain capabilities.
			std::vector<VkSurfaceFormatKHR> formats = {};		// Swap Chain formats.
			std::vector<VkPresentModeKHR> presentModes = {};	// Swap Chain present modes.
		};

		/**
		 * Vulkan Device object.
		 */
		class VulkanDevice {
		public:
			VulkanDevice() {}
			~VulkanDevice() {}

			void Initialize(VkInstance vInstance, VulkanDisplay* pDisplay);
			void Terminate();

			VkSampleCountFlags GetMsaaSamples() const { return vMsaaSamples; }

		public:
			//uint64 CreateSwapChain(glm::vec2 extent);
			//VulkanSwapChain* GetSwapChain(const uint64 index);
			//void DestroySwapChain(const uint64 index);
			//void DestroyAllSwapChains();

			//std::vector<VulkanSwapChain> mSwapChains;

		private:
			void InitializeSurface(VulkanDisplay* pWindow);
			void TerminateSurface();

			void InitializePhysicalDevice(VulkanDisplay* pWindow);
			void TerminatePhysicalDevice();

			void InitializeLogicalDevice();
			void TerminateLogicalDevice();

		private:
			bool IsPhysicalDeviceSuitable(VkPhysicalDevice vDevice);
			//uint64 GetRenderTargetBufferCount() const;

		public:
			VulkanQueue vQueue = {};

			VkPhysicalDeviceProperties vPhysicalDeviceProperties = {};
			VkPhysicalDeviceRayTracingFeaturesKHR vPhysicalDeviceRayTracingFeatures = {};
			VkPhysicalDeviceRayTracingPropertiesKHR vPhysicalDeviceRayTracingProperties = {};
			VkSurfaceCapabilitiesKHR vSurfaceCapabilities = {};
			SwapChainSupportDetails vSwapChainSupportDetails = {};

			std::vector<const char*> mDeviceExtensions;

			VkPhysicalDevice vPhysicalDevice = VK_NULL_HANDLE;
			VkDevice vLogicalDevice = VK_NULL_HANDLE;

			VkSurfaceKHR vSurfaceHandle = VK_NULL_HANDLE;

			UI64 mWindowIndex = 0;

			VkSampleCountFlags vMsaaSamples = VK_SAMPLE_COUNT_64_BIT;
		};
	}
}