#include "dmkafx.h"
#include "VulkanInstance.h"

#include <iostream>
#include <GLFW/glfw3.h>

namespace Dynamik
{
	namespace Backend
	{
		/* DEBUGGER */
		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData
		) {
			std::string myMessageStatement = "Vulkan Validation Layer ";
			std::string myMessagePreStatement = ": ";

			if (messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT)
				myMessagePreStatement = "(General): ";
			else if (messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT)
				myMessagePreStatement = "(Validation): ";
			else if (messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT)
				myMessagePreStatement = "(Performance): ";

			switch (messageSeverity) {
			case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
				std::cerr << myMessageStatement << myMessagePreStatement << pCallbackData->pMessage << std::endl;
				break;
			case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
				DMK_INFO("" + (myMessageStatement + myMessagePreStatement + std::string(pCallbackData->pMessage)));
				break;
			case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
				DMK_WARN("" + (myMessageStatement + myMessagePreStatement + std::string(pCallbackData->pMessage)));
				break;
			case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
				DMK_ERROR("" + (myMessageStatement + myMessagePreStatement + std::string(pCallbackData->pMessage)));
				break;
			default:
				std::cerr << myMessageStatement << myMessagePreStatement << pCallbackData->pMessage << std::endl;
				break;
			}

			return VK_FALSE;
		}

		VkResult createDebugUtilsMessengerEXT(
			VkInstance instance,
			const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
			const VkAllocationCallbacks* pAllocator,
			VkDebugUtilsMessengerEXT* pDebugMessenger
		) {
			auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance,
				"vkCreateDebugUtilsMessengerEXT");

			if (func != nullptr)
				return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
			else
				return VK_ERROR_EXTENSION_NOT_PRESENT;
		}

		void destroyDebugUtilsMessengerEXT(
			VkInstance instance,
			VkDebugUtilsMessengerEXT debugMessenger,
			const VkAllocationCallbacks* pAllocator
		) {
			auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance,
				"vkDestroyDebugUtilsMessengerEXT");

			if (func != nullptr)
				func(instance, debugMessenger, pAllocator);
		}

		void VulkanInstance::initialize(B1 enableValidation, ARRAY<CCPTR> layers)
		{
			isValidationEnabled = enableValidation;
			validationLayers = layers;

			if (enableValidation && !_checkValidationLayerSupport(layers))
				DMKErrorManager::issueErrorBox("Validation Layers Requested, But Not Available!");

			// instance info
			VkApplicationInfo appInfo = {};
			appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			appInfo.pApplicationName = "Dynamik Engine";
			appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
			appInfo.pEngineName = "Dynamik";
			appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
			appInfo.apiVersion = VK_API_VERSION_1_1;

			VkInstanceCreateInfo createInfo = {};
			createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			createInfo.pApplicationInfo = &appInfo;

			extentions = _getRequiredExtensions();
			createInfo.enabledExtensionCount = static_cast<UI32>(extentions.size());
			createInfo.ppEnabledExtensionNames = extentions.data();

			VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
			if (enableValidation) {
				createInfo.enabledLayerCount = static_cast<UI32>(layers.size());
				createInfo.ppEnabledLayerNames = layers.data();

				_populateDebugMessegerCreateInfo(&debugCreateInfo);
				createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
			}
			else {
				createInfo.enabledLayerCount = 0;

				createInfo.pNext = nullptr;
			}

			DMK_VULKAN_ASSERT(vkCreateInstance(&createInfo, nullptr, &instance), "Failed to create instance!");

			if (enableValidation)
				_initializeDebugger();
		}

		void VulkanInstance::terminate()
		{
			if (_debugMessenger != VK_NULL_HANDLE)
				destroyDebugUtilsMessengerEXT(instance, _debugMessenger, nullptr);

			vkDestroyInstance(instance, nullptr);
		}

		VulkanInstance::operator VkInstance() const
		{
			return this->instance;
		}

		void VulkanInstance::_initializeDebugger()
		{
			VkDebugUtilsMessengerCreateInfoEXT createInfo;
			_populateDebugMessegerCreateInfo(&createInfo);

			DMK_VULKAN_ASSERT(createDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &_debugMessenger), "Failed to set up debug messenger!");
		}

		void VulkanInstance::_populateDebugMessegerCreateInfo(POINTER<VkDebugUtilsMessengerCreateInfoEXT> createInfo)
		{
			createInfo->sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
			createInfo->messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
				| VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
				| VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
			createInfo->messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
				| VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
				| VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
			createInfo->pfnUserCallback = debugCallback;

			createInfo->pNext = VK_NULL_HANDLE;
			createInfo->pUserData = VK_NULL_HANDLE;
			createInfo->flags = VK_NULL_HANDLE;
		}

		B1 VulkanInstance::_checkValidationLayerSupport(ARRAY<CCPTR> layers)
		{
			UI32 layerCount = 0;
			vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

			ARRAY<VkLayerProperties> availableLayers(layerCount);
			vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

			for (const char* layerName : layers) {
				B1 layerFound = false;

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

		ARRAY<CCPTR> VulkanInstance::_getRequiredExtensions(B1 pushDescriptorsSupported, B1 checkpointsSupported, B1 meshShadingSupported)
		{
			UI32 glfwExtentionCount = 0;
			const char** glfwExtentions;
			glfwExtentions = glfwGetRequiredInstanceExtensions(&glfwExtentionCount);
			std::vector<CCPTR> extentions(glfwExtentions, glfwExtentions + glfwExtentionCount);

			if (pushDescriptorsSupported)
				extentions.push_back(VK_KHR_PUSH_DESCRIPTOR_EXTENSION_NAME);

			if (checkpointsSupported)
				extentions.push_back(VK_NV_DEVICE_DIAGNOSTIC_CHECKPOINTS_EXTENSION_NAME);

			if (meshShadingSupported)
				extentions.push_back(VK_NV_MESH_SHADER_EXTENSION_NAME);

			extentions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

			return extentions;
		}
	}
}