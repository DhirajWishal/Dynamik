// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GraphicsCore/Backend/PipelineHandle.h"
#include "VulkanBackend/Common/VulkanDevice.h"

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
			/**
			 * Default constructor.
			 */
			RasterGraphicsPipeline() {}

			/**
			 * Default destructor.
			 */
			~RasterGraphicsPipeline() {}

			/**
			 * Initialize the pipeline.
			 * 
			 * @param vDevice: The Vulkan device object.
			 * @param spec: The pipeline specification.
			 */
			void Initialize(const VulkanDevice& vDevice, const GraphicsCore::PipelineSpecification& spec);

			/**
			 * Vulkan pipeline layout operator.
			 */
			operator VkPipelineLayout() const;

			/**
			 * Vulkan pipeline operator.
			 */
			operator VkPipeline() const;

		private:
			VkPipelineLayout vLayout = VK_NULL_HANDLE;	// Vulkan pipeline layout handle.
			VkPipeline vPipeline = VK_NULL_HANDLE;	// Vulkan pipeline handle.
		};
	}
}