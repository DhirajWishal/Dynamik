// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_RENDER_TARGET_H
#define _DYNAMIK_RENDERER_RENDER_TARGET_H

/*
 Author:	Dhiraj Wishal
 Date:		14/06/2020
*/
#include "RFrameBuffer.h"

namespace Dynamik
{
	/*
	 Renderer Render Target
	*/
	class DMK_API RRenderTarget {
	public:
		RRenderTarget() {}
		virtual ~RRenderTarget() {}
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
