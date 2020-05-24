#pragma once
#ifndef _DYNAMIK_VULKAN_COMMAND_BUFFER_H
#define _DYNAMIK_VULKAN_COMMAND_BUFFER_H

/*
 Author:    Dhiraj Wishal
 Date:      24/05/2020
*/
#include "VulkanDevice.h"
#include "VulkanQueue.h"

namespace Dynamik
{
	namespace Backend
	{
		/*
		 Vulkan Command Buffer for the Dynamik RBL
		*/
		class DMK_API VulkanCommandBuffer {
		public:
			VulkanCommandBuffer() {}
			~VulkanCommandBuffer() {}

			void initializeCommandPool(const VulkanDevice& vDevice, const VulkanQueue& vQueue);
			void allocateCommandBuffers(const VulkanDevice& vDevice, UI32 bufferCount);

			const VkCommandBuffer& beginCommandBufferRecording(const VulkanDevice& vDevice, UI32 bufferIndex = 0);

			/* Begin Rendering Context */
			/* Record Objects */
			/* End Rendering Context */

			void endCommandBufferRecording(const VulkanDevice& vDevice, const VkCommandBuffer& commandBuffer);

			void terminate(const VulkanDevice& vDevice);

			operator VkCommandPool() const;

			ARRAY<VkCommandBuffer> buffers;
			VkCommandPool pool = VK_NULL_HANDLE;
		};
	}
}

#endif // !_DYNAMIK_VULKAN_COMMAND_POOL_H
