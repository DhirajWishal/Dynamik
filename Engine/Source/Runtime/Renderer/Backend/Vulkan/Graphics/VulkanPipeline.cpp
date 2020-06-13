// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanPipeline.h"

#include <sys/stat.h>
#include <fcntl.h>

namespace Dynamik
{
	namespace Backend
	{
		void VulkanPipeline::terminate(const VulkanDevice& vDevice)
		{
		}

		VulkanPipeline::operator VkPipeline() const
		{
			return this->pipeline;
		}

		VulkanPipeline::operator VkPipelineLayout() const
		{
			return this->layout;
		}
	}
}