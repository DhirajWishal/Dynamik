// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GraphicsCore/Backend/Display.h"

#include <GLFW/glfw3.h>

namespace DMK
{
	namespace VulkanBackend
	{
		class VulkanDisplay final : public GraphicsCore::Display {
		public:
			VulkanDisplay() {}
			~VulkanDisplay() {}

			virtual void Initialize(GraphicsCore::Instance* pInstance, UI32 width, UI32 height, const char* pTitle) override final;
			virtual void Terminate() override final;

		public:
			VkSurfaceKHR GetSurface() const { return vSurface; }

		private:
			void SetupInputs();
			void SetupCallbacks();

			void CreateSurface();
			void DestroySurface();

		private:
			GLFWwindow* pWindowHandle = nullptr;
			VkSurfaceKHR vSurface = VK_NULL_HANDLE;
		};
	}
}