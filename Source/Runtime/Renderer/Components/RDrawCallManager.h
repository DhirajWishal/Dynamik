// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENEDERER_DRAW_CALL_MANAGER_H
#define _DYNAMIK_RENEDERER_DRAW_CALL_MANAGER_H

#include "RCommandBuffer.h"

namespace std 
{
	using namespace Dynamik;

	template<>
	struct hash<DMKVertexLayout> {
		size_t operator()(DMKVertexLayout const& other) const {
			size_t sum = 0;

			for (auto attribute : other.attributes)
				sum += (size_t)attribute.dataType ^ (size_t)attribute.dataCount ^ (size_t)attribute.attributeType;

			return BIT_SHIFT((sum % (size_t)64));
		}
	};
}

namespace Dynamik
{
	/* Renderer Draw Call Type */
	enum class DMK_API RDrawCallType {
		DRAW_CALL_TYPE_INDEX,
		DRAW_CALL_TYPE_VERTEX,

		DRAW_CALL_TYPE_INDEX_INDIRECT,
	};

	/*
	 Renderer Draw Call Manager
	 This object manages all the draw instructions.
	*/
	class DMK_API RDrawCallManager {
		struct DMK_API DrawEntry {
			DrawEntry() {}
			DrawEntry(
				UI64 fVertex, UI64 vCount, VPTR vBuffer,
				UI64 firstIndex, UI64 indexCount,
				RPipelineObject* pPipelineObj) :
				firstVertex(fVertex), vertexCount(vCount), pVertexBuffer(vBuffer),
				firstIndex(firstIndex), indexCount(indexCount),
				pPipelineObject(pPipelineObj) {}
			~DrawEntry() {}

			UI64 firstVertex = 0;
			UI64 vertexCount = 0;
			UI64 firstIndex = 0;
			UI64 indexCount = 0;

			RPipelineObject* pPipelineObject = nullptr;
			VPTR pVertexBuffer = nullptr;
		};

		struct DMK_API IndexBufferEntry {
			UI64 firstIndex = 0;
			ARRAY<UI32>* pIndexBuffer = nullptr;
		};

		struct DMK_API VertexBufferEntry {
			ARRAY<DrawEntry> drawEntries;
			UI64 vertexCount = 0;
		};

		struct DMK_API VertexBufferContainer {
			ARRAY<DrawEntry> entries;
			RBuffer* vertexBuffer = nullptr;
		};

	public:
		RDrawCallManager() {}
		~RDrawCallManager() {}

		void addDrawEntry(
			UI64 vertexCount, VPTR vertexBuffer, 
			ARRAY<UI32>* indexBuffer,
			RPipelineObject* pPipelineObject, DMKVertexLayout vertexLayout);

		void initializeBuffers(RCoreObject* pCoreObject);

		void setCommandBuffer(RCommandBuffer* pCommandBuffer);

		void beginCommand();
		void bindRenderTarget(RRenderTarget* pRenderTarget, RSwapChain* pSwapChain, UI32 frameIndex);
		void bindDrawCalls(RDrawCallType callType = RDrawCallType::DRAW_CALL_TYPE_INDEX);
		void unbindRenderTarget();
		void endCommand();

		void terminate(RCoreObject* pCoreObject);

	private:
		std::unordered_map<DMKVertexLayout, VertexBufferEntry> entryMap;
		ARRAY<VertexBufferContainer> vertexBuffers;
		ARRAY<IndexBufferEntry> indexBufferEntries;

		/*
		 Index Buffer
		 One index buffer would be enough because all the indexes are given as unsigned 32 bit integers.
		*/
		RBuffer* indexBuffer = nullptr;
		UI64 totalIndexCount = 0;

		RCommandBuffer* pCommandBuffer = nullptr;
	};
}

#endif // !_DYNAMIK_RENEDERER_DRAW_CALL_MANAGER_H
