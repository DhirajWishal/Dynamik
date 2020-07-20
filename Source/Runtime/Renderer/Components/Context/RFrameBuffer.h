// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_FRAME_BUFFER_H
#define _DYNAMIK_RENDERER_FRAME_BUFFER_H

#include "RRenderPass.h"
#include "RFrameBufferAttachment.h"

namespace Dynamik
{
	class DMK_API RCoreObject;
	class DMK_API RSwapChain;
	class DMK_API RRenderPass;
	class DMK_API RFrameBufferAttachment;

	/*
	 Renderer Frame Buffer
	*/
	class DMK_API RFrameBuffer {
	public:
		RFrameBuffer() {}
		virtual ~RFrameBuffer() {}

		virtual void initialize(RCoreObject* pCoreObject, RRenderPass* pRenderPass, DMKExtent2D frameExtent, UI32 bufferCount, ARRAY<ARRAY<RFrameBufferAttachment*>> pAttachments) = 0;
		virtual void terminate(RCoreObject* pCoreObject) = 0;

		ARRAY<ARRAY<RFrameBufferAttachment*>> pAttachments;
		UI32 width = 0;
		UI32 height = 0;
	};
}

#endif // !_DYNAMIK_RENDERER_FRAME_BUFFER_H
