// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENEDERER_DRAW_CALL_MANAGER_H
#define _DYNAMIK_RENEDERER_DRAW_CALL_MANAGER_H

#include "RCommandBuffer.h"
#include "Core/Objects/Resources/IndexBuffer.h"
#include "Core/Objects/Resources/VertexBuffer.h"

#include "REntity.h"
#include "RCommandBufferManager.h"

/* Hash function for the Dynamik Vertex Layout structure */
namespace std
{
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
	struct DMK_API RSecondaryCommandBinding {
		RSecondaryCommandBinding(REntity* pEntity = nullptr) : pRenderEntity(pEntity) {}

		REntity* pRenderEntity = nullptr;
		float runTime = 0.0f;
	};

public:
	RDrawCallManager() : isCommandBuffersInitialized(false) { }
	~RDrawCallManager() {}

	void terminateAll(RCoreObject* pCoreObject);

	void addRenderEntity(REntity* pRenderEntity);
	void removeRenderEntity(REntity* pRenderEntity);

	/*
	 Initialize the primary command buffers.
	*/
	void initializeCommandBuffers(RCoreObject* pCoreObject, RRenderTarget* pRenderTarget, RSwapChain* pSwapChain, DMKRenderingAPI API);

	void reCreateBuffers(RCoreObject* pCoreObject, RRenderTarget* pRenderTarget, RSwapChain* pSwapChain, DMKRenderingAPI API);

	/*
	 This method updates the secondary command buffers and increments the run time of secondary commands.
	*/
	void update(RRenderTarget* pRenderTarget, RSwapChain* pSwapChain, const UI64 frameIndex);

	RCommandBuffer* getPrimaryCommandBuffer(UI64 frameIndex);
	RCommandBuffer* getSecondaryCommandBuffer(UI64 frameIndex);

	void bindSecondaryCommands(RCommandBuffer* pCommandBuffer);

	void resetPrimaryCommandBuffers(RCoreObject* pCoreObject);
	void resetSecondaryCommandBuffers(RCoreObject* pCoreObject);

private:
	/*
	 Secondary command bindings.
	 These bindings are actively used in the secondary command buffers.
	*/
	std::vector<RSecondaryCommandBinding> secondaryCommandBindings;

	/* The local command buffer manager pointer. */
	RCommandBufferManager* pCommandBufferManager = nullptr;

	/* Pointer to command buffers. */
	std::vector<RCommandBuffer*> pCommandBuffers;

	/* Secondary command buffers */
	std::vector<RCommandBuffer*> pSecondaryCommandBuffers;

	UI8 isCommandBuffersInitialized : 1;
};

#endif // !_DYNAMIK_RENEDERER_DRAW_CALL_MANAGER_H
