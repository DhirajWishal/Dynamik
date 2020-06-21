// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_RENDER_TARGET_H
#define _DYNAMIK_RENDERER_RENDER_TARGET_H

/*
 Author:	Dhiraj Wishal
 Date:		14/06/2020
*/
#include "Context/RFrameBuffer.h"
#include "RCommandBuffer.h"

namespace Dynamik
{
	/*
	 Renderer Render Target
	*/
	class DMK_API RRenderTarget {
	public:
		RRenderTarget() {}
		virtual ~RRenderTarget() {}

		virtual void setComponents(POINTER<RFrameBuffer> frameBuffer, POINTER<RRenderPass> renderPass, POINTER<RSwapChain> swapChain) { pFrameBuffer = frameBuffer, pRenderPass = renderPass, pSwapChain = swapChain; }
		virtual void submit(POINTER<RCommandBuffer> pCommandBuffer) {}

		POINTER<RFrameBuffer> pFrameBuffer;
		POINTER<RRenderPass> pRenderPass;
	};

	/*
	 Render Target Texture Object
	*/
	class DMK_API RRenderTargetTexture : public RRenderTarget {
	public:
		RRenderTargetTexture() {}
		virtual ~RRenderTargetTexture() {}
	};
}

#endif // !_DYNAMIK_RENDERER_RENDER_TARGET_H
