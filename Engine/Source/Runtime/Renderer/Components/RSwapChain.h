// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_SWAP_CHAIN_H
#define _DYNAMIK_RENDERER_SWAP_CHAIN_H

/*
 Author:	Dhiraj Wishal
 Date:		14/06/2020
*/
#include "RCoreObject.h"

namespace Dynamik
{
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

		virtual void initialize(POINTER<RCoreObject> pCoreObject, RSwapChainPresentMode ePresentMode) = 0;
		virtual void terminate(POINTER<RCoreObject> pCoreObject) = 0;
	};
}

#endif // !_DYNAMIK_RENDERER_SWAP_CHAIN_H
