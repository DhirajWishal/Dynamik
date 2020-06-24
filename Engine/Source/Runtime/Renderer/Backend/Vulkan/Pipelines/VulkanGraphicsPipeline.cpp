#include "dmkafx.h"
#include "VulkanGraphicsPipeline.h"

#include "../VulkanCoreObject.h"
#include "Tools/Shader/SPIR-V/Disassembler.h"

namespace Dynamik
{
	namespace Backend
	{
		UI32 getAttributeSize(VkFormat format)
		{
			switch (format)
			{
			case VK_FORMAT_R32_SFLOAT:
				return sizeof(F32) * 1;
			case VK_FORMAT_R32G32_SFLOAT:
				return sizeof(F32) * 2;
			case VK_FORMAT_R32G32B32_SFLOAT:
				return sizeof(F32) * 3;
			case VK_FORMAT_R32G32B32A32_SFLOAT:
				return sizeof(F32) * 4;
			default:
				DMK_ERROR_BOX("Unsupported attribute size!");
				break;
			}

			return 0;
		}

		void VulkanGraphicsPipeline::initialize(RCoreObject* pCoreObject, RPipelineCreateInfo createInfo, RPipelineUsage usage)
		{
			ARRAY<VkDescriptorSetLayout> descriptorLayouts;

			VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
			vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
			vertexInputInfo.vertexBindingDescriptionCount = 1;
			ARRAY<VkVertexInputAttributeDescription> inputBindings;
			for (auto shaderModule : createInfo.shaders)
			{
				Tools::SPIRVDisassembler _dissassembler(shaderModule);
				auto descriptorLayoutBindings = _dissassembler.getDescriptorSetLayoutBindings();
				auto descriptorPoolSizes = _dissassembler.getDescriptorPoolSizes();

				if (shaderModule.location == DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX)
				{
					inputBindings = std::move(_dissassembler.getVertexAttributeDescriptions());

					VkVertexInputBindingDescription vertexInputBinding;
					vertexInputBinding.inputRate = VkVertexInputRate::VK_VERTEX_INPUT_RATE_VERTEX;
					vertexInputBinding.binding = 0;
					vertexInputBinding.stride = inputBindings[-1].offset + getAttributeSize(inputBindings[-1].format);
				
					vertexInputInfo.vertexAttributeDescriptionCount = inputBindings.size();
					vertexInputInfo.pVertexBindingDescriptions = &vertexInputBinding;
					vertexInputInfo.pVertexAttributeDescriptions = inputBindings.data();
				}

				VDescriptor descriptor;
				/* Create descriptor set layout */
				VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo;
				descriptorSetLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
				descriptorSetLayoutCreateInfo.flags = VK_NULL_HANDLE;
				descriptorSetLayoutCreateInfo.pNext = VK_NULL_HANDLE;
				descriptorSetLayoutCreateInfo.bindingCount = descriptorLayoutBindings.size();
				descriptorSetLayoutCreateInfo.pBindings = descriptorLayoutBindings.data();

				DMK_VULKAN_ASSERT(vkCreateDescriptorSetLayout(InheritCast<VulkanCoreObject>(pCoreObject).device, &descriptorSetLayoutCreateInfo, nullptr, &descriptor.layout), "Failed to create descriptor set layout!");

				/* Create descriptor pool */
				VkDescriptorPoolCreateInfo descriptorPoolCreateInfo;
				descriptorPoolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
				descriptorPoolCreateInfo.flags = VK_NULL_HANDLE;
				descriptorPoolCreateInfo.pNext = VK_NULL_HANDLE;
				descriptorPoolCreateInfo.maxSets = 1;
				descriptorPoolCreateInfo.poolSizeCount = descriptorPoolSizes.size();
				descriptorPoolCreateInfo.pPoolSizes = descriptorPoolSizes.data();

				DMK_VULKAN_ASSERT(vkCreateDescriptorPool(InheritCast<VulkanCoreObject>(pCoreObject).device, &descriptorPoolCreateInfo, VK_NULL_HANDLE, &descriptor.pool), "Failed to create descriptor pool!");

				/* Allocate descriptor set */
				VkDescriptorSetAllocateInfo descriptorSetAllocateInfo;
				descriptorSetAllocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
				descriptorSetAllocateInfo.pNext = VK_NULL_HANDLE;
				descriptorSetAllocateInfo.descriptorPool = descriptor.pool;
				descriptorSetAllocateInfo.pSetLayouts = &descriptor.layout;
				descriptorSetAllocateInfo.descriptorSetCount = 1;

				DMK_VULKAN_ASSERT(vkAllocateDescriptorSets(InheritCast<VulkanCoreObject>(pCoreObject).device, &descriptorSetAllocateInfo, &descriptor.set), "Failed to allocate descriptor sets!");

				descriptors.pushBack(descriptor);
				descriptorLayouts.pushBack(descriptor.layout);
			}
		}

		void VulkanGraphicsPipeline::terminate(RCoreObject* pCoreObject)
		{
		}
	}
}
