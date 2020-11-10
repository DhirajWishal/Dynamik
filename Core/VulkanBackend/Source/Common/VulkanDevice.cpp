// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/Common/VulkanDevice.h"
#include "Core/Types/Utilities.h"
#include "VulkanBackend/VulkanBackendInstance.h"

#include <iostream>
#include <set>

#include <GLFW/glfw3.h>

namespace DMK
{
	namespace GraphicsCore
	{
		namespace VulkanBackend
		{
			/**
			 * Internal helper namespace.
			 */
			namespace _Helper
			{
				/**
				 * Query swap chain support details.
				 *
				 * @param vPhysicalDevice: The physical device to be checked for.
				 * @param vSurface: The surface to be checked with.
				 * @return VulkanSwapChainSupportDetails structure.
				 */
				VulkanSwapChainSupportDetails QuerySwapChainSupportDetails(VkPhysicalDevice vPhysicalDevice, VkSurfaceKHR vSurface)
				{
					VulkanSwapChainSupportDetails supportDetails = {};
					vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vPhysicalDevice, vSurface, &supportDetails.capabilities);

					UI32 formatCount = 0;
					vkGetPhysicalDeviceSurfaceFormatsKHR(vPhysicalDevice, vSurface, &formatCount, nullptr);

					if (formatCount != 0)
					{
						supportDetails.formats.reserve(formatCount);
						vkGetPhysicalDeviceSurfaceFormatsKHR(vPhysicalDevice, vSurface, &formatCount, supportDetails.formats.data());
					}

					UI32 presentModeCount = 0;
					vkGetPhysicalDeviceSurfacePresentModesKHR(vPhysicalDevice, vSurface, &presentModeCount, nullptr);

					if (presentModeCount != 0)
					{
						supportDetails.presentModes.reserve(presentModeCount);
						vkGetPhysicalDeviceSurfacePresentModesKHR(vPhysicalDevice, vSurface, &presentModeCount, supportDetails.presentModes.data());
					}

					return supportDetails;
				}
			}

			///////////////////////////////////////////////////////////////////////////////////////////////////
			////	Vulkan Queue Definitions
			///////////////////////////////////////////////////////////////////////////////////////////////////

			void VulkanQueue::FindQueueFamilies(VkPhysicalDevice vPhysicalDevice, VkSurfaceKHR vSurface)
			{
				UI32 queueFamilyCount = 0;
				vkGetPhysicalDeviceQueueFamilyProperties(vPhysicalDevice, &queueFamilyCount, nullptr);

				std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
				vkGetPhysicalDeviceQueueFamilyProperties(vPhysicalDevice, &queueFamilyCount, queueFamilies.data());

				I32 i = 0;
				for (auto itr = queueFamilies.begin(); itr != queueFamilies.end(); itr++, i++)
				{
					// Set graphics family.
					if ((itr->queueCount > 0) && (itr->queueFlags & VK_QUEUE_GRAPHICS_BIT))
						graphicsFamily = i;

					// Set compute family.
					if ((itr->queueCount > 0) && (itr->queueFlags & VK_QUEUE_COMPUTE_BIT))
						computeFamily = i;

					// Set transfer family.
					if ((itr->queueCount > 0) && (itr->queueFlags & VK_QUEUE_TRANSFER_BIT))
						transferFamily = i;

					// Escape from the loop if the queues were found.
					if (IsComplete())
						break;
				}
			}

			bool VulkanQueue::IsComplete()
			{
				return graphicsFamily.has_value() && computeFamily.has_value() && transferFamily.has_value();
			}

			///////////////////////////////////////////////////////////////////////////////////////////////////
			////	Vulkan Device Definitions
			///////////////////////////////////////////////////////////////////////////////////////////////////

			void VulkanDevice::Initialize(const DeviceInitInfo& initInfo)
			{
				this->initInfo = initInfo;

				// Initialize the window/ display handle.
				InitializeDisplay();

				// Load validation layers.
				{
					deviceExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
				}

				// Enable ray tracing extensions.
				if (initInfo.enableRayTracing)
				{
					instanceExtensions.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);

					deviceExtensions.push_back(VK_KHR_MAINTENANCE2_EXTENSION_NAME);
					deviceExtensions.push_back(VK_KHR_GET_MEMORY_REQUIREMENTS_2_EXTENSION_NAME);
					deviceExtensions.push_back(VK_KHR_RAY_TRACING_EXTENSION_NAME);
					deviceExtensions.push_back(VK_KHR_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME);
					deviceExtensions.push_back(VK_EXT_DESCRIPTOR_INDEXING_EXTENSION_NAME);
					deviceExtensions.push_back(VK_KHR_PIPELINE_LIBRARY_EXTENSION_NAME);
				}

				// Create the surface.
				CreateSurface();

				// Initialize the Vulkan physical device.
				InitializePhysicalDevice();

				// Initialize the Vulkan logical device.
				InitializeLogicalDevice();
			}

			void VulkanDevice::Terminate()
			{
				// Terminate logical device.
				TerminateLogicalDevice();

				// Terminate physical device.
				TerminatePhysicalDevice();

				// Destroy the surface.
				DestroySurface();

				// Terminate the display.
				TerminateDisplay();
			}

			I8 VulkanDevice::BeginFrame()
			{
				// Poll the GLFW events.
				glfwPollEvents();

				return frameIndex;
			}

			void VulkanDevice::EndFrame()
			{
			}

			void VulkanDevice::InitializeDisplay()
			{
#if defined(DMK_DEBUG) || defined(DMK_RELEASE)
				pWindowHandle = glfwCreateWindow(GetInitInfo().windowWidth, GetInitInfo().windowHeight, GetInitInfo().pTitle, nullptr, nullptr);

#else
				GLFWmonitor* monitor = glfwGetPrimaryMonitor();
				const GLFWvidmode* mode = glfwGetVideoMode(monitor);

				glfwWindowHint(GLFW_RED_BITS, mode->redBits);
				glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
				glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
				glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

				pWindowHandle = glfwCreateWindow(mode->width, mode->height, GetInitInfo().windowHeight, monitor, NULL);
				initInfo.windowWidth = mode->width;
				initInfo.windowHeight = mode->height;

				glfwSetInputMode(pWindowHandle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

#endif

				glfwSetWindowUserPointer(GetWindowHandle(), this);
			}

			void VulkanDevice::TerminateDisplay()
			{
				glfwDestroyWindow(GetWindowHandle());
				glfwTerminate();
			}

			void VulkanDevice::CreateSurface()
			{
				if (vSurface == VK_NULL_HANDLE)
					DMK_VK_ASSERT(glfwCreateWindowSurface(GetParentInstance()->Inherit<VulkanBackendInstance>()->GetInstance(), GetWindowHandle(), nullptr, &vSurface), "Failed to create the Vulkan Surface!");
			}

			void VulkanDevice::DestroySurface()
			{
				vkDestroySurfaceKHR(GetParentInstance()->Inherit<VulkanBackendInstance>()->GetInstance(), GetSurface(), nullptr);
			}

			void VulkanDevice::InitializePhysicalDevice()
			{
				UI32 deviceCount = 0;
				vkEnumeratePhysicalDevices(GetParentInstance()->Inherit<VulkanBackendInstance>()->GetInstance(), &deviceCount, nullptr);

				if (deviceCount == 0)
				{
					Logger::LogError(TEXT("Failed to find GPUs with Vulkan support!"));
					return;
				}

				std::vector<VkPhysicalDevice> devices(deviceCount);
				vkEnumeratePhysicalDevices(GetParentInstance()->Inherit<VulkanBackendInstance>()->GetInstance(), &deviceCount, devices.data());

				// Iterate through all the candidate devices and find the best device.
				for (const VkPhysicalDevice& device : devices)
				{
					if (IsPhysicalDeviceSuitable(device))
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

#endif

				// Get the ray tracing freatres.
				vPhysicalDeviceRayTracingFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_FEATURES_KHR;

				VkPhysicalDeviceFeatures2 deviceFeatures2 = {};
				deviceFeatures2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
				deviceFeatures2.pNext = &vPhysicalDeviceRayTracingFeatures;
				vkGetPhysicalDeviceFeatures2(GetPhysicalDevice(), &deviceFeatures2);

				// Get the ray tracing properties.
				vPhysicalDeviceRayTracingProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PROPERTIES_KHR;

				VkPhysicalDeviceProperties2 deviceProps2 = {};
				deviceProps2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
				deviceProps2.pNext = &vPhysicalDeviceRayTracingProperties;
				vkGetPhysicalDeviceProperties2(GetPhysicalDevice(), &deviceProps2);
			}

			void VulkanDevice::TerminatePhysicalDevice()
			{
				// Nothing to do here, yet...
			}

			void VulkanDevice::InitializeLogicalDevice()
			{
				// Create queues.
				vQueue.FindQueueFamilies(GetPhysicalDevice(), GetSurface());

				std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
				std::set<UI32> uniqueQueueFamilies = {
					vQueue.GetGraphicsFamily().value(),
					vQueue.GetComputeFamily().value(),
					vQueue.GetTransferFamily().value()
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
				createInfo.queueCreateInfoCount = Cast<UI32>(queueCreateInfos.size());
				createInfo.pQueueCreateInfos = queueCreateInfos.data();
				createInfo.pEnabledFeatures = &deviceFeatures;
				createInfo.enabledExtensionCount = Cast<UI32>(deviceExtensions.size());
				createInfo.ppEnabledExtensionNames = deviceExtensions.data();

				if (GetInitInfo().enableValidation)
				{
					createInfo.enabledLayerCount = static_cast<UI32>(GetParentInstance()->Inherit<VulkanBackendInstance>()->GetValidationLayers().size());
					createInfo.ppEnabledLayerNames = GetParentInstance()->Inherit<VulkanBackendInstance>()->GetValidationLayers().data();
				}
				else
				{
					createInfo.enabledLayerCount = 0;
				}

				// Create the logical device.
				DMK_VK_ASSERT(vkCreateDevice(GetPhysicalDevice(), &createInfo, nullptr, &vLogicalDevice), "Failed to create logical device!");

				// Create queues.
				{
					// Graphics Queue.
					vkGetDeviceQueue(GetLogicalDevice(), vQueue.GetGraphicsFamily().value(), 0, &vQueue.vGraphicsQueue);

					// Compute Queue.
					vkGetDeviceQueue(GetLogicalDevice(), vQueue.GetComputeFamily().value(), 0, &vQueue.vComputeQueue);

					// Transfer Queue.
					vkGetDeviceQueue(GetLogicalDevice(), vQueue.GetTransferFamily().value(), 0, &vQueue.vTransferQueue);
				}
			}

			void VulkanDevice::TerminateLogicalDevice()
			{
				vkDestroyDevice(GetLogicalDevice(), nullptr);
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

			VulkanSwapChainSupportDetails VulkanDevice::QuerySwapChainSupportDetails()
			{
				return _Helper::QuerySwapChainSupportDetails(GetPhysicalDevice(), GetSurface());
			}

			bool VulkanDevice::IsPhysicalDeviceSuitable(VkPhysicalDevice vDevice)
			{
				VulkanQueue _queue = {};
				_queue.FindQueueFamilies(vDevice, GetSurface());

				bool extensionsSupported = CheckDeviceExtensionSupport(vDevice, deviceExtensions);
				bool swapChainAdequate = false;
				if (extensionsSupported)
				{
					VulkanSwapChainSupportDetails swapChainSupport = _Helper::QuerySwapChainSupportDetails(vDevice, GetSurface());
					swapChainAdequate = (swapChainSupport.formats.empty()) && (swapChainSupport.presentModes.empty());
				}

				VkPhysicalDeviceFeatures supportedFeatures;
				vkGetPhysicalDeviceFeatures(vDevice, &supportedFeatures);

				return _queue.IsComplete()
					&& extensionsSupported
					&& swapChainAdequate
					&& supportedFeatures.samplerAnisotropy;
			}
		}
	}
}