#pragma once
#ifndef _DYNAMIK_TOOLS_SPIRV_DISASSEMBLER_H
#define _DYNAMIK_TOOLS_SPIRV_DISASSEMBLER_H

/*
 Author:	Dhiraj Wishal
 Date:		10/06/2020
*/
#include "Core/Object/Resource/ShaderModule.h"
#include <vulkan/vulkan.h>

namespace Dynamik
{
	namespace Tools
	{
		/*
		 SPIR-V Disassembler tool
		 This disassembles SPIR-V modules to GLSL and/or HLSL
		*/
		class DMK_API SPIRVDisassembler {
		public:
			SPIRVDisassembler() {}
			SPIRVDisassembler(const DMKShaderModule& sModule) : shaderModule(sModule) {}
			~SPIRVDisassembler() {}

			/*
			 Get the descriptor set layout bindings of the current shader.
			*/
			ARRAY<VkDescriptorSetLayoutBinding> getDescriptorSetLayoutBindings();

			/*
			 Get the descriptor pool sizes of the current shader.
			*/
			ARRAY<VkDescriptorPoolSize> getDescriptorPoolSizes();

			/*
			 Get the vertex input attributes of the current shader
			*/
			ARRAY<VkVertexInputAttributeDescription> getVertexAttributeDescriptions();

			/*
			 Set the shader module
			*/
			void setShaderModule(const DMKShaderModule& sModule);

			/*
			 Convert to GLSL
			*/
			STRING toGLSL();

			/*
			 Convert to HLSL
			*/
			STRING toHLSL();

		private:
			void _parseModule();

		private:
			DMKShaderModule shaderModule;
			ARRAY<VkDescriptorSetLayoutBinding> layoutBindings;
			ARRAY<VkDescriptorPoolSize> poolSizes;
			ARRAY<VkVertexInputAttributeDescription> vertexAttributes;
			B1 isParsed = false;
		};
	}
}

#endif // !_DYNAMIK_TOOLS_SPIRV_DISASSEMBLER_H
