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
	}

	void RDrawCallManager::addRenderEntity(REntity* pRenderEntity)
	{
		secondaryCommandBindings.pushBack(pRenderEntity);
	}

	void RDrawCallManager::initializeCommandBuffers(RCoreObject* pCoreObject, RRenderTarget* pRenderTarget, RSwapChain* pSwapChain, DMKRenderingAPI API)
	{
		if (isCommandBuffersInitialized)
			return;

		isCommandBuffersInitialized = true;

		switch (API)
		{
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
		{
			pCommandBufferManager = StaticAllocator<VulkanCommandBufferManager>::allocate();
		}
		break;
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_DIRECTX:
			break;
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_OPENGL:
			break;
		}

		pCommandBufferManager->initialize(pCoreObject);
		pCommandBuffers = pCommandBufferManager->allocateCommandBuffers(pCoreObject, pSwapChain->bufferCount, RCommandBufferLevel::COMMAND_BUFFEER_LEVEL_PRIMARY);
		pSecondaryCommandBuffers = pCommandBufferManager->allocateCommandBuffers(pCoreObject, pSwapChain->bufferCount, RCommandBufferLevel::COMMAND_BUFFEER_LEVEL_SECONDARY);

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

			for (auto renderMesh : binding.pRenderEntity->meshObjects)
			{
				pCommandBuffer->bindGraphicsPipeline(binding.pRenderEntity->pPipelineObject, renderMesh.pResourceObject);

				pCommandBuffer->drawIndexed(0, renderMesh.vertexOffset, renderMesh.indexCount, 1);
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
