// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanRBL.h"

#include "VulkanCoreObject.h"
#include "Common/VulkanInstance.h"
#include "Common/VulkanSurface.h"
#include "Common/VulkanDevice.h"
#include "Common/VulkanQueue.h"
#include "Common/VulkanCommandBuffer.h"
#include "Common/VulkanCommandBufferManager.h"
#include "Common/VulkanDescriptorSetManager.h"
#include "Context/VulkanSwapChain.h"
#include "Context/VulkanRenderPass.h"
#include "Context/VulkanFrameBuffer.h"
#include "Pipelines/VulkanGraphicsPipeline.h"
#include "Lighting/VulkanBRDFTable.h"
#include "Lighting/VulkanPreFilteredCube.h"
#include "Lighting/VulkanIrradianceCube.h"
#include "Clients/VulkanImGuiBackend.h"

namespace Backend
{
	void VulkanRBL::initializeCoreObject(DMKRendererDescription description)
	{
		pCoreObject = StaticAllocator<VulkanCoreObject>::rawAllocate();
		pCoreObject->initialize(description, getWindowHandle());
	}

	RCoreObject* VulkanRBL::getCoreObject() const
	{
		return pCoreObject;
	}

	void VulkanRBL::terminateCoreObject()
	{
		pCoreObject->terminate();
	}

	RSwapChain* VulkanRBL::createSwapChain(DMKViewport viewport, RSwapChainPresentMode presentMode)
	{
		VulkanSwapChain* pSwapChain = StaticAllocator<VulkanSwapChain>::rawAllocate();
		pSwapChain->initialize(getCoreObject(), viewport, presentMode);

		return pSwapChain;
	}

	void VulkanRBL::terminateSwapChain(RSwapChain* pSwapChain)
	{
		if (!pSwapChain)
		{
			DMK_ERROR("Invalid swap chain object!");
			return;
		}

		pSwapChain->terminate(getCoreObject());
		StaticAllocator<VulkanSwapChain>::rawDeallocate(pSwapChain);
	}

	RRenderTarget* VulkanRBL::createRenderTarget(RSwapChain* pSwapChain, std::vector<RSubpassAttachment> subPasses, std::vector<RSubpassDependency> subPassDependencies)
	{
		if (!pSwapChain)
		{
			DMK_ERROR("Invalid swap chain object!");
			return nullptr;
		}

		RRenderTarget* pRenderTarget = StaticAllocator<RRenderTarget>::rawAllocate();

		/* Initialize Render Pass */
		pRenderTarget->pRenderPass = createRenderPass(pSwapChain, subPasses, subPassDependencies);

		/* Initialize Frame Buffer */
		pRenderTarget->pFrameBuffer = StaticAllocator<VulkanFrameBuffer>::rawAllocate();
		pRenderTarget->pFrameBuffer->initialize(getCoreObject(), pRenderTarget->pRenderPass, pSwapChain->extent, pSwapChain->bufferCount, RUtilities::getFrameBufferAttachments(DMKRenderingAPI::DMK_RENDERING_API_VULKAN, pRenderTarget->pRenderPass->subPasses, getCoreObject(), pSwapChain, pSwapChain->extent));

		return pRenderTarget;
	}

	void VulkanRBL::terminateRenderTarget(RRenderTarget* pRenderTarget)
	{
		if (!pRenderTarget)
		{
			DMK_ERROR("Invalid render target object!");
			return;
		}

		/* Terminate Render Pass */
		terminateRenderPass(pRenderTarget->pRenderPass);

		/* Terminate Frame Buffer */
		terminateFrameBuffer(pRenderTarget->pFrameBuffer);

		StaticAllocator<RRenderTarget>::rawDeallocate(pRenderTarget);
	}

	RRenderPass* VulkanRBL::createRenderPass(RSwapChain* pSwapChain, std::vector<RSubpassAttachment> subPasses, std::vector<RSubpassDependency> subPassDependencies)
	{
		if (!pSwapChain)
		{
			DMK_ERROR("Invalid swap chain object!");
			return nullptr;
		}

		VulkanRenderPass* pRenderPass = StaticAllocator<VulkanRenderPass>::rawAllocate();
		pRenderPass->initialize(getCoreObject(), subPasses, subPassDependencies, pSwapChain);

		return pRenderPass;
	}

	void VulkanRBL::terminateRenderPass(RRenderPass* pRenderPass)
	{
		if (!pRenderPass)
		{
			DMK_ERROR("Invalid render pass object!");
			return;
		}

		pRenderPass->terminate(getCoreObject());
		StaticAllocator<VulkanRenderPass>::rawDeallocate(pRenderPass);
	}

	RFrameBuffer* VulkanRBL::createFrameBuffer(RSwapChain* pSwapChain, RRenderPass* pRenderPass)
	{
		if (!pSwapChain)
		{
			DMK_ERROR("Invalid swap chain object!");
			return nullptr;
		}

		if (!pRenderPass)
		{
			DMK_ERROR("Invalid render pass object!");
			return nullptr;
		}

		VulkanFrameBuffer* pFrameBuffer = StaticAllocator<VulkanFrameBuffer>::rawAllocate();
		pFrameBuffer->initialize(getCoreObject(), pRenderPass, pSwapChain->extent, pSwapChain->bufferCount, RUtilities::getFrameBufferAttachments(DMKRenderingAPI::DMK_RENDERING_API_VULKAN, pRenderPass->subPasses, getCoreObject(), pSwapChain, pSwapChain->extent));

		return pFrameBuffer;
	}

	void VulkanRBL::terminateFrameBuffer(RFrameBuffer* pFrameBuffer)
	{
		if (!pFrameBuffer)
		{
			DMK_ERROR("Invalid frame buffer object!");
			return;
		}

		pFrameBuffer->terminate(getCoreObject());
		StaticAllocator<VulkanFrameBuffer>::rawDeallocate(pFrameBuffer);
	}

	RBuffer* VulkanRBL::createBuffer(RBufferType type, UI64 size, RResourceMemoryType resourceMemoryType)
	{
		if (size <= 0)
		{
			DMK_ERROR("Invalid buffer size!");
			return nullptr;
		}

		VulkanBuffer* pBuffer = StaticAllocator<VulkanBuffer>::rawAllocate();
		pBuffer->initialize(getCoreObject(), type, size, resourceMemoryType);

		return pBuffer;
	}

	void VulkanRBL::terminateBuffer(RBuffer* pBuffer)
	{
		if (!pBuffer)
		{
			DMK_ERROR("Invalid buffer object!");
			return;
		}

		pBuffer->terminate(getCoreObject());
		StaticAllocator<VulkanBuffer>::rawDeallocate(pBuffer);
	}

	RBuffer* VulkanRBL::createVertexBuffer(UI64 size)
	{
		return createBuffer(RBufferType::BUFFER_TYPE_VERTEX, size, RResourceMemoryType(RESOURCE_MEMORY_TYPE_DEVICE_LOCAL | RESOURCE_MEMORY_TYPE_HOST_COHERENT));
	}

	RBuffer* VulkanRBL::createIndexBuffer(UI64 size)
	{
		return createBuffer(RBufferType::BUFFER_TYPE_INDEX, size, RResourceMemoryType(RESOURCE_MEMORY_TYPE_DEVICE_LOCAL | RESOURCE_MEMORY_TYPE_HOST_COHERENT));
	}

	RBuffer* VulkanRBL::createUniformBuffer(UI64 size)
	{
		return createBuffer(RBufferType::BUFFER_TYPE_UNIFORM, size);
	}

	RTexture* VulkanRBL::createTexture(DMKTexture* pTexture)
	{
		VulkanTexture* pVTexture = StaticAllocator<VulkanTexture>::rawAllocate();
		pVTexture->initialize(getCoreObject(), pTexture);
		pVTexture->createView(getCoreObject());

		if ((pTexture->type == DMKTextureType::TEXTURE_TYPE_CUBEMAP) || (pTexture->type == DMKTextureType::TEXTURE_TYPE_CUBEMAP_ARRAY)) /* TODO */
			pVTexture->createSampler(getCoreObject(), RImageSamplerCreateInfo::createCubeMapSampler(0.0f));
		else
			pVTexture->createSampler(getCoreObject(), RImageSamplerCreateInfo::createDefaultSampler(0.0f));

		return pVTexture;
	}

	void VulkanRBL::terminateTexture(RTexture* pTexture)
	{
		if (!pTexture)
		{
			DMK_ERROR("Invalid texture object!");
			return;
		}

		pTexture->terminate(getCoreObject());
		StaticAllocator<VulkanTexture>::rawDeallocate(pTexture);
	}

	RPipelineObject* VulkanRBL::createPipeline(RPipelineSpecification specification, RPipelineUsage pipelineUsage, RRenderTarget* pRenderTarget, DMKViewport viewPort)
	{
		switch (pipelineUsage)
		{
		case RPipelineUsage::PIPELINE_USAGE_GRAPHICS:
		{
			VulkanGraphicsPipeline* pPipeline = StaticAllocator<VulkanGraphicsPipeline>::rawAllocate();
			pPipeline->initialize(getCoreObject(), specification, pipelineUsage, pRenderTarget, viewPort);

			return pPipeline;
		}
		break;
		case RPipelineUsage::PIPELINE_USAGE_COMPUTE:
			break;
		default:
			DMK_ERROR("Invalid pipeline usage!");
			break;
		}

		return nullptr;
	}

	void VulkanRBL::terminatePipeline(RPipelineObject* pPipelineObject)
	{
		if (!pPipelineObject)
		{
			DMK_ERROR("Invalid pipeline object!");
			return;
		}

		for (auto block : pPipelineObject->constantBlocks)
			StaticAllocator<BYTE>::rawDeallocate(block.data, block.byteSize);

		switch (pPipelineObject->myUsage)
		{
		case RPipelineUsage::PIPELINE_USAGE_GRAPHICS:
			pPipelineObject->terminate(getCoreObject());
			StaticAllocator<VulkanGraphicsPipeline>::rawDeallocate(pPipelineObject);
			break;

		case RPipelineUsage::PIPELINE_USAGE_COMPUTE:
			break;
		}
	}

	RBRDFTable* VulkanRBL::createBRDFTable(Vector2F dimentions, DMKFormat format)
	{
		VulkanBRDFTable* pBRDFTable = StaticAllocator<VulkanBRDFTable>::rawAllocate();
		pBRDFTable->initialize(getCoreObject(), dimentions, format);

		return pBRDFTable;
	}

	void VulkanRBL::terminateBRDFTable(RBRDFTable* pBRDFTable)
	{
		if (!pBRDFTable)
		{
			DMK_ERROR("Invalid BRDF table object!");
			return;
		}

		pBRDFTable->terminate(getCoreObject());
		StaticAllocator<VulkanBRDFTable>::rawDeallocate(pBRDFTable);
	}

	RIrradianceCube* VulkanRBL::createIrradianceCube(REnvironmentEntity* pEnvironmentEntity, Vector2F dimentions, DMKFormat format)
	{
		if (!pEnvironmentEntity)
		{
			DMK_ERROR("Environment entity is invalid!");
			return nullptr;
		}

		VulkanIrradianceCube* pIrradianceCube = StaticAllocator<VulkanIrradianceCube>::rawAllocate();
		pIrradianceCube->initialize(getCoreObject(), pEnvironmentEntity, dimentions, format);

		return pIrradianceCube;
	}

	void VulkanRBL::terminateIrradianceCube(RIrradianceCube* pIrradianceCube)
	{
		if (!pIrradianceCube)
		{
			DMK_ERROR("Invalid irradiance cube object!");
			return;
		}

		pIrradianceCube->terminate(getCoreObject());
		StaticAllocator<VulkanIrradianceCube>::rawDeallocate(pIrradianceCube);
	}

	RPreFilteredCube* VulkanRBL::createPreFilteredCube(REnvironmentEntity* pEnvironmentEntity, Vector2F dimentions, DMKFormat format)
	{
		if (!pEnvironmentEntity)
		{
			DMK_ERROR("Environment entity is invalid!");
			return nullptr;
		}

		VulkanPreFilteredCube* pPreFilteredCube = StaticAllocator<VulkanPreFilteredCube>::rawAllocate();
		pPreFilteredCube->initialize(getCoreObject(), pEnvironmentEntity, dimentions, format);

		return pPreFilteredCube;
	}

	void VulkanRBL::terminatePreFilteredCube(RPreFilteredCube* pPreFilteredCube)
	{
		if (!pPreFilteredCube)
		{
			DMK_ERROR("Invalid pre filtered cube object!");
			return;
		}

		pPreFilteredCube->terminate(getCoreObject());
		StaticAllocator<VulkanPreFilteredCube>::rawDeallocate(pPreFilteredCube);
	}

	RImage* VulkanRBL::createStorageImage(DMKFormat format, Vector3F dimentions)
	{
		RImageCreateInfo createInfo = {};
		createInfo.imageFormat = format;
		createInfo.vDimentions = dimentions;
		createInfo.layers = 1;
		createInfo.mipLevels = 1;
		createInfo.sampleCount = DMK_SAMPLE_COUNT_1_BIT;
		createInfo.imageUsage = RImageUsage(RImageUsage::IMAGE_USAGE_TRANSFER_SRC | RImageUsage::IMAGE_USAGE_STORAGE);

		VulkanImage* pImage = StaticAllocator<VulkanImage>::rawAllocate();
		pImage->initialize(getCoreObject(), createInfo);

		pImage->createImageView(getCoreObject(), DMKTexture::TextureSwizzles());

		return pImage;
	}

	void VulkanRBL::terminateImage(RImage* pImage)
	{
		if (!pImage)
		{
			DMK_ERROR("Invalid image object!");
			return;
		}

		pImage->terminate(getCoreObject());
		StaticAllocator<VulkanImage>::rawDeallocate(pImage);
	}
}
