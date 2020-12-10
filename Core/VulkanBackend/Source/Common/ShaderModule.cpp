// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/Common/ShaderModule.h"
#include "VulkanBackend/Common/VulkanDevice.h"

namespace DMK
{
	namespace VulkanBackend
	{
		namespace _Helpers
		{
			/**
			 * Get VkShaderStageFlags from GraphicsCore::ShaderLocation.
			 *
			 * @param location: The shader location.
			 * @return VkShaderStageFlags enum.
			 */
			DMK_FORCEINLINE VkShaderStageFlags GetShaderStageFlag(GraphicsCore::ShaderLocation location)
			{
				switch (location)
				{
				case DMK::GraphicsCore::ShaderLocation::ALL:
					return VkShaderStageFlagBits::VK_SHADER_STAGE_ALL;

				case DMK::GraphicsCore::ShaderLocation::VERTEX:
					return VkShaderStageFlagBits::VK_SHADER_STAGE_VERTEX_BIT;

				case DMK::GraphicsCore::ShaderLocation::TESSELLATION:
					return VkShaderStageFlagBits::VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT | VkShaderStageFlagBits::VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;

				case DMK::GraphicsCore::ShaderLocation::GEOMETRY:
					return VkShaderStageFlagBits::VK_SHADER_STAGE_GEOMETRY_BIT;

				case DMK::GraphicsCore::ShaderLocation::FRAGMENT:
					return VkShaderStageFlagBits::VK_SHADER_STAGE_FRAGMENT_BIT;

				case DMK::GraphicsCore::ShaderLocation::COMPUTE:
					return VkShaderStageFlagBits::VK_SHADER_STAGE_COMPUTE_BIT;

				case DMK::GraphicsCore::ShaderLocation::ALL_GRAPHICS:
					return VkShaderStageFlagBits::VK_SHADER_STAGE_ALL_GRAPHICS;

				case DMK::GraphicsCore::ShaderLocation::RAY_GEN:
					return VkShaderStageFlagBits::VK_SHADER_STAGE_RAYGEN_BIT_KHR | VkShaderStageFlagBits::VK_SHADER_STAGE_RAYGEN_BIT_NV;

				case DMK::GraphicsCore::ShaderLocation::ANY_HIT:
					return VkShaderStageFlagBits::VK_SHADER_STAGE_ANY_HIT_BIT_KHR | VkShaderStageFlagBits::VK_SHADER_STAGE_ANY_HIT_BIT_NV;

				case DMK::GraphicsCore::ShaderLocation::CLOSEST_HIT:
					return VkShaderStageFlagBits::VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR | VkShaderStageFlagBits::VK_SHADER_STAGE_CLOSEST_HIT_BIT_NV;

				case DMK::GraphicsCore::ShaderLocation::MISS:
					return VkShaderStageFlagBits::VK_SHADER_STAGE_MISS_BIT_KHR | VkShaderStageFlagBits::VK_SHADER_STAGE_MISS_BIT_NV;

				case DMK::GraphicsCore::ShaderLocation::INTERSECTION:
					return VkShaderStageFlagBits::VK_SHADER_STAGE_INTERSECTION_BIT_KHR | VkShaderStageFlagBits::VK_SHADER_STAGE_INTERSECTION_BIT_NV;

				case DMK::GraphicsCore::ShaderLocation::CALLABLE:
					return VkShaderStageFlagBits::VK_SHADER_STAGE_CALLABLE_BIT_KHR | VkShaderStageFlagBits::VK_SHADER_STAGE_CALLABLE_BIT_NV;

				case DMK::GraphicsCore::ShaderLocation::TASK:
					return VkShaderStageFlagBits::VK_SHADER_STAGE_TASK_BIT_NV;

				case DMK::GraphicsCore::ShaderLocation::MESH:
					return VkShaderStageFlagBits::VK_SHADER_STAGE_MESH_BIT_NV;

				default:
					Logger::LogError(TEXT("Invalid Shader Location!"));

				}

				return VkShaderStageFlagBits::VK_SHADER_STAGE_ALL;
			}

			/**
			 * Get the VkDescriptorType using GraphicsCore::UniformType.
			 *
			 * @param type: The uniform type.
			 * @return VkDescriptorType enum.
			 */
			DMK_FORCEINLINE VkDescriptorType GetDescriptorType(GraphicsCore::UniformType type)
			{
				switch (type)
				{
				case GraphicsCore::UniformType::UNIFORM_BUFFER:
					return VkDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;

				case GraphicsCore::UniformType::STORAGE_BUFFER:
					return VkDescriptorType::VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;

				case GraphicsCore::UniformType::UNIFORM_BUFFER_DYNAMIC:
					return VkDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;

				case GraphicsCore::UniformType::STORAGE_BUFFER_DYNAMIC:
					return VkDescriptorType::VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;

				case GraphicsCore::UniformType::UNIFORM_TEXEL_BUFFER:
					return VkDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;

				case GraphicsCore::UniformType::STORAGE_TEXEL_BUFFER:
					return VkDescriptorType::VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER;

				case GraphicsCore::UniformType::INPUT_ATTACHMENT:
					return VkDescriptorType::VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;

				case GraphicsCore::UniformType::STORAGE_IMAGE:
					return VkDescriptorType::VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;

				case GraphicsCore::UniformType::CONSTANT:
					break;	/* Doesn't have to do anything here. */

				case GraphicsCore::UniformType::SAMPLER_2D:
					return VkDescriptorType::VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;

				case GraphicsCore::UniformType::SAMPLER_CUBE:
					return VkDescriptorType::VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;

				case GraphicsCore::UniformType::SAMPLER_2D_ARRAY:
					return VkDescriptorType::VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;

				case GraphicsCore::UniformType::SAMPLER_CUBE_ARRAY:
					return VkDescriptorType::VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;

				case GraphicsCore::UniformType::ACCELERATION_STRUCTURE:
					return VkDescriptorType::VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR;

				default:
					Logger::LogError(TEXT("Invalid Uniform type!"));
					break;
				}

				return VkDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			}

			/**
			 * Get VkFormat using DataType.
			 *
			 * @param type: The type.
			 * @return VkFormat enum.
			 */
			DMK_FORCEINLINE VkFormat GetFormat(DataType type)
			{
				if (type == DataType::VEC3)
					return VkFormat::VK_FORMAT_R32G32B32A32_SFLOAT;
				else if (type == DataType::VEC2)
					return VkFormat::VK_FORMAT_R32G32_SFLOAT;
				else if (type == DataType::I32)
					return VkFormat::VK_FORMAT_R32_SFLOAT;

				return VkFormat::VK_FORMAT_UNDEFINED;
			}
		}

		ShaderModule VulkanDevice::CreateShaderModule(const GraphicsCore::ShaderCode& code)
		{
			ShaderModule vShaderModule = {};
			vShaderModule.Initialize(*this, code);

			return vShaderModule;
		}

		void ShaderModule::Initialize(const VulkanDevice& vDevice, const GraphicsCore::ShaderCode& shaderCode)
		{
			VkShaderModuleCreateInfo vCInfo = {};
			vCInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
			vCInfo.flags = VK_NULL_HANDLE;
			vCInfo.pNext = VK_NULL_HANDLE;
			vCInfo.codeSize = static_cast<UI32>(shaderCode.mShaderCode.size());
			vCInfo.pCode = shaderCode.mShaderCode.data();
			vShaderStage = _Helpers::GetShaderStageFlag(shaderCode.GetLocation());

			// Create the shader module.
			DMK_VK_ASSERT(vkCreateShaderModule(vDevice, &vCInfo, nullptr, &vShaderModule), "Failed to create Vulkan Shader Module!");

			// Resolve descriptor set layout bindings and pool sizes.
			{
				VkDescriptorSetLayoutBinding vBinding = {};
				vBinding.stageFlags = vShaderStage;
				vBinding.pImmutableSamplers = VK_NULL_HANDLE;
				vBinding.descriptorCount = 1;

				VkDescriptorPoolSize vPoolSize = {};
				vPoolSize.descriptorCount = 1;

				VkPushConstantRange vPCRange = {};
				vPCRange.stageFlags = vShaderStage;
				vPCRange.offset = 0;

				for (auto itr = shaderCode.mUniforms.begin(); itr != shaderCode.mUniforms.end(); itr++)
				{
					// Process push constants.
					if (itr->GetType() == GraphicsCore::UniformType::CONSTANT)
					{
						vPCRange.size = static_cast<UI32>(itr->Size());

						vPushConstantRanges.insert(vPushConstantRanges.end(), vPCRange);
						vPCRange.offset += vPCRange.size;
					}
					else
					{
						vBinding.binding = static_cast<UI32>(itr->GetBinding());
						vBinding.descriptorType = _Helpers::GetDescriptorType(itr->GetType());
						vPoolSize.type = vBinding.descriptorType;

						vLayoutBindings.insert(vLayoutBindings.end(), vBinding);
						vDescriptorPoolSizes.insert(vDescriptorPoolSizes.end(), vPoolSize);
					}
				}
			}

			// Resolve the inputs only if the shader location is vertex.
			if (shaderCode.GetLocation() == GraphicsCore::ShaderLocation::VERTEX)
			{
				VkVertexInputAttributeDescription vAttribute = {};

				VkVertexInputBindingDescription vBinding = {};
				vBinding.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
				vBinding.stride = 0;

				std::unordered_map<UI32, UI64> bindingMap;

				// Resolve bindings and attributes.
				for (auto itr = shaderCode.mInputAttributes.begin(); itr != shaderCode.mInputAttributes.end(); itr++)
				{
					vAttribute.binding = static_cast<UI32>(itr->mBinding);
					vAttribute.location = static_cast<UI32>(itr->mLocation);
					vAttribute.offset = static_cast<UI32>(itr->mOffset);
					vAttribute.format = _Helpers::GetFormat(itr->mDataType);
					vInputAttributes.insert(vInputAttributes.end(), std::move(vAttribute));

					vBinding.binding = static_cast<UI32>(itr->mBinding);
					vBinding.stride += static_cast<UI32>(itr->mDataType);

					if (bindingMap.find(vBinding.binding) != bindingMap.end())
						vInputBindings.at(bindingMap[vBinding.binding]) = vBinding;
					else
					{
						vInputBindings.insert(vInputBindings.end(), vBinding);
						bindingMap[vBinding.binding] = vInputBindings.size() - 1;
					}
				}
			}
		}

		void ShaderModule::Terminate(const VulkanDevice& vDevice)
		{
			// Destroy the shader module.
			vkDestroyShaderModule(vDevice, vShaderModule, nullptr);
		}
	}
}