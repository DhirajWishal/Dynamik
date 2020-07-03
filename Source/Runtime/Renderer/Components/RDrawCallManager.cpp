// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "RDrawCallManager.h"

namespace Dynamik
{
	void RDrawCallManager::addDrawEntry(UI64 firstVertex, UI64 vertexCount, UI64 firstIndex, UI64 indexCount, RPipelineObject* pPipelineObject, DMKVertexLayout vertexLayout)
	{
		entryMap[vertexLayout].pushBack(
			DrawEntry(firstVertex, vertexCount, firstIndex, indexCount, pPipelineObject));
	}
	
	void RDrawCallManager::setCommandBuffer(const RCommandBuffer* pCommandBuffer)
	{
	}

	void RDrawCallManager::beginCommand()
	{
	}

	void RDrawCallManager::bindTarget(const RRenderTarget* pTarget, const RSwapChain* pSwapChain)
	{
	}

	void RDrawCallManager::bindDrawCalls()
	{
	}

	void RDrawCallManager::unbindTarget()
	{
	}

	void RDrawCallManager::endCommand()
	{
	}
}
