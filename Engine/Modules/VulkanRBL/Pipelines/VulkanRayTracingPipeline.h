// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_RAY_TRACING_PIPELINE_H
#define _DYNAMIK_VULKAN_RAY_TRACING_PIPELINE_H

#include "Renderer/Components/RPipelineObject.h"
#include "../Common/VulkanDevice.h"
#include "../Primitives/VulkanBuffer.h"

namespace Backend
{
	/*
	 Vulkan Ray Tracing Pipeline
	*/
	class DMK_API VulkanRayTracingPipeline : public RPipelineObject {
	public:
		VulkanRayTracingPipeline() {}
		~VulkanRayTracingPipeline() {}

		virtual void initialize(RCoreObject* pCoreObject) override final;
		virtual void terminate(RCoreObject* pCoreObject) override final;

		void createShaderBindingTable(RCoreObject* pCoreObject);

		operator VkDescriptorSetLayout() const;
		operator VkPipelineLayout() const;
		operator VkPipeline() const;

		ARRAY<VkRayTracingShaderGroupCreateInfoKHR> shaderGroups;

		VkDescriptorSetLayout descriptorSetLayout = VK_NULL_HANDLE;
		VkPipelineLayout layout = VK_NULL_HANDLE;
		VkPipeline pipeline = VK_NULL_HANDLE;
		VkPipelineCache pipelineCache = VK_NULL_HANDLE;

		VulkanBuffer shaderBindingTable = {};
	};
}

#endif // !_DYNAMIK_VULKAN_RAY_TRACING_PIPELINE_H
