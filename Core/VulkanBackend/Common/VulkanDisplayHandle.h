// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_BACKEND_DISPLAY_HANDLE_H
#define _DYNAMIK_VULKAN_BACKEND_DISPLAY_HANDLE_H

#include "Inputs/Suppliers/KeyInputSupplier.h"

#include <GLFW/glfw3.h>

namespace DMK
{
	namespace GraphicsCore
	{
		namespace VulkanBackend
		{
			/**
			 * Vulkan Display Handle object.
			 * This object uses GLFW to create the window.
			 */
			class VulkanDisplayHandle {
			public:
				/**
				 * Default constructor.
				 */
				VulkanDisplayHandle() {}

				/**
				 * Default destructor.
				 */
				~VulkanDisplayHandle() {}

			private:
				GLFWwindow* pWindowHandle = nullptr;	// The GLFW window handle.
			};
		}
	}
}

#endif // !_DYNAMIK_VULKAN_BACKEND_DISPLAY_HANDLE_H
