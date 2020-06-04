#include "dmkafx.h"
#include "VulkanDescriptorSetManager.h"

#include "VulkanUtilities.h"

namespace Dynamik
{
	namespace Backend
	{
		VulkanDescriptorSetManager::VulkanDescriptor::operator VkDescriptorSetLayout() const
		{
			return this->layout;
		}

		VulkanDescriptorSetManager::VulkanDescriptor::operator VkDescriptorPool() const
		{
			return this->pool;
		}

		const VkDescriptorSet VulkanDescriptorSetManager::VulkanDescriptor::operator[](I32 index) const
		{
			return this->sets[index];
		}

		VkDescriptorSet VulkanDescriptorSetManager::VulkanDescriptor::get()
		{
			return this->sets[this->nextSet++];
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

			_newDescriptor.sets.resize(setCount);
			DMK_VULKAN_ASSERT(vkAllocateDescriptorSets(vDevice, &setAllocateInfo, _newDescriptor.sets.data()), "Failed to allocate descriptor sets!");

			descriptors.pushBack(_newDescriptor);
		}

		void VulkanDescriptorSetManager::terminateDescriptor(const VulkanDevice& vDevice, I64 ID)
		{
			for (UI32 index = 0; index < descriptors.size(); index++)
			{
				if (descriptors[index].baseID == ID)
				{
					vkDestroyDescriptorPool(vDevice, descriptors[index], nullptr);
					vkDestroyDescriptorSetLayout(vDevice, descriptors[index], nullptr);

					descriptors.remove(index);
					return;
				}
			}
		}

		void VulkanDescriptorSetManager::terminate(const VulkanDevice& vDevice)
		{
			for (auto _descriptor : descriptors)
			{
				vkDestroyDescriptorPool(vDevice, _descriptor, nullptr);
				vkDestroyDescriptorSetLayout(vDevice, _descriptor, nullptr);
			}

			descriptors.clear();
		}

		B1 VulkanDescriptorSetManager::_isNewAvailable(I64 ID)
		{
			for (auto _descriptor : descriptors)
				if (_descriptor.baseID == ID)
					return false;

			return true;
		}
	}
}
