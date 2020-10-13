// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_DEVICE_H
#define _DYNAMIK_VULKAN_DEVICE_H

#include "VulkanInstance.h"
#include "VulkanSurface.h"

#include <vulkan/vulkan_beta.h>

namespace Backend
{
	/*
	 Vulkan Device for the Dynamik Engine
	 This contains both the physical and logical devices.
	*/
	class DMK_API VulkanDevice {
	public:
		VulkanDevice() {}
		~VulkanDevice() {}

		void addExtension(const CCPTR& extension);
		void initialize(VulkanInstance vInstance, VulkanSurface vSurface);
		void initializePhysicalDevice(VulkanInstance vInstance, VulkanSurface vSurface);
		void initializeLogicalDevice(VulkanInstance vInstance, VulkanSurface vSurface);
		void terminate(VulkanInstance vInstance);

		VkSampleCountFlagBits getMaxUsableSampleCount();

		VkPhysicalDeviceRayTracingFeaturesKHR getRayTracingFeatures();
		VkPhysicalDeviceRayTracingPropertiesKHR getRayTracingProperties();

		operator VkPhysicalDevice() const;
		operator VkDevice() const;
		operator VkPhysicalDeviceProperties() const;

		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
		VkDevice logicalDevice = VK_NULL_HANDLE;

		VkPhysicalDeviceProperties physicalDeviceProperties = {};
		VkPhysicalDeviceRayTracingFeaturesKHR rayTracingFeatures = {};
		VkPhysicalDeviceRayTracingPropertiesKHR rayTracingProperties = {};

		std::vector<CCPTR> extensions;
	};
}

#endif // !_DYNAMIK_VULKAN_DEVICE_H
