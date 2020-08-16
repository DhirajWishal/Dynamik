// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_IRRADIANCE_CUBE_H
#define _DYNAMIK_VULKAN_IRRADIANCE_CUBE_H

#include "Renderer/Components/Lighting/RIrradianceCube.h"
#include "../Pipelines/VulkanGraphicsPipeline.h"

namespace Dynamik
{
	namespace Backend
	{
		/*
		 Vulkan Irradiance Cube
		*/
		class DMK_API VulkanIrradianceCube : public RIrradianceCube {
		public:
			VulkanIrradianceCube() = default;
			~VulkanIrradianceCube() = default;

			virtual void initialize(RCoreObject* pCoreObject, REnvironmentEntity* pEnvironmentEntity, DMKExtent2D dimentions, DMKFormat format = DMKFormat::DMK_FORMAT_RGBA_32_SF32) override final;
			virtual void terminate(RCoreObject* pCoreObject) override final;

		private:
			void _initializeTexture(RCoreObject* pCoreObject);
			void _initializeRenderPass(RCoreObject* pCoreObject);
			void _initializeFrameBuffer(RCoreObject* pCoreObject);
			void _initializePipelines(RCoreObject* pCoreObject);
			void _process(RCoreObject* pCoreObject);
			void _terminateSupportStructures(RCoreObject* pCoreObject);

			VulkanGraphicsPipeline pipeline = {};
			VulkanGraphicsPipelineResource pipelineResource = {};
			RFrameBufferAttachment* pAttachment = nullptr;
		};
	}
}

#endif // !_DYNAMIK_VULKAN_IRRADIANCE_CUBE_H
