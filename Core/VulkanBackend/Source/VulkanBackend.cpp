// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/VulkanBackend.h"

#include "VulkanBackend/Common/Assert.h"
#include "VulkanBackend/Common/VulkanDisplayHandle.h"

#include <iostream>
#include <GLFW/glfw3.h>

#define VK_ENABLE_BETA_EXTENSIONS
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_beta.h>

//#ifdef VK_ENABLE_BETA_EXTENSIONS
//vkGetBufferDeviceAddressKHR = reinterpret_cast<PFN_vkGetBufferDeviceAddressKHR>(vkGetDeviceProcAddr(GetLogicalDevice(), "vkGetBufferDeviceAddressKHR"));
//vkBindAccelerationStructureMemoryKHR = reinterpret_cast<PFN_vkBindAccelerationStructureMemoryKHR>(vkGetDeviceProcAddr(GetLogicalDevice(), "vkBindAccelerationStructureMemoryKHR"));
//vkCreateAccelerationStructureKHR = reinterpret_cast<PFN_vkCreateAccelerationStructureKHR>(vkGetDeviceProcAddr(GetLogicalDevice(), "vkCreateAccelerationStructureKHR"));
//vkDestroyAccelerationStructureKHR = reinterpret_cast<PFN_vkDestroyAccelerationStructureKHR>(vkGetDeviceProcAddr(GetLogicalDevice(), "vkDestroyAccelerationStructureKHR"));
//vkGetAccelerationStructureMemoryRequirementsKHR = reinterpret_cast<PFN_vkGetAccelerationStructureMemoryRequirementsKHR>(vkGetDeviceProcAddr(GetLogicalDevice(), "vkGetAccelerationStructureMemoryRequirementsKHR"));
//vkCmdBuildAccelerationStructureKHR = reinterpret_cast<PFN_vkCmdBuildAccelerationStructureKHR>(vkGetDeviceProcAddr(GetLogicalDevice(), "vkCmdBuildAccelerationStructureKHR"));
//vkBuildAccelerationStructureKHR = reinterpret_cast<PFN_vkBuildAccelerationStructureKHR>(vkGetDeviceProcAddr(GetLogicalDevice(), "vkBuildAccelerationStructureKHR"));
//vkGetAccelerationStructureDeviceAddressKHR = reinterpret_cast<PFN_vkGetAccelerationStructureDeviceAddressKHR>(vkGetDeviceProcAddr(GetLogicalDevice(), "vkGetAccelerationStructureDeviceAddressKHR"));
//vkCmdTraceRaysKHR = reinterpret_cast<PFN_vkCmdTraceRaysKHR>(vkGetDeviceProcAddr(GetLogicalDevice(), "vkCmdTraceRaysKHR"));
//vkGetRayTracingShaderGroupHandlesKHR = reinterpret_cast<PFN_vkGetRayTracingShaderGroupHandlesKHR>(vkGetDeviceProcAddr(GetLogicalDevice(), "vkGetRayTracingShaderGroupHandlesKHR"));
//vkCreateRayTracingPipelinesKHR = reinterpret_cast<PFN_vkCreateRayTracingPipelinesKHR>(vkGetDeviceProcAddr(GetLogicalDevice(), "vkCreateRayTracingPipelinesKHR"));
//
//#endif // VK_ENABLE_BETA_EXTENSIONS

namespace DMK
{
	namespace GraphicsCore
	{
		namespace VulkanBackend
		{
			/**
			 * Check if the requrested validation layers are supported.
			 *
			 * @param layers: The validation layers to be checked.
			 */
			bool CheckValidationLayerSupport(const std::vector<CCPTR>& layers)
			{
				UI32 layerCount = 0;
				vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

				std::vector<VkLayerProperties> availableLayers(layerCount);
				vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

				for (const char* layerName : layers) {
					bool layerFound = false;

					for (auto layerProperties : availableLayers) {
						if (strcmp(layerName, layerProperties.layerName) == 0) {
							layerFound = true;
							break;
						}
					}

					if (!layerFound)
						return false;
				}

				return true;
			}

			/**
			 * Vulkan debug callback function.
			 *
			 * @param messageSeverity: The severity of th message.
			 * @param messageType: The type of the message.
			 * @param pCallbackData: The debug callback data.
			 * @param pUserData: Pointer to the user data.
			 */
			static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
				VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
				VkDebugUtilsMessageTypeFlagsEXT messageType,
				const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
				void* pUserData)
			{
				std::string myMessageStatement = "Vulkan Validation Layer ";
				std::string myMessagePreStatement = ": ";

				if (messageType == VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT)
					myMessagePreStatement = "(General): ";
				else if (messageType == VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT)
					myMessagePreStatement = "(Validation): ";
				else if (messageType == VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT)
					myMessagePreStatement = "(Performance): ";

				switch (messageSeverity)
				{
				case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
					std::cerr << myMessageStatement << myMessagePreStatement << pCallbackData->pMessage << std::endl;
					break;
				case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
					ErrorHandler::Logger::LogInfo("" + (myMessageStatement + myMessagePreStatement + std::string(pCallbackData->pMessage)) + "\n");
					break;
				case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
					ErrorHandler::Logger::LogWarn("" + (myMessageStatement + myMessagePreStatement + std::string(pCallbackData->pMessage)) + "\n");
					break;
				case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
					ErrorHandler::Logger::LogError("" + (myMessageStatement + myMessagePreStatement + std::string(pCallbackData->pMessage)) + "\n");
					break;
				default:
					std::cerr << myMessageStatement << myMessagePreStatement << pCallbackData->pMessage << std::endl;
					break;
				}

				return VK_FALSE;
			}

			///////////////////////////////////////////////////////////////////////////////////////////////////
			////	Class Definitions
			///////////////////////////////////////////////////////////////////////////////////////////////////

			void VulkanBackend::Initialize(const BackendInitInfo& initInfo)
			{
				enableValidation = initInfo.enableValidation;

				validationLayers.push_back("VK_LAYER_KHRONOS_validation");
				deviceExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);

				// Get the required extensions using GLFW.
				{
					UI32 glfwExtentionCount = 0;
					const char** glfwExtentions;
					glfwExtentions = glfwGetRequiredInstanceExtensions(&glfwExtentionCount);
					std::vector<CCPTR> extentions(glfwExtentions, glfwExtentions + glfwExtentionCount);

					instanceExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
				}

				// Extensions to be loaded if ray tracing is needed. 
				if (initInfo.enableRayTracing)
				{
					instanceExtensions.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);

					deviceExtensions.push_back(VK_KHR_MAINTENANCE3_EXTENSION_NAME);
					deviceExtensions.push_back(VK_KHR_GET_MEMORY_REQUIREMENTS_2_EXTENSION_NAME);
					deviceExtensions.push_back(VK_KHR_RAY_TRACING_EXTENSION_NAME);
					deviceExtensions.push_back(VK_KHR_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME);
					deviceExtensions.push_back(VK_KHR_DEFERRED_HOST_OPERATIONS_EXTENSION_NAME);
					deviceExtensions.push_back(VK_EXT_DESCRIPTOR_INDEXING_EXTENSION_NAME);
					deviceExtensions.push_back(VK_KHR_PIPELINE_LIBRARY_EXTENSION_NAME);
				}

				// Create the Vulkan Instance. 
				CreateInstance();

				// Create the debugger if needed.
				if (initInfo.enableValidation)
					CreateDebugger();

				// Create the display.
				CreateDisplay(initInfo.displayCreateInfo);
				CreatePhysicalDevice();
				CreateLogicalDevice();
			}

			void VulkanBackend::Terminate()
			{
				DestroyDisplay();
				DestroyLogicalDevice();
				DestroyPhysicalDevice();

				if (enableValidation)
					DestroyDebugger();

				DestroyInstance();
			}

			Buffer* VulkanBackend::CreateRawBuffer(UI64 size, MemoryProperty memoryProperty)
			{
				return nullptr;
			}

			void VulkanBackend::DestroyBuffer(Buffer* pBuffer)
			{
			}

			VertexBuffer* VulkanBackend::CreateVertexBuffer(UI64 stride, UI64 vertexCount, MemoryProperty memoryProperty)
			{
				return nullptr;
			}

			IndexBuffer* VulkanBackend::CreateIndexBuffer(UI64 stride, UI64 vertexCount, MemoryProperty memoryProperty)
			{
				return nullptr;
			}

			void VulkanBackend::CreateInstance()
			{
				if (enableValidation && !CheckValidationLayerSupport(validationLayers))
					ErrorHandler::Logger::LogError(TEXT("Vulkan validation layers requested but not available!"));

				// Instance info
				VkApplicationInfo appInfo = {};
				appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
				appInfo.pApplicationName = "Dynamik Engine";
				appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
				appInfo.pEngineName = "Dynamik";
				appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
				appInfo.apiVersion = VK_API_VERSION_1_2;

				VkInstanceCreateInfo createInfo = {};
				createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
				createInfo.pApplicationInfo = &appInfo;

				createInfo.enabledExtensionCount = static_cast<UI32>(instanceExtensions.size());
				createInfo.ppEnabledExtensionNames = instanceExtensions.data();

				VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = {};
				if (enableValidation) {
					createInfo.enabledLayerCount = static_cast<UI32>(validationLayers.size());
					createInfo.ppEnabledLayerNames = validationLayers.data();

					// Setup debug create info structure.
					{
						debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
						debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
							| VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
							| VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
						debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
							| VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
							| VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
						debugCreateInfo.pfnUserCallback = DebugCallback;

						debugCreateInfo.pNext = VK_NULL_HANDLE;
						debugCreateInfo.pUserData = VK_NULL_HANDLE;
						debugCreateInfo.flags = VK_NULL_HANDLE;
					}

					createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
				}
				else
				{
					createInfo.enabledLayerCount = 0;

					createInfo.pNext = nullptr;
				}

				DMK_VULKAN_ASSERT(vkCreateInstance(&createInfo, nullptr, &vInstance), "Failed to create instance!");
			}

			void VulkanBackend::CreateDebugger()
			{
				VkDebugUtilsMessengerCreateInfoEXT createInfo;
				createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
				createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
					| VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
					| VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
				createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
					| VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
					| VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
				createInfo.pfnUserCallback = DebugCallback;

				createInfo.pNext = VK_NULL_HANDLE;
				createInfo.pUserData = VK_NULL_HANDLE;
				createInfo.flags = VK_NULL_HANDLE;

				auto func = Cast<PFN_vkCreateDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(GetInstance(), "vkCreateDebugUtilsMessengerEXT"));
				DMK_VULKAN_ASSERT(func(GetInstance(), &createInfo, nullptr, &vDebugMessenger), "Failed to setup the Vulkan Debug Messenger!");
			}

			void VulkanBackend::CreateDisplay(const DisplayCreateInfo& displayCreateInfo)
			{
				pDisplayHandle = new VulkanDisplayHandle;
				pDisplayHandle->Initialize(displayCreateInfo);

				pDisplayHandle->SetupInputCenter();
				pDisplayHandle->Inherit<VulkanDisplayHandle>()->CreateSurface(GetInstance());
			}

			void VulkanBackend::CreatePhysicalDevice()
			{
			}

			void VulkanBackend::CreateLogicalDevice()
			{
			}

			void VulkanBackend::DestroyInstance()
			{
				vkDestroyInstance(GetInstance(), nullptr);
			}

			void VulkanBackend::DestroyDebugger()
			{
				auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(GetInstance(), "vkDestroyDebugUtilsMessengerEXT");
				if (func != nullptr)
					func(GetInstance(), vDebugMessenger, nullptr);
			}

			void VulkanBackend::DestroyDisplay()
			{
				GetDisplayHandle()->Terminate();
				delete GetDisplayHandle();
			}

			void VulkanBackend::DestroyPhysicalDevice()
			{
			}

			void VulkanBackend::DestroyLogicalDevice()
			{
			}
		}
	}
}