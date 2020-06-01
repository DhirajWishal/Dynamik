#pragma once
#ifndef _DYNAMIK_VULKAN_COMMAND_BUFFER_H
#define _DYNAMIK_VULKAN_COMMAND_BUFFER_H

/*
 Author:    Dhiraj Wishal
 Date:      24/05/2020
*/
#include "VulkanDevice.h"
#include "VulkanQueue.h"

#include "../Context/VulkanRenderPass.h"
#include "../Context/VulkanFrameBuffer.h"
#include "../Context/VulkanSwapChain.h"

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
			void beginRenderPass(
				const VulkanDevice& vDevice,
				const VulkanRenderPass& vRenderPass,
				const VulkanFrameBuffer& vFrameBuffer,
				const VulkanSwapChain& vSwapChain,
				UI32 bufferIndex,
				ARRAY<F32> clearScrValues = {2.0f/256.0f, 8.0f/256.0f, 32.0f / 256.0f, 1.0f});
			
			/* Record Objects */
			/* End Rendering Context */

			void endRenderPass(const VkCommandBuffer& buffer);
			void endCommandBufferRecording(const VulkanDevice& vDevice, const VkCommandBuffer& commandBuffer);

			void resetPool(const VulkanDevice& vDevice);
			void resetBuffers();

			void terminate(const VulkanDevice& vDevice);

			operator VkCommandPool() const;
			const VkCommandBuffer operator[](UI32 index) const;

			ARRAY<VkCommandBuffer> buffers;
			VkCommandPool pool = VK_NULL_HANDLE;
		};
	}
}

#endif // !_DYNAMIK_VULKAN_COMMAND_POOL_H
