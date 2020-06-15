// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanShader.h"

#include "../VulkanUtilities.h"
#include "Tools/Shader/SPIR-V/Disassembler.h"

namespace Dynamik
{
	namespace Backend
	{
		void VulkanShader::initialize(const VulkanDevice& vDevice, const DMKShaderModule& shader)
		{
			parentModule = shader;

			if (shader.codeType != DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV)
				DMKErrorManager::issueWarnBox("Submitted shader module contains code that is not supported by Vulkan!");

			stageFlag = VulkanUtilities::getShaderStage(shader.location);

			VkShaderModuleCreateInfo createInfo = {};
			createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
			createInfo.codeSize = shader.shaderCode.size();
			createInfo.pCode = (UI32*)shader.shaderCode.data();

			DMK_VULKAN_ASSERT(vkCreateShaderModule(vDevice, &createInfo, nullptr, &shaderModule), "Failed to create Shader module!");
		}

		void VulkanShader::terminate(const VulkanDevice& vDevice)
		{
			vkDestroyShaderModule(vDevice, shaderModule, VK_NULL_HANDLE);
		}

		std::pair<ARRAY<VkDescriptorSetLayoutBinding>, ARRAY<VkDescriptorPoolSize>> VulkanShader::createDescriptorLayoutAndSizes(const VulkanDevice& vDevice)
		{
			Tools::SPIRVDisassembler _disassembler(parentModule);

			return { _disassembler.getDescriptorSetLayoutBindings(), _disassembler.getDescriptorPoolSizes() };
		}

		VulkanShader::operator VkShaderModule() const
		{
			return this->shaderModule;
		}
	}
}