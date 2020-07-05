// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_RENDER_PASS_H
#define _DYNAMIK_RENDERER_RENDER_PASS_H

#include "RSwapChain.h"

namespace Dynamik
{
	class DMK_API RCoreObject;
	class DMK_API RSwapChain;

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
		RRenderPass(ARRAY<RSubPasses> aSubPasses) : subPasses(aSubPasses) {}
		virtual ~RRenderPass() {}

		virtual void initialize(RCoreObject* pCoreObject, ARRAY<RSubPasses> aSubPasses, RSwapChain* pSwapChain) = 0;
		virtual void terminate(RCoreObject* pCoreObject) = 0;

		ARRAY<RSubPasses> subPasses;
	};
}

#endif // !_DYNAMIK_RENDERER_RENDER_PASS_H
