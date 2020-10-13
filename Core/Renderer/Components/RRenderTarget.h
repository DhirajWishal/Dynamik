// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_RENDER_TARGET_H
#define _DYNAMIK_RENDERER_RENDER_TARGET_H

#include "Context/RFrameBuffer.h"
#include "RCommandBuffer.h"

class DMK_API RCommandBuffer;
class DMK_API RRenderPass;
class DMK_API RFrameBuffer;

/*
 Renderer Render Target
*/
class DMK_API RRenderTarget {
public:
	RRenderTarget() : pFrameBuffer(nullptr), pRenderPass(nullptr) {}
	virtual ~RRenderTarget() {}

	void setComponents(RFrameBuffer* frameBuffer, RRenderPass* renderPass) { pFrameBuffer = frameBuffer, pRenderPass = renderPass; }
	virtual void submit(RCommandBuffer* pCommandBuffer) {}

	RFrameBuffer* pFrameBuffer = nullptr;
	RRenderPass* pRenderPass = nullptr;
};

#endif // !_DYNAMIK_RENDERER_RENDER_TARGET_H
