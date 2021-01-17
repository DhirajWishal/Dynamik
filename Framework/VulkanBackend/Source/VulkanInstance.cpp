// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/VulkanInstance.h"
#include "VulkanBackend/Macros.h"
#include "Core/ErrorHandler/Logger.h"
#include "Core/Types/Utilities.h"

#include "VulkanBackend/VulkanDisplay.h"

#include <iostream>
#include <GLFW/glfw3.h>

namespace DMK
{
	namespace VulkanBackend
	{
		namespace _Helpers
		{
			/**
			 * Error callback function for GLFW.
			 *
			 * @param errorCode: The error code.
			 * @param pDescription: The error description.
			 */
			static void GLFWErrorCallback(I32 errorCode, const char* pDescription)
			{
				DMK_LOG_ERROR((TEXT("GLFW -> ") + StringToWString(pDescription)).c_str());
			}

			/**
			 * Check if the requested validation layers are supported.
			 *
			 * @param layers: The validation layers to be checked.
			 * @return Boolean value.
			 */
			inline bool CheckValidationLayerSupport(std::vector<const char*> layers)
			{
				UI32 layerCount = 0;
				vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

				std::vector<VkLayerProperties> availableLayers(layerCount);
				vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

				// Iterate through the layers to check if all the layers are supported.
				for (const char* layerName : layers)
				{
					bool layerFound = false;

					for (const VkLayerProperties& layerProperties : availableLayers)
					{
						if (strcmp(layerName, layerProperties.layerName) == 0)
						{
							layerFound = true;
							break;
						}
					}

					// Return false an unsupported layer was found.
					if (!layerFound)
						return false;
				}

				return true;
			}

			/**
			 * Get the requires instance extensions from GLFW.
			 *
			 * @return std::vector<const char*> containing the required extensions.
			 */
			std::vector<const char*> GetRequiredInstanceExtensions(bool enableValidation)
			{
				UI32 glfwExtentionCount = 0;
				const char** glfwExtensions = nullptr;
				glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtentionCount);
				std::vector<const char*> extentions(glfwExtensions, glfwExtensions + glfwExtentionCount);

				if (enableValidation)
					INSERT_INTO_VECTOR(extentions, VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

				//if (pushDescriptorsSupported)
				//	extentions.push_back(VK_KHR_PUSH_DESCRIPTOR_EXTENSION_NAME);
				//
				//if (checkpointsSupported)
				//	extentions.push_back(VK_NV_DEVICE_DIAGNOSTIC_CHECKPOINTS_EXTENSION_NAME);
				//
				//if (meshShadingSupported)
				//	extentions.push_back(VK_NV_MESH_SHADER_EXTENSION_NAME);
				//
				//extentions.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);

				return extentions;
			}

			/**
			 * Debug Callback function for Vulkan.
			 * This function is used to return debug information provided by Vulkan.
			 *
			 * @param messageSeverity: The severity of the message.
			 * @param messageType: The type of the message.
			 * @param pCallbackData: The callback data.
			 * @param pUserData: The user data that triggered the messenger.
			 * @return VkBool32 value.
			 */
			static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
				VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
				VkDebugUtilsMessageTypeFlagsEXT messageType,
				const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
				void* pUserData)
			{
				WString myMessageStatement = TEXT("Vulkan Validation Layer ");
				WString myMessagePreStatement = TEXT(": ");

				if (messageType == VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT)
					myMessagePreStatement = TEXT("(General): ");
				else if (messageType == VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT)
					myMessagePreStatement = TEXT("(Validation): ");
				else if (messageType == VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT)
					myMessagePreStatement = TEXT("(Performance): ");

				switch (messageSeverity) {
				case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
					Logger::LogDebug(WString(TEXT("") + (myMessageStatement + myMessagePreStatement + StringToWString(pCallbackData->pMessage))).c_str());
					break;
				case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
					Logger::LogInfo(WString(TEXT("") + (myMessageStatement + myMessagePreStatement + StringToWString(pCallbackData->pMessage))).c_str());
					break;
				case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
					Logger::LogWarn(WString(TEXT("") + (myMessageStatement + myMessagePreStatement + StringToWString(pCallbackData->pMessage))).c_str());
					break;
				case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
					DMK_LOG_ERROR(WString(TEXT("") + (myMessageStatement + myMessagePreStatement + StringToWString(pCallbackData->pMessage))).c_str());
					break;
				default:
					std::wcerr << myMessageStatement << myMessagePreStatement << StringToWString(pCallbackData->pMessage) << std::endl;
					break;
				}

				return VK_FALSE;
			}

			/**
			 * Create a new VkDebugUtilsMessengerCreateInfoEXT object.
			 *
			 * @return The newly created VkDebugUtilsMessengerCreateInfoEXT object.
			 */
			VkDebugUtilsMessengerCreateInfoEXT CreateDebugMessengerCreateInfo()
			{
				VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
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

				return createInfo;
			}
		}

		void VulkanInstance::Initialize(bool enableValidation)
		{
			this->mEnableValidation = enableValidation;

			InitializeGLFW();

			if (enableValidation)
				INSERT_INTO_VECTOR(mValidationLayers, "VK_LAYER_KHRONOS_validation");

			CreateInstance();

			if (enableValidation)
				CreateDebugMessenger();
		}

		void VulkanInstance::Terminate()
		{
			if (mValidationLayers.size())
				DestroyDebugMessenger();

			DestroyInstance();

			TerminateGLFW();
		}

		void VulkanInstance::InitializeGLFW()
		{
			glfwInit();
		}

		void VulkanInstance::TerminateGLFW()
		{
			glfwTerminate();
		}

		void VulkanInstance::CreateInstance()
		{
			// Check if the validation layers are supported.
			if (mEnableValidation && !_Helpers::CheckValidationLayerSupport(mValidationLayers))
				DMK_LOG_ERROR(TEXT("Requested validation layers are not available!"));

			// Application info.
			VkApplicationInfo appInfo = {};
			appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			appInfo.pApplicationName = "Dynamik Engine";
			appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
			appInfo.pEngineName = "Dynamik";
			appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
			appInfo.apiVersion = VK_API_VERSION_1_2;

			// Instance create info.
			VkInstanceCreateInfo createInfo = {};
			createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			createInfo.pApplicationInfo = &appInfo;

			// Get and insert the required instance extensions.
			std::vector<const char*> requiredExtensions = std::move(_Helpers::GetRequiredInstanceExtensions(mEnableValidation));
			createInfo.enabledExtensionCount = static_cast<UI32>(requiredExtensions.size());
			createInfo.ppEnabledExtensionNames = requiredExtensions.data();

			// Initialize debugger.
			VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = {};
			if (mEnableValidation)
			{
				createInfo.enabledLayerCount = static_cast<UI32>(mValidationLayers.size());
				createInfo.ppEnabledLayerNames = mValidationLayers.data();

				debugCreateInfo = _Helpers::CreateDebugMessengerCreateInfo();
				createInfo.pNext = static_cast<VkDebugUtilsMessengerCreateInfoEXT*>(&debugCreateInfo);
			}
			else
			{
				createInfo.enabledLayerCount = 0;
				createInfo.pNext = nullptr;
			}

			// Create the instance handle.
			DMK_VK_ASSERT(vkCreateInstance(&createInfo, nullptr, &vInstance), "Failed to create instance!");
		}

		void VulkanInstance::DestroyInstance()
		{
			vkDestroyInstance(vInstance, nullptr);
		}

		void VulkanInstance::CreateDebugMessenger()
		{
			VkDebugUtilsMessengerCreateInfoEXT createInfo = _Helpers::CreateDebugMessengerCreateInfo();

			auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(vInstance, "vkCreateDebugUtilsMessengerEXT");

			// Create the debug messenger handle.
			DMK_VK_ASSERT(func(vInstance, &createInfo, nullptr, &vDebugUtilsMessenger), "Failed to create the debug messenger!");
		}

		void VulkanInstance::DestroyDebugMessenger()
		{
			auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(vInstance, "vkDestroyDebugUtilsMessengerEXT");

			if (func != nullptr)
				func(vInstance, vDebugUtilsMessenger, nullptr);
		}
	}
}