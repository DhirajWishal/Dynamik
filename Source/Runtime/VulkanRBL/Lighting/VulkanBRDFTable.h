// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_BRDF_TABLE_H
#define _DYNAMIK_VULKAN_BRDF_TABLE_H

#include "Renderer/Components/Lighting/RBRDFTable.h"
#include "../Pipelines/VulkanGraphicsPipeline.h"

namespace Dynamik
{
	namespace Backend 
	{
		/*
		 Vulkan BRDF Lookup Table for the Dynamik engine
		*/
		class DMK_API VulkanBRDFTable : public RBRDFTable {
		public:
			VulkanBRDFTable() {}
			~VulkanBRDFTable() {}

			virtual void initialize(RCoreObject* pCoreObject, DMKExtent2D dimentions, DMKFormat format = DMKFormat::DMK_FORMAT_RG_16_SF32) override final;
			virtual void terminate(RCoreObject* pCoreObject) override final;

		private:
			void _initializeTexture(RCoreObject* pCoreObject);
			void _initializeRenderPass(RCoreObject* pCoreObject);
			void _initializeFrameBuffer(RCoreObject* pCoreObject);
			void _initializePipelines(RCoreObject* pCoreObject);

			VulkanGraphicsPipeline pipeline;
		};
	}
}

#endif // !_DYNAMIK_VULKAN_BRDF_TABLE_H
