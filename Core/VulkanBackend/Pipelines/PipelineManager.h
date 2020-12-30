// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GraphicsCore/Backend/PipelineHandle.h"
#include "RasterGraphicsPipeline.h"

namespace DMK
{
	namespace VulkanBackend
	{
		class VulkanDevice;

		/**
		 * Vulkan Pipeline Manager object.
		 * This manages Graphics, Compute and Ray Tracing pipelines in Vulkan.
		 */
		class PipelineManager {
			/**
			 * Pipeline Index structure.
			 */
			struct PipelineIndex {
				PipelineIndex() = default;
				PipelineIndex(UI64 index, GraphicsCore::PipelineType type) : mIndex(index), mType(type) {}

				UI64 mIndex = 0;
				GraphicsCore::PipelineType mType = GraphicsCore::PipelineType::UNDEFINED;
			};

		public:
			PipelineManager() {}
			~PipelineManager() {}

			/**
			 * Create a new Vulkan Pipeline.
			 *
			 * @param vDevice: The device which the pipeline is bound to.
			 * @param spec: The pipeline specification.
			 * @return The pipeline handle.
			 */
			GraphicsCore::PipelineObjectHandle CreatePipeline(const VulkanDevice& vDevice, const GraphicsCore::PipelineSpecification& spec);

			std::unordered_map<GraphicsCore::PipelineSpecification, PipelineIndex> mPipelineMap;	// The pipeline map.
			std::vector<RasterGraphicsPipeline> mRasterGraphicsPipelines;	// The reaster graphics pipelines.
		};
	}
}