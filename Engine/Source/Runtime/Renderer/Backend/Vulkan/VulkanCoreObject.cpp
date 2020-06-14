// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanCoreObject.h"

namespace Dynamik
{
	void VulkanCoreObject::initialize(POINTER<DMKWindowHandle> pWindow, DMKSampleCount eSamples, B1 bEnableValidation)
	{
		/* Initialize the Vulkan Instance */
		myInstance.initialize(bEnableValidation);

		/* Initialize the Vulkan Surface */
		mySurface.initialize(myInstance, pWindow);

		/* Initialize the Vulkan Device */
		myDevice.initialize(myInstance, mySurface);

		if (eSamples > (DMKSampleCount)myDevice.getMaxUsableSampleCount())
		{
			DMKErrorManager::logWarn(DMK_TEXT("Pre defined samples are not supported by the GPU. Setting the default to the maximum usable count."));
			eSamples = (DMKSampleCount)myDevice.getMaxUsableSampleCount();
		}

		/* Initialize the Vulkan Queues */
		myQueue.findQueueFamilies(myDevice, mySurface);
		myQueue.initializeQueues(myDevice);
	}

	void VulkanCoreObject::terminate()
	{
		/* Terminate surface */
		mySurface.terminate(myInstance);

		/* Terminate devices */
		myDevice.terminate(myInstance);

		/* Terminate instance */
		myInstance.terminate();
	}
}
