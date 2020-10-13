// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanPipelineManager.h"

#include "../VulkanUtilities.h"

namespace Backend
{
	VulkanPipelineContainer VulkanPipelineManager::createGraphicsPipeline(const VulkanDevice& vDevice, VulkanGraphicsPipelineInitInfo info)
	{
		VulkanPipelineContainer _container;
		_container.bindPoint = VkPipelineBindPoint::VK_PIPELINE_BIND_POINT_GRAPHICS;

		/* Initialize the pipeline layout */
		VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = (UI32)info.descriptorLayouts.size();
		pipelineLayoutInfo.pSetLayouts = info.descriptorLayouts.data();

		pipelineLayoutInfo.pushConstantRangeCount = (UI32)info.constantBlockDescriptions.size();
		std::vector<VkPushConstantRange> pushConstantRanges;
		for (auto _block : info.constantBlockDescriptions)
		{
			VkPushConstantRange _range;
			_range.size = (UI32)_block.getBlockSize();
			_range.offset = _block.offset;
			_range.stageFlags = VulkanUtilities::getShaderStage(_block.location);

			pushConstantRanges.push_back(_range);
		}
		pipelineLayoutInfo.pPushConstantRanges = pushConstantRanges.data();

		DMK_VULKAN_ASSERT(vkCreatePipelineLayout(vDevice, &pipelineLayoutInfo, VK_NULL_HANDLE, &_container.layout), "Failed to create pipeline layout!");

		/* Initialize the pipeline */
		VkVertexInputBindingDescription vertexBindingDescription;
		vertexBindingDescription.binding = 0;
		vertexBindingDescription.stride = (UI32)info.vertexBufferDescriptor.getVertexSize();
		vertexBindingDescription.inputRate = VkVertexInputRate::VK_VERTEX_INPUT_RATE_VERTEX;

		auto vertexAttributeDescription = VulkanUtilities::getVertexAttributeDescriptions(info.vertexBufferDescriptor);

		VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
		vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertexInputInfo.vertexBindingDescriptionCount = 1;
		vertexInputInfo.vertexAttributeDescriptionCount = (UI32)vertexAttributeDescription.size();
		vertexInputInfo.pVertexBindingDescriptions = &vertexBindingDescription;
		vertexInputInfo.pVertexAttributeDescriptions = vertexAttributeDescription.data();

		VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
		inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		inputAssembly.topology = info.inputAssemblyTopology;
		inputAssembly.primitiveRestartEnable = info.inputAssemblyPrimitiveRestartEnable;

		std::vector<VkViewport> viewports;
		for (I32 i = 0; i < info.viewports.size(); i++) {
			VkViewport viewport = {};
			viewport.x = (float)info.viewports[i].xOffset;
			viewport.y = (float)info.viewports[i].yOffset;
			//viewport.width = (float)info.viewports[i].width;
			//viewport.height = (float)info.viewports[i].height;
			viewport.width = (float)info.swapChainExtent.width;
			viewport.height = (float)info.swapChainExtent.height;
			viewport.minDepth = 0.0f;
			viewport.maxDepth = 1.0f;

			viewports.push_back(viewport);
		}

		// initialize the scissor(s)
		std::vector<VkRect2D> scissors;
		for (UI32 i = 0; i < info.scissorCount; i++) {
			VkRect2D scissor = {};
			scissor.offset = info.offsets[i];
			scissor.extent = info.swapChainExtent;

			scissors.push_back(scissor);
		}
		// initialize the viewport state
		VkPipelineViewportStateCreateInfo viewportState = {};
		viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewportState.viewportCount = (UI32)info.viewports.size();
		viewportState.pViewports = viewports.data();
		viewportState.scissorCount = info.scissorCount;
		viewportState.pScissors = scissors.data();

		// initialize the rasterizer
		VkPipelineRasterizationStateCreateInfo rasterizer = {};
		rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterizer.depthClampEnable = info.rasterizerDepthClampEnable;
		rasterizer.rasterizerDiscardEnable = info.rasterizerDiscardEnable;
		rasterizer.polygonMode = info.rasterizerPolygonMode;
		rasterizer.lineWidth = info.rasterizerLineWidth;
		rasterizer.cullMode = info.rasterizerCullMode;
		rasterizer.frontFace = info.rasterizerFrontFace;

		rasterizer.depthBiasEnable = info.rasterizerDepthBiasEnable;

		// initialize multisampling
		VkPipelineMultisampleStateCreateInfo multisampling = {};
		multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		multisampling.rasterizationSamples = info.multisamplerMsaaSamples;
		multisampling.sampleShadingEnable = info.multisamplerSampleShadingEnable; // enable sample shading in the pipeline
		multisampling.minSampleShading = info.multisamplerMinSampleShading; // min fraction for sample shading; closer to one is smoother

		VkPipelineDepthStencilStateCreateInfo depthStencil = {};
		depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		depthStencil.depthTestEnable = info.depthStencilEnable;
		depthStencil.depthWriteEnable = info.depthStencilWriteEnable;
		depthStencil.depthCompareOp = info.depthStencilCompareOp;
		depthStencil.depthBoundsTestEnable = info.depthStencilBoundsTestEnable;
		depthStencil.stencilTestEnable = info.depthStencilTestEnable;

		std::vector<VkPipelineColorBlendAttachmentState> colorBlendAttachments;

		// initialize the color blender(s)
		for (UI32 i = 0; i < info.colorBlendingColorBlendCount; i++) {
			VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
			colorBlendAttachment.colorWriteMask = info.colorBlenderColorWriteMasks[i];
			colorBlendAttachment.blendEnable = info.colorBlenderBlendEnables[i];

			colorBlendAttachments.push_back(colorBlendAttachment);
		}

		for (VkPipelineColorBlendAttachmentState _state : info.additionalColorBlendStates)
			colorBlendAttachments.push_back(_state);

		// initialize the color blender state
		VkPipelineColorBlendStateCreateInfo colorBlending = {};
		colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		colorBlending.logicOpEnable = info.colorBlendingLogicOpEnable;
		colorBlending.logicOp = info.colorBlendingLogicOp;
		colorBlending.attachmentCount = (UI32)colorBlendAttachments.size();
		colorBlending.pAttachments = colorBlendAttachments.data();
		colorBlending.blendConstants[0] = info.colorBlendingBlendConstants[0];
		colorBlending.blendConstants[1] = info.colorBlendingBlendConstants[1];
		colorBlending.blendConstants[2] = info.colorBlendingBlendConstants[2];
		colorBlending.blendConstants[3] = info.colorBlendingBlendConstants[3];

		// initialize dynamic state
		VkPipelineDynamicStateCreateInfo dynamicStateInfo = {};
		std::vector<VkDynamicState> dynamicState = {
			VK_DYNAMIC_STATE_VIEWPORT,
			VK_DYNAMIC_STATE_SCISSOR
		};
		if (info.dynamicStateEnable) {
			dynamicStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
			dynamicStateInfo.dynamicStateCount = Cast<UI32>(dynamicState.size());
			dynamicStateInfo.pDynamicStates = dynamicState.data();
			dynamicStateInfo.flags = info.dynamicStateFlags;
		}

		std::vector<VkPipelineShaderStageCreateInfo> shaderStages;
		for (auto _shader : info.shaders)
		{
			VkPipelineShaderStageCreateInfo shaderStageInfo;
			shaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			shaderStageInfo.flags = VK_NULL_HANDLE;
			shaderStageInfo.module = _shader;
			shaderStageInfo.pName = "main";
			shaderStageInfo.pNext = VK_NULL_HANDLE;
			shaderStageInfo.pSpecializationInfo = VK_NULL_HANDLE;
			shaderStageInfo.stage = _shader.stageFlag;

			shaderStages.push_back(shaderStageInfo);
		}

		// initialize the pipeline
		VkGraphicsPipelineCreateInfo pipelineInfo = {};
		pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipelineInfo.pNext = nullptr;
		pipelineInfo.stageCount = (UI32)shaderStages.size();
		pipelineInfo.pStages = shaderStages.data();
		pipelineInfo.pVertexInputState = &vertexInputInfo;
		pipelineInfo.pInputAssemblyState = &inputAssembly;
		pipelineInfo.pViewportState = &viewportState;
		pipelineInfo.pRasterizationState = &rasterizer;
		pipelineInfo.pMultisampleState = &multisampling;
		pipelineInfo.pDepthStencilState = &depthStencil;
		pipelineInfo.pColorBlendState = &colorBlending;
		pipelineInfo.subpass = info.pipelineSubPass;
		pipelineInfo.basePipelineHandle = info.pipelineBasePipelineHandle;
		pipelineInfo.basePipelineIndex = info.pipelineBasePipelineIndex;
		pipelineInfo.pTessellationState = nullptr;
		pipelineInfo.layout = _container.layout;
		pipelineInfo.renderPass = info.vRenderPass;
		pipelineInfo.flags = VK_PIPELINE_CREATE_ALLOW_DERIVATIVES_BIT;

		if (info.dynamicStateEnable)
			pipelineInfo.pDynamicState = &dynamicStateInfo;

		//if (myAllocatedInitInfos.find(info).size())
		//{
		//	auto _cache = myGraphicsPipelineCache[myAllocatedInitInfos.indexOf(info)];
		//	pipelineInfo.basePipelineHandle = _cache.basePipeline;
		//	pipelineInfo.basePipelineIndex = -1;
		//	pipelineInfo.flags = VK_PIPELINE_CREATE_DERIVATIVE_BIT;
		//	DMK_VULKAN_ASSERT(vkCreateGraphicsPipelines(vDevice, info.pipelineCache, 1, &pipelineInfo, VK_NULL_HANDLE, &_container.pipeline), "Failed to create graphics pipeline!");
		//}
		//else
		//{
		DMK_VULKAN_ASSERT(vkCreateGraphicsPipelines(vDevice, info.pipelineCache, 1, &pipelineInfo, VK_NULL_HANDLE, &_container.pipeline), "Failed to create graphics pipeline!");

		//	VulkanPipelineCache<VulkanGraphicsPipelineInitInfo> _cache;
		//	_cache.basePipeline = _container.pipeline;
		//	_cache.basePipelineLayout = _container.layout;
		//	_cache.initInfo = info;
		//	myGraphicsPipelineCache.push_back(_cache);
		//	myAllocatedInitInfos.push_back(info);
		//}

		return _container;
	}

	VulkanPipelineContainer VulkanPipelineManager::createRayTracingPipeline(const VulkanDevice& vDevice, VulkanGraphicsPipelineInitInfo info)
	{
		VulkanPipelineContainer _container;
		_container.bindPoint = VkPipelineBindPoint::VK_PIPELINE_BIND_POINT_COMPUTE;

		return _container;
	}

	VulkanPipelineContainer VulkanPipelineManager::createComputePipeline(const VulkanDevice& vDevice, VulkanGraphicsPipelineInitInfo info)
	{
		VulkanPipelineContainer _container;
		_container.bindPoint = VkPipelineBindPoint::VK_PIPELINE_BIND_POINT_RAY_TRACING_NV;

		return _container;
	}
}