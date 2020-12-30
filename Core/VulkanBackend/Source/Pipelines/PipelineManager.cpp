// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/Pipelines/PipelineManager.h"
#include "VulkanBackend/Common/ShaderModule.h"

namespace DMK
{
	namespace VulkanBackend
	{
		GraphicsCore::PipelineObjectHandle PipelineManager::CreatePipeline(const VulkanDevice& vDevice, const GraphicsCore::PipelineSpecification& spec)
		{
			GraphicsCore::PipelineObjectHandle handle = {};
			handle.mSpecification = spec;

			// Create Vulkan shaders.
			std::vector<ShaderModule> shaders;
			for (auto itr = spec.mShaders.begin(); itr != spec.mShaders.end(); itr++)
			{
				ShaderModule shader = {};
				shader.Initialize(vDevice, *itr);

				shaders.insert(shaders.end(), std::move(shader));
			}

			switch (spec.mType)
			{
			case DMK::GraphicsCore::PipelineType::UNDEFINED:
				Logger::LogError(TEXT("Pipeline type should not be UNDEFINED!"));
				break;
			case DMK::GraphicsCore::PipelineType::GRAPHICS:
			{
				// Create and raster graphics pipeline and get the handle..
				RasterGraphicsPipeline pipeline = {};
				handle.mHandle = mRasterGraphicsPipelines.size();

				// Check if the pipeline can be derived from a parent.
				//if (mPipelineMap.find(spec) != mPipelineMap.end())
				//	pipeline.Initialize(vDevice, spec, std::move(shaders), mRasterGraphicsPipelines.data() + mPipelineMap[spec].mIndex);
				//else
				//{
				//	pipeline.Initialize(vDevice, spec, std::move(shaders), nullptr);
				//	mPipelineMap.emplace(std::make_pair(std::move(spec), PipelineIndex(handle.mHandle, spec.mType)));
				//}

				// Insert the pipeline to the vector.
				mRasterGraphicsPipelines.insert(mRasterGraphicsPipelines.end(), std::move(pipeline));
				break;
			}
			case DMK::GraphicsCore::PipelineType::COMPUTE:
				break;
			case DMK::GraphicsCore::PipelineType::RAY_TRACING:
				break;
			default:
				Logger::LogError(TEXT("Invalid pipeline type!"));
				break;
			}

			return handle;
		}
	}
}