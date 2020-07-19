#include "dmkafx.h"
#include "VulkanBRDFTable.h"

#include "../Primitives/VulkanTexture.h"
#include "../Context/VulkanRenderPass.h"
#include "../Context/VulkanFrameBuffer.h"

#include "Services/RuntimeSystems/AssetRegistry.h"
#include "Core/Utilities/ShaderFactory.h"

namespace Dynamik
{
	namespace Backend
	{
		void VulkanBRDFTable::initialize(RCoreObject* pCoreObject, DMKExtent2D dimentions, DMKFormat format)
		{
			this->format = format;
			this->dimentions = dimentions;

			/* Initialize Texture */
			_initializeTexture(pCoreObject);

			/* Initialize Render Pass */
			_initializeRenderPass(pCoreObject);

			/* Initialize Frame Buffer */
			_initializeFrameBuffer(pCoreObject);

			/* Initialize Pipeline */
			_initializePipelines(pCoreObject);
		}

		void VulkanBRDFTable::terminate(RCoreObject* pCoreObject)
		{
			pTexture->terminate(pCoreObject);
			StaticAllocator<VulkanTexture>::rawDeallocate(pTexture);
		}

		void VulkanBRDFTable::_initializeTexture(RCoreObject* pCoreObject)
		{
			pTexture = StaticAllocator<VulkanTexture>::rawAllocate();

			/* Initialize Image */
			RImageCreateInfo imageCreateInfo = {};
			imageCreateInfo.imageFormat = format;
			imageCreateInfo.imageType = DMKTextureType::TEXTURE_TYPE_2D;

			pTexture->pImage = StaticAllocator<VulkanImage>::rawAllocate();
			pTexture->pImage->initialize(pCoreObject, imageCreateInfo);

			/* Initialize Image View */
			pTexture->pImage->createImageView(pCoreObject, DMKTexture::TextureSwizzles());

			/* Initialize Sampler */
			pTexture->pSampler = StaticAllocator<VulkanImageSampler>::rawAllocate();
			pTexture->pSampler->initialize(pCoreObject, RImageSamplerCreateInfo::createDefaultSampler());
		}

		void VulkanBRDFTable::_initializeRenderPass(RCoreObject* pCoreObject)
		{
			renderTarget.pRenderPass = StaticAllocator<VulkanRenderPass>::rawAllocate();

			ARRAY<RSubpassDependency> subpassDependencies(2);
			RSubpassDependency subpassDependency;
			subpassDependency.pipelineDependency = RPipelineDependency::DEPENDENCY_BY_REGION;

			subpassDependency.srcSubpassIndex = VK_SUBPASS_EXTERNAL;
			subpassDependency.dstSubpassIndex = 0;
			subpassDependency.srcPipelineStage = RPipelineStage::PIPELINE_STAGE_BOTTOM_OF_PIPE;
			subpassDependency.dstPipelineStage = RPipelineStage::PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT;
			subpassDependency.srcMemoryAccessType = RMemoryAccessType::MEMORY_ACCESS_TYPE_MEMORY_READ;
			subpassDependency.dstMemoryAccessType = Cast<RMemoryAccessType>(MEMORY_ACCESS_TYPE_COLOR_ATTACHMENT_READ | MEMORY_ACCESS_TYPE_COLOR_ATTACHMENT_WRITE);
			subpassDependencies[0] = subpassDependency;

			subpassDependency.srcSubpassIndex = 0;
			subpassDependency.dstSubpassIndex = VK_SUBPASS_EXTERNAL;
			subpassDependency.srcPipelineStage = RPipelineStage::PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT;
			subpassDependency.dstPipelineStage = RPipelineStage::PIPELINE_STAGE_BOTTOM_OF_PIPE;
			subpassDependency.srcMemoryAccessType = Cast<RMemoryAccessType>(MEMORY_ACCESS_TYPE_COLOR_ATTACHMENT_READ | MEMORY_ACCESS_TYPE_COLOR_ATTACHMENT_WRITE);
			subpassDependency.dstMemoryAccessType = RMemoryAccessType::MEMORY_ACCESS_TYPE_MEMORY_READ;
			subpassDependencies[1] = subpassDependency;

			renderTarget.pRenderPass->initialize(pCoreObject, { RSubPasses::SUBPASSES_COLOR }, subpassDependencies, nullptr, format);
		}
		
		void VulkanBRDFTable::_initializeFrameBuffer(RCoreObject* pCoreObject)
		{
			renderTarget.pFrameBuffer = StaticAllocator<VulkanFrameBuffer>::rawAllocate();
			renderTarget.pFrameBuffer->initialize(pCoreObject, renderTarget.pRenderPass, nullptr, dimentions, 1);
		}
		
		void VulkanBRDFTable::_initializePipelines(RCoreObject* pCoreObject)
		{
			ARRAY<DMKShaderModule> shaders;	/* TODO */
			shaders.pushBack(DMKShaderFactory::createModule(DMKAssetRegistry::getAsset(TEXT("SHADER_PBR_IBL_BRDF_TABLE_VERT_SPV")), DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV));
			shaders.pushBack(DMKShaderFactory::createModule(DMKAssetRegistry::getAsset(TEXT("SHADER_PBR_IBL_BRDF_TABLE_FRAG_SPV")), DMKShaderLocation::DMK_SHADER_LOCATION_FRAGMENT, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV));

			RPipelineSpecification pipelineSepc = {};
			pipelineSepc.shaders = shaders;
		}
	}
}