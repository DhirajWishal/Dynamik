// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/Pipelines/RasterGraphicsPipeline.h"

namespace DMK
{
	namespace VulkanBackend
	{
		void RasterGraphicsPipeline::Initialize(const VulkanDevice& vDevice, const GraphicsCore::PipelineSpecification& spec)
		{
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