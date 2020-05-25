#include "dmkafx.h"
#include "VulkanBuffer.h"

namespace Dynamik
{
	namespace Backend
	{
		void VulkanBuffer::initialize(const VulkanDevice& vDevice, VulkanBufferType type, UI32 bufferSize)
		{
		}

		void VulkanBuffer::terminate(const VulkanDevice& vDevice)
		{
		}

		VulkanBuffer::operator VkBuffer()
		{
			return this->buffer;
		}

		VulkanBuffer::operator VkDeviceMemory()
		{
			return this->bufferMemory;
		}
	}
}