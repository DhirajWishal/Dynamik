// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/Pipelines/RasterGraphicsPipeline.h"

#include "Core/Memory/Functions.h"

namespace DMK
{
	namespace VulkanBackend
	{
		namespace _Helpers
		{
			DMK_FORCEINLINE VkPrimitiveTopology GetPrimitiveTopology(GraphicsCore::PipelinePrimitiveTopology topology)
			{
				switch (topology)
				{
				case DMK::GraphicsCore::PipelinePrimitiveTopology::POINT_LIST:
					return VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_POINT_LIST;

				case DMK::GraphicsCore::PipelinePrimitiveTopology::LINE_LIST:
					return VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_LINE_LIST;

				case DMK::GraphicsCore::PipelinePrimitiveTopology::LINE_STRIP:
					return VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;

				case DMK::GraphicsCore::PipelinePrimitiveTopology::TRIANGLE_LIST:
					return VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

				case DMK::GraphicsCore::PipelinePrimitiveTopology::TRIANGLE_STRIP:
					return VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;

				case DMK::GraphicsCore::PipelinePrimitiveTopology::TRIANGLE_FAN:
					return VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN;

				case DMK::GraphicsCore::PipelinePrimitiveTopology::LINE_LIST_WITH_ADJACENCY:
					return VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY;

				case DMK::GraphicsCore::PipelinePrimitiveTopology::LINE_STRIP_WITH_ADJACENCY:
					return VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY;

				case DMK::GraphicsCore::PipelinePrimitiveTopology::TRIANGLE_LIST_WITH_ADJACENCY:
					return VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY;

				case DMK::GraphicsCore::PipelinePrimitiveTopology::TRIANGLE_STRIP_WITH_ADJACENCY:
					return VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY;

				case DMK::GraphicsCore::PipelinePrimitiveTopology::PATCH_LIST:
					return VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_PATCH_LIST;
				}

				return VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
			}

			DMK_FORCEINLINE VkCullModeFlags GetCullModeFlags(GraphicsCore::PipelineCullMode cullMode)
			{
				switch (cullMode)
				{
				case DMK::GraphicsCore::PipelineCullMode::NONE:
					return VkCullModeFlagBits::VK_CULL_MODE_NONE;

				case DMK::GraphicsCore::PipelineCullMode::FRONT:
					return VkCullModeFlagBits::VK_CULL_MODE_FRONT_BIT;

				case DMK::GraphicsCore::PipelineCullMode::BACK:
					return VkCullModeFlagBits::VK_CULL_MODE_BACK_BIT;

				case DMK::GraphicsCore::PipelineCullMode::FRONT_AND_BACK:
					return VkCullModeFlagBits::VK_CULL_MODE_FRONT_AND_BACK;
				}

				return VkCullModeFlagBits::VK_CULL_MODE_NONE;
			}

			DMK_FORCEINLINE VkFrontFace GetFrontFace(GraphicsCore::PipelinePrimitiveFrontFace frontFace)
			{
				switch (frontFace)
				{
				case DMK::GraphicsCore::PipelinePrimitiveFrontFace::COUNTER_CLOCKWISE:
					return VkFrontFace::VK_FRONT_FACE_COUNTER_CLOCKWISE;

				case DMK::GraphicsCore::PipelinePrimitiveFrontFace::CLOCKWISE:
					return VkFrontFace::VK_FRONT_FACE_CLOCKWISE;
				}

				return VkFrontFace::VK_FRONT_FACE_COUNTER_CLOCKWISE;
			}

			DMK_FORCEINLINE VkPolygonMode GetPolygonMode(GraphicsCore::PipelinePolygonMode mode)
			{
				switch (mode)
				{
				case DMK::GraphicsCore::PipelinePolygonMode::FILL:
					return VkPolygonMode::VK_POLYGON_MODE_FILL;

				case DMK::GraphicsCore::PipelinePolygonMode::LINE:
					return VkPolygonMode::VK_POLYGON_MODE_LINE;

				case DMK::GraphicsCore::PipelinePolygonMode::POINT:
					return VkPolygonMode::VK_POLYGON_MODE_POINT;

				case DMK::GraphicsCore::PipelinePolygonMode::FILL_RECTANGLE:
					return VkPolygonMode::VK_POLYGON_MODE_FILL_RECTANGLE_NV;
				}

				return VkPolygonMode::VK_POLYGON_MODE_FILL;
			}

			DMK_FORCEINLINE VkCompareOp GetCompareOp(CompareOperator op)
			{
				switch (op)
				{
				case DMK::CompareOperator::DONT_COMPARE:
					return VkCompareOp::VK_COMPARE_OP_NEVER;

				case DMK::CompareOperator::LESS:
					return VkCompareOp::VK_COMPARE_OP_LESS;

				case DMK::CompareOperator::EQUAL:
					return VkCompareOp::VK_COMPARE_OP_EQUAL;

				case DMK::CompareOperator::LESS_OR_EQUAL:
					return VkCompareOp::VK_COMPARE_OP_LESS_OR_EQUAL;

				case DMK::CompareOperator::GREATER:
					return VkCompareOp::VK_COMPARE_OP_GREATER;

				case DMK::CompareOperator::NOT_EQUAL:
					return VkCompareOp::VK_COMPARE_OP_NOT_EQUAL;

				case DMK::CompareOperator::GREATER_OR_EQUAL:
					return VkCompareOp::VK_COMPARE_OP_GREATER_OR_EQUAL;

				case DMK::CompareOperator::ALWAYS_TRUE:
					return VkCompareOp::VK_COMPARE_OP_ALWAYS;
				}

				return VkCompareOp::VK_COMPARE_OP_NEVER;
			}

			DMK_FORCEINLINE VkLogicOp GetLogicOp(LogicOperator op)
			{
				switch (op)
				{
				case DMK::LogicOperator::CLEAR:
					return VkLogicOp::VK_LOGIC_OP_CLEAR;

				case DMK::LogicOperator::AND:
					return VkLogicOp::VK_LOGIC_OP_AND;

				case DMK::LogicOperator::AND_REVERSE:
					return VkLogicOp::VK_LOGIC_OP_AND_REVERSE;

				case DMK::LogicOperator::COPY:
					return VkLogicOp::VK_LOGIC_OP_COPY;

				case DMK::LogicOperator::AND_INVERTED:
					return VkLogicOp::VK_LOGIC_OP_AND_INVERTED;

				case DMK::LogicOperator::NO_OP:
					return VkLogicOp::VK_LOGIC_OP_NO_OP;

				case DMK::LogicOperator::XOR:
					return VkLogicOp::VK_LOGIC_OP_XOR;

				case DMK::LogicOperator::OR:
					return VkLogicOp::VK_LOGIC_OP_OR;

				case DMK::LogicOperator::NOR:
					return VkLogicOp::VK_LOGIC_OP_NOR;

				case DMK::LogicOperator::EQUIVALENT:
					return VkLogicOp::VK_LOGIC_OP_EQUIVALENT;

				case DMK::LogicOperator::INVERT:
					return VkLogicOp::VK_LOGIC_OP_INVERT;

				case DMK::LogicOperator::OR_REVERSE:
					return VkLogicOp::VK_LOGIC_OP_OR_REVERSE;

				case DMK::LogicOperator::COPY_INVERTED:
					return VkLogicOp::VK_LOGIC_OP_COPY_INVERTED;

				case DMK::LogicOperator::OR_INVERTED:
					return VkLogicOp::VK_LOGIC_OP_OR_INVERTED;

				case DMK::LogicOperator::NAND:
					return VkLogicOp::VK_LOGIC_OP_NAND;

				case DMK::LogicOperator::SET:
					return VkLogicOp::VK_LOGIC_OP_SET;
				}

				return VkLogicOp::VK_LOGIC_OP_NO_OP;
			}
		}

		RasterGraphicsPipeline::RasterGraphicsPipeline()
		{
			vInputAssemblyStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
			vInputAssemblyStateInfo.flags = VK_NULL_HANDLE;
			vInputAssemblyStateInfo.pNext = VK_NULL_HANDLE;

			vTessellationStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
			vTessellationStateInfo.flags = VK_NULL_HANDLE;
			vTessellationStateInfo.pNext = VK_NULL_HANDLE;

			vViewPortStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
			vViewPortStateInfo.flags = VK_NULL_HANDLE;
			vViewPortStateInfo.pNext = VK_NULL_HANDLE;

			vRasterizationStateinfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
			vRasterizationStateinfo.flags = VK_NULL_HANDLE;
			vRasterizationStateinfo.pNext = VK_NULL_HANDLE;

			vMultisampleStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
			vMultisampleStateInfo.flags = VK_NULL_HANDLE;
			vMultisampleStateInfo.pNext = VK_NULL_HANDLE;

			vDepthStencilStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
			vDepthStencilStateInfo.flags = VK_NULL_HANDLE;
			vDepthStencilStateInfo.pNext = VK_NULL_HANDLE;

			vColorBlendStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
			vColorBlendStateInfo.flags = VK_NULL_HANDLE;
			vColorBlendStateInfo.pNext = VK_NULL_HANDLE;
		}

		void RasterGraphicsPipeline::Initialize(const VulkanDevice& vDevice, const GraphicsCore::PipelineSpecification& spec, std::vector<ShaderModule>&& shaders, const RenderPass& vRenderPass, const RasterGraphicsPipeline* pParent)
		{
			this->mShaders = std::move(shaders);

			std::vector<VkPushConstantRange> vPushConstantRanges;
			std::vector<VkDescriptorSetLayoutBinding> vDescriptorSetLayoutBindings;
			std::vector<VkPipelineShaderStageCreateInfo> vShaderStages;

			for (auto itr = mShaders.begin(); itr != mShaders.end(); itr++)
			{
				vPushConstantRanges.insert(vPushConstantRanges.end(), itr->vPushConstantRanges.begin(), itr->vPushConstantRanges.end());
				vDescriptorSetLayoutBindings.insert(vDescriptorSetLayoutBindings.end(), itr->vLayoutBindings.begin(), itr->vLayoutBindings.end());

				VkPipelineShaderStageCreateInfo vCI = {};
				vCI.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
				vCI.flags = VK_NULL_HANDLE;
				vCI.pNext = VK_NULL_HANDLE;
				vCI.pSpecializationInfo = VK_NULL_HANDLE;
				vCI.pName = "main";
				vCI.stage = static_cast<VkShaderStageFlagBits>(itr->vShaderStage);
				vCI.module = itr->vShaderModule;

				vShaderStages.insert(vShaderStages.end(), std::move(vCI));
			}

			CreateDescriptorSetLayout(vDevice, std::move(vDescriptorSetLayoutBindings));

			CreatePipelineLayout(vDevice, std::move(vPushConstantRanges));

			// Input assembly state info.
			{
				vInputAssemblyStateInfo.primitiveRestartEnable = GET_VK_BOOL(spec.mInputAssemblySpec.mEnablePrimitiveRestart);
				vInputAssemblyStateInfo.topology = _Helpers::GetPrimitiveTopology(spec.mInputAssemblySpec.mPrimitiveTopology);
			}

			// Tessellation state info.
			{
				vTessellationStateInfo.patchControlPoints = 0;
			}

			// View port state info.
			{
				VkRect2D vRect = {};
				vRect.extent.width = spec.mViewPort.width;
				vRect.extent.height = spec.mViewPort.height;
				vRect.offset = { 0, 0 };

				vViewPortStateInfo.scissorCount = 1;
				vViewPortStateInfo.pScissors = &vRect;

				VkViewport vViewPort = {};
				vViewPort.width = static_cast<float>(spec.mViewPort.width);
				vViewPort.height = static_cast<float>(spec.mViewPort.height);
				vViewPort.x = spec.mViewPort.xOffset;
				vViewPort.y = spec.mViewPort.yOffset;
				vViewPort.minDepth = 0.0f;
				vViewPort.maxDepth = 1.0f;

				vViewPortStateInfo.viewportCount = 1;
				vViewPortStateInfo.pViewports = &vViewPort;
			}

			// Rasterization state info.
			{
				vRasterizationStateinfo.cullMode = _Helpers::GetCullModeFlags(spec.mRasterizerSpec.mCullMode);
				vRasterizationStateinfo.depthClampEnable = GET_VK_BOOL(spec.mRasterizerSpec.mEnableDepthClamp);
				vRasterizationStateinfo.depthBiasEnable = GET_VK_BOOL(spec.mRasterizerSpec.mEnableDepthBias);
				vRasterizationStateinfo.frontFace = _Helpers::GetFrontFace(spec.mRasterizerSpec.mFrontFace);
				vRasterizationStateinfo.lineWidth = spec.mRasterizerSpec.mPrimitiveLineWidth;
				vRasterizationStateinfo.polygonMode = _Helpers::GetPolygonMode(spec.mRasterizerSpec.mPolygonMode);
				vRasterizationStateinfo.rasterizerDiscardEnable = GET_VK_BOOL(spec.mRasterizerSpec.mEnableDiscard);
				vRasterizationStateinfo.depthBiasConstantFactor = spec.mRasterizerSpec.mDepthBiasFactor;
				vRasterizationStateinfo.depthBiasSlopeFactor = spec.mRasterizerSpec.mDepthSlopeFactor;
			}

			// Multisampling state info.
			{
				vMultisampleStateInfo.pSampleMask = VK_NULL_HANDLE;
				vMultisampleStateInfo.rasterizationSamples = static_cast<VkSampleCountFlagBits>(vDevice.GetMsaaSamples());
				vMultisampleStateInfo.sampleShadingEnable = GET_VK_BOOL(spec.mMultisamplingSpec.mEnableSampleShading);
				vMultisampleStateInfo.minSampleShading = spec.mMultisamplingSpec.mMinSampleShading;
				vMultisampleStateInfo.alphaToCoverageEnable = GET_VK_BOOL(spec.mMultisamplingSpec.mEnableAlphaToCoverage);
				vMultisampleStateInfo.alphaToOneEnable = GET_VK_BOOL(spec.mMultisamplingSpec.mEnableAlphaToOne);
			}

			// Depth stencil state info.
			{
				vDepthStencilStateInfo.depthTestEnable = GET_VK_BOOL(spec.mDepthStencilSpec.mEnableTest);
				vDepthStencilStateInfo.stencilTestEnable = GET_VK_BOOL(spec.mDepthStencilSpec.mEnableStencilTest);
				vDepthStencilStateInfo.depthWriteEnable = GET_VK_BOOL(spec.mDepthStencilSpec.mEnableWriteTest);
				vDepthStencilStateInfo.depthBoundsTestEnable = GET_VK_BOOL(spec.mDepthStencilSpec.mEnableBoundTests);
				vDepthStencilStateInfo.depthCompareOp = _Helpers::GetCompareOp(spec.mDepthStencilSpec.mComareOperator);
				vDepthStencilStateInfo.front = {};
				vDepthStencilStateInfo.back = {};
				vDepthStencilStateInfo.maxDepthBounds = spec.mDepthStencilSpec.mMaxBound;
				vDepthStencilStateInfo.minDepthBounds = spec.mDepthStencilSpec.mMinBound;
			}

			// Color blend state info.
			{
				vColorBlendStateInfo.logicOpEnable = GET_VK_BOOL(spec.mColorBlendSpec.mEnable);
				vColorBlendStateInfo.logicOp = _Helpers::GetLogicOp(spec.mColorBlendSpec.mLogicalOperator);
				MemoryFunctions::CopyData(vColorBlendStateInfo.blendConstants, spec.mColorBlendSpec.mBlendConstants, sizeof(float) * 4);
			}

			VkGraphicsPipelineCreateInfo vPipelineCI = {};
			vPipelineCI.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
			vPipelineCI.flags = pParent ? VK_PIPELINE_CREATE_DERIVATIVE_BIT : VK_PIPELINE_CREATE_ALLOW_DERIVATIVES_BIT;
			vPipelineCI.pNext = VK_NULL_HANDLE;
			vPipelineCI.pInputAssemblyState = &vInputAssemblyStateInfo;
			vPipelineCI.pTessellationState = &vTessellationStateInfo;
			vPipelineCI.pViewportState = &vViewPortStateInfo;
			vPipelineCI.pRasterizationState = &vRasterizationStateinfo;
			vPipelineCI.pMultisampleState = &vMultisampleStateInfo;
			vPipelineCI.pDepthStencilState = &vDepthStencilStateInfo;
			vPipelineCI.pColorBlendState = &vColorBlendStateInfo;
			vPipelineCI.stageCount = static_cast<UI32>(vShaderStages.size());
			vPipelineCI.pStages = vShaderStages.data();
			vPipelineCI.renderPass = vRenderPass;
			vPipelineCI.layout = vLayout;
			vPipelineCI.basePipelineIndex = 0;
			vPipelineCI.basePipelineHandle = pParent ? pParent->vPipeline : VK_NULL_HANDLE;

			DMK_VK_ASSERT(vkCreateGraphicsPipelines(vDevice, VK_NULL_HANDLE, 1, &vPipelineCI, nullptr, &vPipeline), "Failed to create Raster Graphics Pipeline!");
		}

		RasterGraphicsPipeline::operator VkPipelineLayout() const
		{
			return vLayout;
		}

		RasterGraphicsPipeline::operator VkPipeline() const
		{
			return vPipeline;
		}

		void RasterGraphicsPipeline::CreateDescriptorSetLayout(const VulkanDevice& vDevice, std::vector<VkDescriptorSetLayoutBinding>&& bindings)
		{
			VkDescriptorSetLayoutCreateInfo vLayoutCI = {};
			vLayoutCI.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
			vLayoutCI.flags = VK_NULL_HANDLE;
			vLayoutCI.pNext = VK_NULL_HANDLE;
			vLayoutCI.bindingCount = static_cast<UI32>(bindings.size());
			vLayoutCI.pBindings = bindings.data();

			DMK_VK_ASSERT(vkCreateDescriptorSetLayout(vDevice, &vLayoutCI, nullptr, &vDescriptorSetLayout), "Failed to create Vulkan descriptor set layout!");
		}

		void RasterGraphicsPipeline::CreatePipelineLayout(const VulkanDevice& vDevice, std::vector<VkPushConstantRange>&& pushConstantRanges)
		{
			VkPipelineLayoutCreateInfo vPipelineLayoutCI = {};
			vPipelineLayoutCI.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
			vPipelineLayoutCI.flags = VK_NULL_HANDLE;
			vPipelineLayoutCI.pNext = VK_NULL_HANDLE;
			vPipelineLayoutCI.pushConstantRangeCount = static_cast<UI32>(pushConstantRanges.size());
			vPipelineLayoutCI.pPushConstantRanges = pushConstantRanges.data();
			vPipelineLayoutCI.setLayoutCount = 1;
			vPipelineLayoutCI.pSetLayouts = &vDescriptorSetLayout;
			DMK_VK_ASSERT(vkCreatePipelineLayout(vDevice, &vPipelineLayoutCI, nullptr, &vLayout), "Failed to create graphis pipeline layout!");
		}
	}
}