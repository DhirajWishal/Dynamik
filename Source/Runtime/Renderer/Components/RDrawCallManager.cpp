// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "RDrawCallManager.h"

#include "VulkanRBL/Primitives/VulkanBuffer.h"
#include "../RUtilities.h"

#include "VulkanRBL/Common/VulkanCommandBufferManager.h"

namespace Dynamik
{
	using namespace Backend;

	void RDrawCallManager::terminateAll(RCoreObject* pCoreObject)
	{
		pCommandBufferManager->terminateBuffers(pCoreObject, pCommandBuffers);
		pCommandBufferManager->terminateBuffers(pCoreObject, pSecondaryCommandBuffers);
		pCommandBufferManager->terminate(pCoreObject, {});

		StaticAllocator<RCommandBufferManager>::rawDeallocate(pCommandBufferManager, 0);
	}

	void RDrawCallManager::addRenderEntity(REntity* pRenderEntity)
	{
		secondaryCommandBindings.pushBack(pRenderEntity);
	}

	void RDrawCallManager::initializeCommandBuffers(RCoreObject* pCoreObject, RRenderTarget* pRenderTarget, RSwapChain* pSwapChain, DMKRenderingAPI API)
	{
		if (isCommandBuffersInitialized)
		{
			pCommandBufferManager->resetBuffers(pCoreObject, pCommandBuffers);
			pCommandBufferManager->resetBuffers(pCoreObject, pSecondaryCommandBuffers);
			return;
		}

		isCommandBuffersInitialized = true;

		reCreateBuffers(pCoreObject, pRenderTarget, pSwapChain, API);
	}

	void RDrawCallManager::reCreateBuffers(RCoreObject* pCoreObject, RRenderTarget* pRenderTarget, RSwapChain* pSwapChain, DMKRenderingAPI API)
	{
		if (!pCommandBufferManager)
		{
			switch (API)
			{
			case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
			{
				pCommandBufferManager = StaticAllocator<VulkanCommandBufferManager>::rawAllocate();
			}
			break;
			case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_DIRECTX:
				break;
			case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_OPENGL:
				break;
			}
		}

		pCommandBufferManager->initialize(pCoreObject);
		if (!pCommandBuffers.size())
			pCommandBuffers = pCommandBufferManager->allocateCommandBuffers(pCoreObject, pSwapChain->bufferCount, RCommandBufferLevel::COMMAND_BUFFEER_LEVEL_PRIMARY);
		else
			pCommandBufferManager->resetBuffers(pCoreObject, pCommandBuffers);

		if (!pSecondaryCommandBuffers.size())
			pSecondaryCommandBuffers = pCommandBufferManager->allocateCommandBuffers(pCoreObject, pSwapChain->bufferCount, RCommandBufferLevel::COMMAND_BUFFEER_LEVEL_SECONDARY);
		else
			pCommandBufferManager->resetBuffers(pCoreObject, pSecondaryCommandBuffers);

		/* Initialize the primary command buffer */
		{
			for (UI32 itr = 0; itr < pCommandBuffers.size(); itr++)
			{
				RCommandBuffer* pBuffer = pCommandBuffers[itr];
				pBuffer->begin();
				pBuffer->bindRenderTarget(pRenderTarget, pSwapChain, itr);
				pBuffer->unbindRenderTarget();
				pBuffer->end();
			}
		}
	}

	void RDrawCallManager::update(RRenderTarget* pRenderTarget, RSwapChain* pSwapChain, const UI64 frameIndex)
	{
		RCommandBuffer* pParentCommandBuffer = getPrimaryCommandBuffer(frameIndex);
		RCommandBuffer* pSecondaryCommandBuffer = getSecondaryCommandBuffer(frameIndex);

		/* Begin the parent command buffer. */
		pParentCommandBuffer->beginParent();

		/* Bind a render target to the parent command buffer. */
		pParentCommandBuffer->bindRenderTarget(pRenderTarget, pSwapChain, Cast<UI32>(frameIndex), RSubpassContentType::SUBPASS_CONTENT_TYPE_SECONDARY_COMMAND_BUFFER);

		/* Begin the inherited secondary command buffer. */
		pSecondaryCommandBuffer->beginInherited(pRenderTarget, frameIndex);

		/* Bind the secondary commands. */
		bindSecondaryCommands(pSecondaryCommandBuffer);

		/* End the secondary command buffers. */
		pSecondaryCommandBuffer->end();

		/* Execute the secondary command buffer calls. */
		pSecondaryCommandBuffer->executeSecondaryCommands(pParentCommandBuffer);

		/* Unbind the render target from the primary command buffer. */
		pParentCommandBuffer->unbindRenderTarget();

		/* End the primary command buffer. */
		pParentCommandBuffer->end();
	}

	RCommandBuffer* RDrawCallManager::getPrimaryCommandBuffer(UI64 frameIndex)
	{
		return pCommandBuffers[frameIndex];
	}

	RCommandBuffer* RDrawCallManager::getSecondaryCommandBuffer(UI64 frameIndex)
	{
		return pSecondaryCommandBuffers[frameIndex];
	}

	void RDrawCallManager::bindSecondaryCommands(RCommandBuffer* pCommandBuffer)
	{
		for (UI32 index = 0; index < secondaryCommandBindings.size(); index++)
		{
			auto& binding = secondaryCommandBindings[index];

			pCommandBuffer->bindVertexBuffer(binding.pRenderEntity->pVertexBuffer, 0);
			pCommandBuffer->bindIndexBuffer(binding.pRenderEntity->pIndexBuffer);

			for (UI32 itr = 0; itr < binding.pRenderEntity->meshObjects.size(); itr++)
			{
				pCommandBuffer->bindGraphicsPipeline(binding.pRenderEntity->pPipelineObject, binding.pRenderEntity->meshObjects[itr].pResourceObject);

				pCommandBuffer->drawIndexed(0, binding.pRenderEntity->meshObjects[itr].vertexOffset, binding.pRenderEntity->meshObjects[itr].indexCount, 1);
			}

			binding.runTime += 1.0f;
		}
	}

	void RDrawCallManager::resetPrimaryCommandBuffers(RCoreObject* pCoreObject)
	{
		pCommandBufferManager->resetBuffers(pCoreObject, pCommandBuffers);
	}

	void RDrawCallManager::resetSecondaryCommandBuffers(RCoreObject* pCoreObject)
	{
		pCommandBufferManager->resetBuffers(pCoreObject, pSecondaryCommandBuffers);
	}
}
