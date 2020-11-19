// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/Common/VulkanDeviceManager.h"
#include "VulkanBackend/Common/VulkanDevice.h"

#include "Core/Types/SingleDataStore.h"
#include "Core/Types/Utilities.h"

#include <GLFW/glfw3.h>

namespace DMK
{
	namespace VulkanBackend
	{
		typedef SingleDataStore<VulkanDevice> Store;

		void VulkanDeviceManager::Initialize(VulkanInstance* pInstance)
		{
			this->pParentInstance = pInstance;
		}

		void VulkanDeviceManager::Terminate()
		{
			// Initialize the counter and pointer.
			auto counter = Store::Size();
			auto ptr = Store::Data();

			// Terminate all the active devices.
			while (counter--)
				Store::Get(counter).Terminate();

			// Clear the store.
			Store::Clear();
		}

		GraphicsCore::DeviceHandle VulkanDeviceManager::CreateDevice(GraphicsCore::DeviceInitInfo initInfo)
		{
			// Create and initialize the device.
			VulkanDevice vDevice = {};
			vDevice.Initialize(initInfo, pParentInstance);

			// Add data to the store.
			Store::PushBack(std::move(vDevice));

			// Return the Device handle.
			return GraphicsCore::DeviceHandle(Store::Size() - 1);
		}

		void VulkanDeviceManager::DestroyDevice(const GraphicsCore::DeviceHandle& deviceHandle)
		{
			// Get the relavent device object and terminate it.
			Store::Get(deviceHandle.mDeviceID).Terminate();

			// Remove it from the store.
			Store::Remove(deviceHandle.mDeviceID);
		}

		void VulkanDeviceManager::PollInputs()
		{
			glfwPollEvents();
		}
	}
}