// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanIrradianceCube.h"

#include "../Primitives/VulkanTexture.h"
#include "../Context/VulkanRenderPass.h"
#include "../Context/Attachments/VulkanColorAttachment.h"
#include "../Common/VulkanOneTimeCommandBuffer.h"
#include "../VulkanUtilities.h"
#include "../Context/VulkanFrameBuffer.h"

#include "Renderer/RUtilities.h"
#include "Renderer/Components/REnvironmentMap.h"
#include "Tools/Shader/GLSL/Compiler.h"
#include "Services/RuntimeSystems/AssetRegistry.h"
#include "Core/Math/MathFunctions.h"
#include "Core/Types/StaticArray.h"

namespace Dynamik
{
	namespace Backend
	{
		void VulkanIrradianceCube::initialize(RCoreObject* pCoreObject, REnvironmentMap* pEnvironmentMap, DMKExtent2D dimentions, DMKFormat format)
		{
			this->format = format;
			this->dimentions = dimentions;
			this->pParent = pEnvironmentMap;

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

		void VulkanIrradianceCube::terminate(RCoreObject* pCoreObject)
		{
			pTexture->terminate(pCoreObject);
			StaticAllocator<VulkanTexture>::rawDeallocate(pTexture);
		}

		void VulkanIrradianceCube::_initializeTexture(RCoreObject* pCoreObject)
		{
			pTexture = StaticAllocator<VulkanTexture>::rawAllocate();

			/* Initialize Image */
			RImageCreateInfo imageCreateInfo = {};
			imageCreateInfo.imageFormat = format;
			imageCreateInfo.imageType = DMKTextureType::TEXTURE_TYPE_CUBEMAP;
			imageCreateInfo.vDimentions.width = dimentions.width;
			imageCreateInfo.vDimentions.height = dimentions.height;
			imageCreateInfo.vDimentions.depth = 1;
			imageCreateInfo.imageUsage = RImageUsage(IMAGE_USAGE_COLOR_ATTACHMENT | IMAGE_USAGE_RENDER | IMAGE_USAGE_TRANSFER_DST);
			imageCreateInfo.layers = 6;
			imageCreateInfo.mipLevels = Cast<UI32>(floor(log2(dimentions.width))) + 1;

			pTexture->pImage = StaticAllocator<VulkanImage>::rawAllocate();
			pTexture->pImage->initialize(pCoreObject, imageCreateInfo);

			/* Initialize Image View */
			pTexture->pImage->createImageView(pCoreObject, DMKTexture::TextureSwizzles());

			/* Initialize Sampler */
			pTexture->pSampler = StaticAllocator<VulkanImageSampler>::rawAllocate();
			pTexture->pSampler->initialize(pCoreObject, RImageSamplerCreateInfo::createCubeMapSampler());
		}

		void VulkanIrradianceCube::_initializeRenderPass(RCoreObject* pCoreObject)
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

		void VulkanIrradianceCube::_initializeFrameBuffer(RCoreObject* pCoreObject)
		{
			RImageCreateInfo imageCreateInfo = {};
			imageCreateInfo.vDimentions.width = dimentions.width;
			imageCreateInfo.vDimentions.height = dimentions.height;
			imageCreateInfo.vDimentions.depth = 1.0f;
			imageCreateInfo.imageUsage = RImageUsage(RImageUsage::IMAGE_USAGE_COLOR_ATTACHMENT | RImageUsage::IMAGE_USAGE_TRANSFER_SRC);
			imageCreateInfo.imageFormat = format;
			imageCreateInfo.mipLevels = 1;
			imageCreateInfo.layers = 1;

			pAttachment = StaticAllocator<VulkanColorAttachment>::rawAllocate();
			pAttachment->pImageAttachment = StaticAllocator<VulkanImage>::rawAllocate();

			pAttachment->pImageAttachment->initialize(pCoreObject, imageCreateInfo);
			pAttachment->pImageAttachment->createImageView(pCoreObject, DMKTexture::TextureSwizzles());

			renderTarget.pFrameBuffer = StaticAllocator<VulkanFrameBuffer>::rawAllocate();
			renderTarget.pFrameBuffer->initialize(pCoreObject, renderTarget.pRenderPass, dimentions, 1, { { pAttachment } });

			pAttachment->pImageAttachment->setLayout(pCoreObject, RImageLayout::IMAGE_LAYOUT_COLOR_ATTACHMENT);
		}

		void VulkanIrradianceCube::_initializePipelines(RCoreObject* pCoreObject)
		{
			Tools::GLSLCompiler compiler;

			ARRAY<DMKShaderModule> shaders;

			auto shaderVS = compiler.getSPIRV(DMKAssetRegistry::getAsset(TEXT("SHADER_PBR_IBL_FILTER_CUBE_VERT")), DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX);
			shaderVS.addInputAttribute(DMKShaderInputAttribute(DMKFormat::DMK_FORMAT_RGBA_32_SF32, 1));
			shaderVS.addInputAttribute(DMKShaderInputAttribute(DMKFormat::DMK_FORMAT_RGBA_32_SF32, 1));
			shaderVS.addInputAttribute(DMKShaderInputAttribute(DMKFormat::DMK_FORMAT_RG_32_SF32, 1));

			shaders.pushBack(shaderVS);
			shaders.pushBack(compiler.getSPIRV(DMKAssetRegistry::getAsset(TEXT("SHADER_PBR_IBL_IRRADIANCE_CUBE_FRAG")), DMKShaderLocation::DMK_SHADER_LOCATION_FRAGMENT));

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

			pipeline.initializeResources(pCoreObject, ARRAY<RBuffer*>(), { pParent->pTexture });
		}

		void VulkanIrradianceCube::_process(RCoreObject* pCoreObject)
		{
			VulkanOneTimeCommandBuffer buffer(pCoreObject);

			struct ConstantOne {
				Matrix4F matrix = Matrix4F::Identity;
			} constantOne;

			struct ConstantTwo {
				F32 deltaPhi = (2.0f * Cast<F32>(M_PI)) / 180.0f;
				F32 deltaTheta = (0.5f * Cast<F32>(M_PI)) / 64.0f;
			} constantTwo;

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

			/* Matrices */
			ARRAY<Matrix4F> matrices;
			matrices.pushBack(DMathLib::rotate(DMathLib::rotate(Matrix4F::Identity, DMathLib::radians(90.0f), Vector3F(0.0f, 1.0f, 0.0f)), DMathLib::radians(180.0f), Vector3F(1.0f, 0.0f, 0.0f)));
			matrices.pushBack(DMathLib::rotate(DMathLib::rotate(Matrix4F::Identity, DMathLib::radians(-90.0f), Vector3F(0.0f, 1.0f, 0.0f)), DMathLib::radians(180.0f), Vector3F(1.0f, 0.0f, 0.0f)));
			matrices.pushBack(DMathLib::rotate(Matrix4F::Identity, DMathLib::radians(-90.0f), Vector3F(1.0f, 0.0f, 0.0f)));
			matrices.pushBack(DMathLib::rotate(Matrix4F::Identity, DMathLib::radians(90.0f), Vector3F(1.0f, 0.0f, 0.0f)));
			matrices.pushBack(DMathLib::rotate(Matrix4F::Identity, DMathLib::radians(180.0f), Vector3F(1.0f, 0.0f, 0.0f)));
			matrices.pushBack(DMathLib::rotate(Matrix4F::Identity, DMathLib::radians(180.0f), Vector3F(0.0f, 0.0f, 1.0f)));

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

			VulkanUtilities::rawTransitionImageLayout(
				buffer, Inherit<VulkanImage>(pTexture->pImage)->image,
				VK_IMAGE_LAYOUT_UNDEFINED,
				VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
				pTexture->pImage->mipLevel, pTexture->pImage->layers,
				pTexture->pImage->format);

			pTexture->pImage->layout = RImageLayout::IMAGE_LAYOUT_TRANSFER_DST;

			VkImageCopy copyRegion = {};

			copyRegion.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			copyRegion.srcSubresource.baseArrayLayer = 0;
			copyRegion.srcSubresource.mipLevel = 0;
			copyRegion.srcSubresource.layerCount = 1;
			copyRegion.srcOffset = { 0, 0, 0 };

			copyRegion.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			copyRegion.dstSubresource.layerCount = 1;
			copyRegion.dstOffset = { 0, 0, 0 };

			for (UI32 i = 0; i < pTexture->pImage->mipLevel; i++)
			{
				for (UI32 j = 0; j < 6; j++)
				{
					vViewport.width = dimentions.width * Cast<F32>(std::pow(0.5f, i));
					vViewport.height = dimentions.height * Cast<F32>(std::pow(0.5f, i));
					vkCmdSetViewport(buffer, 0, 1, &vViewport);

					VkRect2D vScissor = {};
					vScissor.extent.width = Cast<I32>(dimentions.width);
					vScissor.extent.height = Cast<I32>(dimentions.height);
					vkCmdSetScissor(buffer, 0, 1, &vScissor);

					vkCmdBeginRenderPass(buffer, &beginInfo, VK_SUBPASS_CONTENTS_INLINE);

					vkCmdBindPipeline(buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);

					constantOne.matrix = DMathLib::perspective(Cast<F32>(M_PI) / 2.0f, 1.0f, 0.1f, 512.0f) * matrices[j];
					vkCmdPushConstants(buffer, pipeline, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(ConstantOne), &constantOne);
					vkCmdPushConstants(buffer, pipeline, VK_SHADER_STAGE_FRAGMENT_BIT, sizeof(ConstantOne), sizeof(ConstantTwo), &constantTwo);

					if (pipeline.isResourceAvailable)
						vkCmdBindDescriptorSets(buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline, 0, 1, &pipeline.descriptor.set, 0, VK_NULL_HANDLE);

					VkDeviceSize offsets[1] = { 0 };
					vkCmdBindVertexBuffers(buffer, 0, 1, &Inherit<VulkanBuffer>(pParent->pVertexBuffer)->buffer, offsets);

					if (pParent->pIndexBuffer)
					{
						vkCmdBindIndexBuffer(buffer, Inherit<VulkanBuffer>(pParent->pIndexBuffer)->buffer, 0, VK_INDEX_TYPE_UINT32);
						vkCmdDrawIndexed(buffer, Cast<UI32>(pParent->pIndexBuffer->getSize() / sizeof(UI32)), 1, 0, 0, 0);
					}
					else
					{
						vkCmdDraw(buffer, Cast<UI32>(pParent->pMeshComponent->vertexBuffer.size()), 1, 0, 0);
					}

					vkCmdEndRenderPass(buffer);

					{
						VulkanUtilities::rawTransitionImageLayout(
							buffer, Inherit<VulkanImage>(pAttachment->pImageAttachment)->image,
							VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
							VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
							pAttachment->pImageAttachment->mipLevel, pAttachment->pImageAttachment->layers,
							pAttachment->pImageAttachment->format);

						copyRegion.dstSubresource.baseArrayLayer = j;
						copyRegion.dstSubresource.mipLevel = i;

						copyRegion.extent.width = Cast<UI32>(vViewport.width);
						copyRegion.extent.height = Cast<UI32>(vViewport.height);
						copyRegion.extent.depth = 1;

						vkCmdCopyImage(buffer,
							Inherit<VulkanImage>(pAttachment->pImageAttachment)->image,
							VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
							Inherit<VulkanImage>(pTexture->pImage)->image,
							VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &copyRegion);

						VulkanUtilities::rawTransitionImageLayout(
							buffer, Inherit<VulkanImage>(pAttachment->pImageAttachment)->image,
							VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
							VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
							pAttachment->pImageAttachment->mipLevel, pAttachment->pImageAttachment->layers,
							pAttachment->pImageAttachment->format);
					}
				}
			}

			VulkanUtilities::rawTransitionImageLayout(
				buffer, Inherit<VulkanImage>(pTexture->pImage)->image,
				VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
				VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
				pTexture->pImage->mipLevel, pTexture->pImage->layers,
				pTexture->pImage->format);

			pTexture->pImage->layout = RImageLayout::IMAGE_LAYOUT_SHADER_READ_ONLY;
		}

		void VulkanIrradianceCube::_terminateSupportStructures(RCoreObject* pCoreObject)
		{
			pipeline.terminate(pCoreObject);

			renderTarget.pRenderPass->terminate(pCoreObject);
			StaticAllocator<VulkanRenderPass>::rawDeallocate(renderTarget.pRenderPass);

			renderTarget.pFrameBuffer->terminate(pCoreObject);
			StaticAllocator<VulkanFrameBuffer>::rawDeallocate(renderTarget.pFrameBuffer);
		}
	}
}
