// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "Disassembler.h"

#include "VulkanRBL/VulkanUtilities.h"

#include <spirv_glsl.hpp>
#include <spirv_hlsl.hpp>

namespace Tools
{
	DMK_FORCEINLINE std::vector<UI32> ConvertToUI32Vector(const ARRAY<UI32>& code)
	{
		std::vector<UI32> _code((code.size() / 4));

		for (UI32 index = 0; index < (code.size() / 4); index++)
			_code[index] = code[index];

		return _code;
	}

	DMK_FORCEINLINE VkFormat GetFormat(UI32 count)
	{
		if (count == 1)
			return VK_FORMAT_R32_SFLOAT;
		else if (count == 2)
			return VK_FORMAT_R32G32_SFLOAT;
		else if (count == 3)
			return VK_FORMAT_R32G32B32A32_SFLOAT;
		else if (count == 4)
			return VK_FORMAT_R32G32B32A32_SFLOAT;

		return VK_FORMAT_UNDEFINED;
	}

	DMK_FORCEINLINE UI64 GetFormatToSize(VkFormat format)
	{
		if (format == VK_FORMAT_R32_SFLOAT)
			return sizeof(F32) * 1;
		else if (format == VK_FORMAT_R32G32_SFLOAT)
			return sizeof(F32) * 2;
		else if (format == VK_FORMAT_R32G32B32_SFLOAT)
			return sizeof(F32) * 3;
		else if (format == VK_FORMAT_R32G32B32A32_SFLOAT)
			return sizeof(F32) * 4;

		return 0;
	}

	ARRAY<DMKUniformBuffer> SPIRVDisassembler::getUniformBuffers()
	{
		if (!isParsed)
			_parseModule();

		return uniformBuffers;
	}

	ARRAY<DMKShaderInputAttribute> SPIRVDisassembler::getInputAttributes()
	{
		if (!isParsed)
			_parseModule();

		return inputAttributes;
	}

	void SPIRVDisassembler::setShaderModule(const DMKShaderModule& sModule)
	{
		shaderModule = sModule;
	}

	STRING SPIRVDisassembler::toGLSL()
	{
		spirv_cross::CompilerGLSL _glslCompiler(std::move(ConvertToUI32Vector(shaderModule.shaderCode)));

		return _glslCompiler.compile();
	}

	STRING SPIRVDisassembler::toHLSL()
	{
		spirv_cross::CompilerHLSL _hlslCompiler(std::move(ConvertToUI32Vector(shaderModule.shaderCode)));

		return _hlslCompiler.compile();
	}

	void SPIRVDisassembler::_parseModule()
	{
		spirv_cross::Compiler _compiler(std::move(ConvertToUI32Vector(shaderModule.shaderCode)));
		spirv_cross::ShaderResources resources = _compiler.get_shader_resources();
		spirv_cross::SPIRType _type;

		UI64 offsetCount = 0;

		/* Uniform buffers */
		for (auto& resource : resources.uniform_buffers)
		{
			unsigned set = _compiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
			unsigned binding = _compiler.get_decoration(resource.id, spv::DecorationBinding);

			DMKUniformBuffer _uniformBuffer(binding, DMKUniformType::DMK_UNIFORM_TYPE_UNIFORM_BUFFER);

			for (UI32 index = 0; index < _compiler.get_type(resource.base_type_id).member_types.size(); index++)
			{
				auto Ty = _compiler.get_type(_compiler.get_type(resource.base_type_id).member_types[index]);
				UI32 byteSize = (Ty.width / 8) * Ty.vecsize * Ty.columns;
				offsetCount += byteSize;

				_uniformBuffer.addAttribute(STRING(_compiler.get_member_name(resource.base_type_id, index)), byteSize);
			}

			_uniformBuffer.initialize();
			uniformBuffers.pushBack(_uniformBuffer);
		}

		/* Storage buffers */
		for (auto& resource : resources.storage_buffers)
		{
			unsigned set = _compiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
			unsigned binding = _compiler.get_decoration(resource.id, spv::DecorationBinding);

			for (auto ID : _compiler.get_type(resource.base_type_id).member_types)
			{
				auto Ty = _compiler.get_type(ID);
				UI32 byteSize = (Ty.width / sizeof(F32)) * Ty.vecsize * Ty.columns;
				offsetCount += byteSize;
			}

			DMKUniformBuffer _uniformBuffer(binding, DMKUniformType::DMK_UNIFORM_TYPE_STORAGE_BUFFER);

			for (UI32 index = 0; index < _compiler.get_type(resource.base_type_id).member_types.size(); index++)
			{
				auto Ty = _compiler.get_type(_compiler.get_type(resource.base_type_id).member_types[index]);
				UI32 byteSize = (Ty.width / 8) * Ty.vecsize * Ty.columns;
				offsetCount += byteSize;

				_uniformBuffer.addAttribute(STRING(_compiler.get_member_name(resource.base_type_id, index)), byteSize);
			}

			_uniformBuffer.initialize();
			uniformBuffers.pushBack(_uniformBuffer);
		}

		/* Shader inputs */
		DMKShaderInputAttribute inputAttribute;
		for (auto& resource : resources.stage_inputs)
		{
			unsigned location = _compiler.get_decoration(resource.id, spv::DecorationLocation);
			unsigned binding = _compiler.get_decoration(resource.id, spv::DecorationBinding);

			_type = _compiler.get_type(resource.base_type_id);

			DMKShaderInputAttribute _inputAttribute;
			_inputAttribute.dataCount = _type.columns;
			_inputAttribute.dataFormat = Cast<DMKFormat>(GetFormat(_type.vecsize));
			inputAttributes.pushBack(_inputAttribute);
		}


		/* Shader outputs */
		for (auto& resource : resources.stage_outputs)
		{
			unsigned location = _compiler.get_decoration(resource.id, spv::DecorationLocation);
			unsigned binding = _compiler.get_decoration(resource.id, spv::DecorationBinding);
		}

		/* Shader subpass inputs */
		for (auto& resource : resources.subpass_inputs)
		{
			unsigned set = _compiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
			unsigned binding = _compiler.get_decoration(resource.id, spv::DecorationBinding);
		}

		/* Shader storage images */
		for (auto& resource : resources.storage_images)
		{
			unsigned set = _compiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
			unsigned binding = _compiler.get_decoration(resource.id, spv::DecorationBinding);

			DMKUniformBuffer _uniformBuffer(binding, DMKUniformType::DMK_UNIFORM_TYPE_STORAGE_IMAGE);

			for (UI32 index = 0; index < _compiler.get_type(resource.base_type_id).member_types.size(); index++)
			{
				auto Ty = _compiler.get_type(_compiler.get_type(resource.base_type_id).member_types[index]);
				UI32 byteSize = (Ty.width / 8) * Ty.vecsize * Ty.columns;
				offsetCount += byteSize;

				_uniformBuffer.addAttribute(STRING(_compiler.get_member_name(resource.base_type_id, index)), byteSize);
			}
			
			uniformBuffers.pushBack(_uniformBuffer);
		}

		/* Shader sampled images */
		for (auto& resource : resources.sampled_images)
		{
			unsigned set = _compiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
			unsigned binding = _compiler.get_decoration(resource.id, spv::DecorationBinding);

			DMKUniformBuffer _uniformBuffer(binding, DMKUniformType::DMK_UNIFORM_TYPE_SAMPLER_2D);

			for (UI32 index = 0; index < _compiler.get_type(resource.base_type_id).member_types.size(); index++)
			{
				auto Ty = _compiler.get_type(_compiler.get_type(resource.base_type_id).member_types[index]);
				UI32 byteSize = (Ty.width / 8) * Ty.vecsize * Ty.columns;
				offsetCount += byteSize;

				_uniformBuffer.addAttribute(STRING(_compiler.get_member_name(resource.base_type_id, index)), byteSize);
			}

			uniformBuffers.pushBack(_uniformBuffer);
		}

		/* Shader atomic counters */
		for (auto& resource : resources.atomic_counters)
		{
			unsigned set = _compiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
			unsigned binding = _compiler.get_decoration(resource.id, spv::DecorationBinding);
		}

		/* Shader acceleration structures*/
		for (auto& resource : resources.acceleration_structures)
		{
			unsigned set = _compiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
			unsigned binding = _compiler.get_decoration(resource.id, spv::DecorationBinding);

			DMKUniformBuffer _uniformBuffer(binding, DMKUniformType::DMK_UNIFORM_TYPE_ACCELERATION_STRUCTURE);

			for (UI32 index = 0; index < _compiler.get_type(resource.base_type_id).member_types.size(); index++)
			{
				auto Ty = _compiler.get_type(_compiler.get_type(resource.base_type_id).member_types[index]);
				UI32 byteSize = (Ty.width / 8) * Ty.vecsize * Ty.columns;
				offsetCount += byteSize;

				_uniformBuffer.addAttribute(STRING(_compiler.get_member_name(resource.base_type_id, index)), byteSize);
			}

			_uniformBuffer.initialize();
			uniformBuffers.pushBack(_uniformBuffer);
		}

		/* Shader push constant buffers */
		for (auto& resource : resources.push_constant_buffers)
		{
			unsigned set = _compiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
			unsigned binding = _compiler.get_decoration(resource.id, spv::DecorationBinding);

			DMKUniformBuffer _uniformBuffer(binding, DMKUniformType::DMK_UNIFORM_TYPE_CONSTANT);

			for (UI32 index = 0; index < _compiler.get_type(resource.base_type_id).member_types.size(); index++)
			{
				auto Ty = _compiler.get_type(_compiler.get_type(resource.base_type_id).member_types[index]);
				UI32 byteSize = (Ty.width / 8) * Ty.vecsize * Ty.columns;
				offsetCount += byteSize;

				_uniformBuffer.addAttribute(STRING(_compiler.get_member_name(resource.base_type_id, index)), byteSize);
			}

			_uniformBuffer.initialize();
			uniformBuffers.pushBack(_uniformBuffer);
		}

		/* Shader separate images */
		for (auto& resource : resources.separate_images)
		{
			unsigned set = _compiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
			unsigned binding = _compiler.get_decoration(resource.id, spv::DecorationBinding);

			DMKUniformBuffer _uniformBuffer(binding, DMKUniformType::DMK_UNIFORM_TYPE_SAMPLER_2D);

			for (UI32 index = 0; index < _compiler.get_type(resource.base_type_id).member_types.size(); index++)
			{
				auto Ty = _compiler.get_type(_compiler.get_type(resource.base_type_id).member_types[index]);
				UI32 byteSize = (Ty.width / 8) * Ty.vecsize * Ty.columns;
				offsetCount += byteSize;

				_uniformBuffer.addAttribute(STRING(_compiler.get_member_name(resource.base_type_id, index)), byteSize);
			}

			uniformBuffers.pushBack(_uniformBuffer);
		}

		/* Shader samplers */
		for (auto& resource : resources.separate_samplers)
		{
			unsigned set = _compiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
			unsigned binding = _compiler.get_decoration(resource.id, spv::DecorationBinding);
		}

		/* Check true if successfully parsed */
		isParsed = true;
	}
}
