// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/Common/VulkanDevice.h"
#include "VulkanBackend/Common/VulkanInstance.h"
#include "Core/Types/Utilities.h"

#include <iostream>
#include <set>

namespace DMK
{
	namespace VulkanBackend
	{
		/**
		 * Internal helpers namespace.
		 */
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

			VkSampleCountFlags GetMaxUsableSamples(VkPhysicalDevice vPhysicalDevice)
			{
				VkPhysicalDeviceProperties physicalDeviceProperties;
				vkGetPhysicalDeviceProperties(vPhysicalDevice, &physicalDeviceProperties);

				VkSampleCountFlags counts = physicalDeviceProperties.limits.framebufferColorSampleCounts & physicalDeviceProperties.limits.framebufferDepthSampleCounts;
				if (counts & VK_SAMPLE_COUNT_64_BIT) { return VK_SAMPLE_COUNT_64_BIT; }
				if (counts & VK_SAMPLE_COUNT_32_BIT) { return VK_SAMPLE_COUNT_32_BIT; }
				if (counts & VK_SAMPLE_COUNT_16_BIT) { return VK_SAMPLE_COUNT_16_BIT; }
				if (counts & VK_SAMPLE_COUNT_8_BIT) { return VK_SAMPLE_COUNT_8_BIT; }
				if (counts & VK_SAMPLE_COUNT_4_BIT) { return VK_SAMPLE_COUNT_4_BIT; }
				if (counts & VK_SAMPLE_COUNT_2_BIT) { return VK_SAMPLE_COUNT_2_BIT; }

				return VK_SAMPLE_COUNT_1_BIT;
			}
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////
		////	Vulkan Device Definitions
		///////////////////////////////////////////////////////////////////////////////////////////////////

		void VulkanDevice::Initialize(const GraphicsCore::DeviceInitInfo& initInfo, GraphicsCore::Instance* pInstance)
		{
			this->initInfo = initInfo;
			this->pInstance = pInstance->Derive<VulkanInstance>();

			// Initialize the window/ display handle.
			InitializeDisplay();

			// Load required extensions.
			{
				deviceExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
			}

			// Enable ray tracing extensions.
			if (initInfo.tryEnableRayTracing)
			{
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
			// Terminate all buffers.
			DestroyAllBuffers();

			// Terminate all Swap Chains.
			DestroyAllSwapChains();

			// Terminate all color buffers.
			DestroyAllColorBuffers();

			// Terminate all depth buffers.
			DestroyAllDepthBuffers();

			// Terminate all render passes.
			DestroyAllRenderPasses();

			// Terminate all frame buffers.
			DestroyAllFrameBuffers();

			// Terminate logical device.
			TerminateLogicalDevice();

			// Terminate physical device.
			TerminatePhysicalDevice();

			// Destroy the surface.
			DestroySurface();

			// Terminate the display.
			TerminateDisplay();
		}

		GraphicsCore::BufferRef VulkanDevice::CreateBuffer(GraphicsCore::BufferType type, UI64 size)
		{
			switch (type)
			{
			case DMK::GraphicsCore::BufferType::VERTEX:
				break;

			case DMK::GraphicsCore::BufferType::INDEX:
				break;

			case DMK::GraphicsCore::BufferType::UNIFORM_DATA:
			{
				UniformBuffer buffer = {};
				buffer.Initialize(this, size);

				mUniformBuffers.insert(mUniformBuffers.end(), std::move(buffer));

				return GraphicsCore::BufferRef(type, mUniformBuffers.size() - 1, size, 0);
			}

			case DMK::GraphicsCore::BufferType::STAGGING:
			{
				StaggingBuffer buffer = {};
				buffer.Initialize(this, size);

				mStaggingBuffers.insert(mStaggingBuffers.end(), std::move(buffer));

				return GraphicsCore::BufferRef(type, mStaggingBuffers.size() - 1, size, 0);
			}

			default:
				Logger::LogError(TEXT("Undefined or invalid buffer type!"));
				break;
			}

			return GraphicsCore::BufferRef();
		}

		GraphicsCore::Buffer* VulkanDevice::GetBuffer(const GraphicsCore::BufferRef& ref)
		{
			switch (ref.mType)
			{
			case DMK::GraphicsCore::BufferType::VERTEX:
				break;
			case DMK::GraphicsCore::BufferType::INDEX:
				break;
			case DMK::GraphicsCore::BufferType::UNIFORM_DATA:
				return mUniformBuffers.data() + ref.mHandle;

			case DMK::GraphicsCore::BufferType::STAGGING:
				return mStaggingBuffers.data() + ref.mHandle;

			default:
				Logger::LogError(TEXT("Undefined or invalid buffer type!"));
				break;
			}

			return nullptr;
		}

		void VulkanDevice::TerminateBuffer(const GraphicsCore::BufferRef& ref)
		{
			auto pBuffer = GetBuffer(ref);
			pBuffer->Terminate(this);

			switch (ref.mType)
			{
			case DMK::GraphicsCore::BufferType::VERTEX:
				break;

			case DMK::GraphicsCore::BufferType::INDEX:
				break;

			case DMK::GraphicsCore::BufferType::UNIFORM_DATA:
				mUniformBuffers.erase(mUniformBuffers.begin() + ref.mHandle);
				break;

			case DMK::GraphicsCore::BufferType::STAGGING:
				mStaggingBuffers.erase(mStaggingBuffers.begin() + ref.mHandle);
				break;

			default:
				Logger::LogError(TEXT("Undefined or invalid buffer type!"));
				break;
			}
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
			pWindowHandle = glfwCreateWindow(GetInitInfo().windowWidth, GetInitInfo().windowHeight, WStringToString(GetInitInfo().pWindowTitle).c_str(), nullptr, nullptr);

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
		}

		void VulkanDevice::CreateSurface()
		{
			if (vSurface == VK_NULL_HANDLE)
				DMK_VK_ASSERT(glfwCreateWindowSurface(GetParentInstance()->GetInstance(), GetWindowHandle(), nullptr, &vSurface), "Failed to create the Vulkan Surface!");
		}

		void VulkanDevice::DestroySurface()
		{
			vkDestroySurfaceKHR(GetParentInstance()->GetInstance(), GetSurface(), nullptr);
		}

		void VulkanDevice::InitializePhysicalDevice()
		{
			UI32 deviceCount = 0;
			vkEnumeratePhysicalDevices(GetParentInstance()->GetInstance(), &deviceCount, nullptr);

			if (deviceCount == 0)
			{
				Logger::LogError(TEXT("Failed to find GPUs with Vulkan support!"));
				return;
			}

			std::vector<VkPhysicalDevice> devices(deviceCount);
			vkEnumeratePhysicalDevices(GetParentInstance()->GetInstance(), &deviceCount, devices.data());

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

			// Get surface capabilities.
			DMK_VK_ASSERT(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(GetPhysicalDevice(), GetSurface(), &vSurfaceCapabilities), "Failed to get Surface Capabilities");

			// Get swap chain support details.
			vSwapChainSupportDetails = _Helpers::QuerySwapChainSupportDetails(GetPhysicalDevice(), GetSurface());

			// Initialize MSAA samples.
			{
				vMsaaSamples = vPhysicalDeviceProperties.limits.framebufferColorSampleCounts & vPhysicalDeviceProperties.limits.framebufferDepthSampleCounts;

				if (vMsaaSamples & VK_SAMPLE_COUNT_64_BIT) vMsaaSamples = VK_SAMPLE_COUNT_64_BIT;
				else if (vMsaaSamples & VK_SAMPLE_COUNT_32_BIT) vMsaaSamples = VK_SAMPLE_COUNT_32_BIT;
				else if (vMsaaSamples & VK_SAMPLE_COUNT_16_BIT) vMsaaSamples = VK_SAMPLE_COUNT_16_BIT;
				else if (vMsaaSamples & VK_SAMPLE_COUNT_8_BIT) vMsaaSamples = VK_SAMPLE_COUNT_8_BIT;
				else if (vMsaaSamples & VK_SAMPLE_COUNT_4_BIT) vMsaaSamples = VK_SAMPLE_COUNT_4_BIT;
				else if (vMsaaSamples & VK_SAMPLE_COUNT_2_BIT) vMsaaSamples = VK_SAMPLE_COUNT_2_BIT;
				else vMsaaSamples = VK_SAMPLE_COUNT_1_BIT;
			}
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
				createInfo.enabledLayerCount = static_cast<UI32>(GetParentInstance()->GetValidationLayers().size());
				createInfo.ppEnabledLayerNames = GetParentInstance()->GetValidationLayers().data();
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

		bool VulkanDevice::IsPhysicalDeviceSuitable(VkPhysicalDevice vDevice)
		{
			Queue _queue = {};
			_queue.FindQueueFamilies(vDevice, GetSurface());

			bool extensionsSupported = CheckDeviceExtensionSupport(vDevice, deviceExtensions);
			bool swapChainAdequate = false;
			if (extensionsSupported)
			{
				SwapChainSupportDetails swapChainSupport = _Helpers::QuerySwapChainSupportDetails(vDevice, GetSurface());
				swapChainAdequate = (!swapChainSupport.formats.empty()) && (!swapChainSupport.presentModes.empty());
			}

			VkPhysicalDeviceFeatures supportedFeatures;
			vkGetPhysicalDeviceFeatures(vDevice, &supportedFeatures);

			return _queue.IsComplete()
				&& extensionsSupported
				&& swapChainAdequate
				&& supportedFeatures.samplerAnisotropy;
		}

		void VulkanDevice::DestroyBuffer(const GraphicsCore::BufferHandle& handle)
		{
#define TERMINATE_AND_ERASE_BUFFER(bArray)						\
	(bArray.data() + handle.GetHandle())->Terminate(this);		\
	bArray.erase(bArray.begin() + handle.GetHandle())

			switch (handle.GetType())
			{
			case DMK::GraphicsCore::BufferType::UNIFORM_DATA:
				TERMINATE_AND_ERASE_BUFFER(mUniformBuffers);
				break;

			case DMK::GraphicsCore::BufferType::STAGGING:
				TERMINATE_AND_ERASE_BUFFER(mStaggingBuffers);
				break;

			default:
				Logger::LogError(TEXT("Invalid or unsupported buffer type!"));
				break;
			}
		}

		void VulkanDevice::DestroyAllBuffers(GraphicsCore::BufferType type)
		{
#define TERMINATE_BUFFER_AND_CLEAR(bArray)												\
	for(auto itr = bArray.begin(); itr != bArray.end(); itr++)							\
			itr->Terminate(this);														\
	bArray.clear()

			switch (type)
			{
			case DMK::GraphicsCore::BufferType::UNDEFINED:
				TERMINATE_BUFFER_AND_CLEAR(mUniformBuffers);
				TERMINATE_BUFFER_AND_CLEAR(mStaggingBuffers);
				break;

			case DMK::GraphicsCore::BufferType::UNIFORM_DATA:
				TERMINATE_BUFFER_AND_CLEAR(mUniformBuffers);
				break;

			case DMK::GraphicsCore::BufferType::STAGGING:
				TERMINATE_BUFFER_AND_CLEAR(mStaggingBuffers);
				break;

			default:
				Logger::LogError(TEXT("Invalid or unsupported buffer type!"));
				break;
			}
		}

		void VulkanDevice::SubmitDataToBuffer(const GraphicsCore::BufferHandle& handle, void* pData, UI64 size, UI64 offset)
		{
			switch (handle.GetType())
			{
			case DMK::GraphicsCore::BufferType::VERTEX:
				break;
			case DMK::GraphicsCore::BufferType::INDEX:
				break;
			case DMK::GraphicsCore::BufferType::UNIFORM_DATA:
				(mUniformBuffers.data() + handle.GetHandle())->CopyData(this, pData, size, offset);
				break;
			case DMK::GraphicsCore::BufferType::STAGGING:
				(mStaggingBuffers.data() + handle.GetHandle())->CopyData(this, pData, size, offset);
				break;
			default:
				Logger::LogError(TEXT("Invalid buffer type!"));
				break;
			}
		}
	}
}