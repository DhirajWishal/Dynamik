// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/Common/VulkanDevice.h"
using namespace DMK::GraphicsCore::VulkanBackend;

int main()
{
	VulkanDevice vDevice;

	DMK::GraphicsCore::DeviceInitInfo initInfo = {};
	initInfo.enableRayTracing = false;
	vDevice.Initialize(initInfo);

	while (true)
	{
		vDevice.BeginFrame();
		vDevice.EndFrame();
	}

	vDevice.Terminate();
}