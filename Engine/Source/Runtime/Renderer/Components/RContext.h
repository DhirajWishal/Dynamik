// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_CONTEXT_H
#define _DYNAMIK_RENDERER_CONTEXT_H

/*
 Author:	Dhiraj Wishal
 Date:		15/06/2020
*/
#include "Context/RFrameBuffer.h"
#include "ContextTypeDefs.h"

namespace Dynamik
{
	/*
	 Renderer Context
	*/
	class DMK_API RContext {
	public:
		RContext() {}
		virtual ~RContext() {}

		virtual void initialize(POINTER<RCoreObject> pCoreObject, DMKRenderContextType eType, DMKViewport viewport) {}
		virtual void terminate(POINTER<RCoreObject> pCoreObject) {}

	public:
		POINTER<RRenderPass> renderPass;
		POINTER<RSwapChain> swapChain;
		POINTER<RFrameBuffer> frameBuffer;
	};
}

#endif // !_DYNAMIK_RENDERER_CONTEXT_H
