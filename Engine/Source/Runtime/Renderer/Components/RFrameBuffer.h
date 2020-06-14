// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_FRAME_BUFFER_H
#define _DYNAMIK_RENDERER_FRAME_BUFFER_H

/*
 Author:	Dhiraj Wishal
 Date:		14/06/2020
*/
#include "RRenderPass.h"

namespace Dynamik
{
	/*
	 Renderer Frame Buffer
	*/
	class DMK_API RFrameBuffer {
	public:
		RFrameBuffer() {}
		virtual ~RFrameBuffer() {}

		virtual void initialize(POINTER<RCoreObject> pCoreObject, POINTER<RRenderPass> pRenderPass) = 0;
		virtual void terminate(POINTER<RCoreObject> pCoreObject) = 0;
	};
}

#endif // !_DYNAMIK_RENDERER_FRAME_BUFFER_H
