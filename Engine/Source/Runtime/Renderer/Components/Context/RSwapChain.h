// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_SWAP_CHAIN_H
#define _DYNAMIK_RENDERER_SWAP_CHAIN_H

/*
 Author:	Dhiraj Wishal
 Date:		14/06/2020
*/
#include "../RCoreObject.h"
#include "Core/Math/MathTypes.h"
#include "../Primitives/RImage.h"

namespace Dynamik
{
	class DMK_API RCoreObject;
	class DMK_API RImage;
	class DMK_API RImageView;

	/* Swapchain present mode */
	enum class DMK_API RSwapChainPresentMode {
		SWAPCHAIN_PRESENT_MODE_IMMEDIATE,
		SWAPCHAIN_PRESENT_MODE_FIFO,
		SWAPCHAIN_PRESENT_MODE_MAILBOX,
		SWAPCHAIN_PRESENT_MODE_SHADER_DEMAND_REFRESH,
		SWAPCHAIN_PRESENT_MODE_SHADER_CONTINUOUS_REFRESH,
	};

	/*
	 Renderer Swap Chain
	*/
	class DMK_API RSwapChain {
	public:
		RSwapChain() {}
		virtual ~RSwapChain() {}

		virtual void initialize(POINTER<RCoreObject> pCoreObject, DMKViewport viewport, RSwapChainPresentMode ePresentMode) = 0;
		virtual void terminate(POINTER<RCoreObject> pCoreObject) = 0;

		ARRAY<POINTER<RImage>> images;
		ARRAY<POINTER<RImageView>> imageViews;
		VEC2F extent = VEC2F(0.0f);
		UI32 bufferCount = 0;
		DMKFormat format = DMKFormat::DMK_FORMAT_UNDEFINED;
		DMKViewport viewPort;
	};
}

#endif // !_DYNAMIK_RENDERER_SWAP_CHAIN_H
