// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_BACKEND_OBJECT_H
#define _DYNAMIK_VULKAN_BACKEND_OBJECT_H

#include <vulkan/vulkan.h>

namespace DMK
{
	namespace GraphicsCore
	{
		namespace VulkanBackend
		{
			class VulkanDevice;

			/**
			 * Vulkan Object.
			 * This is the base class for all the Vulkan objects except the Vulkan Device.
			 */
			class VulkanObject {
			public:
				/**
				 * Default constructor.
				 */
				VulkanObject() = default;

				/**
				 * Default destructor.
				 */
				virtual ~VulkanObject() {}

				/**
				 * Set the parent device pointer for the Vulkan Object.
				 *
				 * @param pParentDevice: The VulkanDevice pointer.
				 */
				void SetParent(VulkanDevice* pParentDevice) { this->pParentDevice = pParentDevice; }

				/**
				 * Get the parent device object pointer.
				 *
				 * @return: VulkanDevice pointer.
				 */
				VulkanDevice* GetParent() const { return pParentDevice; }

			protected:
				VulkanDevice* pParentDevice = nullptr;	// Parent device pointer.
			};
		}
	}
}

#endif // !_DYNAMIK_VULKAN_BACKEND_OBJECT_H
