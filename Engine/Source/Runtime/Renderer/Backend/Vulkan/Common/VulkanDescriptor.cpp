#include "dmkafx.h"
#include "VulkanDescriptor.h"

namespace Dynamik
{
	namespace Backend
	{
		void VulkanDescriptor::initialize(const VulkanDevice& vDevice, const DMKUniformBufferDescriptor& UBODescriptor)
		{
		}

		void VulkanDescriptor::initializeLayout(const VulkanDevice& vDevice, const DMKUniformBufferDescriptor& UBODescriptor)
		{
		}

		void VulkanDescriptor::initializePool(const VulkanDevice& vDevice, const DMKUniformBufferDescriptor& UBODescriptor)
		{
		}

		void VulkanDescriptor::terminate(const VulkanDevice& vDevice)
		{
			vkDestroyDescriptorPool(vDevice, pool, nullptr);
			vkDestroyDescriptorSetLayout(vDevice, layout, nullptr);
		}

		VulkanDescriptor::operator VkDescriptorSetLayout() const
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