// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_CORE_OBJECT_H
#define _DYNAMIK_RENDERER_CORE_OBJECT_H

#include "Core/Globals/RenderSettings.h"
#include "CoreTypeDefs.h"
#include "Window/WindowHandle.h"
#include "RCommandBuffer.h"

namespace Dynamik
{
	class DMK_API RSwapChain;
	class DMK_API RCommandBuffer;

	/*
	 Renderer Core Object
	 This is an API specific component which contains the core components of an API.
	 eg: (in Vulkan),
	   - Instance
	   - Physical Device
	   - Logical Device
	   - Queues

	   Session("something")
	*/
	class DMK_API RCoreObject {
	public:
		RCoreObject() {}
		virtual ~RCoreObject() {}

		virtual void initialize(DMKWindowHandle* pWindow, DMKSampleCount eSamples, B1 bEnableValidation) = 0;
		virtual void terminate() = 0;

		virtual void idleCall() = 0;

		virtual I32 prepareFrame(RSwapChain* pSwapChain) = 0;
		virtual void submitCommand(RCommandBuffer* pCommandBuffer, RSwapChain* pSwapChain) = 0;

		virtual DMKFormat getDepthFormat() = 0;

		DMKSampleCount sampleCount = DMKSampleCount::DMK_SAMPLE_COUNT_64_BIT;

	protected:
		virtual void initializeSyncComponents() = 0;
	};
}

#endif // !_DYNAMIK_RENDERER_CORE_OBJECT_H
