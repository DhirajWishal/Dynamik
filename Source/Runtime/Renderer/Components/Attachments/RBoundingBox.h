// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_BOUNDING_BOX_ATTACHMENT_H
#define _DYNAMIK_RENDERER_BOUNDING_BOX_ATTACHMENT_H

#include "Core/Objects/Resources/VertexBuffer.h"
#include "../RPipelineObject.h"
#include "../Primitives/RBuffer.h"

/*
 Renderer Bounding Box
*/
class DMK_API RBoundingBox {
public:
	RBoundingBox() : renderingAPI(DMKRenderingAPI::DMK_RENDERING_API_VULKAN) {}
	RBoundingBox(DMKRenderingAPI renderingAPI) : renderingAPI(renderingAPI) {}
	virtual ~RBoundingBox() {}

	virtual void initialize(RCoreObject* pCoreObject, RRenderTarget* pRenderTarget, RSwapChain* pSwapChain, RBuffer* pCameraUniform);
	virtual void terminate(RCoreObject* pCoreObject);

	ARRAY<DMKShaderModule> shaders;
	RPipelineObject* pPipeline = nullptr;
	RPipelineResource* pPipelineResource = nullptr;
	RBuffer* pUniformBuffer = nullptr;

protected:
	DMKRenderingAPI renderingAPI = DMKRenderingAPI::DMK_RENDERING_API_VULKAN;
};

#endif // !_DYNAMIK_RENDERER_BOUNDING_BOX_ATTACHMENT_H
