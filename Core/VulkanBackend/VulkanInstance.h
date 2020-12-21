// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GraphicsCore/Backend/Instance.h"

#include <vector>
#include <vulkan/vulkan.h>

namespace DMK
{
	namespace VulkanBackend
	{
		class VulkanInstance final : public GraphicsCore::Instance {
		public:
			VulkanInstance() {}
			~VulkanInstance() {}

			virtual void Initialize(bool enableValidation) override final;
			virtual void Terminate() override final;

		public:
			virtual GraphicsCore::Display* CreateDisplay(UI32 width, UI32 height, const char* pTitle) override final;
			virtual void DestroyDisplay(GraphicsCore::Display* pDisplay) override final;

		private:
			void InitializeGLFW();
			void TerminateGLFW();

			void CreateInstance();
			void DestroyInstance();

			void CreateDebugMessenger();
			void DestroyDebugMessenger();

		public:
			VkInstance GetInstance() const { return vInstance; }
			std::vector<const char*>& GetValidationLayers() { return mValidationLayers; }

		private:
			std::vector<const char*> mValidationLayers;

			VkInstance vInstance = VK_NULL_HANDLE;
			VkDebugUtilsMessengerEXT vDebugUtilsMessenger = VK_NULL_HANDLE;
		};
	}
}