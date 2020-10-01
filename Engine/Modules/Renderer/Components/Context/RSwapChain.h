// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_SWAP_CHAIN_H
#define _DYNAMIK_RENDERER_SWAP_CHAIN_H

#include "../RCoreObject.h"
#include "Core/Math/MathTypes.h"
#include "../Primitives/RImage.h"

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

	virtual void initialize(RCoreObject* pCoreObject, DMKViewport viewport, RSwapChainPresentMode ePresentMode) = 0;
	virtual void terminate(RCoreObject* pCoreObject) = 0;

	std::vector<RImage*> images;
	DMKExtent2D extent = DMKExtent2D(0.0f);
	UI32 bufferCount = 0;
	DMKFormat format = DMKFormat::DMK_FORMAT_UNDEFINED;
	DMKViewport viewPort;
};

#endif // !_DYNAMIK_RENDERER_SWAP_CHAIN_H
