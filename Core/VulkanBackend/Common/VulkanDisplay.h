// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GraphicsCore/Backend/DisplayObject.h"

#include <GLFW/glfw3.h>

namespace DMK
{
	namespace VulkanBackend
	{
		/**
		 * Vulkan Display object.
		 * This uses GLFW to create the window.
		 */
		class VulkanDisplay : public GraphicsCore::DisplayObject {
		public:
			VulkanDisplay() {}
			~VulkanDisplay() {}

			virtual void Initialize(UI32 width, UI32 height, const char* pTitle, Inputs::InputCenter* pInputCenter = nullptr) override final;
			virtual void Terminate() override final;

		private:
			GLFWwindow* pWindowHandle = nullptr;
		};
	}
}