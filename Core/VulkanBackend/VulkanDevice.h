// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GraphicsCore/Backend/Device.h"
#include "VulkanQueue.h"

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

			/**
			 * Query swap chain support details.
			 *
			 * @param vPhysicalDevice: The physical device to be checked for.
			 * @param vSurface: The surface to be checked with.
			 * @return SwapChainSupportDetails structure.
			 */
			static SwapChainSupportDetails Query(VkPhysicalDevice vPhysicalDevice, VkSurfaceKHR vSurface);
		};

		class VulkanDevice final : public GraphicsCore::Device {
		public:
			VulkanDevice() {}
			~VulkanDevice() {}

			virtual void Initialize(GraphicsCore::Display* pDisplay) override final;
			virtual void Terminate() override final;

		public:
			VkPhysicalDeviceProperties& GetPhysicalDeviceProperties() { return vPhysicalDeviceProperties; }
			VkSurfaceCapabilitiesKHR& GetSurfaceCapabilities() { return vSurfaceCapabilities; }
			SwapChainSupportDetails& GetSwapChainSupportDetails() { return vSwapChainSupportDetails; }

			VulkanQueue& GetQueue() { return vQueue; }

			VkPhysicalDevice GetPhysicalDevice() const { return vPhysicalDevice; }
			VkDevice GetLogicalDevice() const { return vLogicalDevice; }

		private:
			void CreatePhysicalDevice();

			void CreateLogicalDevice();
			void DestroyLogicalDevice();

		private:
			VkPhysicalDeviceProperties vPhysicalDeviceProperties = {};
			VkSurfaceCapabilitiesKHR vSurfaceCapabilities = {};
			SwapChainSupportDetails vSwapChainSupportDetails = {};

			VulkanQueue vQueue = {};
			std::vector<const char*> mDeviceExtensions;

			VkPhysicalDevice vPhysicalDevice = VK_NULL_HANDLE;
			VkDevice vLogicalDevice = VK_NULL_HANDLE;
		};
	}
}