// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_BACKEND_OBJECT_H
#define _DYNAMIK_VULKAN_BACKEND_OBJECT_H

#include "Core/Macros/Global.h"
#include <vulkan/vulkan.h>

namespace DMK
{
	namespace GraphicsCore
	{
		namespace VulkanBackend
		{
			/**
			 * Vulkan Object for the Dynamik Engine.
			 * This object is (one of) the base class(es) of all the objects in the Vulkan Backend.
			 */
			class DMK_API VulkanObject {
			public:
				/**
				 * Default constructor.
				 */
				VulkanObject() {}

				/**
				 * Default destructor.
				 */
				virtual ~VulkanObject() {}

				/**
				 * Set the logical device which the object is build upon on.
				 *
				 * @param vDevice: The VkDevice object.
				 */
				void SetDevice(const VkDevice& vDevice) { logicalDevice = vDevice; }

				/**
				 * Get the vulkan logical device.
				 */
				VkDevice GetDevice() const { return logicalDevice; }

				/**
				 * Set the physical device which the object is build upon on.
				 *
				 * @param vDevice: The VkPhysicalDevice object.
				 */
				void SetPhysicalDevice(const VkPhysicalDevice& vDevice) { physicalDevice = vDevice; }

				/**
				 * Get the vulkan physical device.
				 */
				VkPhysicalDevice GetPhysicalDevice() const { return physicalDevice; }

				/* Data */
			protected:
				VkDevice logicalDevice = VK_NULL_HANDLE;
				VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
			};
		}
	}
}

#endif // !_DYNAMIK_VULKAN_BACKEND_OBJECT_H
