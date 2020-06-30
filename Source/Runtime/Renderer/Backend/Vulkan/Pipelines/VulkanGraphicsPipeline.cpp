// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanGraphicsPipeline.h"

#include "../VulkanUtilities.h"
#include "../VulkanCoreObject.h"
#include "Tools/Shader/SPIR-V/Disassembler.h"

namespace Dynamik
{
	namespace Backend
	{
		UI32 getAttributeSize(VkFormat format)
		{
			switch (format)
			{
			case VK_FORMAT_R32_SFLOAT:
				return sizeof(F32) * 1;
			case VK_FORMAT_R32G32_SFLOAT:
				return sizeof(F32) * 2;
			case VK_FORMAT_R32G32B32_SFLOAT:
				return sizeof(F32) * 3;
			case VK_FORMAT_R32G32B32A32_SFLOAT:
				return sizeof(F32) * 4;
			default:
				DMK_ERROR_BOX("Unsupported attribute size!");
				break;
			}

			return 0;
		}

		void VulkanGraphicsPipeline::initialize(RCoreObject* pCoreObject, RPipelineSpecification createInfo, RPipelineUsage usage, RRenderTarget* pRenderTarget, RSwapChain* pSwapChain)
		{
			if (usage != RPipelineUsage::PIPELINE_USAGE_GRAPHICS)
			{
				DMK_ERROR_BOX("Invalid Pipeline Usage!");
				return;
			}

			ARRAY<VkDescriptorSetLayout> descriptorLayouts;
			ARRAY<VulkanResourceLayout> resourceLayouts;

			/* Initialize Vertex Input Info */
			VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
			vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
			vertexInputInfo.flags = VK_NULL_HANDLE;
			vertexInputInfo.pNext = VK_NULL_HANDLE;
			vertexInputInfo.vertexBindingDescriptionCount = 1;

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

				resourceLayouts[index] = VulkanUtilities::getResourceLayout(createInfo.shaders[index].resourceLayout, createInfo.shaders[index].location);

				if (createInfo.shaders[index].location == DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX)
				{
					vertexInputInfo.pVertexBindingDescriptions = &resourceLayouts[index].vertexInputBinding;
					vertexInputInfo.vertexAttributeDescriptionCount = resourceLayouts[index].vertexInputAttributes.size();
					vertexInputInfo.pVertexAttributeDescriptions = resourceLayouts[index].vertexInputAttributes.data();
				}

				if ((resourceLayouts[index].descriptorBindings.size() < 1) && (resourceLayouts[index].descriptorPoolSizes.size() < 1))
					continue;

				VDescriptor descriptor;
				/* Create descriptor set layout */
				VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo = {};
				descriptorSetLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
				descriptorSetLayoutCreateInfo.flags = VK_NULL_HANDLE;
				descriptorSetLayoutCreateInfo.pNext = VK_NULL_HANDLE;
				descriptorSetLayoutCreateInfo.bindingCount = resourceLayouts[index].descriptorBindings.size();
				descriptorSetLayoutCreateInfo.pBindings = resourceLayouts[index].descriptorBindings.data();

				DMK_VULKAN_ASSERT(vkCreateDescriptorSetLayout(InheritCast<VulkanCoreObject>(pCoreObject).device, &descriptorSetLayoutCreateInfo, nullptr, &descriptor.layout), "Failed to create descriptor set layout!");

				/* Create descriptor pool */
				VkDescriptorPoolCreateInfo descriptorPoolCreateInfo = {};
				descriptorPoolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
				descriptorPoolCreateInfo.flags = VK_NULL_HANDLE;
				descriptorPoolCreateInfo.pNext = VK_NULL_HANDLE;
				descriptorPoolCreateInfo.maxSets = 1;
				descriptorPoolCreateInfo.poolSizeCount = resourceLayouts[index].descriptorPoolSizes.size();
				descriptorPoolCreateInfo.pPoolSizes = resourceLayouts[index].descriptorPoolSizes.data();

				DMK_VULKAN_ASSERT(vkCreateDescriptorPool(InheritCast<VulkanCoreObject>(pCoreObject).device, &descriptorPoolCreateInfo, VK_NULL_HANDLE, &descriptor.pool), "Failed to create descriptor pool!");

				/* Allocate descriptor set */
				VkDescriptorSetAllocateInfo descriptorSetAllocateInfo = {};
				descriptorSetAllocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
				descriptorSetAllocateInfo.pNext = VK_NULL_HANDLE;
				descriptorSetAllocateInfo.descriptorPool = descriptor.pool;
				descriptorSetAllocateInfo.pSetLayouts = &descriptor.layout;
				descriptorSetAllocateInfo.descriptorSetCount = 1;

				DMK_VULKAN_ASSERT(vkAllocateDescriptorSets(InheritCast<VulkanCoreObject>(pCoreObject).device, &descriptorSetAllocateInfo, &descriptor.set), "Failed to allocate descriptor sets!");

				descriptors.pushBack(descriptor);
				descriptorLayouts.pushBack(descriptor.layout);
			}

			/* Initialize Pipeline Layout */
			VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo = {};
			pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
			pipelineLayoutCreateInfo.flags = VK_NULL_HANDLE;
			pipelineLayoutCreateInfo.pNext = VK_NULL_HANDLE;
			pipelineLayoutCreateInfo.pushConstantRangeCount = 0;			/* TODO */
			pipelineLayoutCreateInfo.pPushConstantRanges = VK_NULL_HANDLE;	/* TODO */
			pipelineLayoutCreateInfo.setLayoutCount = descriptorLayouts.size();
			pipelineLayoutCreateInfo.pSetLayouts = descriptorLayouts.data();

			DMK_VULKAN_ASSERT(vkCreatePipelineLayout(InheritCast<VulkanCoreObject>(pCoreObject).device, &pipelineLayoutCreateInfo, VK_NULL_HANDLE, &layout), "Failed to create pipeline layout!");

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
			VkViewport viewport = {};
			viewport.x = (F32)pSwapChain->viewPort.xOffset;
			viewport.y = (F32)pSwapChain->viewPort.yOffset;
			viewport.width = (F32)pSwapChain->extent.width;
			viewport.height = (F32)pSwapChain->extent.height;
			viewport.minDepth = 0.0f;
			viewport.maxDepth = 1.0f;

			/* Initialize Scissors */
			ARRAY<VkRect2D> scissors = {};
			for (auto scissor : createInfo.scissorInfos) {
				VkRect2D vScissor = {};
				vScissor.offset.x = scissor.offset.x;
				vScissor.offset.y = scissor.offset.y;
				vScissor.extent.width = pSwapChain->extent.width;
				vScissor.extent.height = pSwapChain->extent.height;

				scissors.pushBack(vScissor);
			}

			/* Initialize View Port State */
			VkPipelineViewportStateCreateInfo viewportState = {};
			viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
			viewportState.flags = VK_NULL_HANDLE;
			viewportState.pNext = VK_NULL_HANDLE;
			viewportState.scissorCount = scissors.size();
			viewportState.pScissors = scissors.data();
			viewportState.viewportCount = 1;
			viewportState.pViewports = &viewport;

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
			colorBlending.attachmentCount = blendAttachments.size();
			colorBlending.pAttachments = blendAttachments.data();

			/* Initialize Dynamic States */
			VkPipelineDynamicStateCreateInfo dynamicState = {};
			dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
			dynamicState.flags = VK_NULL_HANDLE;
			dynamicState.pNext = VK_NULL_HANDLE;

			auto dynamicStates = VulkanUtilities::getDynamicStates(createInfo.dynamicStates);
			dynamicState.dynamicStateCount = dynamicStates.size();
			dynamicState.pDynamicStates = dynamicStates.data();

			/* Initialize Pipeline */
			VkGraphicsPipelineCreateInfo pipelineInfo = {};
			pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
			pipelineInfo.flags = VK_PIPELINE_CREATE_ALLOW_DERIVATIVES_BIT;
			pipelineInfo.pNext = VK_NULL_HANDLE;
			pipelineInfo.stageCount = shaderStages.size();
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
			pipelineInfo.renderPass = InheritCast<VulkanRenderPass>(pRenderTarget->pRenderPass).renderPass;

			DMK_VULKAN_ASSERT(vkCreateGraphicsPipelines(InheritCast<VulkanCoreObject>(pCoreObject).device, VK_NULL_HANDLE /* TODO */, 1, &pipelineInfo, VK_NULL_HANDLE, &pipeline), "Failed to create graphics pipeline!");
		}

		void VulkanGraphicsPipeline::terminate(RCoreObject* pCoreObject)
		{
			vkDestroyPipeline(InheritCast<VulkanCoreObject>(pCoreObject).device, pipeline, nullptr);
			vkDestroyPipelineLayout(InheritCast<VulkanCoreObject>(pCoreObject).device, layout, nullptr);
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
}
