#pragma once
#ifndef _DYNAMIK_VULKAN_PIPELINE_MANAGER_H
#define _DYNAMIK_VULKAN_PIPELINE_MANAGER_H

/*
 Author:	Dhiraj Wishal
 Date:		02/06/2020
*/
#include "VulkanDevice.h"
#include "VulkanViewport.h"
#include "VulkanDescriptorSetManager.h"

#include "../Context/VulkanRenderPass.h"
#include "../Primitives/VulkanShader.h"

#include "Core/Object/Resource/Primitives.h"
#include "GameLibrary/GameAsset.h"

namespace Dynamik
{
	namespace Backend
	{
		/*
		 Vulkan Pipeline Container
		*/
		struct DMK_API VulkanPipelineContainer {
			VkPipelineBindPoint bindPoint = VkPipelineBindPoint::VK_PIPELINE_BIND_POINT_COMPUTE;
			VkPipeline pipeline = VK_NULL_HANDLE;
			VkPipelineLayout layout = VK_NULL_HANDLE;
		};

		/*
		 Vulkan Graphics Pipeline create info structure
		*/
		struct DMK_API VulkanGraphicsPipelineInitInfo {
			DMKGameAssetType assetType = DMKGameAssetType::DMK_GAME_ASSET_TYPE_MESH;
			DMKVertexBufferDescriptor vertexBufferDescriptor;
			ARRAY<DMKConstantBlockDescription> constantBlockDescriptions;

			VulkanRenderPass vRenderPass;
			ARRAY<VulkanViewport> viewports;
			VkExtent2D swapChainExtent;
			ARRAY<VulkanShader> shaders;

			ARRAY<VkDescriptorSetLayout> descriptorLayouts;

			// primitive assembly info
			VkPrimitiveTopology inputAssemblyTopology = VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;	// Vulkan input assembler topologies
			VkBool32 inputAssemblyPrimitiveRestartEnable = VK_FALSE;			// Vulkan primitive assembly restart enable

			// scissor info
			UI32 scissorCount = 1;											// Vulkan scissor count
			ARRAY<VkOffset2D> offsets = { { 0, 0 } };						// Vulkan scissor offsets

			// rasterizer info
			VkBool32 rasterizerDepthClampEnable = VK_FALSE;						// Vulkan rasterizer depth clamp enable
			VkBool32 rasterizerDiscardEnable = VK_FALSE;						// Vulkan rasterizer discard enable
			VkPolygonMode rasterizerPolygonMode = VkPolygonMode::VK_POLYGON_MODE_FILL;			// Vulkan rasterizer polygon mode
			F32 rasterizerLineWidth = 1.0f;									// Vulkan rasterizer line width
			VkCullModeFlagBits rasterizerCullMode = VkCullModeFlagBits::VK_CULL_MODE_BACK_BIT;		// Vulkan rasterizer cull mode
			VkFrontFace rasterizerFrontFace = VkFrontFace::VK_FRONT_FACE_COUNTER_CLOCKWISE;	// Vulkan rasterizer front face
			VkBool32 rasterizerDepthBiasEnable = VK_FALSE;						// Vulkan rasterizer depth bias enable

			// multi sampling info
			VkSampleCountFlagBits multisamplerMsaaSamples = VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT;	// Vulkan multisampler MSAA samples
			VkBool32 multisamplerSampleShadingEnable = VK_FALSE;					// Vulkan multi sampler sample shading enable
			F32 multisamplerMinSampleShading = 0.2f;							// Vulkan multi sampler sample shading

			// depth stencil info
			VkBool32 depthStencilEnable = VK_TRUE;								// Vulkan depth stencil enable
			VkBool32 depthStencilWriteEnable = VK_TRUE;							// Vulkan depth stencil write enable
			VkCompareOp depthStencilCompareOp = VkCompareOp::VK_COMPARE_OP_LESS;	// Vulkan depth stencil compare op
			VkBool32 depthStencilBoundsTestEnable = VK_FALSE;					// Vulkan depth stencil bounds test enable
			VkBool32 depthStencilTestEnable = VK_FALSE;							// Vulkan depth stencil test enable

			// color blender info
			ARRAY<VkPipelineColorBlendAttachmentState> additionalColorBlendStates;
			ARRAY<VkColorComponentFlags> colorBlenderColorWriteMasks = {	// Vulkan color blend write masks
				VK_COLOR_COMPONENT_R_BIT	// Red
				| VK_COLOR_COMPONENT_G_BIT	// Green
				| VK_COLOR_COMPONENT_B_BIT	// Blue
				| VK_COLOR_COMPONENT_A_BIT	// Alpha
			};
			ARRAY<VkBool32> colorBlenderBlendEnables = { VK_FALSE };		// Vulkan color blend blend enables

			VkBool32 colorBlendingLogicOpEnable = VK_FALSE;						// Vulkan color blend blending logical op enable
			VkLogicOp colorBlendingLogicOp = VkLogicOp::VK_LOGIC_OP_COPY;		// Vulkan color blend blending logical op
			UI32 colorBlendingColorBlendCount = 1;							// Vulkan color blend blending count
			ARRAY<F32> colorBlendingBlendConstants = {					// Vulkan color blend constants
				0.0f,	// Red
				0.0f,	// Green
				0.0f,	// Blue
				0.0f	// Alpha
			};

			// dynamic state info
			B1 dynamicStateEnable = false;									// Vulkan dynamic state enable
			VkPipelineDynamicStateCreateFlags dynamicStateFlags = 0;			// Vulkan dynamic state flags

			// pipeline info
			UI32 pipelineStageCount = 2;									// Vulkan pipeline stage count
			UI32 pipelineSubPass = 0;										// Vulkan pipeline sub pass
			VkPipeline pipelineBasePipelineHandle = VK_NULL_HANDLE;				// Vulkan base pipeline handle
			UI32 pipelineBasePipelineIndex = 0;
			VkPipelineCache pipelineCache = VK_NULL_HANDLE;					// Vulkan pipeline cache
			VkPipelineLayout pipelineLayout = VK_NULL_HANDLE;
		};

		/*
		 Vulkan Pipeline Manager for the Dynamik RBL
		*/
		class DMK_API VulkanPipelineManager {
		public:
			VulkanPipelineManager() {}
			~VulkanPipelineManager() {}

			VulkanPipelineContainer createGraphicsPipeline(const VulkanDevice& vDevice, VulkanGraphicsPipelineInitInfo info);
			VulkanPipelineContainer createRayTracingPipeline(const VulkanDevice& vDevice, VulkanGraphicsPipelineInitInfo info);
			VulkanPipelineContainer createComputePipeline(const VulkanDevice& vDevice, VulkanGraphicsPipelineInitInfo info);
		
		private:

		};
	}
}

#endif // !_DYNAMIK_VULKAN_PIPELINE_MANAGER_H
