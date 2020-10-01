// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_TOOLS_SPIRV_DISASSEMBLER_H
#define _DYNAMIK_TOOLS_SPIRV_DISASSEMBLER_H

#include "Core/Objects/Resources/ShaderModule.h"
#include <vulkan/vulkan.h>

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
		 Get the uniform buffers in the shader. 
		*/
		std::vector<DMKUniformBuffer> getUniformBuffers();

		/*
		 Get the input attributes in this shader.
		*/
		std::vector<DMKShaderInputAttribute> getInputAttributes();

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

		std::vector<DMKUniformBuffer> uniformBuffers;
		std::vector<DMKShaderInputAttribute> inputAttributes;
		bool isParsed = false;
	};
}

#endif // !_DYNAMIK_TOOLS_SPIRV_DISASSEMBLER_H
