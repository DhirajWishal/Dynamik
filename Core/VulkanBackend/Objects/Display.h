// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GraphicsCore/Backend/BackendHandles.h"
#include "Inputs/InputCenter.h"

#include <GLFW/glfw3.h>

namespace DMK
{
	namespace VulkanBackend
	{
		/**
		 * Vulkan Display structure.
		 * This contains information about a single Display/ Window.
		 */
		struct VulkanDisplay {
			GLFWwindow* pWindowHandle = nullptr;

			static VulkanDisplay Create(UI32 width, UI32 height, const char* pTitle, Inputs::InputCenter* pInputCenter = nullptr);
			static void Destroy(const VulkanDisplay& display);
		};
	}
}