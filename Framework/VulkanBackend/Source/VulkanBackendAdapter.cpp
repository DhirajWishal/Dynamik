// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/VulkanBackendAdapter.h"

namespace DMK
{
	namespace VulkanBackend
	{
		void VulkanBackendAdapter::Initialize(bool enableValidation)
		{
			mInstance.Initialize(enableValidation);
		}

		void VulkanBackendAdapter::Terminate()
		{
			mInstance.Terminate();

			//mDevices.Clear();
			//mDisplays.Clear();
		}

		GraphicsCore::DisplayHandle VulkanBackendAdapter::CreateDisplay(UI32 width, UI32 height, const char* pTitle)
		{
			//VulkanDisplay display = {};
			//display.Initialize(&mInstance, width, height, pTitle);
			//
			//return CreateHandle<GraphicsCore::DisplayHandle>(mDisplays.Insert(display) + 1);

			VulkanDisplay* pDisplay = new VulkanDisplay();
			pDisplay->Initialize(&mInstance, width, height, pTitle);

			return CreateHandle<GraphicsCore::DisplayHandle>(reinterpret_cast<UI64>(pDisplay));
		}

		Inputs::InputCenter* VulkanBackendAdapter::GetDisplayInputCenter(const GraphicsCore::DisplayHandle& displayHandle)
		{
			//return mDisplays.Get(GetHandle(displayHandle) - 1).GetInputCenter();
			return reinterpret_cast<VulkanDisplay*>((GetHandle(displayHandle)))->GetInputCenter();
		}

		void VulkanBackendAdapter::DestroyDisplay(const GraphicsCore::DisplayHandle& handle)
		{
			//VulkanDisplay& display = mDisplays.Get(GetHandle(handle) - 1);
			//display.Terminate();
			//
			//mDisplays.Remove(GetHandle(handle) - 1);

			VulkanDisplay* pDisplay = reinterpret_cast<VulkanDisplay*>((GetHandle(handle)));
			pDisplay->Terminate();

			delete pDisplay;
		}

		GraphicsCore::DeviceHandle VulkanBackendAdapter::CreateDevice(const GraphicsCore::DisplayHandle& displayHandle)
		{
			//VulkanDevice device = {};
			//device.Initialize(mDisplays.Location(GetHandle(displayHandle) - 1));
			//
			//return CreateHandle<GraphicsCore::DeviceHandle>(mDevices.Insert(device) + 1);

			VulkanDevice* pDevice = new VulkanDevice();
			pDevice->Initialize(reinterpret_cast<VulkanDisplay*>((GetHandle(displayHandle))));

			return CreateHandle<GraphicsCore::DeviceHandle>(reinterpret_cast<UI64>(pDevice));
		}

		void VulkanBackendAdapter::DestroyDevice(const GraphicsCore::DeviceHandle& handle)
		{
			//VulkanDevice& display = mDevices.Get(GetHandle(handle) - 1);
			//display.Terminate();
			//
			//mDevices.Remove(GetHandle(handle) - 1);

			VulkanDevice* pDevice = reinterpret_cast<VulkanDevice*>((GetHandle(handle)));
			pDevice->Terminate();

			delete pDevice;
		}
	}
}