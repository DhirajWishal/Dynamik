#include "dmkafx.h"
#include "VulkanDescriptor.h"

#include "VulkanUtilities.h"

namespace Dynamik
{
	namespace Backend
	{
		void VulkanDescriptorSetLayout::initialize(const VulkanDevice& vDevice, const ARRAY<DMKUniformBufferDescriptor>& descriptors)
		{
			VkDescriptorSetLayoutCreateInfo initInfo;
			initInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
			initInfo.pNext = VK_NULL_HANDLE;

			auto bindings = VulkanUtilities::getDescriptorSetLayoutBindings(descriptors);
			initInfo.bindingCount = bindings.size();
			initInfo.pBindings = bindings.data();

			DMK_VULKAN_ASSERT(vkCreateDescriptorSetLayout(vDevice, &initInfo, nullptr, &layout), "Failed to create descriptor set layout!");
		}

		void VulkanDescriptor::initializeLayout(const VulkanDevice& vDevice, const ARRAY<DMKUniformBufferDescriptor>& descriptors)
		{

		}

		void VulkanDescriptor::initializePool(const VulkanDevice& vDevice, const ARRAY<DMKUniformBufferDescriptor>& descriptors)
		{
		}

		void VulkanDescriptorSetLayout::terminate(const VulkanDevice& vDevice)
		{
			vkDestroyDescriptorPool(vDevice, pool, nullptr);
			vkDestroyDescriptorSetLayout(vDevice, layout, nullptr);
		}

		VulkanDescriptorSetLayout::operator VkDescriptorSetLayout() const
		{
			return this->layout;
		}

		VulkanDescriptor::operator VkDescriptorPool() const
		{
			return this->pool;
		}

		const VkDescriptorSet VulkanDescriptor::operator[](UI32 index) const
		{
			return this->sets[index];
		}
	}
}