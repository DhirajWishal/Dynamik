// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENEDERER_DRAW_CALL_MANAGER_H
#define _DYNAMIK_RENEDERER_DRAW_CALL_MANAGER_H

#include "RCommandBuffer.h"
#include "Core/Objects/Resources/VertexBuffer.h"

/* Hash function for the Dynamik Vertex Layout structure */
namespace std
{
	using namespace Dynamik;

	template<>
	struct hash<DMKVertexLayout> {
		size_t operator()(DMKVertexLayout const& other) const {
			size_t sum = 0;

			for (auto attribute : other.attributes)
				sum += (size_t)FormatSize(attribute.dataFormat) ^ (size_t)attribute.dataCount ^ (size_t)attribute.attributeType;

			return (size_t)(1ULL << (sum % 64ULL));
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
	public:

		struct DMK_API DrawEntry {
			DrawEntry() {}
			DrawEntry(
				UI64 fVertex, DMKVertexBuffer vertexBuffer,
				UI64 firstIndex, UI64 indexCount,
				RPipelineObject* pPipelineObj) :
				firstVertex(fVertex), vertexBuffer(vertexBuffer),
				firstIndex(firstIndex), indexCount(indexCount),
				pPipelineObject(pPipelineObj) {}
			~DrawEntry() {}

			UI64 firstVertex = 0;
			UI64 firstIndex = 0;
			UI64 indexCount = 0;

			RPipelineObject* pPipelineObject = nullptr;
			DMKVertexBuffer vertexBuffer;
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

		struct DMK_API EmptyDraw {
			EmptyDraw() {}
			EmptyDraw(RPipelineObject* pPipeline) : pPipeline(pPipeline) {}
			~EmptyDraw() {}

			RPipelineObject* pPipeline = nullptr;
		};

		struct DMK_API DebugDraw {
			DMKVertexBuffer rawVertexBuffer;
			ARRAY<UI32>* pRawIndexBuffer;
			RPipelineObject* pPipeline = nullptr;
			RBuffer* pVertexBuffer = nullptr;
			UI64 vertexCount = 0;
			RBuffer* pIndexBuffer = nullptr;
			UI64 indexCount = 0;
		};

		struct DMK_API EnvironmentDraw {
			RPipelineObject* pPipeline = nullptr;
			RBuffer* pVertexBuffer = nullptr;
			UI64 vertexCount = 0;
			RBuffer* pIndexBuffer = nullptr;
			UI64 indexCount = 0;
		};

		RDrawCallManager() {}
		~RDrawCallManager() {}

		UI64 addDrawEntry(
			DMKVertexBuffer vertexBuffer,
			ARRAY<UI32>* indexBuffer,
			RPipelineObject* pPipelineObject);

		UI64 addEmptyEntry(RPipelineObject* pPipelineObject);

		void setEnvironment(RPipelineObject* pPipeline, RBuffer* pVertexBuffer, UI64 vertexCount, RBuffer* pIndexBuffer, UI64 indexCount);
		EnvironmentDraw& getEnvironmentData();

		UI64 addDebugEntry(
			DMKVertexBuffer vertexBuffer,
			ARRAY<UI32>* indexBuffer,
			RPipelineObject* pPipelineObject);

		void initializeBuffers(RCoreObject* pCoreObject);

		void setCommandBuffer(RCommandBuffer* pCommandBuffer);

		void beginCommand();
		void bindRenderTarget(RRenderTarget* pRenderTarget, RSwapChain* pSwapChain, UI32 frameIndex);
		void bindDrawCalls(RDrawCallType callType = RDrawCallType::DRAW_CALL_TYPE_INDEX);
		void unbindRenderTarget();
		void endCommand();

		void terminate(RCoreObject* pCoreObject);

		DebugDraw& getDebugEntry(I64 index);

		const B1 isInitialized() const;

	private:
		std::unordered_map<DMKVertexLayout, VertexBufferEntry> entryMap;
		ARRAY<VertexBufferContainer> vertexBuffers;
		ARRAY<IndexBufferEntry> indexBufferEntries;
		ARRAY<EmptyDraw> emptyDraws;
		ARRAY<DebugDraw> debugEntries;
		EnvironmentDraw myEnvironment;

		/*
		 Index Buffer
		 One index buffer would be enough because all the indexes are given as unsigned 32 bit integers.
		*/
		RBuffer* indexBuffer = nullptr;
		UI64 totalIndexCount = 0;

		RCommandBuffer* pCommandBuffer = nullptr;

		B1 bIsInitialized = false;
	};
}

#endif // !_DYNAMIK_RENEDERER_DRAW_CALL_MANAGER_H
