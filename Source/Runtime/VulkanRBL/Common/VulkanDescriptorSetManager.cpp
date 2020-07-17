// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanDescriptorSetManager.h"

#include "../VulkanUtilities.h"

namespace Dynamik
{
	namespace Backend
	{
		VulkanDescriptor VulkanDescriptorSetManager::createDescriptor(const VulkanDevice& vDevice, ARRAY<ARRAY<VkDescriptorSetLayoutBinding>> layouts, ARRAY<ARRAY<VkDescriptorPoolSize>> poolSizes)
		{
			VulkanDescriptor _descriptor;

			/* Initialize basic data */
			ARRAY<VkDescriptorSetLayoutBinding> _finalBindings;
			ARRAY<VkDescriptorPoolSize> _finalSizes;

			for (auto _layout : layouts)
				for (auto _binding : _layout)
					_finalBindings.pushBack(_binding);

			for (auto _pool : poolSizes)
				for (auto _size : _pool)
					_finalSizes.pushBack(_size);

			/* Initialize layout */
			VkDescriptorSetLayoutCreateInfo layoutCrateInfo;
			layoutCrateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
			layoutCrateInfo.flags = VK_NULL_HANDLE;
			layoutCrateInfo.pNext = VK_NULL_HANDLE;
			layoutCrateInfo.bindingCount = Cast<UI32>(_finalBindings.size());
			layoutCrateInfo.pBindings = _finalBindings.data();

			DMK_VULKAN_ASSERT(vkCreateDescriptorSetLayout(vDevice, &layoutCrateInfo, nullptr, &_descriptor.layout), "Failed to create descriptor set layout!");

			/* Initialize pool */
			VkDescriptorPoolCreateInfo poolCreateInfo;
			poolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
			poolCreateInfo.flags = VK_NULL_HANDLE;
			poolCreateInfo.pNext = VK_NULL_HANDLE;
			poolCreateInfo.maxSets = 1;
			poolCreateInfo.poolSizeCount = Cast<UI32>(_finalSizes.size());
			poolCreateInfo.pPoolSizes = _finalSizes.data();
			
			DMK_VULKAN_ASSERT(vkCreateDescriptorPool(vDevice, &poolCreateInfo, VK_NULL_HANDLE, &_descriptor.pool), "Failed to create descriptor pool!");

			/* Initialize set */
			VkDescriptorSetAllocateInfo setAllocateInfo;
			setAllocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
			setAllocateInfo.pNext = VK_NULL_HANDLE;
			setAllocateInfo.descriptorSetCount = 1;
			setAllocateInfo.descriptorPool = _descriptor.pool;
			setAllocateInfo.pSetLayouts = &_descriptor.layout;

			DMK_VULKAN_ASSERT(vkAllocateDescriptorSets(vDevice, &setAllocateInfo, &_descriptor.set), "Failed to allocate descriptor sets!");

			return _descriptor;
		}

		void VulkanDescriptorSetManager::terminateDescriptor(const VulkanDevice& vDevice, const VulkanDescriptor& vDescriptor)
		{
			vkDestroyDescriptorSetLayout(vDevice, vDescriptor.layout, VK_NULL_HANDLE);
			vkDestroyDescriptorPool(vDevice, vDescriptor.pool, VK_NULL_HANDLE);
		}

		void VulkanDescriptorSetManager::updateDescriptor(const VulkanDevice& vDevice, const VkDescriptorSet vSet, ARRAY<std::pair<VkDescriptorBufferInfo, UI32>> bufferInfos, ARRAY<VkDescriptorImageInfo> imageInfos, ARRAY<ARRAY<VkDescriptorSetLayoutBinding>> layouts)
		{
			ARRAY<VkWriteDescriptorSet> descriptorWrites;
			UI64 bufferIndex = 0;
			UI64 imageIndex = 0;

			VkWriteDescriptorSet _write;
			_write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			_write.pNext = VK_NULL_HANDLE;

			_write.dstArrayElement = VK_NULL_HANDLE;

			_write.pTexelBufferView = VK_NULL_HANDLE;
			_write.pBufferInfo = VK_NULL_HANDLE;
			_write.pImageInfo = VK_NULL_HANDLE;

			for (auto _layouts : layouts)
			{
				for (auto _binding : _layouts)
				{
					_write.descriptorCount = 1;
					_write.descriptorType = _binding.descriptorType;
					_write.dstBinding = _binding.binding;
					_write.dstSet = vSet;

					switch (_binding.descriptorType)
					{
					case VK_DESCRIPTOR_TYPE_SAMPLER:
						_write.pImageInfo = &imageInfos[imageIndex++];
						break;
					case VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER:
						_write.pImageInfo = &imageInfos[imageIndex++];
						break;
					case VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE:
						_write.pImageInfo = &imageInfos[imageIndex++];
						break;
					case VK_DESCRIPTOR_TYPE_STORAGE_IMAGE:
						_write.pImageInfo = &imageInfos[imageIndex++];
						break;
					case VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER:
						_write.pBufferInfo = &bufferInfos[bufferIndex].first;
						_write.dstBinding = bufferInfos[bufferIndex++].second;
						break;
					case VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER:
						_write.pBufferInfo = &bufferInfos[bufferIndex].first;
						_write.dstBinding = bufferInfos[bufferIndex++].second;
						break;
					case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER:
						_write.pBufferInfo = &bufferInfos[bufferIndex].first;
						_write.dstBinding = bufferInfos[bufferIndex++].second;
						break;
					case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER:
						_write.pBufferInfo = &bufferInfos[bufferIndex].first;
						_write.dstBinding = bufferInfos[bufferIndex++].second;
						break;
					case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC:
						_write.pBufferInfo = &bufferInfos[bufferIndex].first;
						_write.dstBinding = bufferInfos[bufferIndex++].second;
						break;
					case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC:
						_write.pBufferInfo = &bufferInfos[bufferIndex].first;
						_write.dstBinding = bufferInfos[bufferIndex++].second;
						break;
					case VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT:
						DMK_ERROR_BOX("Unsupported descriptor type!");
						break;
					case VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK_EXT:
						DMK_ERROR_BOX("Unsupported descriptor type!");
						break;
					case VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV:
						DMK_ERROR_BOX("Unsupported descriptor type!");
						break;
					default:
						DMK_ERROR_BOX("Invalid descriptor type!");
						break;
					}

					descriptorWrites.pushBack(_write);
				}
			}

			vkUpdateDescriptorSets(vDevice, Cast<UI32>(descriptorWrites.size()), descriptorWrites.data(), VK_NULL_HANDLE, VK_NULL_HANDLE);
		}
	}
}
