// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanGraphicsPipeline.h"

#include "../Primitives/VulkanImageSampler.h"
#include "../VulkanUtilities.h"
#include "../VulkanCoreObject.h"
#include "Tools/Shader/SPIR-V/Disassembler.h"

#include <fstream>

namespace Backend
{
	/*
	 Get the descriptor type using the uniform type.
	*/
	DMK_FORCEINLINE VkDescriptorType GetDescriptorType(DMKUniformType type)
	{
		switch (type)
		{
		case DMKUniformType::DMK_UNIFORM_TYPE_UNIFORM_BUFFER:
			return VkDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;

		case DMKUniformType::DMK_UNIFORM_TYPE_STORAGE_BUFFER:
			return VkDescriptorType::VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;

		case DMKUniformType::DMK_UNIFORM_TYPE_UNIFORM_BUFFER_DYNAMIC:
			return VkDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;

		case DMKUniformType::DMK_UNIFORM_TYPE_STORAGE_BUFFER_DYNAMIC:
			return VkDescriptorType::VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;

		case DMKUniformType::DMK_UNIFORM_TYPE_UNIFORM_TEXEL_BUFFER:
			return VkDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;

		case DMKUniformType::DMK_UNIFORM_TYPE_STORAGE_TEXEL_BUFFER:
			return VkDescriptorType::VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER;

		case DMKUniformType::DMK_UNIFORM_TYPE_INPUT_ATTACHMENT:
			return VkDescriptorType::VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;

		case DMKUniformType::DMK_UNIFORM_TYPE_STORAGE_IMAGE:
			return VkDescriptorType::VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;

		case DMKUniformType::DMK_UNIFORM_TYPE_CONSTANT:
			break;	/* Doesn't have to do anything here. */

		case DMKUniformType::DMK_UNIFORM_TYPE_SAMPLER_2D:
			return VkDescriptorType::VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;

		case DMKUniformType::DMK_UNIFORM_TYPE_SAMPLER_CUBE:
			return VkDescriptorType::VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;

		case DMKUniformType::DMK_UNIFORM_TYPE_SAMPLER_2D_ARRAY:
			return VkDescriptorType::VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;

		case DMKUniformType::DMK_UNIFORM_TYPE_SAMPLER_CUBE_ARRAY:
			return VkDescriptorType::VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;

		case DMKUniformType::DMK_UNIFORM_TYPE_ACCELERATION_STRUCTURE:
			return VkDescriptorType::VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR;
		default:
			DMK_ERROR("Invalid or unknown uniform type!");
			break;
		}

		return VkDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	}

	/*
	 Get descriptor set layout bindings using shader uniforms.
	*/
	DMK_FORCEINLINE ARRAY<VkDescriptorSetLayoutBinding> GetDescriptorSetLayoutBindings(ARRAY<DMKUniformBuffer> uniforms, DMKShaderLocation location)
	{
		ARRAY<VkDescriptorSetLayoutBinding> bindings;

		VkDescriptorSetLayoutBinding binding = {};
		binding.pImmutableSamplers = nullptr;
		binding.descriptorCount = 0;
		binding.stageFlags = VulkanUtilities::getShaderStage(location);

		for (UI32 index = 0; index < uniforms.size(); index++)
		{
			if (uniforms[index].type == DMKUniformType::DMK_UNIFORM_TYPE_CONSTANT)
				continue;	/* Skip if the type is DMK_UNIFORM_TYPE_CONSTANT */

			binding.binding = Cast<UI32>(uniforms[index].getBindingLocation());
			binding.descriptorType = GetDescriptorType(uniforms[index].type);

			bindings.pushBack(binding);
		}

		return bindings;
	}

	/*
	 Get descriptor pool sizes.
	*/
	DMK_FORCEINLINE ARRAY<VkDescriptorPoolSize> GetDescriptorPoolSizes(ARRAY<DMKUniformBuffer> uniforms, DMKShaderLocation location)
	{
		ARRAY<VkDescriptorPoolSize> sizes;
		VkDescriptorPoolSize poolSize = {};
		poolSize.descriptorCount = 0;

		for (UI32 index = 0; index < uniforms.size(); index++)
		{
			poolSize.type = GetDescriptorType(uniforms[index].type);
			sizes.pushBack(poolSize);
		}

		return sizes;
	}

	/*
	 Get push constant ranges.
	*/
	DMK_FORCEINLINE ARRAY<VkPushConstantRange> GetPushConstantRanges(ARRAY<DMKUniformBuffer> uniforms, DMKShaderLocation location)
	{
		ARRAY<VkPushConstantRange> ranges;
		VkPushConstantRange range = {};
		range.stageFlags = VulkanUtilities::getShaderStage(location);
		range.offset = 0;

		for (UI32 index = 0; index < uniforms.size(); index++)
		{
			if (uniforms[index].type != DMKUniformType::DMK_UNIFORM_TYPE_CONSTANT)
				continue;

			range.size = Cast<UI32>(uniforms[index].byteSize());
			ranges.pushBack(range);

			range.offset += Cast<UI32>(uniforms[index].byteSize());
		}

		return ranges;
	}

	void VulkanGraphicsPipelineResource::update(RCoreObject* pCoreObject, ARRAY<RBuffer*> pBuffers, ARRAY<RTexture*> pTextures)
	{
		/* Re order the resource bindings or else resources will be mapped to the wrong shader resource */
		if (resourceBindings.size())
		{
			/* We find the minimum binding as users might not always start with the index 0. */
			UI64 minimumBinding = resourceBindings[0].binding;
			for (UI64 index = 0; index < resourceBindings.size(); index++)
				if (minimumBinding > resourceBindings[index].binding)
					minimumBinding = resourceBindings[index].binding;

			ARRAY<VkDescriptorSetLayoutBinding> bindings(resourceBindings.size());
			for (UI64 index = 0; index < resourceBindings.size(); index++)
				bindings[resourceBindings[index].binding - minimumBinding] = resourceBindings[index];

			resourceBindings = std::move(bindings);
		}
		else
		{
			/* If resources are unavailable, we don't need to do any processing. */
			return;
		}

		ARRAY<VkWriteDescriptorSet> descriptorWrites;

		VkWriteDescriptorSet descriptorWrite = {};
		descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrite.pNext = VK_NULL_HANDLE;
		descriptorWrite.descriptorCount = 1;
		descriptorWrite.dstSet = set;
		descriptorWrite.dstArrayElement = 0;
		descriptorWrite.pBufferInfo = VK_NULL_HANDLE;
		descriptorWrite.pImageInfo = VK_NULL_HANDLE;
		descriptorWrite.pTexelBufferView = VK_NULL_HANDLE;

		UI64 bufferIndex = 0;
		ARRAY<VkDescriptorBufferInfo> bufferInfos(pBuffers.size());

		UI64 textureIndex = 0;
		ARRAY<VkDescriptorImageInfo> imageInfos(pTextures.size());

		for (UI64 index = 0; index < resourceBindings.size(); index++)
		{
			descriptorWrite.dstBinding = resourceBindings[index].binding;
			descriptorWrite.descriptorType = resourceBindings[index].descriptorType;

			switch (descriptorWrite.descriptorType)
			{
			case VK_DESCRIPTOR_TYPE_SAMPLER:
				if (!pTextures.isValidIndex(textureIndex))
				{
					DMK_ERROR("A texture entry is not supplied!");
					textureIndex++;
					break;
				}

				imageInfos[textureIndex].imageLayout = VulkanUtilities::getVulkanLayout(pTextures[textureIndex]->pImage->layout);
				imageInfos[textureIndex].imageView = InheritCast<VulkanImageView>(pTextures[textureIndex]->pImage->pImageView);
				imageInfos[textureIndex].sampler = InheritCast<VulkanImageSampler>(pTextures[textureIndex]->pSampler);
				descriptorWrite.pImageInfo = imageInfos.location(textureIndex);
				textureIndex++;
				break;

			case VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER:
				if (!pTextures.isValidIndex(textureIndex))
				{
					DMK_ERROR("A texture entry is not supplied!");
					textureIndex++;
					break;
				}

				imageInfos[textureIndex].imageLayout = VulkanUtilities::getVulkanLayout(pTextures[textureIndex]->pImage->layout);
				imageInfos[textureIndex].imageView = InheritCast<VulkanImageView>(pTextures[textureIndex]->pImage->pImageView);
				imageInfos[textureIndex].sampler = InheritCast<VulkanImageSampler>(pTextures[textureIndex]->pSampler);
				descriptorWrite.pImageInfo = imageInfos.location(textureIndex);
				textureIndex++;
				break;

			case VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE:
				if (!pTextures.isValidIndex(textureIndex))
				{
					DMK_ERROR("A texture entry is not supplied!");
					textureIndex++;
					break;
				}

				imageInfos[textureIndex].imageLayout = VulkanUtilities::getVulkanLayout(pTextures[textureIndex]->pImage->layout);
				imageInfos[textureIndex].imageView = InheritCast<VulkanImageView>(pTextures[textureIndex]->pImage->pImageView);
				imageInfos[textureIndex].sampler = InheritCast<VulkanImageSampler>(pTextures[textureIndex]->pSampler);
				descriptorWrite.pImageInfo = imageInfos.location(textureIndex);
				textureIndex++;
				break;

			case VK_DESCRIPTOR_TYPE_STORAGE_IMAGE:
				if (!pTextures.isValidIndex(textureIndex))
				{
					DMK_ERROR("A texture entry is not supplied!");
					textureIndex++;
					break;
				}

				imageInfos[textureIndex].imageLayout = VulkanUtilities::getVulkanLayout(pTextures[textureIndex]->pImage->layout);
				imageInfos[textureIndex].imageView = InheritCast<VulkanImageView>(pTextures[textureIndex]->pImage->pImageView);
				imageInfos[textureIndex].sampler = InheritCast<VulkanImageSampler>(pTextures[textureIndex]->pSampler);
				descriptorWrite.pImageInfo = imageInfos.location(textureIndex);
				textureIndex++;
				break;

			case VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER:
				DMK_ERROR("Dynamik Currently Does Not Support This Feature (VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER)");
				break;

			case VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER:
				DMK_ERROR("Dynamik Currently Does Not Support This Feature (VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER)");
				break;

			case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER:
				if (!pBuffers.isValidIndex(bufferIndex))
				{
					DMK_ERROR("A uniform entry is not supplied!");
					bufferIndex++;
					break;
				}

				bufferInfos[bufferIndex].buffer = InheritCast<VulkanBuffer>(pBuffers[bufferIndex]);
				bufferInfos[bufferIndex].range = pBuffers[bufferIndex]->getSize();
				bufferInfos[bufferIndex].offset = 0;	/* TODO */
				descriptorWrite.pBufferInfo = bufferInfos.location(bufferIndex);
				bufferIndex++;
				break;

			case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER:
				if (!pBuffers.isValidIndex(bufferIndex))
				{
					DMK_ERROR("A uniform entry is not supplied!");
					bufferIndex++;
					break;
				}

				bufferInfos[bufferIndex].buffer = InheritCast<VulkanBuffer>(pBuffers[bufferIndex]);
				bufferInfos[bufferIndex].range = pBuffers[bufferIndex]->getSize();
				bufferInfos[bufferIndex].offset = 0;	/* TODO */
				descriptorWrite.pBufferInfo = bufferInfos.location(bufferIndex);
				bufferIndex++;
				break;

			case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC:
				if (!pBuffers.isValidIndex(bufferIndex))
				{
					DMK_ERROR("A uniform entry is not supplied!");
					bufferIndex++;
					break;
				}

				bufferInfos[bufferIndex].buffer = InheritCast<VulkanBuffer>(pBuffers[bufferIndex]);
				bufferInfos[bufferIndex].range = pBuffers[bufferIndex]->getSize();
				bufferInfos[bufferIndex].offset = 0;	/* TODO */
				descriptorWrite.pBufferInfo = bufferInfos.location(bufferIndex);
				bufferIndex++;
				break;

			case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC:
				if (!pBuffers.isValidIndex(bufferIndex))
				{
					DMK_ERROR("A uniform entry is not supplied!");
					bufferIndex++;
					break;
				}

				bufferInfos[bufferIndex].buffer = InheritCast<VulkanBuffer>(pBuffers[bufferIndex]);
				bufferInfos[bufferIndex].range = pBuffers[bufferIndex]->getSize();
				bufferInfos[bufferIndex].offset = 0;	/* TODO */
				descriptorWrite.pBufferInfo = bufferInfos.location(bufferIndex);
				bufferIndex++;
				break;

			case VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT:
				DMK_ERROR("Dynamik Currently Does Not Support This Feature (VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT)");
				break;

			case VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK_EXT:
				DMK_ERROR("Dynamik Currently Does Not Support This Feature (VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK_EXT)");
				break;

			case VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV:
				DMK_ERROR("Dynamik Currently Does Not Support This Feature (VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV)");
				break;

			default:
				DMK_ERROR_BOX("Invalid Vulkan Descriptor Type!");
				break;
			}

			descriptorWrites.pushBack(descriptorWrite);
		}

		vkUpdateDescriptorSets(pCoreObject->getAs<VulkanCoreObject>()->device, Cast<UI32>(descriptorWrites.size()), descriptorWrites.data(), 0, VK_NULL_HANDLE);
	}

	void VulkanGraphicsPipeline::initialize(RCoreObject* pCoreObject, RPipelineSpecification createInfo, RPipelineUsage usage, RRenderTarget* pRenderTarget, DMKViewport viewport)
	{
		if (usage != RPipelineUsage::PIPELINE_USAGE_GRAPHICS)
		{
			DMK_ERROR_BOX("Invalid Pipeline Usage!");
			return;
		}

		mySpecification = createInfo;

		ARRAY<VulkanResourceLayout> resourceLayouts;
		ARRAY<VkDescriptorPoolSize> descriptorPoolSizes;
		ARRAY<VkPushConstantRange> pushConstants;

		/* Initialize Vertex Input Info */
		VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
		vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertexInputInfo.flags = VK_NULL_HANDLE;
		vertexInputInfo.pNext = VK_NULL_HANDLE;

		/* Resolve Shaders */
		ARRAY<VkPipelineShaderStageCreateInfo> shaderStages;
		VkPipelineShaderStageCreateInfo shaderStage = {};
		shaderStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		shaderStage.flags = VK_NULL_HANDLE;
		shaderStage.pNext = VK_NULL_HANDLE;
		shaderStage.pSpecializationInfo = VK_NULL_HANDLE;

		resourceLayouts.resize(createInfo.shaders.size());
		for (UI32 index = 0; index < createInfo.shaders.size(); index++)
		{
			shaderStage.pName = "main";
			shaderStage.module = VulkanUtilities::createShaderModule(pCoreObject, createInfo.shaders[index]);
			shaderStage.stage = VulkanUtilities::getShaderStage(createInfo.shaders[index].location);
			shaderStages.pushBack(shaderStage);

			resourceBindings.insert(GetDescriptorSetLayoutBindings(createInfo.shaders[index].getUniforms(), createInfo.shaders[index].location));
			descriptorPoolSizes.insert(GetDescriptorPoolSizes(createInfo.shaders[index].getUniforms(), createInfo.shaders[index].location));

			pushConstants.insert(GetPushConstantRanges(createInfo.shaders[index].getUniforms(), createInfo.shaders[index].location));

			if (createInfo.shaders[index].location == DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX)
			{
				resourceLayouts[index].vertexInputBindings.insert(VulkanUtilities::getVertexBindingDescriptions(createInfo.shaders[index]));
				resourceLayouts[index].vertexInputAttributes = VulkanUtilities::getVertexAttributeDescriptions(createInfo.shaders[index]);

				vertexInputInfo.vertexBindingDescriptionCount = Cast<UI32>(resourceLayouts[index].vertexInputBindings.size());
				vertexInputInfo.pVertexBindingDescriptions = resourceLayouts[index].vertexInputBindings.data();
				vertexInputInfo.vertexAttributeDescriptionCount = (UI32)resourceLayouts[index].vertexInputAttributes.size();
				vertexInputInfo.pVertexAttributeDescriptions = resourceLayouts[index].vertexInputAttributes.data();
			}
		}

		/* Resolve push constant offsets */
		UI64 _pushConstantOffset = 0;
		for (UI32 itr = 0; itr < pushConstants.size(); itr++)
		{
			pushConstants[itr].offset = Cast<UI32>(_pushConstantOffset);
			_pushConstantOffset += pushConstants[itr].size;
		}

		/* Initialize Pipeline Layout */
		VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo = {};
		pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutCreateInfo.flags = VK_NULL_HANDLE;
		pipelineLayoutCreateInfo.pNext = VK_NULL_HANDLE;
		pipelineLayoutCreateInfo.pushConstantRangeCount = Cast<UI32>(pushConstants.size());
		pipelineLayoutCreateInfo.pPushConstantRanges = pushConstants.data();
		pipelineLayoutCreateInfo.setLayoutCount = 0;
		pipelineLayoutCreateInfo.pSetLayouts = nullptr;

		/* Create Constant Blocks */
		for (auto entry : pushConstants)
		{
			PConstantBlock newBlock;
			newBlock.byteSize = entry.size;
			newBlock.location = VulkanUtilities::getShaderLocation(Cast<VkShaderStageFlagBits>(entry.stageFlags));
			newBlock.offset = entry.offset;
			constantBlocks.pushBack(newBlock);
		}

		if ((resourceBindings.size() > 0) && (descriptorPoolSizes.size() > 0))
		{
			/* Resolve the descriptor data. */
			{
				/* Descriptor set layout */
				for (UI64 index = 0; index < resourceBindings.size(); index++)
					resourceBindings[index].descriptorCount = Cast<UI32>(createInfo.resourceCount);

				/* Descriptor pool */
				for (UI64 index = 0; index < descriptorPoolSizes.size(); index++)
					descriptorPoolSizes[index].descriptorCount = Cast<UI32>(createInfo.resourceCount);
			}

			/* Create descriptor set layout */
			VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo = {};
			descriptorSetLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
			descriptorSetLayoutCreateInfo.flags = VK_NULL_HANDLE;
			descriptorSetLayoutCreateInfo.pNext = VK_NULL_HANDLE;
			descriptorSetLayoutCreateInfo.bindingCount = Cast<UI32>(resourceBindings.size());
			descriptorSetLayoutCreateInfo.pBindings = resourceBindings.data();

			DMK_VULKAN_ASSERT(vkCreateDescriptorSetLayout(pCoreObject->getAs<VulkanCoreObject>()->device, &descriptorSetLayoutCreateInfo, nullptr, &descriptor.layout), "Failed to create descriptor set layout!");

			/* Create descriptor pool */
			VkDescriptorPoolCreateInfo descriptorPoolCreateInfo = {};
			descriptorPoolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
			descriptorPoolCreateInfo.flags = VK_NULL_HANDLE;
			descriptorPoolCreateInfo.pNext = VK_NULL_HANDLE;
			descriptorPoolCreateInfo.maxSets = Cast<UI32>(createInfo.resourceCount);
			descriptorPoolCreateInfo.poolSizeCount = Cast<UI32>(descriptorPoolSizes.size());
			descriptorPoolCreateInfo.pPoolSizes = descriptorPoolSizes.data();

			DMK_VULKAN_ASSERT(vkCreateDescriptorPool(pCoreObject->getAs<VulkanCoreObject>()->device, &descriptorPoolCreateInfo, VK_NULL_HANDLE, &descriptor.pool), "Failed to create descriptor pool!");

			pipelineLayoutCreateInfo.setLayoutCount = 1;
			pipelineLayoutCreateInfo.pSetLayouts = &descriptor.layout;
			isResourceAvailable = true;
		}

		DMK_VULKAN_ASSERT(vkCreatePipelineLayout(pCoreObject->getAs<VulkanCoreObject>()->device, &pipelineLayoutCreateInfo, VK_NULL_HANDLE, &layout), "Failed to create pipeline layout!");

		/* Initialize Primitive Assembly Info */
		VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
		inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		inputAssembly.flags = VK_NULL_HANDLE;
		inputAssembly.pNext = VK_NULL_HANDLE;
		inputAssembly.topology = (VkPrimitiveTopology)createInfo.primitiveAssemblyInfo.primitiveTopology;
		inputAssembly.primitiveRestartEnable = createInfo.primitiveAssemblyInfo.enablePrimitiveRestart;

		/* Initialize Tessellation Control State */
		VkPipelineTessellationStateCreateInfo tessellationState = {};
		tessellationState.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
		tessellationState.flags = VK_NULL_HANDLE;
		tessellationState.pNext = VK_NULL_HANDLE;
		tessellationState.patchControlPoints = createInfo.tessellationStateControlInfo.patchControlPoints;

		/* Initialize View Port */
		VkViewport vViewport = {};
		vViewport.x = (F32)viewport.xOffset;
		vViewport.y = (F32)viewport.yOffset;
		vViewport.width = Cast<F32>(viewport.width);
		vViewport.height = Cast<F32>(viewport.height);
		vViewport.minDepth = 0.0f;
		vViewport.maxDepth = 1.0f;

		/* Initialize Scissors */
		ARRAY<VkRect2D> scissors = {};
		for (auto scissor : createInfo.scissorInfos) {
			VkRect2D vScissor = {};
			vScissor.offset.x = (I32)scissor.offset.x;
			vScissor.offset.y = (I32)scissor.offset.y;
			vScissor.extent.width = (UI32)viewport.width;
			vScissor.extent.height = (UI32)viewport.height;

			scissors.pushBack(vScissor);
		}

		/* Initialize View Port State */
		VkPipelineViewportStateCreateInfo viewportState = {};
		viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewportState.flags = VK_NULL_HANDLE;
		viewportState.pNext = VK_NULL_HANDLE;
		viewportState.scissorCount = (UI32)scissors.size();
		viewportState.pScissors = scissors.data();
		viewportState.viewportCount = 1;
		viewportState.pViewports = &vViewport;

		/* Initialize Rasterizer */
		VkPipelineRasterizationStateCreateInfo rasterizer = {};
		rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterizer.flags = VK_NULL_HANDLE;
		rasterizer.pNext = VK_NULL_HANDLE;
		rasterizer.cullMode = (VkCullModeFlags)createInfo.rasterizerInfo.cullMode;
		rasterizer.depthClampEnable = createInfo.rasterizerInfo.depthClampEnable;
		rasterizer.depthBiasEnable = createInfo.rasterizerInfo.depthBiasEnable;
		rasterizer.frontFace = (VkFrontFace)createInfo.rasterizerInfo.frontFace;
		rasterizer.lineWidth = createInfo.rasterizerInfo.lineWidth;
		rasterizer.polygonMode = (VkPolygonMode)createInfo.rasterizerInfo.polygonMode;
		rasterizer.rasterizerDiscardEnable = createInfo.rasterizerInfo.discardEnable;
		rasterizer.depthBiasConstantFactor = createInfo.rasterizerInfo.constantFactor;
		rasterizer.depthBiasSlopeFactor = createInfo.rasterizerInfo.slopeFactor;

		/* Initialize Multi Sampling */
		VkPipelineMultisampleStateCreateInfo multisampling = {};
		multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		multisampling.flags = VK_NULL_HANDLE;
		multisampling.pNext = VK_NULL_HANDLE;
		multisampling.pSampleMask = VK_NULL_HANDLE;
		multisampling.rasterizationSamples = (VkSampleCountFlagBits)createInfo.multiSamplingInfo.sampleCount;
		multisampling.sampleShadingEnable = createInfo.multiSamplingInfo.enableSampleShading;
		multisampling.minSampleShading = createInfo.multiSamplingInfo.minSampleShading;
		multisampling.alphaToCoverageEnable = createInfo.multiSamplingInfo.enableAlphaToCoverage;
		multisampling.alphaToOneEnable = createInfo.multiSamplingInfo.enableAlphaToOne;

		/* Initialize Depth Stencil */
		VkPipelineDepthStencilStateCreateInfo depthStencil = {};
		depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		depthStencil.flags = VK_NULL_HANDLE;
		depthStencil.pNext = VK_NULL_HANDLE;
		depthStencil.depthTestEnable = createInfo.depthStencilInfo.enableStencil;
		depthStencil.stencilTestEnable = createInfo.depthStencilInfo.enableStencilTests;
		depthStencil.depthWriteEnable = createInfo.depthStencilInfo.enableWrite;
		depthStencil.depthBoundsTestEnable = createInfo.depthStencilInfo.enableBoundsTest;
		depthStencil.depthCompareOp = (VkCompareOp)createInfo.depthStencilInfo.compareOp;
		depthStencil.front = VulkanUtilities::getStencilOpState(createInfo.depthStencilInfo.frontOpState);
		depthStencil.back = VulkanUtilities::getStencilOpState(createInfo.depthStencilInfo.backOpState);
		depthStencil.maxDepthBounds = createInfo.depthStencilInfo.maxBounds;
		depthStencil.minDepthBounds = createInfo.depthStencilInfo.minBounds;

		/* Initialize Color Blend */
		VkPipelineColorBlendStateCreateInfo colorBlending = {};
		colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		colorBlending.flags = VK_NULL_HANDLE;
		colorBlending.pNext = VK_NULL_HANDLE;
		colorBlending.logicOpEnable = createInfo.colorBlendInfo.enableColorBlendLogicOp;
		colorBlending.logicOp = (VkLogicOp)createInfo.colorBlendInfo.blendLogicOp;
		colorBlending.blendConstants[0] = createInfo.colorBlendInfo.blendConstants[0];
		colorBlending.blendConstants[1] = createInfo.colorBlendInfo.blendConstants[1];
		colorBlending.blendConstants[2] = createInfo.colorBlendInfo.blendConstants[2];
		colorBlending.blendConstants[3] = createInfo.colorBlendInfo.blendConstants[3];

		auto blendAttachments = VulkanUtilities::getBlendStates(createInfo.colorBlendInfo.blendStates);
		colorBlending.attachmentCount = (UI32)blendAttachments.size();
		colorBlending.pAttachments = blendAttachments.data();

		/* Initialize Dynamic States */
		VkPipelineDynamicStateCreateInfo dynamicState = {};
		dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		dynamicState.flags = VK_NULL_HANDLE;
		dynamicState.pNext = VK_NULL_HANDLE;

		auto dynamicStates = VulkanUtilities::getDynamicStates(createInfo.dynamicStates);
		dynamicState.dynamicStateCount = (UI32)dynamicStates.size();
		dynamicState.pDynamicStates = dynamicStates.data();

		/* Initialize Pipeline */
		VkGraphicsPipelineCreateInfo pipelineInfo = {};
		pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipelineInfo.flags = VK_PIPELINE_CREATE_ALLOW_DERIVATIVES_BIT;
		pipelineInfo.pNext = VK_NULL_HANDLE;
		pipelineInfo.stageCount = (UI32)shaderStages.size();
		pipelineInfo.pStages = shaderStages.data();
		pipelineInfo.pInputAssemblyState = &inputAssembly;
		pipelineInfo.pVertexInputState = &vertexInputInfo;
		pipelineInfo.pTessellationState = &tessellationState;
		pipelineInfo.pViewportState = &viewportState;
		pipelineInfo.pRasterizationState = &rasterizer;
		pipelineInfo.pMultisampleState = &multisampling;
		pipelineInfo.pDepthStencilState = &depthStencil;
		pipelineInfo.pColorBlendState = &colorBlending;
		pipelineInfo.pDynamicState = &dynamicState;
		pipelineInfo.subpass = 0;
		pipelineInfo.basePipelineIndex = 0;
		pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;	/* TODO */
		pipelineInfo.layout = layout;
		pipelineInfo.renderPass = VK_NULL_HANDLE;

		if (pRenderTarget)
			pipelineInfo.renderPass = InheritCast<VulkanRenderPass>(pRenderTarget->pRenderPass).renderPass;


		if (createInfo.pPipelineCache)
		{
			if (*createInfo.pPipelineCache)
			{
				if (pipelineCache == VK_NULL_HANDLE)
					pipelineCache = Cast<VkPipelineCache>(*createInfo.pPipelineCache);
				else
				{
					vkDestroyPipelineCache(pCoreObject->getAs<VulkanCoreObject>()->device, pipelineCache, nullptr);
					pipelineCache = Cast<VkPipelineCache>(*createInfo.pPipelineCache);
				}
			}
			else
			{
				if (pipelineCache == VK_NULL_HANDLE)
					createPipelineCache(pCoreObject, sizeof(pipelineInfo), &pipelineInfo);

				*createInfo.pPipelineCache = Cast<VPTR>(pipelineCache);
			}
		}
		else
			if (pipelineCache == VK_NULL_HANDLE)
				createPipelineCache(pCoreObject, sizeof(pipelineInfo), &pipelineInfo);

		DMK_VULKAN_ASSERT(vkCreateGraphicsPipelines(pCoreObject->getAs<VulkanCoreObject>()->device, pipelineCache, 1, &pipelineInfo, VK_NULL_HANDLE, &pipeline), "Failed to create graphics pipeline!");

		/* Terminate Shader Modules */
		for (auto stage : shaderStages)
			vkDestroyShaderModule(pCoreObject->getAs<VulkanCoreObject>()->device, stage.module, nullptr);
	}

	void VulkanGraphicsPipeline::reCreate(RCoreObject* pCoreObject, RRenderTarget* pRenderTarget, DMKViewport viewport)
	{
		/* Initialize Vertex Input Info */
		VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
		vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertexInputInfo.flags = VK_NULL_HANDLE;
		vertexInputInfo.pNext = VK_NULL_HANDLE;

		/* Resolve Shaders */
		ARRAY<VkPipelineShaderStageCreateInfo> shaderStages;
		VkPipelineShaderStageCreateInfo shaderStage = {};
		shaderStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		shaderStage.flags = VK_NULL_HANDLE;
		shaderStage.pNext = VK_NULL_HANDLE;
		shaderStage.pSpecializationInfo = VK_NULL_HANDLE;

		ARRAY<VulkanResourceLayout> resourceLayouts(mySpecification.shaders.size());
		for (UI32 index = 0; index < mySpecification.shaders.size(); index++)
		{
			shaderStage.pName = "main";
			shaderStage.module = VulkanUtilities::createShaderModule(pCoreObject, mySpecification.shaders[index]);
			shaderStage.stage = VulkanUtilities::getShaderStage(mySpecification.shaders[index].location);
			shaderStages.pushBack(shaderStage);

			resourceBindings.insert(GetDescriptorSetLayoutBindings(mySpecification.shaders[index].getUniforms(), mySpecification.shaders[index].location));

			if (mySpecification.shaders[index].location == DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX)
			{
				resourceLayouts[index].vertexInputBindings.insert(VulkanUtilities::getVertexBindingDescriptions(mySpecification.shaders[index]));
				resourceLayouts[index].vertexInputAttributes = VulkanUtilities::getVertexAttributeDescriptions(mySpecification.shaders[index]);

				vertexInputInfo.vertexBindingDescriptionCount = Cast<UI32>(resourceLayouts[index].vertexInputBindings.size());
				vertexInputInfo.pVertexBindingDescriptions = resourceLayouts[index].vertexInputBindings.data();
				vertexInputInfo.vertexAttributeDescriptionCount = (UI32)resourceLayouts[index].vertexInputAttributes.size();
				vertexInputInfo.pVertexAttributeDescriptions = resourceLayouts[index].vertexInputAttributes.data();
			}
		}

		/* Initialize Primitive Assembly Info */
		VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
		inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		inputAssembly.flags = VK_NULL_HANDLE;
		inputAssembly.pNext = VK_NULL_HANDLE;
		inputAssembly.topology = (VkPrimitiveTopology)mySpecification.primitiveAssemblyInfo.primitiveTopology;
		inputAssembly.primitiveRestartEnable = mySpecification.primitiveAssemblyInfo.enablePrimitiveRestart;

		/* Initialize Tessellation Control State */
		VkPipelineTessellationStateCreateInfo tessellationState = {};
		tessellationState.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
		tessellationState.flags = VK_NULL_HANDLE;
		tessellationState.pNext = VK_NULL_HANDLE;
		tessellationState.patchControlPoints = (UI32)mySpecification.tessellationStateControlInfo.patchControlPoints;

		/* Initialize View Port */
		VkViewport vViewport = {};
		vViewport.x = (F32)viewport.xOffset;
		vViewport.y = (F32)viewport.yOffset;
		vViewport.width = Cast<F32>(viewport.width);
		vViewport.height = Cast<F32>(viewport.height);
		vViewport.minDepth = 0.0f;
		vViewport.maxDepth = 1.0f;

		/* Initialize Scissors */
		ARRAY<VkRect2D> scissors = {};
		for (auto scissor : mySpecification.scissorInfos) {
			VkRect2D vScissor = {};
			vScissor.offset.x = (I32)scissor.offset.x;
			vScissor.offset.y = (I32)scissor.offset.y;
			vScissor.extent.width = (UI32)viewport.width;
			vScissor.extent.height = (UI32)viewport.height;

			scissors.pushBack(vScissor);
		}

		/* Initialize View Port State */
		VkPipelineViewportStateCreateInfo viewportState = {};
		viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewportState.flags = VK_NULL_HANDLE;
		viewportState.pNext = VK_NULL_HANDLE;
		viewportState.scissorCount = (UI32)scissors.size();
		viewportState.pScissors = scissors.data();
		viewportState.viewportCount = 1;
		viewportState.pViewports = &vViewport;

		/* Initialize Rasterizer */
		VkPipelineRasterizationStateCreateInfo rasterizer = {};
		rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterizer.flags = VK_NULL_HANDLE;
		rasterizer.pNext = VK_NULL_HANDLE;
		rasterizer.cullMode = (VkCullModeFlags)mySpecification.rasterizerInfo.cullMode;
		rasterizer.depthClampEnable = mySpecification.rasterizerInfo.depthClampEnable;
		rasterizer.depthBiasEnable = mySpecification.rasterizerInfo.depthBiasEnable;
		rasterizer.frontFace = (VkFrontFace)mySpecification.rasterizerInfo.frontFace;
		rasterizer.lineWidth = mySpecification.rasterizerInfo.lineWidth;
		rasterizer.polygonMode = (VkPolygonMode)mySpecification.rasterizerInfo.polygonMode;
		rasterizer.rasterizerDiscardEnable = mySpecification.rasterizerInfo.discardEnable;
		rasterizer.depthBiasConstantFactor = mySpecification.rasterizerInfo.constantFactor;
		rasterizer.depthBiasSlopeFactor = mySpecification.rasterizerInfo.slopeFactor;

		/* Initialize Multi Sampling */
		VkPipelineMultisampleStateCreateInfo multisampling = {};
		multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		multisampling.flags = VK_NULL_HANDLE;
		multisampling.pNext = VK_NULL_HANDLE;
		multisampling.rasterizationSamples = (VkSampleCountFlagBits)mySpecification.multiSamplingInfo.sampleCount;
		multisampling.sampleShadingEnable = mySpecification.multiSamplingInfo.enableSampleShading;
		multisampling.minSampleShading = mySpecification.multiSamplingInfo.minSampleShading;
		multisampling.alphaToCoverageEnable = mySpecification.multiSamplingInfo.enableAlphaToCoverage;
		multisampling.alphaToOneEnable = mySpecification.multiSamplingInfo.enableAlphaToOne;

		/* Initialize Depth Stencil */
		VkPipelineDepthStencilStateCreateInfo depthStencil = {};
		depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		depthStencil.flags = VK_NULL_HANDLE;
		depthStencil.pNext = VK_NULL_HANDLE;
		depthStencil.depthTestEnable = mySpecification.depthStencilInfo.enableStencil;
		depthStencil.stencilTestEnable = mySpecification.depthStencilInfo.enableStencilTests;
		depthStencil.depthWriteEnable = mySpecification.depthStencilInfo.enableWrite;
		depthStencil.depthBoundsTestEnable = mySpecification.depthStencilInfo.enableBoundsTest;
		depthStencil.depthCompareOp = (VkCompareOp)mySpecification.depthStencilInfo.compareOp;
		depthStencil.front = VulkanUtilities::getStencilOpState(mySpecification.depthStencilInfo.frontOpState);
		depthStencil.back = VulkanUtilities::getStencilOpState(mySpecification.depthStencilInfo.backOpState);
		depthStencil.maxDepthBounds = mySpecification.depthStencilInfo.maxBounds;
		depthStencil.minDepthBounds = mySpecification.depthStencilInfo.minBounds;

		/* Initialize Color Blend */
		VkPipelineColorBlendStateCreateInfo colorBlending = {};
		colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		colorBlending.flags = VK_NULL_HANDLE;
		colorBlending.pNext = VK_NULL_HANDLE;
		colorBlending.logicOpEnable = mySpecification.colorBlendInfo.enableColorBlendLogicOp;
		colorBlending.logicOp = (VkLogicOp)mySpecification.colorBlendInfo.blendLogicOp;
		colorBlending.blendConstants[0] = mySpecification.colorBlendInfo.blendConstants[0];
		colorBlending.blendConstants[1] = mySpecification.colorBlendInfo.blendConstants[1];
		colorBlending.blendConstants[2] = mySpecification.colorBlendInfo.blendConstants[2];
		colorBlending.blendConstants[3] = mySpecification.colorBlendInfo.blendConstants[3];

		auto blendAttachments = VulkanUtilities::getBlendStates(mySpecification.colorBlendInfo.blendStates);
		colorBlending.attachmentCount = (UI32)blendAttachments.size();
		colorBlending.pAttachments = blendAttachments.data();

		/* Initialize Dynamic States */
		VkPipelineDynamicStateCreateInfo dynamicState = {};
		dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		dynamicState.flags = VK_NULL_HANDLE;
		dynamicState.pNext = VK_NULL_HANDLE;

		auto dynamicStates = VulkanUtilities::getDynamicStates(mySpecification.dynamicStates);
		dynamicState.dynamicStateCount = (UI32)dynamicStates.size();
		dynamicState.pDynamicStates = dynamicStates.data();

		/* Initialize Pipeline */
		VkGraphicsPipelineCreateInfo pipelineInfo = {};
		pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipelineInfo.flags = VK_PIPELINE_CREATE_ALLOW_DERIVATIVES_BIT | VK_PIPELINE_CREATE_DERIVATIVE_BIT;
		pipelineInfo.pNext = VK_NULL_HANDLE;
		pipelineInfo.stageCount = (UI32)shaderStages.size();
		pipelineInfo.pStages = shaderStages.data();
		pipelineInfo.pInputAssemblyState = &inputAssembly;
		pipelineInfo.pVertexInputState = &vertexInputInfo;
		pipelineInfo.pTessellationState = &tessellationState;
		pipelineInfo.pViewportState = &viewportState;
		pipelineInfo.pRasterizationState = &rasterizer;
		pipelineInfo.pMultisampleState = &multisampling;
		pipelineInfo.pDepthStencilState = &depthStencil;
		pipelineInfo.pColorBlendState = &colorBlending;
		pipelineInfo.pDynamicState = &dynamicState;
		pipelineInfo.subpass = 0;
		pipelineInfo.basePipelineIndex = -1;
		pipelineInfo.basePipelineHandle = pipeline;
		pipelineInfo.layout = layout;
		pipelineInfo.renderPass = VK_NULL_HANDLE;

		if (pRenderTarget)
			pipelineInfo.renderPass = InheritCast<VulkanRenderPass>(pRenderTarget->pRenderPass).renderPass;

		VkPipeline _newPipeline = VK_NULL_HANDLE;
		DMK_VULKAN_ASSERT(vkCreateGraphicsPipelines(pCoreObject->getAs<VulkanCoreObject>()->device, pipelineCache, 1, &pipelineInfo, VK_NULL_HANDLE, &_newPipeline), "Failed to create graphics pipeline!");

		/* Destroy the old pipeline */
		vkDestroyPipeline(pCoreObject->getAs<VulkanCoreObject>()->device, pipeline, nullptr);

		pipeline = _newPipeline;

		/* Terminate Shader Modules */
		for (auto stage : shaderStages)
			vkDestroyShaderModule(pCoreObject->getAs<VulkanCoreObject>()->device, stage.module, nullptr);
	}

	void VulkanGraphicsPipeline::terminate(RCoreObject* pCoreObject)
	{
		/* Terminate Descriptor */
		vkDestroyDescriptorPool(pCoreObject->getAs<VulkanCoreObject>()->device, descriptor.pool, nullptr);
		vkDestroyDescriptorSetLayout(pCoreObject->getAs<VulkanCoreObject>()->device, descriptor.layout, nullptr);

		/* Terminate Pipeline */
		vkDestroyPipeline(pCoreObject->getAs<VulkanCoreObject>()->device, pipeline, nullptr);
		vkDestroyPipelineLayout(pCoreObject->getAs<VulkanCoreObject>()->device, layout, nullptr);

		/* Terminate Pipeline Cache */
		vkDestroyPipelineCache(pCoreObject->getAs<VulkanCoreObject>()->device, pipelineCache, nullptr);
	}

	void VulkanGraphicsPipeline::createPipelineCache(RCoreObject* pCoreObject, UI64 byteSize, VPTR pData)
	{
		VkPipelineCacheCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
		createInfo.pNext = VK_NULL_HANDLE;
		createInfo.flags = VK_NULL_HANDLE;
		createInfo.initialDataSize = Cast<UI32>(byteSize);
		createInfo.pInitialData = pData;

		DMK_VULKAN_ASSERT(vkCreatePipelineCache(pCoreObject->getAs<VulkanCoreObject>()->device, &createInfo, nullptr, &pipelineCache), "Failed to create pipeline cache!");
	}

	ARRAY<RPipelineResource*> VulkanGraphicsPipeline::allocateResources(RCoreObject* pCoreObject)
	{
		ARRAY<VkDescriptorSetLayout> _descriptorLayouts(mySpecification.resourceCount, descriptor.layout);

		VkDescriptorSetAllocateInfo descriptorSetAllocateInfo = {};
		descriptorSetAllocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		descriptorSetAllocateInfo.pNext = VK_NULL_HANDLE;
		descriptorSetAllocateInfo.descriptorPool = descriptor.pool;
		descriptorSetAllocateInfo.pSetLayouts = _descriptorLayouts.data();
		descriptorSetAllocateInfo.descriptorSetCount = Cast<UI32>(mySpecification.resourceCount);

		ARRAY<VkDescriptorSet> _descriptors(mySpecification.resourceCount);
		DMK_VULKAN_ASSERT(vkAllocateDescriptorSets(pCoreObject->getAs<VulkanCoreObject>()->device, &descriptorSetAllocateInfo, _descriptors.data()), "Failed to allocate descriptor sets!");

		ARRAY<RPipelineResource*> resources;

		for (auto descriptor : _descriptors)
		{
			VulkanGraphicsPipelineResource* pResource = StaticAllocator<VulkanGraphicsPipelineResource>::allocate();
			pResource->resourceBindings = resourceBindings;
			pResource->set = descriptor;

			resources.pushBack(pResource);
		}

		return resources;
	}

	void VulkanGraphicsPipeline::deallocateResources(ARRAY<RPipelineResource*> resources)
	{
		for (UI32 index = 0; index < resources.size(); index++)
			StaticAllocator<VulkanGraphicsPipelineResource>::deallocate(resources[index]);
	}

	VulkanGraphicsPipeline::operator VkPipelineLayout() const
	{
		return this->layout;
	}

	VulkanGraphicsPipeline::operator VkPipeline() const
	{
		return this->pipeline;
	}
}
