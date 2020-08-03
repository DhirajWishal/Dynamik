// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_PRE_FILTERED_CUBE_H
#define _DYNAMIK_VULKAN_PRE_FILTERED_CUBE_H

#include "Renderer/Components/Lighting/RPreFilteredCube.h"
#include "../Pipelines/VulkanGraphicsPipeline.h"
#include "../Context/Attachments/VulkanColorAttachment.h"

namespace Dynamik
{
	namespace Backend
	{
		/*
		 Vulkan Pre Filtered Cube
		*/
		class DMK_API VulkanPreFilteredCube : public RPreFilteredCube {
		public:
			VulkanPreFilteredCube() {}
			~VulkanPreFilteredCube() {}

			virtual void initialize(RCoreObject* pCoreObject, REnvironmentMap* pEnvironmentMap, DMKExtent2D dimentions, DMKFormat format = DMKFormat::DMK_FORMAT_RGBA_16_SF32) override final;
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

#endif // !_DYNAMIK_VULKAN_PRE_FILTERED_CUBE_H
