// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GraphicsCore/Backend/BackendAdapter.h"

#include "VulkanInstance.h"
#include "VulkanDisplay.h"
#include "VulkanDevice.h"

#include "Core/Types/SparseSet.h"

namespace DMK
{
	namespace VulkanBackend
	{
		/**
		 * Vulkan Backend Adapter.
		 * This class creates, manages and destroys Vulkan Backend based objects and services.
		 */
		class VulkanBackendAdapter final : public GraphicsCore::BackendAdapter {
		public:
			VulkanBackendAdapter() {}
			~VulkanBackendAdapter() {}

			virtual void Initialize(bool enableValidation = true) override final;
			virtual void Terminate() override final;

			virtual GraphicsCore::DisplayHandle CreateDisplay(UI32 width, UI32 height, const char* pTitle = "Dynamik Engine") override final;
			virtual Inputs::InputCenter* GetDisplayInputCenter(const GraphicsCore::DisplayHandle& displayHandle) override final;
			virtual void DestroyDisplay(const GraphicsCore::DisplayHandle& handle) override final;

			virtual GraphicsCore::DeviceHandle CreateDevice(const GraphicsCore::DisplayHandle& displayHandle) override final;
			virtual void DestroyDevice(const GraphicsCore::DeviceHandle& handle) override final;

		private:
			SparseSet<VulkanDisplay> mDisplays;
			SparseSet<VulkanDevice> mDevices;

			VulkanInstance mInstance = {};
		};
	}
}
