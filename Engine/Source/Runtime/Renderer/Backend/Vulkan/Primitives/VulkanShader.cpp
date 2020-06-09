#include "dmkafx.h"
#include "VulkanShader.h"

#include "../Common/VulkanUtilities.h"

#include <spirv_glsl.hpp>
#include <iostream>

namespace Dynamik
{
	namespace Backend
	{
		std::vector<UI32> convertToUI32Vector(const ARRAY<UI32>& code)
		{
			std::vector<UI32> _code;

			for (UI32 index = 0; index < (code.size() / 4); index++)
				_code.push_back(code[index]);

			return _code;
		}

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

		VkDescriptorSetLayout VulkanShader::createDescriptorSetLayout(const VulkanDevice& vDevice)
		{
			spirv_cross::CompilerGLSL _glslCompiler(std::move(convertToUI32Vector(parentModule.shaderCode)));
			spirv_cross::ShaderResources resources = _glslCompiler.get_shader_resources();

			ARRAY<VkDescriptorSetLayoutBinding> layoutBindings;
			VkDescriptorSetLayoutBinding _binding;
			_binding.pImmutableSamplers = VK_NULL_HANDLE;
			_binding.stageFlags = VulkanUtilities::getShaderStage(parentModule.location);

			/* Uniform buffers */
			for (auto& resource : resources.uniform_buffers)
			{
				unsigned set = _glslCompiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
				unsigned binding = _glslCompiler.get_decoration(resource.id, spv::DecorationBinding);
				printf("Set: %u\t Binding: %u\t Type: %s\n", set, binding, resource.name.c_str());

				for (UI32 index = 0; index < _glslCompiler.get_type(resource.base_type_id).member_types.size(); index++)
					printf("\tMembers: %s\n", _glslCompiler.get_member_name(resource.base_type_id, index).c_str());

				_binding.binding = binding;
				_binding.descriptorCount = 1;
				_binding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
				layoutBindings.pushBack(_binding);
			}

			/* Storage buffers */
			for (auto& resource : resources.storage_buffers)
			{
				unsigned set = _glslCompiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
				unsigned binding = _glslCompiler.get_decoration(resource.id, spv::DecorationBinding);
				printf("Set: %u\t Binding: %u\t Type: %s\n", set, binding, resource.name.c_str());

				for (UI32 index = 0; index < _glslCompiler.get_type(resource.base_type_id).member_types.size(); index++)
					printf("\tMembers: %s\n", _glslCompiler.get_member_name(resource.base_type_id, index).c_str());

				_binding.binding = binding;
				_binding.descriptorCount = 1;
				_binding.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
				layoutBindings.pushBack(_binding);
			}

			/* Shader inputs */
			VkVertexInputAttributeDescription _attributeDescription;
			for (auto& resource : resources.stage_inputs)
			{
				unsigned location = _glslCompiler.get_decoration(resource.id, spv::DecorationLocation);
				unsigned binding = _glslCompiler.get_decoration(resource.id, spv::DecorationBinding);
				unsigned offset = _glslCompiler.get_decoration(resource.base_type_id, spv::DecorationOffset);
				//unsigned offset = _glslCompiler.get_decoration(resource.id, spv::DecorationMaxByteOffset);
				printf("Location: %u\t Binding: %u\t Offset: %u\t Type: %s\n", location, binding, offset, resource.name.c_str());


			}

			/* Shader outputs */
			for (auto& resource : resources.stage_outputs)
			{
				unsigned location = _glslCompiler.get_decoration(resource.id, spv::DecorationLocation);
				unsigned binding = _glslCompiler.get_decoration(resource.id, spv::DecorationBinding);
				printf("Location: %u\t Binding: %u\t Type: %s\n", location, binding, resource.name.c_str());
			}

			/* Shader subpass inputs */
			for (auto& resource : resources.subpass_inputs)
			{
				unsigned set = _glslCompiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
				unsigned binding = _glslCompiler.get_decoration(resource.id, spv::DecorationBinding);
				printf("Set: %u\t Binding: %u\t Type: %s\n", set, binding, resource.name.c_str());

				_binding.binding = binding;
				_binding.descriptorCount = 1;
				_binding.descriptorType = VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
				layoutBindings.pushBack(_binding);
			}

			/* Shader storage images */
			for (auto& resource : resources.storage_images)
			{
				unsigned set = _glslCompiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
				unsigned binding = _glslCompiler.get_decoration(resource.id, spv::DecorationBinding);
				printf("Set: %u\t Binding: %u\t Type: %s\n", set, binding, resource.name.c_str());

				_binding.binding = binding;
				_binding.descriptorCount = 1;
				_binding.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
				layoutBindings.pushBack(_binding);
			}

			/* Shader sampled images */
			for (auto& resource : resources.sampled_images)
			{
				unsigned set = _glslCompiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
				unsigned binding = _glslCompiler.get_decoration(resource.id, spv::DecorationBinding);
				printf("Set: %u\t Binding: %u\t Type: %s\n", set, binding, resource.name.c_str());

				_binding.binding = binding;
				_binding.descriptorCount = 1;
				_binding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
				layoutBindings.pushBack(_binding);
			}

			/* Shader atomic counters */
			for (auto& resource : resources.atomic_counters)
			{
				unsigned set = _glslCompiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
				unsigned binding = _glslCompiler.get_decoration(resource.id, spv::DecorationBinding);
				printf("Set: %u\t Binding: %u\t Type: %s\n", set, binding, resource.name.c_str());
			}

			/* Shader acceleration structures*/
			for (auto& resource : resources.acceleration_structures)
			{
				unsigned set = _glslCompiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
				unsigned binding = _glslCompiler.get_decoration(resource.id, spv::DecorationBinding);
				printf("Set: %u\t Binding: %u\t Type: %s\n", set, binding, resource.name.c_str());

				_binding.binding = binding;
				_binding.descriptorCount = 1;
				_binding.descriptorType = VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV;
				layoutBindings.pushBack(_binding);
			}

			/* Shader push constant buffers */
			for (auto& resource : resources.push_constant_buffers)
			{
				unsigned set = _glslCompiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
				unsigned binding = _glslCompiler.get_decoration(resource.id, spv::DecorationBinding);
				printf("Set: %u\t Binding: %u\t Type: %s\n", set, binding, resource.name.c_str());

				for (UI32 index = 0; index < _glslCompiler.get_type(resource.base_type_id).member_types.size(); index++)
					printf("\tMembers: %s\n", _glslCompiler.get_member_name(resource.base_type_id, index).c_str());
			}

			/* Shader separate images */
			for (auto& resource : resources.separate_images)
			{
				unsigned set = _glslCompiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
				unsigned binding = _glslCompiler.get_decoration(resource.id, spv::DecorationBinding);
				printf("Set: %u\t Binding: %u\t Type: %s\n", set, binding, resource.name.c_str());

				_binding.binding = binding;
				_binding.descriptorCount = 1;
				_binding.descriptorType = VK_DESCRIPTOR_TYPE_SAMPLER;
				layoutBindings.pushBack(_binding);
			}

			/* Shader samplers */
			for (auto& resource : resources.separate_samplers)
			{
				unsigned set = _glslCompiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
				unsigned binding = _glslCompiler.get_decoration(resource.id, spv::DecorationBinding);
				printf("Set: %u\t Binding: %u\t Type: %s\n", set, binding, resource.name.c_str());
			}

			VkDescriptorSetLayoutCreateInfo createInfo;
			createInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
			createInfo.flags = VK_NULL_HANDLE;
			createInfo.pNext = VK_NULL_HANDLE;
			createInfo.bindingCount = layoutBindings.size();
			createInfo.pBindings = layoutBindings.data();

			VkDescriptorSetLayout _layout;
			DMK_VULKAN_ASSERT(vkCreateDescriptorSetLayout(vDevice, &createInfo, nullptr, &_layout), "Failed to create descriptor set layout!");

			return _layout;
		}

		VulkanShader::operator VkShaderModule() const
		{
			return this->shaderModule;
		}
	}
}