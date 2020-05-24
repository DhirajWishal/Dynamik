#pragma once
#ifndef _DYNAMIK_VULKAN_INSTANCE_H
#define _DYNAMIK_VULKAN_INSTANCE_H

/*
 Author:    Dhiraj Wishal
 Date:      24/05/2020
*/
#include "Macros/Global.h"
#include "Types/DataTypes.h"
#include <vulkan/vulkan.h>

namespace Dynamik
{
	namespace Backend
	{
		/*
		 Vulkan Instance for the Dynamik RBL
		*/
		class DMK_API VulkanInstance {
		public:
			VulkanInstance() {}
			~VulkanInstance() {}

			void initialize(B1 enableValidation, ARRAY<CCPTR> layers = { "VK_LAYER_KHRONOS_validation" });
			void terminate();

			operator VkInstance() const;

			ARRAY<CCPTR> validationLayers;
			ARRAY<CCPTR> extentions;
			VkInstance instance = VK_NULL_HANDLE;
			B1 isValidationEnabled = false;

		private:
			VkDebugUtilsMessengerEXT _debugMessenger = VK_NULL_HANDLE;

			void _initializeDebugger();
			void _populateDebugMessegerCreateInfo(POINTER<VkDebugUtilsMessengerCreateInfoEXT> createInfo);

			B1 _checkValidationLayerSupport(ARRAY<CCPTR> layers);
			ARRAY<CCPTR> _getRequiredExtensions(B1 pushDescriptorsSupported = false, B1 checkpointsSupported = false, B1 meshShadingSupported = false);
		};
	}
}

#endif // !_DYNAMIK_VULKAN_INSTANCE_H
