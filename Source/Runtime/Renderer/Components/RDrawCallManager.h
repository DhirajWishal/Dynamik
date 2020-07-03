// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENEDERER_DRAW_CALL_MANAGER_H
#define _DYNAMIK_RENEDERER_DRAW_CALL_MANAGER_H

/*
 Author:	Dhiraj Wishal
 Date:		03/07/2020
*/
#include "RCommandBuffer.h"

namespace Dynamik
{
	/*
	 Renderer Draw Call Manager
	 This object manages all the draw instructions.
	*/
	class DMK_API RDrawCallManager {
		struct DMK_API DrawEntry {
			DrawEntry() {}
			DrawEntry(UI64 fVertex, UI64 vCount, UI64 fIndex, UI64 iCount, RPipelineObject* pPipelineObj) :
			firstVertex(fVertex), vertexCount(vCount), firstIndex(fIndex), indexCount(iCount), pPipelineObject(pPipelineObj) {}
			~DrawEntry() {}

			UI64 firstVertex = 0;
			UI64 vertexCount = 0;
			UI64 firstIndex = 0;
			UI64 indexCount = 0;

			RPipelineObject* pPipelineObject;
		};

	public:
		RDrawCallManager() {}
		~RDrawCallManager() {}

		void addDrawEntry(
			UI64 firstVertex, UI64 vertexCount, UI64 firstIndex, UI64 indexCount,
			RPipelineObject* pPipelineObject, DMKVertexLayout vertexLayout);

		void setCommandBuffer(const RCommandBuffer* pCommandBuffer);
		void beginCommand();
		void bindTarget(const RRenderTarget* pTarget, const RSwapChain* pSwapChain);
		void bindDrawCalls();
		void unbindTarget();
		void endCommand();

		RCommandBuffer* pCommandBuffer = nullptr;

	private:
		std::unordered_map<DMKVertexLayout, ARRAY<DrawEntry>> entryMap;
	};
}

#endif // !_DYNAMIK_RENEDERER_DRAW_CALL_MANAGER_H
