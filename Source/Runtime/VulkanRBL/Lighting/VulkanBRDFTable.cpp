#include "dmkafx.h"
#include "VulkanBRDFTable.h"

#include "../Primitives/VulkanTexture.h"
#include "../Context/VulkanRenderPass.h"
#include "../Context/VulkanFrameBuffer.h"
#include "../Common/VulkanOneTimeCommandBuffer.h"

#include "Services/RuntimeSystems/AssetRegistry.h"
#include "Core/Utilities/ShaderFactory.h"
#include "Core/Types/StaticArray.h"
#include "Renderer/RUtilities.h"

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

		/* Issue Process Command */
		_process(pCoreObject);

		/* Terminate Support Structures */
		_terminateSupportStructures(pCoreObject);
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
		imageCreateInfo.vDimentions.width = dimentions.width;
		imageCreateInfo.vDimentions.height = dimentions.height;
		imageCreateInfo.vDimentions.depth = 1;
		imageCreateInfo.imageUsage = RImageUsage(IMAGE_USAGE_COLOR_ATTACHMENT | IMAGE_USAGE_RENDER);

		pTexture->pImage = StaticAllocator<VulkanImage>::rawAllocate();
		pTexture->pImage->initialize(pCoreObject, imageCreateInfo);

		/* Initialize Image View */
		pTexture->pImage->createImageView(pCoreObject, DMKTexture::TextureSwizzles());

		/* Initialize Sampler */
		pTexture->pSampler = StaticAllocator<VulkanImageSampler>::rawAllocate();
		pTexture->pSampler->initialize(pCoreObject, RImageSamplerCreateInfo::createDefaultSampler());

		pTexture->makeRenderable(pCoreObject);
	}

	void VulkanBRDFTable::_initializeRenderPass(RCoreObject* pCoreObject)
	{
		renderTarget.pRenderPass = StaticAllocator<VulkanRenderPass>::rawAllocate();

		ARRAY<RSubpassAttachment> subpassAttachments(1);
		subpassAttachments[0].subpass = RSubPasses::SUBPASSES_COLOR;
		subpassAttachments[0].format = format;
		subpassAttachments[0].samples = DMK_SAMPLE_COUNT_1_BIT;
		subpassAttachments[0].loadOp = RSubpassAttachmentLoadOp::SUBPASS_ATTACHMENT_LOAD_OP_CLEAR;
		subpassAttachments[0].storeOp = RSubpassAttachmentStoreOp::SUBPASS_ATTACHMENT_STORE_OP_STORE;
		subpassAttachments[0].stencilLoadOp = RSubpassAttachmentLoadOp::SUBPASS_ATTACHMENT_LOAD_OP_DONT_CARE;
		subpassAttachments[0].stencilStoreOp = RSubpassAttachmentStoreOp::SUBPASS_ATTACHMENT_STORE_OP_DONT_CARE;
		subpassAttachments[0].initialLayout = RImageLayout::IMAGE_LAYOUT_UNDEFINED;
		subpassAttachments[0].finalLayout = RImageLayout::IMAGE_LAYOUT_SHADER_READ_ONLY;

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

		renderTarget.pRenderPass->initialize(pCoreObject, subpassAttachments, subpassDependencies, nullptr, format);
	}

	void VulkanBRDFTable::_initializeFrameBuffer(RCoreObject* pCoreObject)
	{
		renderTarget.pFrameBuffer = StaticAllocator<VulkanFrameBuffer>::rawAllocate();

		RFrameBufferAttachment* pAttachment = StaticAllocator<RFrameBufferAttachment>::rawAllocate();
		pAttachment->setImage(pTexture->pImage);

		renderTarget.pFrameBuffer->initialize(pCoreObject, renderTarget.pRenderPass, dimentions, 1, { { pAttachment } });
	}

	void VulkanBRDFTable::_initializePipelines(RCoreObject* pCoreObject)
	{
		ARRAY<DMKShaderModule> shaders;
		shaders.pushBack(DMKShaderModule(DMKAssetRegistry::getAsset(TEXT("SHADER_PBR_IBL_BRDF_TABLE_VERT_SPV")), DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV));
		shaders.pushBack(DMKShaderModule(DMKAssetRegistry::getAsset(TEXT("SHADER_PBR_IBL_BRDF_TABLE_FRAG_SPV")), DMKShaderLocation::DMK_SHADER_LOCATION_FRAGMENT, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV));

		DMKViewport _viewport;
		_viewport.width = Cast<I32>(dimentions.width);
		_viewport.height = Cast<I32>(dimentions.height);
		_viewport.windowHandle = nullptr;

		RPipelineSpecification pipelineSpec = {};
		pipelineSpec.shaders = shaders;
		pipelineSpec.dynamicStates = { RDynamicState::DYNAMIC_STATE_VIEWPORT, RDynamicState::DYNAMIC_STATE_SCISSOR };
		pipelineSpec.scissorInfos.resize(1);
		pipelineSpec.colorBlendInfo.blendStates = RUtilities::createBasicColorBlendStates();
		pipelineSpec.multiSamplingInfo.sampleCount = DMK_SAMPLE_COUNT_1_BIT;
		pipeline.initialize(pCoreObject, pipelineSpec, RPipelineUsage::PIPELINE_USAGE_GRAPHICS, &renderTarget, _viewport);
	}

	void VulkanBRDFTable::_process(RCoreObject* pCoreObject)
	{
		VulkanOneTimeCommandBuffer buffer(pCoreObject);

		/* Begin Render Pass */
		VkRenderPassBeginInfo beginInfo = {};
		beginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		beginInfo.pNext = VK_NULL_HANDLE;
		beginInfo.framebuffer = Inherit<VulkanFrameBuffer>(renderTarget.pFrameBuffer)->buffers[0];
		beginInfo.renderArea.extent.width = Cast<I32>(dimentions.width);
		beginInfo.renderArea.extent.height = Cast<I32>(dimentions.height);
		beginInfo.renderPass = Inherit<VulkanRenderPass>(renderTarget.pRenderPass)->renderPass;
		beginInfo.clearValueCount = 1;

		StaticArray<VkClearValue, 1> clearValues;
		clearValues[0].color = { { 0.0f, 0.0f, 0.0f, 1.0f } };
		beginInfo.pClearValues = clearValues.data();

		vkCmdBeginRenderPass(buffer, &beginInfo, VK_SUBPASS_CONTENTS_INLINE);

		/* Bind Viewport */
		VkViewport vViewport = {};
		vViewport.maxDepth = 1.0f;
		vViewport.minDepth = 0.0f;
		vViewport.width = dimentions.width;
		vViewport.height = dimentions.height;
		vkCmdSetViewport(buffer, 0, 1, &vViewport);

		/* Bind Scissor */
		VkRect2D vScissor = {};
		vScissor.extent.width = Cast<I32>(dimentions.width);
		vScissor.extent.height = Cast<I32>(dimentions.height);
		vkCmdSetScissor(buffer, 0, 1, &vScissor);

		/* Bind Pipeline */
		vkCmdBindPipeline(buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);

		/* Draw Call */
		vkCmdDraw(buffer, 3, 1, 0, 0);

		/* End Render Pass */
		vkCmdEndRenderPass(buffer);
	}

	void VulkanBRDFTable::_terminateSupportStructures(RCoreObject* pCoreObject)
	{
		pipeline.terminate(pCoreObject);

		renderTarget.pRenderPass->terminate(pCoreObject);
		StaticAllocator<VulkanRenderPass>::rawDeallocate(renderTarget.pRenderPass);

		renderTarget.pFrameBuffer->terminate(pCoreObject);
		StaticAllocator<VulkanFrameBuffer>::rawDeallocate(renderTarget.pFrameBuffer);
	}
}
