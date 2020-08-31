// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanRayTracingPipeline.h"

#include "../VulkanCoreObject.h"
#include "../VulkanUtilities.h"

#include "Core/Types/StaticArray.h"
#include "Core/Utilities/ShaderFactory.h"

namespace Backend
{
	void VulkanRayTracingPipeline::initialize(RCoreObject* pCoreObject)
	{
		VkDescriptorSetLayoutBinding accelerationStructureLayoutBinding{};
		accelerationStructureLayoutBinding.binding = 0;
		accelerationStructureLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR;
		accelerationStructureLayoutBinding.descriptorCount = 1;
		accelerationStructureLayoutBinding.stageFlags = VK_SHADER_STAGE_RAYGEN_BIT_KHR | VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR;

		VkDescriptorSetLayoutBinding resultImageLayoutBinding{};
		resultImageLayoutBinding.binding = 1;
		resultImageLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
		resultImageLayoutBinding.descriptorCount = 1;
		resultImageLayoutBinding.stageFlags = VK_SHADER_STAGE_RAYGEN_BIT_KHR;

		VkDescriptorSetLayoutBinding uniformBufferBinding{};
		uniformBufferBinding.binding = 2;
		uniformBufferBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		uniformBufferBinding.descriptorCount = 1;
		uniformBufferBinding.stageFlags = VK_SHADER_STAGE_RAYGEN_BIT_KHR | VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR | VK_SHADER_STAGE_MISS_BIT_KHR;

		VkDescriptorSetLayoutBinding vertexBufferBinding{};
		vertexBufferBinding.binding = 3;
		vertexBufferBinding.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
		vertexBufferBinding.descriptorCount = 1;
		vertexBufferBinding.stageFlags = VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR;

		VkDescriptorSetLayoutBinding indexBufferBinding{};
		indexBufferBinding.binding = 4;
		indexBufferBinding.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
		indexBufferBinding.descriptorCount = 1;
		indexBufferBinding.stageFlags = VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR;

		ARRAY<VkDescriptorSetLayoutBinding> bindings = {
			accelerationStructureLayoutBinding,
			resultImageLayoutBinding,
			uniformBufferBinding,
			vertexBufferBinding,
			indexBufferBinding
		};

		VkDescriptorSetLayoutCreateInfo layoutInfo{};
		layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
		layoutInfo.pBindings = bindings.data();
		DMK_VULKAN_ASSERT(vkCreateDescriptorSetLayout(Inherit<VulkanCoreObject>(pCoreObject)->device, &layoutInfo, nullptr, &descriptorSetLayout), "Failed to create descriptor set layout!");

		VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo{};
		pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutCreateInfo.setLayoutCount = 1;
		pipelineLayoutCreateInfo.pSetLayouts = &descriptorSetLayout;

		DMK_VULKAN_ASSERT(vkCreatePipelineLayout(Inherit<VulkanCoreObject>(pCoreObject)->device, &pipelineLayoutCreateInfo, nullptr, &layout), "Failed to create pipeline layout!");

		constexpr UI32 shaderIndexRaygen = 0;
		constexpr UI32 shaderIndexMiss = 1;
		constexpr UI32 shaderIndexClosestHit = 2;

		VkPipelineShaderStageCreateInfo shaderStage = {};
		shaderStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		shaderStage.flags = VK_NULL_HANDLE;
		shaderStage.pNext = VK_NULL_HANDLE;
		shaderStage.pSpecializationInfo = VK_NULL_HANDLE;
		shaderStage.pName = "main";

		StaticArray<VkPipelineShaderStageCreateInfo, 3> shaderStages;
		shaderStages[shaderIndexRaygen] = shaderStage;
		shaderStages[shaderIndexRaygen].module = VulkanUtilities::createShaderModule(pCoreObject, DMKShaderFactory::createModule(TEXT(""), DMKShaderLocation::DMK_SHADER_LOCATION_RAY_GEN, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV));
		shaderStages[shaderIndexRaygen].stage = VulkanUtilities::getShaderStage(DMKShaderLocation::DMK_SHADER_LOCATION_RAY_GEN);

		shaderStages[shaderIndexMiss] = shaderStage;
		shaderStages[shaderIndexMiss].module = VulkanUtilities::createShaderModule(pCoreObject, DMKShaderFactory::createModule(TEXT(""), DMKShaderLocation::DMK_SHADER_LOCATION_MISS, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV));
		shaderStages[shaderIndexMiss].stage = VulkanUtilities::getShaderStage(DMKShaderLocation::DMK_SHADER_LOCATION_MISS);

		shaderStages[shaderIndexClosestHit] = shaderStage;
		shaderStages[shaderIndexClosestHit].module = VulkanUtilities::createShaderModule(pCoreObject, DMKShaderFactory::createModule(TEXT(""), DMKShaderLocation::DMK_SHADER_LOCATION_CLOSEST_HIT, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV));
		shaderStages[shaderIndexClosestHit].stage = VulkanUtilities::getShaderStage(DMKShaderLocation::DMK_SHADER_LOCATION_CLOSEST_HIT);

		VkSpecializationMapEntry specializationMapEntry = {};
		specializationMapEntry.constantID = 0;
		specializationMapEntry.offset = 0;
		specializationMapEntry.size = sizeof(UI32);

		UI32 maxRecursion = 4;

		VkSpecializationInfo specializationInfo = {};
		specializationInfo.mapEntryCount = 1;
		specializationInfo.pMapEntries = &specializationMapEntry;
		specializationInfo.dataSize = 4;
		specializationInfo.pData = &maxRecursion;
		shaderStages[shaderIndexRaygen].pSpecializationInfo = &specializationInfo;

		VkRayTracingShaderGroupCreateInfoKHR raygenGroupCI{};
		raygenGroupCI.sType = VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_KHR;
		raygenGroupCI.type = VK_RAY_TRACING_SHADER_GROUP_TYPE_GENERAL_KHR;
		raygenGroupCI.generalShader = shaderIndexRaygen;
		raygenGroupCI.closestHitShader = VK_SHADER_UNUSED_KHR;
		raygenGroupCI.anyHitShader = VK_SHADER_UNUSED_KHR;
		raygenGroupCI.intersectionShader = VK_SHADER_UNUSED_KHR;
		shaderGroups.pushBack(raygenGroupCI);

		VkRayTracingShaderGroupCreateInfoKHR missGroupCI{};
		missGroupCI.sType = VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_KHR;
		missGroupCI.type = VK_RAY_TRACING_SHADER_GROUP_TYPE_GENERAL_KHR;
		missGroupCI.generalShader = shaderIndexMiss;
		missGroupCI.closestHitShader = VK_SHADER_UNUSED_KHR;
		missGroupCI.anyHitShader = VK_SHADER_UNUSED_KHR;
		missGroupCI.intersectionShader = VK_SHADER_UNUSED_KHR;
		shaderGroups.pushBack(missGroupCI);

		VkRayTracingShaderGroupCreateInfoKHR closesHitGroupCI{};
		closesHitGroupCI.sType = VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_KHR;
		closesHitGroupCI.type = VK_RAY_TRACING_SHADER_GROUP_TYPE_TRIANGLES_HIT_GROUP_KHR;
		closesHitGroupCI.generalShader = VK_SHADER_UNUSED_KHR;
		closesHitGroupCI.closestHitShader = shaderIndexClosestHit;
		closesHitGroupCI.anyHitShader = VK_SHADER_UNUSED_KHR;
		closesHitGroupCI.intersectionShader = VK_SHADER_UNUSED_KHR;
		shaderGroups.pushBack(closesHitGroupCI);

		VkRayTracingPipelineCreateInfoKHR rayTracingPipelineCI{};
		rayTracingPipelineCI.sType = VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_CREATE_INFO_KHR;
		rayTracingPipelineCI.stageCount = static_cast<uint32_t>(shaderStages.size());
		rayTracingPipelineCI.pStages = shaderStages.data();
		rayTracingPipelineCI.groupCount = static_cast<uint32_t>(shaderGroups.size());
		rayTracingPipelineCI.pGroups = shaderGroups.data();
		rayTracingPipelineCI.maxRecursionDepth = 4;
		rayTracingPipelineCI.layout = layout;
		rayTracingPipelineCI.libraries.sType = VK_STRUCTURE_TYPE_PIPELINE_LIBRARY_CREATE_INFO_KHR;

		DMK_VULKAN_ASSERT(vkCreateRayTracingPipelinesKHR(Inherit<VulkanCoreObject>(pCoreObject)->device, pipelineCache, 1, &rayTracingPipelineCI, nullptr, &pipeline), "Failed to create ray tracing pipeline!");

		/* Terminate shaders */
		vkDestroyShaderModule(Inherit<VulkanCoreObject>(pCoreObject)->device, shaderStages[shaderIndexRaygen].module, nullptr);
		vkDestroyShaderModule(Inherit<VulkanCoreObject>(pCoreObject)->device, shaderStages[shaderIndexMiss].module, nullptr);
		vkDestroyShaderModule(Inherit<VulkanCoreObject>(pCoreObject)->device, shaderStages[shaderIndexClosestHit].module, nullptr);
	}

	void VulkanRayTracingPipeline::terminate(RCoreObject* pCoreObject)
	{
		/* Terminate Descriptor Set Layout */
		vkDestroyDescriptorSetLayout(InheritCast<VulkanCoreObject>(pCoreObject).device, descriptorSetLayout, nullptr);

		/* Terminate Pipeline */
		vkDestroyPipeline(InheritCast<VulkanCoreObject>(pCoreObject).device, pipeline, nullptr);
		vkDestroyPipelineLayout(InheritCast<VulkanCoreObject>(pCoreObject).device, layout, nullptr);

		/* Terminate Pipeline Cache */
		vkDestroyPipelineCache(InheritCast<VulkanCoreObject>(pCoreObject).device, pipelineCache, nullptr);
	}

	void VulkanRayTracingPipeline::createShaderBindingTable(RCoreObject* pCoreObject)
	{
		const uint32_t groupCount = Cast<UI32>(shaderGroups.size());
		auto properties = InheritCast<VulkanCoreObject>(pCoreObject).device.getRayTracingProperties();

		const uint32_t sbtSize = properties.shaderGroupBaseAlignment * groupCount;

		shaderBindingTable.initialize(pCoreObject, RBufferType::BUFFER_TYPE_RAY_TRACING, sbtSize, RResourceMemoryType::RESOURCE_MEMORY_TYPE_HOST_VISIBLE);

		// Write the shader handles to the shader binding table
		ARRAY<UI8> shaderHandleStorage(sbtSize);
		DMK_VULKAN_ASSERT(vkGetRayTracingShaderGroupHandlesKHR(InheritCast<VulkanCoreObject>(pCoreObject).device, pipeline, 0, groupCount, sbtSize, shaderHandleStorage.data()), "Failed to get ray tracing shader groups!");

		UI8* data = Cast<UI8*>(shaderBindingTable.getData(pCoreObject, sbtSize, 0));
		// This part is required, as the alignment and handle size may differ
		for (UI32 i = 0; i < groupCount; i++)
		{
			memcpy(data, shaderHandleStorage.data() + i * properties.shaderGroupHandleSize, properties.shaderGroupHandleSize);
			data += properties.shaderGroupBaseAlignment;
		}
		shaderBindingTable.unmapMemory(pCoreObject);
	}

	VulkanRayTracingPipeline::operator VkDescriptorSetLayout() const
	{
		return this->descriptorSetLayout;
	}

	VulkanRayTracingPipeline::operator VkPipelineLayout() const
	{
		return this->layout;
	}

	VulkanRayTracingPipeline::operator VkPipeline() const
	{
		return this->pipeline;
	}
}
