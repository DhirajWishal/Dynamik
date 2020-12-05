// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GraphicsCore/Backend/PipelineHandle.h"
#include "VulkanBackend/Common/VulkanDevice.h"
#include "VulkanBackend/Common/ShaderModule.h"

namespace DMK
{
	namespace VulkanBackend
	{
		/**
		 * Vulkan Raster Graphics Pipeline object.
		 * This pipeline render objects using a rasterizer to render objects. This is the most primitive and widely
		 * used rendering technique.
		 */
		class RasterGraphicsPipeline {
		public:
			RasterGraphicsPipeline() {}
			~RasterGraphicsPipeline() {}

			/**
			 * Initialize the pipeline.
			 *
			 * @param vDevice: The Vulkan device object.
			 * @param spec: The pipeline specification.
			 * @param shaders: The shaders the pipeline uses.
			 * @param pParent: The parent pipeline handle to derive this pipeline from. Default is nullptr. If a
			 *	      parent pipeline is not defined, this pipeline will be used as the parent for any future
			 *        suitable pipelines.
			 */
			void Initialize(const VulkanDevice& vDevice, const GraphicsCore::PipelineSpecification& spec, std::vector<ShaderModule>&& shaders, const RasterGraphicsPipeline* pParent = nullptr);

			/**
			 * Vulkan pipeline layout operator.
			 */
			operator VkPipelineLayout() const;

			/**
			 * Vulkan pipeline operator.
			 */
			operator VkPipeline() const;

		private:
			std::vector<ShaderModule> mShaders;	// The shaders used by the pipeline.
			VkPipelineLayout vLayout = VK_NULL_HANDLE;	// Vulkan pipeline layout handle.
			VkPipeline vPipeline = VK_NULL_HANDLE;	// Vulkan pipeline handle.
		};
	}
}