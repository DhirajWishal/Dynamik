#include "dmkafx.h"
#include "VulkanDescriptorSetManager.h"

#include "VulkanUtilities.h"

namespace Dynamik
{
	namespace Backend
	{
		std::pair<VulkanBuffer, VulkanDescriptor> VulkanDescriptorSetManager::createCameraDescriptor(const VulkanDevice& vDevice, UI32 binding)
		{
			std::pair<VulkanBuffer, VulkanDescriptor> _pair;

			/* Create uniform buffer */
			_pair.first.initialize(vDevice, BufferType::BUFFER_TYPE_UNIFORM, sizeof(MAT4F) * 2);

			/* Initialize descriptor layout */
			VkDescriptorSetLayoutBinding _binding;
			_binding.binding = binding;
			_binding.descriptorCount = 1;
			_binding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			_binding.pImmutableSamplers = VK_NULL_HANDLE;
			_binding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

			VkDescriptorSetLayoutCreateInfo initInfo;
			initInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
			initInfo.pNext = VK_NULL_HANDLE;
			initInfo.bindingCount = 1;
			initInfo.pBindings = &_binding;

			DMK_VULKAN_ASSERT(vkCreateDescriptorSetLayout(vDevice, &initInfo, nullptr, &_pair.second.layout), "Failed to create descriptor set layout!");

			/* Create descriptor pool */
			VkDescriptorPoolSize _size;
			_size.descriptorCount = 1;
			_size.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;

			VkDescriptorPoolCreateInfo poolInitInfo;
			poolInitInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
			poolInitInfo.pNext = VK_NULL_HANDLE;
			poolInitInfo.flags = VK_NULL_HANDLE;
			poolInitInfo.maxSets = 1;
			poolInitInfo.poolSizeCount = 1;
			poolInitInfo.pPoolSizes = &_size;

			DMK_VULKAN_ASSERT(vkCreateDescriptorPool(vDevice, &poolInitInfo, nullptr, &_pair.second.pool), "Failed to create descriptor pool!");

			/* Create descriptor sets */
			VkDescriptorSetAllocateInfo setAllocateInfo;
			setAllocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
			setAllocateInfo.pNext = VK_NULL_HANDLE;
			setAllocateInfo.descriptorSetCount = 1;
			setAllocateInfo.descriptorPool = _pair.second.pool;
			setAllocateInfo.pSetLayouts = &_pair.second.layout;

			DMK_VULKAN_ASSERT(vkAllocateDescriptorSets(vDevice, &setAllocateInfo, &_pair.second.set), "Failed to allocate descriptor sets!");

			VkDescriptorBufferInfo _bufferInfo;
			_bufferInfo.buffer = _pair.first;
			_bufferInfo.offset = 0;
			_bufferInfo.range = sizeof(MAT4F) * 2;

			VkWriteDescriptorSet _write;
			_write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			_write.descriptorCount = 1;
			_write.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			_write.dstArrayElement = 1;
			_write.dstBinding = binding;
			_write.dstSet = _pair.second.set;
			_write.pBufferInfo = &_bufferInfo;
			_write.pNext = VK_NULL_HANDLE;

			vkUpdateDescriptorSets(vDevice, 1, &_write, 0, VK_NULL_HANDLE);

			return _pair;
		}

		void VulkanDescriptorSetManager::createDescriptor(const VulkanDevice& vDevice, const DMKUniformBufferDescriptor& descriptor, I64 ID, UI32 setCount)
		{
			/* Check if the requested descriptor ID already exists */
			if (!_isNewAvailable(ID))
			{
				DMKErrorManager::issueWarnBox("Requested descriptor is already created!");
				return;
			}

			VulkanDescriptor _newDescriptor;

			/* Initialize descriptor layout */
			VkDescriptorSetLayoutCreateInfo initInfo;
			initInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
			initInfo.pNext = VK_NULL_HANDLE;

			auto bindings = VulkanUtilities::getDescriptorSetLayoutBindings(descriptor);
			initInfo.bindingCount = bindings.size();
			initInfo.pBindings = bindings.data();

			DMK_VULKAN_ASSERT(vkCreateDescriptorSetLayout(vDevice, &initInfo, nullptr, &_newDescriptor.layout), "Failed to create descriptor set layout!");

			/* Initialize descriptor pool */
			VkDescriptorPoolCreateInfo poolCreateInfo;
			poolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
			poolCreateInfo.flags = VK_NULL_HANDLE;
			poolCreateInfo.pNext = VK_NULL_HANDLE;

			auto _poolSizes = VulkanUtilities::getDescriptorPoolSizes(descriptor, setCount);

			poolCreateInfo.poolSizeCount = _poolSizes.size();
			poolCreateInfo.pPoolSizes = _poolSizes.data();
			poolCreateInfo.maxSets = setCount;

			DMK_VULKAN_ASSERT(vkCreateDescriptorPool(vDevice, &poolCreateInfo, nullptr, &_newDescriptor.pool), "Failed to create descriptor pool!");

			/* Initialize descriptor sets */
			VkDescriptorSetAllocateInfo setAllocateInfo;
			setAllocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
			setAllocateInfo.pNext = VK_NULL_HANDLE;
			setAllocateInfo.descriptorPool = _newDescriptor.pool;
			setAllocateInfo.pSetLayouts = &_newDescriptor.layout;
			setAllocateInfo.descriptorSetCount = setCount;

			//_newDescriptor.sets.resize(setCount);
			DMK_VULKAN_ASSERT(vkAllocateDescriptorSets(vDevice, &setAllocateInfo, &_newDescriptor.set), "Failed to allocate descriptor sets!");

			descriptors.pushBack(_newDescriptor);
		}

		void VulkanDescriptorSetManager::terminateDescriptor(const VulkanDevice& vDevice, I64 ID)
		{
			//for (UI32 index = 0; index < descriptors.size(); index++)
			//{
			//	if (descriptors[index].baseID == ID)
			//	{
			//		vkDestroyDescriptorPool(vDevice, descriptors[index], nullptr);
			//		vkDestroyDescriptorSetLayout(vDevice, descriptors[index], nullptr);
			//
			//		descriptors.remove(index);
			//		return;
			//	}
			//}
		}

		void VulkanDescriptorSetManager::terminate(const VulkanDevice& vDevice)
		{
			//for (auto _descriptor : descriptors)
			//{
			//	vkDestroyDescriptorPool(vDevice, _descriptor, nullptr);
			//	vkDestroyDescriptorSetLayout(vDevice, _descriptor, nullptr);
			//}
			//
			//descriptors.clear();
		}

		VulkanDescriptor VulkanDescriptorSetManager::createDescriptor(const VulkanDevice& vDevice, VulkanRenderableMesh meshComponent)
		{
			DMKUniformBufferDescriptor _descriptor;
		
			VulkanDescriptor _newDescriptor;

			/* Initialize descriptor layout */
			VkDescriptorSetLayoutCreateInfo initInfo;
			initInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
			initInfo.pNext = VK_NULL_HANDLE;

			auto bindings = VulkanUtilities::getDescriptorSetLayoutBindings(_descriptor);
			initInfo.bindingCount = bindings.size();
			initInfo.pBindings = bindings.data();

			DMK_VULKAN_ASSERT(vkCreateDescriptorSetLayout(vDevice, &initInfo, nullptr, &_newDescriptor.layout), "Failed to create descriptor set layout!");
		
			/* Initialize descriptor pool */
			VkDescriptorPoolCreateInfo poolCreateInfo;
			poolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
			poolCreateInfo.flags = VK_NULL_HANDLE;
			poolCreateInfo.pNext = VK_NULL_HANDLE;

			auto _poolSizes = VulkanUtilities::getDescriptorPoolSizes(_descriptor, 1);

			poolCreateInfo.poolSizeCount = _poolSizes.size();
			poolCreateInfo.pPoolSizes = _poolSizes.data();
			poolCreateInfo.maxSets = 1;

			DMK_VULKAN_ASSERT(vkCreateDescriptorPool(vDevice, &poolCreateInfo, nullptr, &_newDescriptor.pool), "Failed to create descriptor pool!");

			/* Initialize descriptor sets */
			VkDescriptorSetAllocateInfo setAllocateInfo;
			setAllocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
			setAllocateInfo.pNext = VK_NULL_HANDLE;
			setAllocateInfo.descriptorPool = _newDescriptor.pool;
			setAllocateInfo.pSetLayouts = &_newDescriptor.layout;
			setAllocateInfo.descriptorSetCount = 1;

			DMK_VULKAN_ASSERT(vkAllocateDescriptorSets(vDevice, &setAllocateInfo, &_newDescriptor.set), "Failed to allocate descriptor sets!");

		}

		B1 VulkanDescriptorSetManager::_isNewAvailable(I64 ID)
		{
			//for (auto _descriptor : descriptors)
			//	if (_descriptor.baseID == ID)
			//		return false;
			//
			//return true;
		}
	}
}
