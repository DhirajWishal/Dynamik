// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanDevice.h"

#include "VulkanQueue.h"

#include <set>

namespace Dynamik
{
	namespace Backend
	{
		void VulkanDevice::initialize(VulkanInstance vInstance, VulkanSurface vSurface)
		{
			extentions.pushBack(VK_KHR_SWAPCHAIN_EXTENSION_NAME);

			initializePhysicalDevice(vInstance, vSurface);
			initializeLogicalDevice(vInstance, vSurface);
		}

		void VulkanDevice::initializePhysicalDevice(VulkanInstance vInstance, VulkanSurface vSurface)
		{
			UI32 deviceCount = 0;
			vkEnumeratePhysicalDevices(vInstance, &deviceCount, nullptr);

			if (deviceCount == 0)
				DMK_ERROR_BOX("Failed to find GPUs with Vulkan support!");

			ARRAY<VkPhysicalDevice> devices(deviceCount);
			vkEnumeratePhysicalDevices(vInstance, &deviceCount, devices.data());

			//std::multimap<I32, VkPhysicalDevice> candidates;

			for (const auto& device : devices) {
				if (vSurface.isDeviceSuitable(device)) {
					vkGetPhysicalDeviceProperties(device, &physicalDeviceProperties);

					if (physicalDeviceProperties.deviceType == VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
						physicalDevice = device;
					else if (physicalDeviceProperties.deviceType == VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)
						physicalDevice = device;
					else
						physicalDevice = device;


					break;
				}

				physicalDevice = VK_NULL_HANDLE;
			}

			if (physicalDevice == VK_NULL_HANDLE)
				DMK_ERROR_BOX("Failed to find a suitable GPU!");

#if defined(DMK_DEBUG)
			printf("\n\t---------- VULKAN PHYSICAL DEVICE INFO ----------\n");
			printf("API Version: %I32d\n", physicalDeviceProperties.apiVersion);
			printf("Driver Version: %I32d\n", physicalDeviceProperties.driverVersion);
			printf("Vendor ID: %I32d\n", physicalDeviceProperties.vendorID);
			printf("Device ID: %I32d\n", physicalDeviceProperties.deviceID);

			switch (physicalDeviceProperties.deviceType) {
			case VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_OTHER:
				printf("Device Type: Other GPU\n");
				break;
			case VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
				printf("Device Type: Discrete GPU (dedicated)\n");
				break;
			case VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
				printf("Device Type: Integrated GPU (onboard)\n");
				break;
			case VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
				printf("Device Type: Virtual GPU\n");
				break;
			case VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_CPU:
				printf("Device Type: CPU\n");
				break;
			default:
				printf("Device Type: *UNIDENTIFIED\n");
				break;
			}

			printf("Device Name: %s\n", physicalDeviceProperties.deviceName);
			printf("\t-------------------------------------------------\n\n");

			// ----------
#endif
		}

		void VulkanDevice::initializeLogicalDevice(VulkanInstance vInstance, VulkanSurface vSurface)
		{
			VulkanQueue indices;
			indices.findQueueFamilies(physicalDevice, vSurface);

			ARRAY<VkDeviceQueueCreateInfo> queueCreateInfos;
			std::set<UI32> uniqueQueueFamilies = {
				indices.processFamily.value(),
				indices.utilityFamily.value()
			};

			F32 queuePriority = 1.0f;
			for (UI32 queueFamily : uniqueQueueFamilies) 
			{
				VkDeviceQueueCreateInfo queueCreateInfo = {};
				queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
				queueCreateInfo.queueFamilyIndex = queueFamily;
				queueCreateInfo.queueCount = 1;
				queueCreateInfo.pQueuePriorities = &queuePriority;
				queueCreateInfos.pushBack(queueCreateInfo);
			}

			VkPhysicalDeviceFeatures deviceFeatures = {};
			deviceFeatures.samplerAnisotropy = VK_TRUE;
			deviceFeatures.sampleRateShading = VK_TRUE; // enable sample shading feature for the device

			VkDeviceCreateInfo createInfo = {};
			createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
			createInfo.queueCreateInfoCount = static_cast<UI32>(queueCreateInfos.size());
			createInfo.pQueueCreateInfos = queueCreateInfos.data();
			createInfo.pEnabledFeatures = &deviceFeatures;
			createInfo.enabledExtensionCount = static_cast<UI32>(extentions.size());
			createInfo.ppEnabledExtensionNames = extentions.data();

			if (vInstance.isValidationEnabled)
			{
				createInfo.enabledLayerCount = static_cast<UI32>(vInstance.validationLayers.size());
				createInfo.ppEnabledLayerNames = vInstance.validationLayers.data();
			}
			else
			{
				createInfo.enabledLayerCount = 0;
			}

			DMK_VULKAN_ASSERT(vkCreateDevice(physicalDevice, &createInfo, nullptr, &logicalDevice), "Failed to create logical device!");
		}

		void VulkanDevice::terminate(VulkanInstance vInstance)
		{
			vkDestroyDevice(logicalDevice, nullptr);
		}

		VkSampleCountFlagBits VulkanDevice::getMaxUsableSampleCount()
		{
			VkSampleCountFlags counts = std::min(
				physicalDeviceProperties.limits.framebufferColorSampleCounts,
				physicalDeviceProperties.limits.framebufferDepthSampleCounts);

			if (counts & VK_SAMPLE_COUNT_64_BIT)  return VK_SAMPLE_COUNT_64_BIT;
			if (counts & VK_SAMPLE_COUNT_32_BIT)  return VK_SAMPLE_COUNT_32_BIT;
			if (counts & VK_SAMPLE_COUNT_16_BIT)  return VK_SAMPLE_COUNT_16_BIT;
			if (counts & VK_SAMPLE_COUNT_8_BIT)  return VK_SAMPLE_COUNT_8_BIT;
			if (counts & VK_SAMPLE_COUNT_4_BIT)  return VK_SAMPLE_COUNT_4_BIT;
			if (counts & VK_SAMPLE_COUNT_2_BIT)  return VK_SAMPLE_COUNT_2_BIT;

			return VK_SAMPLE_COUNT_1_BIT;
		}

		VulkanDevice::operator VkPhysicalDevice() const
		{
			return this->physicalDevice;
		}

		VulkanDevice::operator VkDevice() const
		{
			return this->logicalDevice;
		}

		VulkanDevice::operator VkPhysicalDeviceProperties() const
		{
			return this->physicalDeviceProperties;
		}
	}
}