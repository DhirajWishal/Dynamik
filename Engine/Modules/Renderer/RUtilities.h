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
	static std::vector<RColorBlendState> createBasicColorBlendStates();
	static std::vector<RSubpassAttachment> createSubPasses(DMKRenderContextType contextType, RCoreObject* pCoreObject, RSwapChain* pSwapChain);
	static std::vector<RSubPasses> getSubpassNames(DMKRenderContextType contextType);

	static std::vector<std::vector<RFrameBufferAttachment*>> getFrameBufferAttachments(DMKRenderingAPI API, std::vector<RSubpassAttachment> subPassAttachments, RCoreObject* pCoreObject, RSwapChain* pSwapChain, DMKExtent2D imageExtent);

	static RTexture* createBRDFTable(RCoreObject* pCoreObject, float dimentions);
};

#endif // !_DYNAMIK_RENDERER_UTILITIES_H
