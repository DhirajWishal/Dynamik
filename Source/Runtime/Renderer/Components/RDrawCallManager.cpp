// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "RDrawCallManager.h"

#include "VulkanRBL/Primitives/VulkanBuffer.h"
#include "../RUtilities.h"

namespace Dynamik
{
	UI64 RDrawCallManager::addDrawEntry(DMKVertexBuffer vertexBuffer, ARRAY<UI32>* indexBuffer, RPipelineObject* pPipelineObject)
	{
		entryMap[vertexBuffer.layout].drawEntries.pushBack(
			DrawEntry(entryMap[vertexBuffer.layout].vertexCount, vertexBuffer, totalIndexCount, indexBuffer->size(), pPipelineObject));
		entryMap[vertexBuffer.layout].vertexCount += vertexBuffer.size();

		IndexBufferEntry _entry;
		_entry.firstIndex = totalIndexCount;
		_entry.pIndexBuffer = indexBuffer;
		indexBufferEntries.pushBack(_entry);

		totalIndexCount += indexBuffer->size();

		return entryMap[vertexBuffer.layout].drawEntries.size() - 1;
	}

	UI64 RDrawCallManager::addEmptyEntry(RPipelineObject* pPipelineObject)
	{
		emptyDraws.pushBack(EmptyDraw(pPipelineObject));

		return emptyDraws.size() - 1;
	}

	void RDrawCallManager::setEnvironment(RPipelineObject* pPipeline, RBuffer* pVertexBuffer, UI64 vertexCount, RBuffer* pIndexBuffer, UI64 indexCount)
	{
		myEnvironment.pPipeline = pPipeline;
		myEnvironment.pVertexBuffer = pVertexBuffer;
		myEnvironment.vertexCount = vertexCount;
		myEnvironment.pIndexBuffer = pIndexBuffer;
		myEnvironment.indexCount = indexCount;
	}

	RDrawCallManager::EnvironmentDraw& RDrawCallManager::getEnvironmentData()
	{
		return myEnvironment;
	}

	UI64 RDrawCallManager::addDebugEntry(DMKVertexBuffer vertexBuffer, ARRAY<UI32>* indexBuffer, RPipelineObject* pPipelineObject)
	{
		DebugDraw entry;
		entry.indexCount = indexBuffer->size();
		entry.rawVertexBuffer = vertexBuffer;
		entry.vertexCount = vertexBuffer.size();
		entry.pRawIndexBuffer = indexBuffer;
		entry.pPipeline = pPipelineObject;
		debugEntries.pushBack(entry);

		return debugEntries.size() - 1;
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
				DMKMemoryFunctions::moveData(vertexPointer.get(), drawEntry.vertexBuffer.data(), drawEntry.vertexBuffer.byteSize());
				vertexPointer += drawEntry.vertexBuffer.byteSize();

				drawEntry.vertexBuffer.clear();
			}
			staggingBuffer->unmapMemory(pCoreObject);

			_container.vertexBuffer = StaticAllocator<Backend::VulkanBuffer>::rawAllocate();
			_container.vertexBuffer->initialize(pCoreObject, RBufferType::BUFFER_TYPE_VERTEX, bufferSize, RResourceMemoryType(RESOURCE_MEMORY_TYPE_DEVICE_LOCAL | RESOURCE_MEMORY_TYPE_HOST_COHERENT));
			_container.vertexBuffer->copy(pCoreObject, staggingBuffer, bufferSize, 0, 0);

			vertexBuffers.pushBack(_container);

			staggingBuffer->terminate(pCoreObject);
			StaticAllocator<RBuffer>::rawDeallocate(staggingBuffer, 0);
		}

		entryMap.clear();

		/* Initialize Index Buffer */
		UI64 bufferSize = totalIndexCount * sizeof(UI32);

		/* Check if we have data to allocate an index buffer */
		if (bufferSize == 0)
			return;

		RBuffer* staggingBuffer = StaticAllocator<Backend::VulkanBuffer>::rawAllocate();
		staggingBuffer->initialize(pCoreObject, RBufferType::BUFFER_TYPE_STAGGING, bufferSize);
		POINTER<BYTE> indexPointer = staggingBuffer->getData(pCoreObject, bufferSize, 0);

		for (auto entry : indexBufferEntries)
		{
			DMKMemoryFunctions::moveData(indexPointer.get(), entry.pIndexBuffer->data(), entry.pIndexBuffer->size() * entry.pIndexBuffer->typeSize());
			indexPointer += entry.pIndexBuffer->size() * entry.pIndexBuffer->typeSize();
			entry.pIndexBuffer->clear();
		}
		staggingBuffer->unmapMemory(pCoreObject);

		indexBuffer = StaticAllocator<Backend::VulkanBuffer>::rawAllocate();
		indexBuffer->initialize(pCoreObject, RBufferType::BUFFER_TYPE_INDEX, bufferSize, RResourceMemoryType(RESOURCE_MEMORY_TYPE_DEVICE_LOCAL | RESOURCE_MEMORY_TYPE_HOST_COHERENT));
		indexBuffer->copy(pCoreObject, staggingBuffer, bufferSize, 0, 0);

		staggingBuffer->terminate(pCoreObject);
		StaticAllocator<RBuffer>::rawDeallocate(staggingBuffer, 0);

		indexBufferEntries.clear();

		/* Initialize Debug Entries */
		for (UI64 index = 0; index < debugEntries.size(); index++)
		{
			auto& entry = debugEntries[index];

			/* Initialize Vertex Buffer */
			{
				RBuffer* pStaggingBuffer = StaticAllocator<Backend::VulkanBuffer>::rawAllocate();
				pStaggingBuffer->initialize(pCoreObject, RBufferType::BUFFER_TYPE_STAGGING, entry.rawVertexBuffer.byteSize());
				pStaggingBuffer->setData(pCoreObject, entry.rawVertexBuffer.byteSize(), 0, entry.rawVertexBuffer.data());

				entry.pVertexBuffer = StaticAllocator<Backend::VulkanBuffer>::rawAllocate();
				entry.pVertexBuffer->initialize(pCoreObject, RBufferType::BUFFER_TYPE_VERTEX, entry.rawVertexBuffer.byteSize());
				entry.pVertexBuffer->copy(pCoreObject, pStaggingBuffer, entry.rawVertexBuffer.byteSize());
				entry.rawVertexBuffer.clear();

				pStaggingBuffer->terminate(pCoreObject);
				StaticAllocator<RBuffer>::rawDeallocate(pStaggingBuffer, 0);
			}

			/* Initialize Index Buffer */
			{
				RBuffer* pStaggingBuffer = StaticAllocator<Backend::VulkanBuffer>::rawAllocate();
				pStaggingBuffer->initialize(pCoreObject, RBufferType::BUFFER_TYPE_STAGGING, entry.pRawIndexBuffer->size() * entry.pRawIndexBuffer->typeSize());
				pStaggingBuffer->setData(pCoreObject, entry.pRawIndexBuffer->size() * entry.pRawIndexBuffer->typeSize(), 0, entry.pRawIndexBuffer->data());

				entry.pIndexBuffer = StaticAllocator<Backend::VulkanBuffer>::rawAllocate();
				entry.pIndexBuffer->initialize(pCoreObject, RBufferType::BUFFER_TYPE_INDEX, entry.pRawIndexBuffer->size() * entry.pRawIndexBuffer->typeSize());
				entry.pIndexBuffer->copy(pCoreObject, pStaggingBuffer, entry.pRawIndexBuffer->size() * entry.pRawIndexBuffer->typeSize());
				entry.pRawIndexBuffer->clear();

				pStaggingBuffer->terminate(pCoreObject);
				StaticAllocator<RBuffer>::rawDeallocate(pStaggingBuffer, 0);
			}
		}

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
		/* Bind Environment */
		{
			pCommandBuffer->bindVertexBuffer(myEnvironment.pVertexBuffer, 0);
			pCommandBuffer->bindIndexBuffer(myEnvironment.pIndexBuffer);
			pCommandBuffer->bindGraphicsPipeline(myEnvironment.pPipeline);
			if (callType == RDrawCallType::DRAW_CALL_TYPE_INDEX)
				pCommandBuffer->drawIndexed(0, 0, myEnvironment.indexCount, 1);
			else if (callType == RDrawCallType::DRAW_CALL_TYPE_VERTEX)
				pCommandBuffer->drawVertexes(0, myEnvironment.vertexCount, 1);
		}

		if (indexBuffer)
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
					pCommandBuffer->drawVertexes(entry.firstVertex, entry.vertexBuffer.size(), 1);
			}
		}

		/* Bind empty draws */
		for (auto draw : emptyDraws)
		{
			pCommandBuffer->bindGraphicsPipeline(draw.pPipeline);
			pCommandBuffer->drawVertexes(0, 3, 1);
		}

		/* Bind debug entries */
		for (auto entry : debugEntries)
		{
			pCommandBuffer->bindVertexBuffer(entry.pVertexBuffer, 0);
			pCommandBuffer->bindIndexBuffer(entry.pIndexBuffer);
			pCommandBuffer->bindGraphicsPipeline(entry.pPipeline);
			pCommandBuffer->drawIndexed(0, 0, entry.indexCount, 1);
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
		/* Terminate Environment */
		myEnvironment.pVertexBuffer->terminate(pCoreObject);
		StaticAllocator<RBuffer>::rawDeallocate(myEnvironment.pVertexBuffer, 0);
		myEnvironment.pIndexBuffer->terminate(pCoreObject);
		StaticAllocator<RBuffer>::rawDeallocate(myEnvironment.pIndexBuffer, 0);

		for (auto buffer : vertexBuffers)
		{
			buffer.vertexBuffer->terminate(pCoreObject);
			StaticAllocator<RBuffer>::rawDeallocate(buffer.vertexBuffer, 0);
		}

		indexBuffer->terminate(pCoreObject);
		StaticAllocator<RBuffer>::rawDeallocate(indexBuffer, 0);

		/* Terminate Debug Entries */
		for (auto entry : debugEntries)
		{
			entry.pVertexBuffer->terminate(pCoreObject);
			StaticAllocator<RBuffer>::rawDeallocate(entry.pVertexBuffer, 0);

			entry.pIndexBuffer->terminate(pCoreObject);
			StaticAllocator<RBuffer>::rawDeallocate(entry.pIndexBuffer, 0);
		}
	}

	RDrawCallManager::DebugDraw& RDrawCallManager::getDebugEntry(I64 index)
	{
		return debugEntries[index];
	}
}
