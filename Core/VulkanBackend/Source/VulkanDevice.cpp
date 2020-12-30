// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/VulkanDevice.h"
#include "VulkanBackend/Macros.h"
#include "VulkanBackend/VulkanDisplay.h"
#include "VulkanBackend/VulkanInstance.h"

#include <set>

namespace DMK
{
	namespace VulkanBackend
	{
		namespace _Helpers
		{
			/**
			 * Get the max usable sample count of a physical device.
			 *
			 * @param vPhysicalDevice: The physical device.
			 * @return VkSampleCountFlags enum.
			 */
			VkSampleCountFlags GetMaxUsableSamples(VkPhysicalDevice vPhysicalDevice)
			{
				VkPhysicalDeviceProperties physicalDeviceProperties;
				vkGetPhysicalDeviceProperties(vPhysicalDevice, &physicalDeviceProperties);

				VkSampleCountFlags counts = physicalDeviceProperties.limits.framebufferColorSampleCounts & physicalDeviceProperties.limits.framebufferDepthSampleCounts;
				if (counts & VK_SAMPLE_COUNT_64_BIT) return VK_SAMPLE_COUNT_64_BIT;
				if (counts & VK_SAMPLE_COUNT_32_BIT) return VK_SAMPLE_COUNT_32_BIT;
				if (counts & VK_SAMPLE_COUNT_16_BIT) return VK_SAMPLE_COUNT_16_BIT;
				if (counts & VK_SAMPLE_COUNT_8_BIT) return VK_SAMPLE_COUNT_8_BIT;
				if (counts & VK_SAMPLE_COUNT_4_BIT) return VK_SAMPLE_COUNT_4_BIT;
				if (counts & VK_SAMPLE_COUNT_2_BIT) return VK_SAMPLE_COUNT_2_BIT;

				return VK_SAMPLE_COUNT_1_BIT;
			}

			/**
			 * Check if the extensions are supported for the Physical Device.
			 *
			 * @param vPhysicalDevice: The physical device to be checked for.
			 * @param deviceExtensions: The device extensions to be checked with.
			 * @return Boolean value.
			 */
			bool CheckDeviceExtensionSupport(VkPhysicalDevice vPhysicalDevice, std::vector<const char*> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME })
			{
				UI32 extensionCount = 0;
				vkEnumerateDeviceExtensionProperties(vPhysicalDevice, nullptr, &extensionCount, nullptr);

				std::vector<VkExtensionProperties> availableExtensions(extensionCount);
				vkEnumerateDeviceExtensionProperties(vPhysicalDevice, nullptr, &extensionCount, availableExtensions.data());

				std::set<String> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

				for (const VkExtensionProperties& extension : availableExtensions)
					requiredExtensions.erase(extension.extensionName);

				return requiredExtensions.empty();
			}

			/**
			 * Check if a physical device is suitable to use.
			 *
			 * @param vDevice: The physical device to be checked.
			 * @param vSurface: The surface the device will be using.
			 * @param deviceExtensions: The physical device extensions.
			 * @return Boolean value.
			 */
			bool IsPhysicalDeviceSuitable(VkPhysicalDevice vDevice, VkSurfaceKHR vSurface, const std::vector<const char*>& deviceExtensions)
			{
				VulkanQueue vQueue = {};
				vQueue.Initialize(vDevice, vSurface);

				bool extensionsSupported = _Helpers::CheckDeviceExtensionSupport(vDevice, deviceExtensions);
				bool swapChainAdequate = false;
				if (extensionsSupported)
				{
					SwapChainSupportDetails swapChainSupport = SwapChainSupportDetails::Query(vDevice, vSurface);
					swapChainAdequate = (!swapChainSupport.formats.empty()) && (!swapChainSupport.presentModes.empty());
				}

				VkPhysicalDeviceFeatures supportedFeatures = {};
				vkGetPhysicalDeviceFeatures(vDevice, &supportedFeatures);

				return vQueue.IsComplete()
					&& extensionsSupported
					&& swapChainAdequate
					&& supportedFeatures.samplerAnisotropy;
				return true;
			}
		}

		SwapChainSupportDetails SwapChainSupportDetails::Query(VkPhysicalDevice vPhysicalDevice, VkSurfaceKHR vSurface)
		{
			SwapChainSupportDetails supportDetails = {};
			vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vPhysicalDevice, vSurface, &supportDetails.capabilities);

			UI32 formatCount = 0;
			vkGetPhysicalDeviceSurfaceFormatsKHR(vPhysicalDevice, vSurface, &formatCount, nullptr);

			if (formatCount != 0)
			{
				supportDetails.formats.resize(formatCount);
				vkGetPhysicalDeviceSurfaceFormatsKHR(vPhysicalDevice, vSurface, &formatCount, supportDetails.formats.data());
			}

			UI32 presentModeCount = 0;
			vkGetPhysicalDeviceSurfacePresentModesKHR(vPhysicalDevice, vSurface, &presentModeCount, nullptr);

			if (presentModeCount != 0)
			{
				supportDetails.presentModes.resize(presentModeCount);
				vkGetPhysicalDeviceSurfacePresentModesKHR(vPhysicalDevice, vSurface, &presentModeCount, supportDetails.presentModes.data());
			}

			return supportDetails;
		}

		void VulkanDevice::Initialize(GraphicsCore::Display* pDisplay)
		{
			this->pDisplay = pDisplay;
			INSERT_INTO_VECTOR(mDeviceExtensions, VK_KHR_SWAPCHAIN_EXTENSION_NAME);

			CreatePhysicalDevice();
			CreateLogicalDevice();
		}

		void VulkanDevice::Terminate()
		{
			DestroyLogicalDevice();
		}

		void VulkanDevice::CreatePhysicalDevice()
		{
			VulkanDisplay& display = *pDisplay->Derive<VulkanDisplay>();
			VulkanInstance& instance = *display.GetInstance()->Derive<VulkanInstance>();

			UI32 deviceCount = 0;
			vkEnumeratePhysicalDevices(instance.GetInstance(), &deviceCount, nullptr);

			if (deviceCount == 0)
			{
				Logger::LogError(TEXT("Failed to find GPUs with Vulkan support!"));
				return;
			}

			std::vector<VkPhysicalDevice> devices(deviceCount);
			vkEnumeratePhysicalDevices(instance.GetInstance(), &deviceCount, devices.data());

			// Iterate through all the candidate devices and find the best device.
			for (const VkPhysicalDevice& device : devices)
			{
				if (_Helpers::IsPhysicalDeviceSuitable(device, display.GetSurface(), mDeviceExtensions))
				{
					vkGetPhysicalDeviceProperties(device, &vPhysicalDeviceProperties);

					if (vPhysicalDeviceProperties.deviceType == VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
						vPhysicalDevice = device;
					else if (vPhysicalDeviceProperties.deviceType == VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)
						vPhysicalDevice = device;
					else
						vPhysicalDevice = device;

					break;
				}

				vPhysicalDevice = VK_NULL_HANDLE;
			}

			//  Check if a physical device was found.
			if (vPhysicalDevice == VK_NULL_HANDLE)
			{
				Logger::LogError(TEXT("A suitable physical device was not found!"));
				return;
			}

#ifdef DMK_DEBUG
			wprintf(TEXT("\n\t---------- VULKAN PHYSICAL DEVICE INFO ----------\n"));
			wprintf(TEXT("API Version: %I32d\n"), vPhysicalDeviceProperties.apiVersion);
			wprintf(TEXT("Driver Version: %I32d\n"), vPhysicalDeviceProperties.driverVersion);
			wprintf(TEXT("Vendor ID: %I32d\n"), vPhysicalDeviceProperties.vendorID);
			wprintf(TEXT("Device ID: %I32d\n"), vPhysicalDeviceProperties.deviceID);

			switch (vPhysicalDeviceProperties.deviceType)
			{
			case VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_OTHER:
				wprintf(TEXT("Device Type: Other GPU\n"));
				break;
			case VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
				wprintf(TEXT("Device Type: Discrete GPU (dedicated)\n"));
				break;
			case VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
				wprintf(TEXT("Device Type: Integrated GPU (onboard)\n"));
				break;
			case VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
				wprintf(TEXT("Device Type: Virtual GPU\n"));
				break;
			case VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_CPU:
				wprintf(TEXT("Device Type: CPU\n"));
				break;
			default:
				wprintf(TEXT("Device Type: *UNIDENTIFIED\n"));
				break;
			}

			wprintf(TEXT("Device Name: %hs\n"), vPhysicalDeviceProperties.deviceName);
			wprintf(TEXT("\t-------------------------------------------------\n\n"));

#endif	// DMK_DEBUG

			vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vPhysicalDevice, display.GetSurface(), &vSurfaceCapabilities);
			vSwapChainSupportDetails = SwapChainSupportDetails::Query(vPhysicalDevice, display.GetSurface());
		}

		void VulkanDevice::CreateLogicalDevice()
		{
			VulkanDisplay& display = *pDisplay->Derive<VulkanDisplay>();
			VulkanInstance& instance = *display.GetInstance()->Derive<VulkanInstance>();

			vQueue.Initialize(vPhysicalDevice, display.GetSurface());

			std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
			std::set<UI32> uniqueQueueFamilies = {
				vQueue.mGraphicsFamily.value(),
				vQueue.mComputeFamily.value(),
				vQueue.mTransferFamily.value()
			};

			float queuePriority = 1.0f;
			for (UI32 queueFamily : uniqueQueueFamilies)
			{
				VkDeviceQueueCreateInfo queueCreateInfo = {};
				queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
				queueCreateInfo.queueFamilyIndex = queueFamily;
				queueCreateInfo.queueCount = 1;
				queueCreateInfo.pQueuePriorities = &queuePriority;
				queueCreateInfos.push_back(queueCreateInfo);
			}

			// Physical device features.
			VkPhysicalDeviceFeatures deviceFeatures = {};
			deviceFeatures.samplerAnisotropy = VK_TRUE;
			deviceFeatures.sampleRateShading = VK_TRUE; // Enable sample shading feature for the device

			// Device create info.
			VkDeviceCreateInfo createInfo = {};
			createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
			createInfo.queueCreateInfoCount = static_cast<UI32>(queueCreateInfos.size());
			createInfo.pQueueCreateInfos = queueCreateInfos.data();
			createInfo.pEnabledFeatures = &deviceFeatures;
			createInfo.enabledExtensionCount = static_cast<UI32>(mDeviceExtensions.size());
			createInfo.ppEnabledExtensionNames = mDeviceExtensions.data();

			std::vector<const char*>& validationLayers = instance.GetValidationLayers();
			if (instance.IsValidationEnabled())
			{
				createInfo.enabledLayerCount = static_cast<UI32>(validationLayers.size());
				createInfo.ppEnabledLayerNames = validationLayers.data();
			}
			else
				createInfo.enabledLayerCount = 0;

			// Create the logical device.
			DMK_VK_ASSERT(vkCreateDevice(vPhysicalDevice, &createInfo, nullptr, &vLogicalDevice), "Failed to create logical device!");
		}

		void VulkanDevice::DestroyLogicalDevice()
		{
			vkDestroyDevice(vLogicalDevice, nullptr);
		}
	}
}