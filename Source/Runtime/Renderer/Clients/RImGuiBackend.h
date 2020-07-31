// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_IM_GUI_CLIENT_H
#define _DYNAMIK_RENDERER_IM_GUI_CLIENT_H

#include "ImGuiBackendHandle.h"
#include "../Components/RCoreObject.h"
#include "../Components/RPipelineObject.h"
#include "../Components/Primitives/RTexture.h"

namespace Dynamik
{
	/*
	 Renderer Im Gui Backend
	 This object is the main Im Gui backend for the Dynamik Engine.
	 Each RBL will contain an object which allows Im Gui to render its components through the active RBL.
	*/
	class DMK_API RImGuiBackend : public DMKImGuiBackendHandle {
	public:
		RImGuiBackend() = default;
		virtual ~RImGuiBackend() = default;

		virtual void setCoreObject(RCoreObject* pCoreObject) { this->pCoreObject = pCoreObject; }
		virtual void setRenderTarget(RRenderTarget* pRenderTarget) { this->pRenderTarget = pRenderTarget; }
		virtual void bindCommands(RCommandBuffer* pCommandBuffer) = 0;
		virtual void reCreatePipeline(RCoreObject* pCoreObject, RRenderTarget* pRenderTarget, DMKViewport viewport) = 0;

	protected:
		RCoreObject* pCoreObject = nullptr;
		RRenderTarget* pRenderTarget = nullptr;

		RPipelineObject* pPipelineObject = nullptr;
		RTexture* pFontTexture = nullptr;

		RBuffer* pVertexBuffer = nullptr;
		UI64 vertexCount = 0;

		RBuffer* pIndexBuffer = nullptr;
		UI64 indexCount = 0;

		struct DMK_API RConstantBlock {
			Vector2F scale = { 0.0f, 0.0f };
			Vector2F translate = { 0.0f, 0.0f };
		};
	};
}

#endif // !_DYNAMIK_IM_GUI_CLIENT_H
