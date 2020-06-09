#include "dmkafx.h"
#include "VulkanDescriptorSetManager.h"

#include "VulkanUtilities.h"

namespace Dynamik
{
	namespace Backend
	{
		//VulkanDescriptor VulkanDescriptorSetManager::createDescriptor(const VulkanDevice& vDevice, VulkanRenderableMesh meshComponent)
		//{
		//	DMKUniformBufferDescriptor _descriptor;
		//
		//	VulkanDescriptor _newDescriptor;
		//
		//	/* Initialize descriptor layout */
		//	VkDescriptorSetLayoutCreateInfo initInfo;
		//	initInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		//	initInfo.pNext = VK_NULL_HANDLE;
		//
		//	auto bindings = VulkanUtilities::getDescriptorSetLayoutBindings(meshComponent.meshComponent->renderSpecifications.shaderModules);
		//	initInfo.bindingCount = bindings.size();
		//	initInfo.pBindings = bindings.data();
		//
		//	DMK_VULKAN_ASSERT(vkCreateDescriptorSetLayout(vDevice, &initInfo, nullptr, &_newDescriptor.layout), "Failed to create descriptor set layout!");
		//
		//	/* Initialize descriptor pool */
		//	VkDescriptorPoolCreateInfo poolCreateInfo;
		//	poolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		//	poolCreateInfo.flags = VK_NULL_HANDLE;
		//	poolCreateInfo.pNext = VK_NULL_HANDLE;
		//
		//	auto _poolSizes = VulkanUtilities::getDescriptorPoolSizes(_descriptor, 1);
		//
		//	poolCreateInfo.poolSizeCount = _poolSizes.size();
		//	poolCreateInfo.pPoolSizes = _poolSizes.data();
		//	poolCreateInfo.maxSets = 1;
		//
		//	DMK_VULKAN_ASSERT(vkCreateDescriptorPool(vDevice, &poolCreateInfo, nullptr, &_newDescriptor.pool), "Failed to create descriptor pool!");
		//
		//	/* Initialize descriptor sets */
		//	VkDescriptorSetAllocateInfo setAllocateInfo;
		//	setAllocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		//	setAllocateInfo.pNext = VK_NULL_HANDLE;
		//	setAllocateInfo.descriptorPool = _newDescriptor.pool;
		//	setAllocateInfo.pSetLayouts = &_newDescriptor.layout;
		//	setAllocateInfo.descriptorSetCount = 1;
		//
		//	DMK_VULKAN_ASSERT(vkAllocateDescriptorSets(vDevice, &setAllocateInfo, &_newDescriptor.set), "Failed to allocate descriptor sets!");
		//
		//	return _newDescriptor;
		//}

		B1 VulkanDescriptorSetManager::_isNewAvailable(I64 ID)
		{
			//for (auto _descriptor : descriptors)
			//	if (_descriptor.baseID == ID)
			//		return false;
			//
			return true;
		}
	}
}
