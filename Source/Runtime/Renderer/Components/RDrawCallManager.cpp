// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "RDrawCallManager.h"

#include "../Backend/Vulkan/Primitives/VulkanBuffer.h"

namespace Dynamik
{
	void RDrawCallManager::addDrawEntry(UI64 vertexCount, VPTR vertexBuffer, UI64 indexCount, VPTR indexBuffer, RPipelineObject* pPipelineObject, DMKVertexLayout vertexLayout)
	{
		entryMap[vertexLayout].drawEntries.pushBack(
			DrawEntry(entryMap[vertexLayout].vertexCount, vertexCount, vertexBuffer, totalIndexCount, indexCount, pPipelineObject));
		entryMap[vertexLayout].vertexCount += vertexCount;

		IndexBufferEntry _entry;
		_entry.firstIndex = totalIndexCount;
		_entry.indexCount = indexCount;
		_entry.pIndexBuffer = indexBuffer;
		indexBufferEntries.pushBack(_entry);

		totalIndexCount += indexCount;
	}

	void RDrawCallManager::initializeBuffers(RCoreObject* pCoreObject)
	{
		/* Initialize Vertex Buffers */
		for (auto entry : entryMap)
		{
			UI64 bufferSize = entry.first.getVertexSize() * entry.second.vertexCount;

			VertexBufferContainer _container;
			_container.entries = entry.second.drawEntries;

			RBuffer* staggingBuffer = StaticAllocator<Backend::VulkanBuffer>::rawAllocate();
			staggingBuffer->initialize(pCoreObject, RBufferType::BUFFER_TYPE_STAGGING, bufferSize);
			POINTER<BYTE> vertexPointer = staggingBuffer->getData(pCoreObject, bufferSize, 0);

			for (auto drawEntry : entry.second.drawEntries)
			{
				DMKMemoryFunctions::moveData(vertexPointer.get(), drawEntry.pVertexBuffer, drawEntry.vertexCount * entry.first.getVertexSize());
				vertexPointer += drawEntry.vertexCount * entry.first.getVertexSize();
			}
			staggingBuffer->unmapMemory(pCoreObject);

			_container.vertexBuffer = StaticAllocator<Backend::VulkanBuffer>::rawAllocate();
			_container.vertexBuffer->initialize(pCoreObject, RBufferType::BUFFER_TYPE_VERTEX, bufferSize);
			_container.vertexBuffer->copy(pCoreObject, staggingBuffer, bufferSize, 0, 0);

			vertexBuffers.pushBack(_container);

			staggingBuffer->terminate(pCoreObject);
			//StaticAllocator<RBuffer>::rawDeallocate(staggingBuffer, 0);
		}

		entryMap.clear();

		/* Initialize Index Buffer */
		UI64 bufferSize = totalIndexCount * sizeof(UI32);

		RBuffer* staggingBuffer = StaticAllocator<Backend::VulkanBuffer>::rawAllocate();
		staggingBuffer->initialize(pCoreObject, RBufferType::BUFFER_TYPE_STAGGING, bufferSize);
		POINTER<BYTE> indexPointer = staggingBuffer->getData(pCoreObject, bufferSize, 0);

		for (auto entry : indexBufferEntries)
		{
			DMKMemoryFunctions::moveData(indexPointer.get(), entry.pIndexBuffer, entry.indexCount * sizeof(UI32));
			indexPointer += entry.indexCount * sizeof(UI32);
		}
		staggingBuffer->unmapMemory(pCoreObject);

		indexBuffer = StaticAllocator<Backend::VulkanBuffer>::rawAllocate();
		indexBuffer->initialize(pCoreObject, RBufferType::BUFFER_TYPE_INDEX, totalIndexCount * sizeof(UI32));
		indexBuffer->copy(pCoreObject, staggingBuffer, bufferSize, 0, 0);

		staggingBuffer->terminate(pCoreObject);
		//StaticAllocator<RBuffer>::rawDeallocate(staggingBuffer, 0);

		indexBufferEntries.clear();

#ifdef DMK_DEBUG
		DMK_INFO("Number of individual vertex buffers: " + std::to_string(vertexBuffers.size()));

#endif // DMK_DEBUG
	}

	void RDrawCallManager::setCommandBuffer(RCommandBuffer* pCommandBuffer)
	{
		this->pCommandBuffer = pCommandBuffer;
	}

	void RDrawCallManager::beginCommand()
	{
		pCommandBuffer->begin();
	}

	void RDrawCallManager::bindRenderTarget(RRenderTarget* pRenderTarget, RSwapChain* pSwapChain, UI32 frameIndex)
	{
		pCommandBuffer->bindRenderTarget(pRenderTarget, pSwapChain, frameIndex);
	}

	void RDrawCallManager::bindDrawCalls(RDrawCallType callType)
	{
		pCommandBuffer->bindIndexBuffer(indexBuffer);

		for (auto container : vertexBuffers)
		{
			pCommandBuffer->bindVertexBuffer(container.vertexBuffer, 0);

			for (auto entry : container.entries)
			{
				pCommandBuffer->bindGraphicsPipeline(entry.pPipelineObject);

				if (callType == RDrawCallType::DRAW_CALL_TYPE_INDEX)
					pCommandBuffer->drawIndexed(entry.firstIndex, entry.firstVertex, entry.indexCount, 1);
				else if (callType == RDrawCallType::DRAW_CALL_TYPE_VERTEX)
					pCommandBuffer->drawVertexes(entry.firstVertex, entry.vertexCount, 1);
			}
		}
	}

	void RDrawCallManager::unbindRenderTarget()
	{
		pCommandBuffer->unbindRenderTarget();
	}

	void RDrawCallManager::endCommand()
	{
		pCommandBuffer->end();
	}

	void RDrawCallManager::terminate(RCoreObject* pCoreObject)
	{
		for (auto buffer : vertexBuffers)
		{
			buffer.vertexBuffer->terminate(pCoreObject);
			StaticAllocator<RBuffer>::rawDeallocate(buffer.vertexBuffer, 0);
		}

		indexBuffer->terminate(pCoreObject);
		StaticAllocator<RBuffer>::rawDeallocate(indexBuffer, 0);
	}
}
