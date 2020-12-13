// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Types/StaticSparseSet.h"
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
			using Index = UI8;
			using Store = StaticSparseSet<VulkanDisplay, Index>;

			GLFWwindow* pWindowHandle = nullptr;
		};

		/**
		 * Create a new display.
		 *
		 * @param width: The width of the display.
		 * @param height: The height of the display.
		 * @param pTitle: The title of the window.
		 * @param pInputCenter: The input center to return the inputs to. Default is nullptr.
		 * @return The display index.
		 */
		VulkanDisplay::Index CreateDisplay(UI32 width, UI32 height, const char* pTitle, Inputs::InputCenter* pInputCenter = nullptr);

		/**
		 * Destroy a created display.
		 *
		 * @param vIndex: The index of the display to be destroyed.
		 */
		void DestroyDisplay(const VulkanDisplay::Index& vIndex);
	}
}