// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/Objects/Display.h"

namespace DMK
{
	namespace VulkanBackend
	{
		VulkanDisplay::Index CreateDisplay(UI32 width, UI32 height, const char* pTitle, Inputs::InputCenter* pInputCenter)
		{
			VulkanDisplay display = {};

#ifdef DMK_DEBUG
			display.pWindowHandle = glfwCreateWindow(width, height, pTitle, nullptr, nullptr);

#else
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* mode = glfwGetVideoMode(monitor);

			glfwWindowHint(GLFW_RED_BITS, mode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

			display.pWindowHandle = glfwCreateWindow(mode->width, mode->height, pTitle, monitor, NULL);

			glfwSetInputMode(display.pWindowHandle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

#endif // DMK_DEBUG

			return VulkanDisplay::Store::Insert(std::move(display));
		}

		void DestroyDisplay(const VulkanDisplay::Index& vIndex)
		{
			VulkanDisplay& display = VulkanDisplay::Store::Get(vIndex);

			glfwDestroyWindow(display.pWindowHandle);
			VulkanDisplay::Store::Remove(vIndex);
		}
	}
}