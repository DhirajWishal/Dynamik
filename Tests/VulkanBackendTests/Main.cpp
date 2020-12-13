// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/Objects/Instance.h"
#include "VulkanBackend/Objects/Display.h"
#include "VulkanBackend/Objects/Device.h"
using namespace DMK::VulkanBackend;

#include "Core/Benchmark/Timer.h"
#include "Thread/Utilities.h"

int main()
{
	DMK::VulkanBackend::InitializeGLFW();

	UI8 instanceID = 0;
	UI8 displayID = 0;
	UI8 deviceID = 0;

	{
		DMK::Benchmark::Timer timer;
#ifdef DMK_DEBUG
		instanceID = DMK::VulkanBackend::CreateInstance(true);

#else
		instanceID = DMK::VulkanBackend::CreateInstance(false);

#endif // DMK_DEBUG

		displayID = DMK::VulkanBackend::CreateDisplay(1280, 720, "Dynamik Engine: Vulkan Backend Tests");
		deviceID = DMK::VulkanBackend::CreateDevice(instanceID, displayID);
	}

	DMK::Thread::Utilities::Sleep(5000000);

	{
		DMK::Benchmark::Timer timer;
		DMK::VulkanBackend::DestroyDevice(instanceID, deviceID);
		DMK::VulkanBackend::DestroyDisplay(displayID);
		DMK::VulkanBackend::DestroyInstance(instanceID);
	}

	DMK::VulkanBackend::TerminateGLFW();
}