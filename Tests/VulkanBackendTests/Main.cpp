// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/Common/VulkanDeviceManager.h"
#include "VulkanBackend/Common/ShaderModule.h"
using namespace DMK::GraphicsCore;
using namespace DMK::VulkanBackend;

#include "Core/Benchmark/Timer.h"
#include "Thread/Utilities.h"

#include <thread>

int main()
{
	VulkanInstance instance = {};
	instance.Initialize(true);

	auto pDevice = instance.CreateDevice(DeviceInitInfo());

}