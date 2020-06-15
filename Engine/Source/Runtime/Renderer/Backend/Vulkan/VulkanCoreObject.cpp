// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanCoreObject.h"

namespace Dynamik
{
	void VulkanCoreObject::initialize(POINTER<DMKWindowHandle> pWindow, DMKSampleCount eSamples, B1 bEnableValidation)
	{
		/* Initialize the Vulkan Instance */
		instance.initialize(bEnableValidation);

		/* Initialize the Vulkan Surface */
		surface.initialize(instance, pWindow);

		/* Initialize the Vulkan Device */
		device.initialize(instance, surface);

		sampleCount = eSamples;
		if (eSamples > (DMKSampleCount)device.getMaxUsableSampleCount())
		{
			DMKErrorManager::logWarn(DMK_TEXT("Pre defined samples are not supported by the GPU. Setting the default to the maximum usable count."));
			sampleCount = (DMKSampleCount)device.getMaxUsableSampleCount();
		}

		/* Initialize the Vulkan Queues */
		queues.findQueueFamilies(device, surface);
		queues.initializeQueues(device);
	}

	void VulkanCoreObject::terminate()
	{
		/* Terminate surface */
		surface.terminate(instance);

		/* Terminate devices */
		device.terminate(instance);

		/* Terminate instance */
		instance.terminate();
	}

	VulkanCoreObject::operator Backend::VulkanInstance() const
	{
		return instance;
	}

	VulkanCoreObject::operator Backend::VulkanDevice() const
	{
		return device;
	}

	VulkanCoreObject::operator Backend::VulkanSurface() const
	{
		return surface;
	}

	VulkanCoreObject::operator Backend::VulkanQueue() const
	{
		return queues;
	}
}
