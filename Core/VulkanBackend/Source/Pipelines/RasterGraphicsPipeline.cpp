// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/Pipelines/RasterGraphicsPipeline.h"

namespace DMK
{
	namespace VulkanBackend
	{
		void RasterGraphicsPipeline::Initialize(const VulkanDevice& vDevice, const GraphicsCore::PipelineSpecification& spec, std::vector<ShaderModule>&& shaders, const RasterGraphicsPipeline* pParent)
		{
			this->mShaders = std::move(shaders);

			VkGraphicsPipelineCreateInfo vPipelineCI = {};

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
	}
}