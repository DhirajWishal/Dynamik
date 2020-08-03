// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_GRAPHICS_PIPELINE_H
#define _DYNAMIK_VULKAN_GRAPHICS_PIPELINE_H

#include "Renderer/Components/RPipelineObject.h"
#include "Core/Types/Array.h"
#include <vulkan/vulkan.h>

namespace Dynamik
{
	namespace Backend
	{
		/*
		 Vulkan Graphics Pipeline Resource
		*/
		struct DMK_API VulkanGraphicsPipelineResource : public RPipelineResource {
			virtual void update(RCoreObject* pCoreObject, ARRAY<RBuffer*> pBuffers, ARRAY<RTexture*> pTextures) override final;
			
			ARRAY<VkDescriptorSetLayoutBinding> resourceBindings;
			VkDescriptorSet set = VK_NULL_HANDLE;
		};

		/*
		 Vulkan Graphics Pipeline
		*/
		class DMK_API VulkanGraphicsPipeline : public RPipelineObject {
			struct DMK_API VDescriptor {
				VkDescriptorSetLayout layout = VK_NULL_HANDLE;
				VkDescriptorPool pool = VK_NULL_HANDLE;
			};

		public:
			VulkanGraphicsPipeline() {}
			~VulkanGraphicsPipeline() {}

			virtual void initialize(RCoreObject* pCoreObject, RPipelineSpecification createInfo, RPipelineUsage usage, RRenderTarget* pRenderTarget, DMKViewport viewport) override final;
			virtual void reCreate(RCoreObject* pCoreObject, RRenderTarget* pRenderTarget, DMKViewport viewport) override final;
			virtual void terminate(RCoreObject* pCoreObject) override final;

			virtual void createPipelineCache(RCoreObject* pCoreObject, UI64 byteSize, VPTR pData) override final;
			virtual ARRAY<RPipelineResource*> allocateResources(RCoreObject* pCoreObject) override final;

			operator VkPipelineLayout() const;
			operator VkPipeline() const;

			VDescriptor descriptor;

			VkPipelineLayout layout = VK_NULL_HANDLE;
			VkPipeline pipeline = VK_NULL_HANDLE;
			VkPipelineCache pipelineCache = VK_NULL_HANDLE;

		private:
			ARRAY<VkDescriptorSetLayoutBinding> resourceBindings;
		};
	}
}

#endif // !_DYNAMIK_VULKAN_GRAPHICS_PIPELINE_H
