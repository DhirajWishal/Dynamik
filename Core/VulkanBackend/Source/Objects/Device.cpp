// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/Objects/Device.h"
#include "VulkanBackend/Objects/Queue.h"
#include "VulkanBackend/Macros.h"
#include "Core/ErrorHandler/Logger.h"

#include <set>

namespace DMK
{
	namespace VulkanBackend
	{
		namespace _Helpers
		{
			/**
			 * Query swap chain support details.
			 *
			 * @param vPhysicalDevice: The physical device to be checked for.
			 * @param vSurface: The surface to be checked with.
			 * @return SwapChainSupportDetails structure.
			 */
			SwapChainSupportDetails QuerySwapChainSupportDetails(VkPhysicalDevice vPhysicalDevice, VkSurfaceKHR vSurface)
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
			 * Create a new VkSurfaceKHR handle.
			 *
			 * @param vInstance: The instance the surface is linked to.
			 * @param vDisplay: The display object to create the surface to.
			 * @return VkSurfaceKHR handle.
			 */
			VkSurfaceKHR CreateSurface(VkInstance vInstance, const VulkanDisplay& vDisplay)
			{
				VkSurfaceKHR vSurface = VK_NULL_HANDLE;
				DMK_VK_ASSERT(glfwCreateWindowSurface(vInstance, vDisplay.pWindowHandle, nullptr, &vSurface), "Failed to create the Vulkan Surface!");

				return vSurface;
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
				VulkanQueue _queue = CreateTempQueue(vDevice);

				bool extensionsSupported = _Helpers::CheckDeviceExtensionSupport(vDevice, deviceExtensions);
				bool swapChainAdequate = false;
				if (extensionsSupported)
				{
					SwapChainSupportDetails swapChainSupport = _Helpers::QuerySwapChainSupportDetails(vDevice, vSurface);
					swapChainAdequate = (!swapChainSupport.formats.empty()) && (!swapChainSupport.presentModes.empty());
				}

				VkPhysicalDeviceFeatures supportedFeatures;
				vkGetPhysicalDeviceFeatures(vDevice, &supportedFeatures);

				return IsQueueComplete(_queue)
					&& extensionsSupported
					&& swapChainAdequate
					&& supportedFeatures.samplerAnisotropy;
				return true;
			}

			/**
			 * Create a new physical device.
			 *
			 * @param vInstance: The vulkan instance.
			 * @param vSurface: The surface the physical device renders to.
			 * @param deviceExtensions: The device extensions.
			 * @return The Vulkan physical device handle.
			 */
			VkPhysicalDevice CreatePhysicalDevice(VkInstance vInstance, VkSurfaceKHR vSurface, const std::vector<const char*>& deviceExtensions)
			{
				UI32 deviceCount = 0;
				vkEnumeratePhysicalDevices(vInstance, &deviceCount, nullptr);

				if (deviceCount == 0)
				{
					Logger::LogError(TEXT("Failed to find GPUs with Vulkan support!"));
					return VkPhysicalDevice();
				}

				std::vector<VkPhysicalDevice> devices(deviceCount);
				vkEnumeratePhysicalDevices(vInstance, &deviceCount, devices.data());

				VkPhysicalDevice vPhysicalDevice = VK_NULL_HANDLE;
				VkPhysicalDeviceProperties vPhysicalDeviceProperties = {};
				// Iterate through all the candidate devices and find the best device.
				for (const VkPhysicalDevice& device : devices)
				{
					if (_Helpers::IsPhysicalDeviceSuitable(device, vSurface, deviceExtensions))
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
					return VkPhysicalDevice();
				}

#ifdef DMK_DEBUG
				printf("\n\t---------- VULKAN PHYSICAL DEVICE INFO ----------\n");
				printf("API Version: %I32d\n", vPhysicalDeviceProperties.apiVersion);
				printf("Driver Version: %I32d\n", vPhysicalDeviceProperties.driverVersion);
				printf("Vendor ID: %I32d\n", vPhysicalDeviceProperties.vendorID);
				printf("Device ID: %I32d\n", vPhysicalDeviceProperties.deviceID);

				switch (vPhysicalDeviceProperties.deviceType)
				{
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

				printf("Device Name: %s\n", vPhysicalDeviceProperties.deviceName);
				printf("\t-------------------------------------------------\n\n");

#endif	// DMK_DEBUG

				return vPhysicalDevice;
			}

			/**
			 * Create a new Vulkan logical device handle.
			 *
			 * @param enableValidation: Whether or not to enable validation.
			 * @param validationLayers: The validation layers to use.
			 * @param deviceExtensions: The device extensions to use.
			 * @param vPhysicalDevice: The physical device which the logical device is bound to.
			 * @param vQueueIndex: The queue index.
			 * @return VkDevice handle.
			 */
			VkDevice CreateLogicalDevice(bool enableValidation, const std::vector<const char*>& validationLayers, const std::vector<const char*>& deviceExtensions, VkPhysicalDevice vPhysicalDevice, VulkanQueue::Index vQueueIndex)
			{
				auto& queue = VulkanQueue::Store::Get(vQueueIndex);

				std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
				std::set<UI32> uniqueQueueFamilies = {
					queue.mGraphicsFamily.value(),
					queue.mComputeFamily.value(),
					queue.mTransferFamily.value()
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
				createInfo.enabledExtensionCount = static_cast<UI32>(deviceExtensions.size());
				createInfo.ppEnabledExtensionNames = deviceExtensions.data();

				if (enableValidation)
				{
					createInfo.enabledLayerCount = static_cast<UI32>(validationLayers.size());
					createInfo.ppEnabledLayerNames = validationLayers.data();
				}
				else
				{
					createInfo.enabledLayerCount = 0;
				}

				// Create the logical device.
				VkDevice vLogicalDevice = VK_NULL_HANDLE;
				DMK_VK_ASSERT(vkCreateDevice(vPhysicalDevice, &createInfo, nullptr, &vLogicalDevice), "Failed to create logical device!");

				// Create queues.
				{
					// Graphics Queue.
					vkGetDeviceQueue(vLogicalDevice, queue.mGraphicsFamily.value(), 0, &queue.vGraphicsQueue);

					// Compute Queue.
					vkGetDeviceQueue(vLogicalDevice, queue.mComputeFamily.value(), 0, &queue.vComputeQueue);

					// Transfer Queue.
					vkGetDeviceQueue(vLogicalDevice, queue.mTransferFamily.value(), 0, &queue.vTransferQueue);
				}

				return vLogicalDevice;
			}
		}

		VulkanDevice::Index CreateDevice(const VulkanInstance::Index& vInstanceIndex, const VulkanDisplay::Index& vDisplayIndex)
		{
			auto& instance = VulkanInstance::Store::Get(vInstanceIndex);
			auto& display = VulkanDisplay::Store::Get(vDisplayIndex);

			std::vector<const char*> deviceExtensions;
			INSERT_TO_VECTOR(deviceExtensions, VK_KHR_SWAPCHAIN_EXTENSION_NAME);

			VulkanDevice device = {};
			device.vSurface = _Helpers::CreateSurface(instance.vInstance, display);
			device.vPhysicalDevice = _Helpers::CreatePhysicalDevice(instance.vInstance, device.vSurface, deviceExtensions);
			device.vSampleCount = _Helpers::GetMaxUsableSamples(device.vPhysicalDevice);
			device.vQueueIndex = CreateQueue(device.vPhysicalDevice);
			device.vLogicalDevice = _Helpers::CreateLogicalDevice(instance.vDebugMessenger, instance.mValidationLayers, deviceExtensions, device.vPhysicalDevice, device.vQueueIndex);

			return VulkanDevice::Store::Insert(std::move(device));
		}

		void DestroyDevice(const VulkanInstance::Index& vInstanceIndex, const VulkanDevice::Index& vDeviceIndex)
		{
			auto& instance = VulkanInstance::Store::Get(vInstanceIndex);
			auto& device = VulkanDevice::Store::Get(vDeviceIndex);

			vkDestroySurfaceKHR(instance.vInstance, device.vSurface, nullptr);
			vkDestroyDevice(device.vLogicalDevice, nullptr);

			VulkanDevice::Store::Remove(vDeviceIndex);
		}
	}
}