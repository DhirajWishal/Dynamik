// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_CORE_OBJECT_H
#define _DYNAMIK_VULKAN_CORE_OBJECT_H

/*
 Author:	Dhiraj Wishal
 Date:		14/06/2020
*/
#include "../../Components/RCoreObject.h"

#include "Common/VulkanDevice.h"
#include "Common/VulkanQueue.h"

namespace Dynamik
{
	/*
	 Vulkan Core Object
	*/
	class DMK_API VulkanCoreObject : public RCoreObject {
	public:
		VulkanCoreObject() {}
		~VulkanCoreObject() {}

		virtual void initialize(POINTER<DMKWindowHandle> pWindow, DMKSampleCount eSamples, B1 bEnableValidation);
		virtual void terminate();

		Backend::VulkanInstance myInstance;
		Backend::VulkanDevice myDevice;
		Backend::VulkanSurface mySurface;
		Backend::VulkanQueue myQueue;
	};
}

#endif // !_DYNAMIK_VULKAN_CORE_OBJECT_H
