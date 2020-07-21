// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanPreFilteredCube.h"

#include "../Primitives/VulkanTexture.h"
#include "../Context/VulkanRenderPass.h"
#include "../Context/Attachments/VulkanColorAttachment.h"
#include "../Common/VulkanOneTimeCommandBuffer.h"
#include "../Context/VulkanFrameBuffer.h"

#include "Renderer/RUtilities.h"
#include "Tools/Shader/GLSL/Compiler.h"
#include "Services/RuntimeSystems/AssetRegistry.h"
#include "Core/Math/MathFunctions.h"
#include "Core/Types/StaticArray.h"

#include <corecrt_math_defines.h>

namespace Dynamik
{
	namespace Backend
	{
		void VulkanPreFilteredCube::initialize(RCoreObject* pCoreObject, RTexture* pEnvironmentTexture, DMKExtent2D dimentions, DMKFormat format)
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
			_initializePipelines(pCoreObject, pEnvironmentTexture);

			/* Issue Process Command */
			_process(pCoreObject);

			/* Terminate Support Structures */
			_terminateSupportStructures(pCoreObject);
		}

		void VulkanPreFilteredCube::terminate(RCoreObject* pCoreObject)
		{
			pTexture->terminate(pCoreObject);
			StaticAllocator<VulkanTexture>::rawDeallocate(pTexture);
		}
		
		void VulkanPreFilteredCube::_initializeTexture(RCoreObject* pCoreObject)
		{
			pTexture = StaticAllocator<VulkanTexture>::rawAllocate();

			/* Initialize Image */
			RImageCreateInfo imageCreateInfo = {};
			imageCreateInfo.imageFormat = format;
			imageCreateInfo.imageType = DMKTextureType::TEXTURE_TYPE_CUBEMAP;
			imageCreateInfo.vDimentions.width = dimentions.width;
			imageCreateInfo.vDimentions.height = dimentions.height;
			imageCreateInfo.vDimentions.depth = 1;
			imageCreateInfo.imageUsage = RImageUsage(IMAGE_USAGE_COLOR_ATTACHMENT | IMAGE_USAGE_RENDER);
			imageCreateInfo.layers = 6;
			imageCreateInfo.mipLevels = Cast<UI32>(floor(log2(dimentions.width))) + 1;

			pTexture->pImage = StaticAllocator<VulkanImage>::rawAllocate();
			pTexture->pImage->initialize(pCoreObject, imageCreateInfo);

			/* Initialize Image View */
			pTexture->pImage->createImageView(pCoreObject, DMKTexture::TextureSwizzles());

			/* Initialize Sampler */
			pTexture->pSampler = StaticAllocator<VulkanImageSampler>::rawAllocate();
			pTexture->pSampler->initialize(pCoreObject, RImageSamplerCreateInfo::createCubeMapSampler());

			pTexture->makeRenderable(pCoreObject);
		}
		
		void VulkanPreFilteredCube::_initializeRenderPass(RCoreObject* pCoreObject)
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
			subpassAttachments[0].finalLayout = RImageLayout::IMAGE_LAYOUT_COLOR_ATTACHMENT;

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
		
		void VulkanPreFilteredCube::_initializeFrameBuffer(RCoreObject* pCoreObject)
		{
			RFrameBufferAttachmentInfo attachmentInfo;
			attachmentInfo.format = format;
			attachmentInfo.msaaSamples = DMKSampleCount::DMK_SAMPLE_COUNT_1_BIT;
			attachmentInfo.imageWidth = dimentions.width;
			attachmentInfo.imageHeight = dimentions.height;

			VulkanColorAttachment* pAttachment = StaticAllocator<VulkanColorAttachment>::rawAllocate();
			pAttachment->initialize(pCoreObject, attachmentInfo);

			renderTarget.pFrameBuffer->initialize(pCoreObject, renderTarget.pRenderPass, dimentions, 1, { { pAttachment } });
		
			pAttachment->pImageAttachment->setLayout(pCoreObject, RImageLayout::IMAGE_LAYOUT_COLOR_ATTACHMENT);
		}

		void VulkanPreFilteredCube::_initializePipelines(RCoreObject* pCoreObject, RTexture* pEnvironmentTexture)
		{
			Tools::GLSLCompiler compiler;

			ARRAY<DMKShaderModule> shaders;
			shaders.pushBack(compiler.getSPIRV(DMKAssetRegistry::getAsset(TEXT("SHADER_PBR_IBL_FILTER_CUBE_VERT")), DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX));
			shaders.pushBack(compiler.getSPIRV(DMKAssetRegistry::getAsset(TEXT("SHADER_PBR_IBL_PREFILTER_ENVIRONMENT_FRAG")), DMKShaderLocation::DMK_SHADER_LOCATION_FRAGMENT));

			DMKViewport _viewport;
			_viewport.width = Cast<I32>(dimentions.width);
			_viewport.height = Cast<I32>(dimentions.height);
			_viewport.windowHandle = nullptr;

			RPipelineSpecification pipelineSepc = {};
			pipelineSepc.shaders = shaders;
			pipelineSepc.dynamicStates = { RDynamicState::DYNAMIC_STATE_VIEWPORT, RDynamicState::DYNAMIC_STATE_SCISSOR };
			pipelineSepc.scissorInfos.resize(1);
			pipelineSepc.colorBlendInfo.blendStates = RUtilities::createBasicColorBlendStates();
			pipelineSepc.multiSamplingInfo.sampleCount = DMK_SAMPLE_COUNT_1_BIT;
			pipeline.initialize(pCoreObject, pipelineSepc, RPipelineUsage::PIPELINE_USAGE_GRAPHICS, &renderTarget, _viewport);
		
			pipeline.submitConstantData(StaticAllocator<ConstantBlock>::allocate(), 0);

			pipeline.initializeResources(pCoreObject, ARRAY<RBuffer*>(), { pEnvironmentTexture });
		}

		void VulkanPreFilteredCube::_process(RCoreObject* pCoreObject)
		{
			VulkanOneTimeCommandBuffer buffer(pCoreObject);
			ConstantBlock constantBlock;

			/* Begin Render Pass */
			VkRenderPassBeginInfo beginInfo = {};
			beginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			beginInfo.pNext = VK_NULL_HANDLE;
			beginInfo.framebuffer = Inherit<VulkanFrameBuffer>(renderTarget.pFrameBuffer)->buffers[0];
			beginInfo.renderArea.extent.width = Cast<I32>(dimentions.width);
			beginInfo.renderArea.extent.height = Cast<I32>(dimentions.height);
			beginInfo.renderPass = Inherit<VulkanRenderPass>(renderTarget.pRenderPass)->renderPass;
			beginInfo.clearValueCount = 1;

			/* Matrices */
			ARRAY<Matrix4F> matrices;
			matrices.pushBack(DMathLib::rotate(DMathLib::rotate(Matrix4F::Identity, DMathLib::radians(90.0f), Vector3F(0.0f, 1.0f, 0.0f)), DMathLib::radians(180.0f), Vector3F(1.0f, 0.0f, 0.0f)));
			matrices.pushBack(DMathLib::rotate(DMathLib::rotate(Matrix4F::Identity, DMathLib::radians(-90.0f), Vector3F(0.0f, 1.0f, 0.0f)), DMathLib::radians(180.0f), Vector3F(1.0f, 0.0f, 0.0f)));
			matrices.pushBack(DMathLib::rotate(Matrix4F::Identity, DMathLib::radians(-90.0f), Vector3F(1.0f, 0.0f, 0.0f)));
			matrices.pushBack(DMathLib::rotate(Matrix4F::Identity, DMathLib::radians(90.0f), Vector3F(1.0f, 0.0f, 0.0f)));
			matrices.pushBack(DMathLib::rotate(Matrix4F::Identity, DMathLib::radians(180.0f), Vector3F(1.0f, 0.0f, 0.0f)));
			matrices.pushBack(DMathLib::rotate(Matrix4F::Identity, DMathLib::radians(180.0f), Vector3F(0.0f, 0.0f, 1.0f)));
			
			StaticArray<VkClearValue, 1> clearValues;
			clearValues[0].color = { { 0.0f, 0.0f, 0.0f, 1.0f } };
			beginInfo.pClearValues = clearValues.data();

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

			VkImageSubresourceRange subresourceRange = {};
			subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			subresourceRange.baseMipLevel = 0;
			subresourceRange.levelCount = pTexture->pImage->mipLevel;
			subresourceRange.layerCount = 6;

			pTexture->pImage->setLayout(pCoreObject, RImageLayout::IMAGE_LAYOUT_TRANSFER_DST);

			for (UI32 i = 0; i < subresourceRange.levelCount; i++)
			{
				vViewport.width = dimentions.width * std::pow(0.5f, i);
				vViewport.height = dimentions.height * std::pow(0.5f, i);
				vkCmdSetViewport(buffer, 0, 1, &vViewport);

				vkCmdBeginRenderPass(buffer, &beginInfo, VK_SUBPASS_CONTENTS_INLINE);

				constantBlock.matrix = DMathLib::perspective(M_PI / 2.0f, 1.0f, 0.1f, 512.0f) * matrices[i];
				vkCmdPushConstants(buffer, pipeline, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(ConstantBlock), &constantBlock);

				vkCmdBindPipeline(buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);

				if (pipeline.isResourceAvailable)
					vkCmdBindDescriptorSets(buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline, 0, 1, &pipeline.descriptor.set, 0, VK_NULL_HANDLE);
			}
		}

		void VulkanPreFilteredCube::_terminateSupportStructures(RCoreObject* pCoreObject)
		{
		}
	}
}
