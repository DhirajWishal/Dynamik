#include "dmkafx.h"
#include "VulkanGraphicsPipeline.h"

#include "Tools/Shader/SPIR-V/Disassembler.h"

namespace Dynamik
{
	namespace Backend
	{
		void VulkanGraphicsPipeline::initialize(POINTER<RCoreObject> pCoreObject, RPipelineCreateInfo createInfo, RPipelineUsage usage)
		{
			for (auto shaderModule : createInfo.shaders)
			{
				Tools::SPIRVDisassembler _dissassembler(shaderModule);
			}
		}

		void VulkanGraphicsPipeline::terminate(POINTER<RCoreObject> pCoreObject)
		{
		}
	}
}
