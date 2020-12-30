// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/Common/VulkanDisplay.h"

namespace DMK
{
	namespace VulkanBackend
	{
		void VulkanDisplay::Initialize(UI32 width, UI32 height, const char* pTitle, Inputs::InputCenter* pInputCenter)
		{
#ifdef DMK_DEBUG
			pWindowHandle = glfwCreateWindow(width, height, pTitle, nullptr, nullptr);

#else
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* mode = glfwGetVideoMode(monitor);

			glfwWindowHint(GLFW_RED_BITS, mode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

			pWindowHandle = glfwCreateWindow(mode->width, mode->height, pTitle, monitor, NULL);

			glfwSetInputMode(pWindowHandle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

#endif // DMK_DEBUG

			glfwSetWindowUserPointer(pWindowHandle, this);
		}

		void VulkanDisplay::Terminate()
		{
			glfwDestroyWindow(pWindowHandle);
		}
	}
}