// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "Disassembler.h"

#include "VulkanRBL/VulkanUtilities.h"

#include <spirv_glsl.hpp>
#include <spirv_hlsl.hpp>

namespace Tools
{
	inline std::vector<UI32> convertToUI32Vector(const ARRAY<UI32>& code)
	{
		std::vector<UI32> _code((code.size() / 4));

		for (UI32 index = 0; index < (code.size() / 4); index++)
			_code[index] = code[index];

		return _code;
	}

	inline VkFormat getFormat(UI32 count)
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

	inline UI64 getFormatToSize(VkFormat format)
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

	ARRAY<VkDescriptorSetLayoutBinding> SPIRVDisassembler::getDescriptorSetLayoutBindings()
	{
		if (!isParsed)
			_parseModule();

		return layoutBindings;
	}

	ARRAY<VkDescriptorSetLayoutBinding> SPIRVDisassembler::getOrderedDescriptorSetLayoutBindings()
	{
		if (!isParsed)
			_parseModule();

		if (!layoutBindings.size())
			return ARRAY<VkDescriptorSetLayoutBinding>();

		ARRAY<VkDescriptorSetLayoutBinding> bindings(layoutBindings.size());

		UI32 minimumBinding = layoutBindings[0].binding;
		for (auto binding : layoutBindings)
			if (minimumBinding > binding.binding)
				minimumBinding = binding.binding;

		for (auto binding : layoutBindings)
			bindings[binding.binding - minimumBinding] = binding;

		return bindings;
	}

	ARRAY<VkDescriptorPoolSize> SPIRVDisassembler::getDescriptorPoolSizes()
	{
		if (!isParsed)
			_parseModule();

		return poolSizes;
	}

	ARRAY<VkVertexInputAttributeDescription> SPIRVDisassembler::getVertexAttributeDescriptions()
	{
		if (!isParsed)
			_parseModule();

		if (!vertexAttributes.size())
			return ARRAY<VkVertexInputAttributeDescription>();

		ARRAY<VkVertexInputAttributeDescription> inputs(vertexAttributes.size());

		UI32 minimumLocation = vertexAttributes[0].location;
		for (auto binding : vertexAttributes)
			if (minimumLocation > binding.location)
				minimumLocation = binding.location;

		for (auto binding : vertexAttributes)
			inputs[binding.location - minimumLocation] = binding;

		vertexAttributes = std::move(inputs);

		UI64 offsets = 0;
		for (UI64 index = 0; index < vertexAttributes.size(); index++)
		{
			UI64 n_offsets = getFormatToSize(vertexAttributes[index].format);
			vertexAttributes[index].offset = Cast<UI32>(offsets);

			offsets += n_offsets;
		}


		return vertexAttributes;
	}

	ARRAY<VkPushConstantRange> SPIRVDisassembler::getPushConstantRanges()
	{
		if (!isParsed)
			_parseModule();

		return pushConstantRanges;
	}

	ARRAY<VkVertexInputBindingDescription> SPIRVDisassembler::getVertexBindingDescriptions()
	{
		if (!isParsed)
			_parseModule();

		if (!bindingDescriptions.size())
			return ARRAY<VkVertexInputBindingDescription>();

		ARRAY<VkVertexInputBindingDescription> inputs(bindingDescriptions.size());

		UI32 minimumBinding = bindingDescriptions[0].binding;
		for (auto binding : bindingDescriptions)
			if (minimumBinding > binding.binding)
				minimumBinding = binding.binding;

		for (auto binding : bindingDescriptions)
			inputs[binding.binding - minimumBinding] = binding;

		bindingDescriptions = inputs;
		return bindingDescriptions;
	}

	void SPIRVDisassembler::setShaderModule(const DMKShaderModule& sModule)
	{
		shaderModule = sModule;
	}

	STRING SPIRVDisassembler::toGLSL()
	{
		spirv_cross::CompilerGLSL _glslCompiler(std::move(convertToUI32Vector(shaderModule.shaderCode)));

		return _glslCompiler.compile();
	}

	STRING SPIRVDisassembler::toHLSL()
	{
		spirv_cross::CompilerHLSL _hlslCompiler(std::move(convertToUI32Vector(shaderModule.shaderCode)));

		return _hlslCompiler.compile();
	}

	void SPIRVDisassembler::_parseModule()
	{
		spirv_cross::CompilerGLSL _glslCompiler(std::move(convertToUI32Vector(shaderModule.shaderCode)));
		spirv_cross::ShaderResources resources = _glslCompiler.get_shader_resources();
		spirv_cross::SPIRType _type;

		VkDescriptorPoolSize _poolSize;
		_poolSize.descriptorCount = 1;

		VkDescriptorSetLayoutBinding _binding;
		_binding.pImmutableSamplers = VK_NULL_HANDLE;
		_binding.stageFlags = Backend::VulkanUtilities::getShaderStage(shaderModule.location);
		_binding.descriptorCount = 1;

		UI64 offsetCount = 0;

		/* Uniform buffers */
		for (auto& resource : resources.uniform_buffers)
		{
			unsigned set = _glslCompiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
			unsigned binding = _glslCompiler.get_decoration(resource.id, spv::DecorationBinding);
#ifdef DMK_DEBUG
			printf("Set: %u\t Binding: %u\t Type: %s\n", set, binding, resource.name.c_str());

			for (UI32 index = 0; index < _glslCompiler.get_type(resource.base_type_id).member_types.size(); index++)
				printf("\t Members: %s\n", _glslCompiler.get_member_name(resource.base_type_id, index).c_str());

			printf("\n");
#endif // DMK_DEBUG


			_binding.binding = _glslCompiler.get_decoration(resource.id, spv::DecorationBinding);
			_binding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			layoutBindings.pushBack(_binding);

			_poolSize.descriptorCount = 1;
			_poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			poolSizes.pushBack(_poolSize);

			for (auto ID : _glslCompiler.get_type(resource.base_type_id).member_types)
			{
				auto Ty = _glslCompiler.get_type(ID);
				UI32 byteSize = (Ty.width / sizeof(F32)) * Ty.vecsize * Ty.columns;
				offsetCount += byteSize;

				/* Check if the member is a matrix */
			}
		}

		/* Storage buffers */
		for (auto& resource : resources.storage_buffers)
		{
#ifdef DMK_DEBUG
			unsigned set = _glslCompiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
			unsigned binding = _glslCompiler.get_decoration(resource.id, spv::DecorationBinding);
			printf("Set: %u\t Binding: %u\t Type: %s\n", set, binding, resource.name.c_str());

			for (UI32 index = 0; index < _glslCompiler.get_type(resource.base_type_id).member_types.size(); index++)
				printf("\t Members: %s\n", _glslCompiler.get_member_name(resource.base_type_id, index).c_str());

			printf("\n");
#endif // DMK_DEBUG

			_binding.binding = _glslCompiler.get_decoration(resource.id, spv::DecorationBinding);
			_binding.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
			layoutBindings.pushBack(_binding);

			_poolSize.type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
			poolSizes.pushBack(_poolSize);

			for (auto ID : _glslCompiler.get_type(resource.base_type_id).member_types)
			{
				auto Ty = _glslCompiler.get_type(ID);
				UI32 byteSize = (Ty.width / sizeof(F32)) * Ty.vecsize * Ty.columns;
				offsetCount += byteSize;
			}
		}

		/* Shader inputs */
		VkVertexInputAttributeDescription _attributeDescription;
		VkVertexInputBindingDescription bindingDescription;
		_attributeDescription.offset = 0;
		DMKShaderInputAttribute inputAttribute;
		for (auto& resource : resources.stage_inputs)
		{
			unsigned location = _glslCompiler.get_decoration(resource.id, spv::DecorationLocation);
			unsigned binding = _glslCompiler.get_decoration(resource.id, spv::DecorationBinding);
#ifdef DMK_DEBUG
			printf("Location: %u\t Binding: %u\t Type: %s\n", location, binding, resource.name.c_str());

#endif // DMK_DEBUG

			_type = _glslCompiler.get_type(resource.base_type_id);

			_attributeDescription.binding = _glslCompiler.get_decoration(resource.id, spv::DecorationBinding);
			_attributeDescription.location = _glslCompiler.get_decoration(resource.id, spv::DecorationLocation);
			_attributeDescription.format = getFormat(_type.vecsize);
			vertexAttributes.pushBack(_attributeDescription);

			_attributeDescription.offset += (_type.width / sizeof(D64)) * ((_type.vecsize == 3) ? 4 : _type.vecsize);
		}

		if (_attributeDescription.offset)
		{
			bindingDescription.binding = 0;
			bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
			bindingDescription.stride = _attributeDescription.offset;
			bindingDescriptions.pushBack(bindingDescription);
		}

#ifdef DMK_DEBUG
		printf("\n");

#endif // DMK_DEBUG


		/* Shader outputs */
		for (auto& resource : resources.stage_outputs)
		{
#ifdef DMK_DEBUG
			unsigned location = _glslCompiler.get_decoration(resource.id, spv::DecorationLocation);
			unsigned binding = _glslCompiler.get_decoration(resource.id, spv::DecorationBinding);
			printf("Location: %u\t Binding: %u\t Type: %s\n", location, binding, resource.name.c_str());

			printf("\n");
#endif // DMK_DEBUG
		}

		/* Shader subpass inputs */
		for (auto& resource : resources.subpass_inputs)
		{
#ifdef DMK_DEBUG
			unsigned set = _glslCompiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
			unsigned binding = _glslCompiler.get_decoration(resource.id, spv::DecorationBinding);
			printf("Set: %u\t Binding: %u\t Type: %s\n", set, binding, resource.name.c_str());

			printf("\n");
#endif // DMK_DEBUG

			_binding.binding = _glslCompiler.get_decoration(resource.id, spv::DecorationBinding);
			_binding.descriptorCount = 1;
			_binding.descriptorType = VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
			layoutBindings.pushBack(_binding);

			_poolSize.descriptorCount = 1;
			_poolSize.type = VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
			poolSizes.pushBack(_poolSize);
		}

		/* Shader storage images */
		for (auto& resource : resources.storage_images)
		{
#ifdef DMK_DEBUG
			unsigned set = _glslCompiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
			unsigned binding = _glslCompiler.get_decoration(resource.id, spv::DecorationBinding);
			printf("Set: %u\t Binding: %u\t Type: %s\n", set, binding, resource.name.c_str());

			printf("\n");
#endif // DMK_DEBUG

			_binding.binding = _glslCompiler.get_decoration(resource.id, spv::DecorationBinding);
			_binding.descriptorCount = 1;
			_binding.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			layoutBindings.pushBack(_binding);

			_poolSize.descriptorCount = 1;
			_poolSize.type = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			poolSizes.pushBack(_poolSize);
		}

		/* Shader sampled images */
		for (auto& resource : resources.sampled_images)
		{
#ifdef DMK_DEBUG
			unsigned set = _glslCompiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
			unsigned binding = _glslCompiler.get_decoration(resource.id, spv::DecorationBinding);
			printf("Set: %u\t Binding: %u\t Type: %s\n", set, binding, resource.name.c_str());

			printf("\n");
#endif // DMK_DEBUG

			_binding.binding = _glslCompiler.get_decoration(resource.id, spv::DecorationBinding);
			_binding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			layoutBindings.pushBack(_binding);

			_poolSize.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			poolSizes.pushBack(_poolSize);
		}

		/* Shader atomic counters */
		for (auto& resource : resources.atomic_counters)
		{
#ifdef DMK_DEBUG
			unsigned set = _glslCompiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
			unsigned binding = _glslCompiler.get_decoration(resource.id, spv::DecorationBinding);
			printf("Set: %u\t Binding: %u\t Type: %s\n", set, binding, resource.name.c_str());

			printf("\n");
#endif // DMK_DEBUG
		}

		/* Shader acceleration structures*/
		for (auto& resource : resources.acceleration_structures)
		{
#ifdef DMK_DEBUG
			unsigned set = _glslCompiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
			unsigned binding = _glslCompiler.get_decoration(resource.id, spv::DecorationBinding);
			printf("Set: %u\t Binding: %u\t Type: %s\n", set, binding, resource.name.c_str());

			printf("\n");
#endif // DMK_DEBUG

			_binding.binding = _glslCompiler.get_decoration(resource.id, spv::DecorationBinding);
			_binding.descriptorCount = 1;
			_binding.descriptorType = VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV;
			layoutBindings.pushBack(_binding);

			_poolSize.descriptorCount = 1;
			_poolSize.type = VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV;
			poolSizes.pushBack(_poolSize);
		}

		/* Shader push constant buffers */
		VkPushConstantRange _range;
		_range.stageFlags = Backend::VulkanUtilities::getShaderStage(shaderModule.location);
		_range.offset = 0;
		for (auto& resource : resources.push_constant_buffers)
		{
			_range.size = 0;
#ifdef DMK_DEBUG
			unsigned set = _glslCompiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
			unsigned binding = _glslCompiler.get_decoration(resource.id, spv::DecorationBinding);
			printf("Set: %u\t Binding: %u\t Type: %s\n", set, binding, resource.name.c_str());

			printf("\n");
#endif // DMK_DEBUG

			for (auto ID : _glslCompiler.get_type(resource.base_type_id).member_types)
			{
				auto Ty = _glslCompiler.get_type(ID);
				_range.size += ((Ty.width / 8) * ((Ty.vecsize == 3) ? 4 : Ty.vecsize) * Ty.columns);
			}

			pushConstantRanges.pushBack(_range);
			_range.offset += _range.size;
		}
		offsetCount += _range.offset;

		/* Shader separate images */
		for (auto& resource : resources.separate_images)
		{
#ifdef DMK_DEBUG
			unsigned set = _glslCompiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
			unsigned binding = _glslCompiler.get_decoration(resource.id, spv::DecorationBinding);
			printf("Set: %u\t Binding: %u\t Type: %s\n", set, binding, resource.name.c_str());

			printf("\n");
#endif // DMK_DEBUG

			_binding.binding = _glslCompiler.get_decoration(resource.id, spv::DecorationBinding);
			_binding.descriptorType = VK_DESCRIPTOR_TYPE_SAMPLER;
			layoutBindings.pushBack(_binding);

			_poolSize.type = VK_DESCRIPTOR_TYPE_SAMPLER;
			poolSizes.pushBack(_poolSize);
		}

		/* Shader samplers */
		for (auto& resource : resources.separate_samplers)
		{
#ifdef DMK_DEBUG
			unsigned set = _glslCompiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
			unsigned binding = _glslCompiler.get_decoration(resource.id, spv::DecorationBinding);
			printf("Set: %u\t Binding: %u\t Type: %s\n", set, binding, resource.name.c_str());

			printf("\n");
#endif // DMK_DEBUG
		}

		/* Check true if successfully parsed */
		isParsed = true;
	}
}
