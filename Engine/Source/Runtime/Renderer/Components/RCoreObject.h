// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_CORE_OBJECT_H
#define _DYNAMIK_RENDERER_CORE_OBJECT_H

/*
 Author:	Dhiraj Wishal
 Date:		14/06/2020
*/
#include "Core/Globals/RenderSettings.h"
#include "CoreTypeDefs.h"
#include "Window/WindowHandle.h"

namespace Dynamik
{
	/*
	 Renderer Core Object
	 This is an API specific component which contains the core components of an API.
	 eg: (in Vulkan),
	   - Instance
	   - Physical Device
	   - Logical Device
	   - Queues
	*/
	class DMK_API RCoreObject {
	public:
		RCoreObject() {}
		virtual ~RCoreObject() {}

		virtual void initialize(POINTER<DMKWindowHandle> pWindow, DMKSampleCount eSamples, B1 bEnableValidation) = 0;
		virtual void terminate() = 0;

		DMKSampleCount sampleCount = DMKSampleCount::DMK_SAMPLE_COUNT_64_BIT;
	};
}

#endif // !_DYNAMIK_RENDERER_CORE_OBJECT_H
