// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_INSTANCE_H
#define _DYNAMIK_VULKAN_INSTANCE_H

#include "Core/Macros/Global.h"
#include "Core/Types/DataTypes.h"
#include "VulkanMacros.h"

namespace Backend
{
	/*
	 Vulkan Instance for the Dynamik RBL
	*/
	class DMK_API VulkanInstance {
	public:
		VulkanInstance() {}
		~VulkanInstance() {}

		void addExtension(const CCPTR& extension);
		void initialize(bool enableValidation, std::vector<CCPTR> layers = { "VK_LAYER_KHRONOS_validation" });
		void terminate();

		operator VkInstance() const;

		std::vector<CCPTR> validationLayers;
		std::vector<CCPTR> extentions;
		VkInstance instance = VK_NULL_HANDLE;
		bool isValidationEnabled = false;

	private:
		VkDebugUtilsMessengerEXT _debugMessenger = VK_NULL_HANDLE;

		void _initializeDebugger();
		void _populateDebugMessegerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT* createInfo);

		bool _checkValidationLayerSupport(std::vector<CCPTR> layers);
		std::vector<CCPTR> _getRequiredExtensions(bool pushDescriptorsSupported = false, bool checkpointsSupported = false, bool meshShadingSupported = false);
	};
}

#endif // !_DYNAMIK_VULKAN_INSTANCE_H
