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

		virtual void initialize(RCoreObject* pCoreObject) = 0;
		virtual ARRAY<RCommandBuffer*> allocateCommandBuffers(RCoreObject* pCoreObject, UI32 bufferCount) { return ARRAY<RCommandBuffer*>(); }
		virtual void resetBuffers(RCoreObject* pCoreObject, ARRAY<RCommandBuffer*> commandBuffers) = 0;
		virtual void terminate(RCoreObject* pCoreObject, ARRAY<RCommandBuffer*> commandBuffers) = 0;
	};
}

#endif // !_DYNAMIK_RENDERER_COMMAND_BUFFER_MANAGER_H
