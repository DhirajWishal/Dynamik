// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_UTILITIES_H
#define _DYNAMIK_RENDERER_UTILITIES_H

#include "Components/RPipelineObject.h"
#include "Components/ContextTypeDefs.h"

/*
 Renderer Utilities
*/
class DMK_API RUtilities {
public:
	static RPipelineObject* allocatePipeline(DMKRenderingAPI API);
	static RBuffer* allocateBuffer(DMKRenderingAPI API);
	static ARRAY<RColorBlendState> createBasicColorBlendStates();
	static ARRAY<RSubpassAttachment> createSubPasses(DMKRenderContextType contextType, RCoreObject* pCoreObject, RSwapChain* pSwapChain);
	static ARRAY<RSubPasses> getSubpassNames(DMKRenderContextType contextType);

	static ARRAY<ARRAY<RFrameBufferAttachment*>> getFrameBufferAttachments(DMKRenderingAPI API, ARRAY<RSubpassAttachment> subPassAttachments, RCoreObject* pCoreObject, RSwapChain* pSwapChain, DMKExtent2D imageExtent);

	static RTexture* createBRDFTable(RCoreObject* pCoreObject, F32 dimentions);
};

#endif // !_DYNAMIK_RENDERER_UTILITIES_H
