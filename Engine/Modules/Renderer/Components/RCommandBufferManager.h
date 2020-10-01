// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_COMMAND_BUFFER_MANAGER_H
#define _DYNAMIK_RENDERER_COMMAND_BUFFER_MANAGER_H

#include "RCommandBuffer.h"
#include "RRenderTarget.h"

/*
 Renderer Command Buffer Manager
*/
class DMK_API RCommandBufferManager {
public:
	RCommandBufferManager() {}
	virtual ~RCommandBufferManager() {}

	virtual void initialize(RCoreObject* pCoreObject) = 0;
	virtual std::vector<RCommandBuffer*> allocateCommandBuffers(RCoreObject* pCoreObject, UI32 bufferCount, RCommandBufferLevel level = RCommandBufferLevel::COMMAND_BUFFEER_LEVEL_PRIMARY) { return std::vector<RCommandBuffer*>(); }
	virtual void resetBuffers(RCoreObject* pCoreObject, std::vector<RCommandBuffer*> commandBuffers) = 0;
	virtual void terminateBuffers(RCoreObject* pCoreObject, std::vector<RCommandBuffer*> commandBuffers) = 0;
	virtual void terminate(RCoreObject* pCoreObject, std::vector<RCommandBuffer*> commandBuffers) = 0;

	virtual void beginSecondaryCommandBuffers() {}
	/* Swap the currently active command buffer with a specified buffer. */
	virtual void swapCommandBuffers(RCommandBuffer* pMainCommandBuffer, RCommandBuffer* pReturnCommandBuffer = nullptr) {}
};

#endif // !_DYNAMIK_RENDERER_COMMAND_BUFFER_MANAGER_H
