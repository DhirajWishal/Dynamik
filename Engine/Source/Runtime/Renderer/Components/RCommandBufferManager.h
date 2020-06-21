// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_COMMAND_BUFFER_MANAGER_H
#define _DYNAMIK_RENDERER_COMMAND_BUFFER_MANAGER_H

/*
 Author:	Dhiraj Wishal
 Date:		16/06/2020
*/
#include "RCommandBuffer.h"
#include "RRenderTarget.h"

namespace Dynamik
{
	/*
	 Renderer Command Buffer Manager
	*/
	class DMK_API RCommandBufferManager {
	public:
		RCommandBufferManager() {}
		virtual ~RCommandBufferManager() {}

		virtual void initialize(POINTER<RCoreObject> pCoreObject) = 0;
		virtual ARRAY<POINTER<RCommandBuffer>> allocateCommandBuffers(POINTER<RCoreObject> pCoreObject, UI32 bufferCount) { return ARRAY<POINTER<RCommandBuffer>>(); }
		virtual void bindRenderTarget(POINTER<RCommandBuffer> pCommandBuffer, POINTER<RRenderTarget> pRenderTarget, DMKViewport viewport, UI32 bufferIndex) = 0;
		virtual void unbindRenderTarget(POINTER<RCommandBuffer> pCommandBuffer) = 0;
		virtual void resetBuffers(POINTER<RCoreObject> pCoreObject, ARRAY<POINTER<RCommandBuffer>> commandBuffers) = 0;
		virtual void terminate(POINTER<RCoreObject> pCoreObject, ARRAY<POINTER<RCommandBuffer>> commandBuffers) = 0;
	};
}

#endif // !_DYNAMIK_RENDERER_COMMAND_BUFFER_MANAGER_H
