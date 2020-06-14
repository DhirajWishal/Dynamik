// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_RENDER_PASS_H
#define _DYNAMIK_RENDERER_RENDER_PASS_H

/*
 Author:	Dhiraj Wishal
 Date:		14/06/2020
*/
#include "RSwapChain.h"

namespace Dynamik
{
	/* Subpasses */
	enum class DMK_API RSubPasses {
		SUBPASSES_SWAPCHAIN,
		SUBPASSES_DEPTH,
		SUBPASSES_COLOR,
		SUBPASSES_OVERLAY,
	};

	/*
	 Renderer Render Pass
	*/
	class DMK_API RRenderPass {
	public:
		RRenderPass() {}
		virtual ~RRenderPass() {}

		virtual void initialize(POINTER<RCoreObject> pCoreObject, ARRAY<RSubPasses> aSubpasses, POINTER<RSwapChain> pSwapChain) = 0;
		virtual void terminate(POINTER<RCoreObject> pCoreObject) = 0;
	};
}

#endif // !_DYNAMIK_RENDERER_RENDER_PASS_H
