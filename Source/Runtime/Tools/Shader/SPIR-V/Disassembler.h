// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_TOOLS_SPIRV_DISASSEMBLER_H
#define _DYNAMIK_TOOLS_SPIRV_DISASSEMBLER_H

#include "Core/Objects/Resources/ShaderModule.h"
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
			 Get ordered set layout bindings of the current shader.
			*/
			ARRAY<VkDescriptorSetLayoutBinding> getOrderedDescriptorSetLayoutBindings();

			/*
			 Get the descriptor pool sizes of the current shader.
			*/
			ARRAY<VkDescriptorPoolSize> getDescriptorPoolSizes();

			/*
			 Get the vertex input attributes of the current shader
			*/
			ARRAY<VkVertexInputAttributeDescription> getVertexAttributeDescriptions();

			/*
			 Get the push constant information in the current shader.
			*/
			ARRAY<VkPushConstantRange> getPushConstantRanges();

			/*
			 Get the binding description of the current shader.
			 @warn: Only works with vertex shaders.
			*/
			VkVertexInputBindingDescription getVertexBindingDescription();

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
			ARRAY<VkPushConstantRange> pushConstantRanges;
			VkVertexInputBindingDescription bindingDescription;
			B1 isParsed = false;
		};
	}
}

#endif // !_DYNAMIK_TOOLS_SPIRV_DISASSEMBLER_H
