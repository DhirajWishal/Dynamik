#include "dmkafx.h"
#include "VulkanShader.h"

#include "../Common/VulkanUtilities.h"

#include <fstream>

namespace Dynamik
{
	namespace Backend 
	{
		void VulkanShader::initialize(const VulkanDevice& vDevice, const DMKShaderModule& shader, DMKShaderLocation location)
		{
			if (shader.codeType != DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV)
				DMKErrorManager::issueWarnBox("Submitted shader module contains code that is not supported by Vulkan!");

			stageFlag = VulkanUtilities::getShaderStage(location);

			VkShaderModuleCreateInfo createInfo = {};
			createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
			createInfo.codeSize = shader.shaderCode.size();
			createInfo.pCode = reinterpret_cast<const UI32*>(shader.shaderCode.data());

			DMK_VULKAN_ASSERT(vkCreateShaderModule(vDevice, &createInfo, nullptr, &shaderModule), "Failed to create Shader module!");
		}

		void VulkanShader::terminate(const VulkanDevice& vDevice)
		{
		}

		VulkanShader::operator VkShaderModule() const
		{
			return this->shaderModule;
		}
	}
}