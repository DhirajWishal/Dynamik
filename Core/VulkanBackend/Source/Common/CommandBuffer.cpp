// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/Common/CommandBuffer.h"
#include "VulkanBackend/Common/VulkanDevice.h"

namespace DMK
{
	namespace VulkanBackend
	{
		CommandBuffer VulkanDevice::CreateCommandBuffer(VkCommandBufferLevel vCommandBufferLevel)
		{
			// Create new command pool.
			CommandPool vCommandPool = {};

			// Initialize it and insert it to the vector.
			vCommandPool.Initialize(GetLogicalDevice());
			vCommandPools.insert(vCommandPools.end(), std::move(vCommandPool));

			// Setup command buffer.
			CommandBuffer vCommandBuffer = {};
			vCommandBuffer.commandPoolIndex = vCommandPools.size() - 1;

			VkCommandBufferAllocateInfo allocateInfo = {};
			allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			allocateInfo.pNext = VK_NULL_HANDLE;
			allocateInfo.commandBufferCount = 1;
			allocateInfo.commandPool = vCommandPool.vCommandPool;
			allocateInfo.level = vCommandBufferLevel;

			// Allocate command buffers.
			DMK_VK_ASSERT(vkAllocateCommandBuffers(GetLogicalDevice(), &allocateInfo, &vCommandBuffer.vCommandBuffer), "Failed to allocate command buffers!");

			return vCommandBuffer;
		}

		void VulkanDevice::FlushCommands(const CommandBuffer& vCommandBuffer)
		{
			// Submit the command buffer to execute the commands.
			VkSubmitInfo submitInfo = {};
			submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			submitInfo.commandBufferCount = 1;
			submitInfo.pCommandBuffers = &vCommandBuffer.vCommandBuffer;

			// Create a fence.
			VkFenceCreateInfo fenceCreateInfo = {};
			fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
			fenceCreateInfo.flags = VK_NULL_HANDLE;
			fenceCreateInfo.pNext = VK_NULL_HANDLE;

			VkFence fence = VK_NULL_HANDLE;
			DMK_VK_ASSERT(vkCreateFence(GetLogicalDevice(), &fenceCreateInfo, nullptr, &fence), "Failed to create fence!");

			// Submit the queue.
			DMK_VK_ASSERT(vkQueueSubmit(GetQueue().GetGraphicsQueue(), 1, &submitInfo, fence), "Failed to submit the process queue of the one time command buffer!");

			// Wait for fence.
			DMK_VK_ASSERT(vkWaitForFences(GetLogicalDevice(), 1, &fence, VK_TRUE, std::numeric_limits<UI32>::max()), "Failed to wait for fence to complete!");

			// Destroy the created fence.
			vkDestroyFence(GetLogicalDevice(), fence, nullptr);

			// Free the allocated command buffers and pools.
			vkFreeCommandBuffers(GetLogicalDevice(), vCommandPools.at(vCommandBuffer.commandPoolIndex).vCommandPool, 1, &vCommandBuffer.vCommandBuffer);
		}

		void VulkanDevice::TerminateCommandPool(UI64 commandPoolIndex)
		{
			// Terminate the command pool.
			vCommandPools.at(commandPoolIndex).Terminate(GetLogicalDevice());

			// Remove it from the vector.
			vCommandPools.erase(vCommandPools.begin() + commandPoolIndex);
		}

		void CommandPool::Initialize(VkDevice vLogicalDevice)
		{
			VkCommandPoolCreateInfo initInfo = {};
			initInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
			initInfo.flags = VK_NULL_HANDLE;
			initInfo.pNext = VK_NULL_HANDLE;
			initInfo.queueFamilyIndex;

			DMK_VK_ASSERT(vkCreateCommandPool(vLogicalDevice, &initInfo, nullptr, &vCommandPool), "Failed to create Vulkan Command Pool!");
		}

		void CommandPool::Terminate(VkDevice vLogicalDevice)
		{
			vkDestroyCommandPool(vLogicalDevice, vCommandPool, nullptr);
		}

		void CommandBuffer::BeginRecording(VkCommandBufferInheritanceInfo vInheritanceInfo)
		{
			VkCommandBufferBeginInfo beginInfo = {};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			beginInfo.pNext = VK_NULL_HANDLE;
			beginInfo.pInheritanceInfo = &vInheritanceInfo;
			beginInfo.flags = VK_NULL_HANDLE;

			DMK_VK_ASSERT(vkBeginCommandBuffer(vCommandBuffer, &beginInfo), "Failed to begin command buffer recording!");
		}

		void CommandBuffer::EndRecording()
		{
			DMK_VK_ASSERT(vkEndCommandBuffer(vCommandBuffer), "Failed to end command buffer recording!");
		}

		void CommandBuffer::Reset()
		{
			DMK_VK_ASSERT(vkResetCommandBuffer(vCommandBuffer, 0), "Failed to reset command buffer records!");
		}

		void CommandBuffer::SetImageLayout(const VkImage& vImage, UI32 mipLevel, UI32 layerCount, VkFormat vFormat, VkImageLayout vOldLayout, VkImageLayout vNewLayout)
		{
			VkImageMemoryBarrier barrier = {};
			barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
			barrier.oldLayout = vOldLayout;
			barrier.newLayout = vNewLayout;
			barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			barrier.image = vImage;

			if (vNewLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL)
			{
				barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;

				if (vFormat == VK_D32_SFLOAT_S8_UINT || vFormat == VK_D24_UNORM_S8_UINT)
					barrier.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
			}
			else
				barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;

			barrier.subresourceRange.baseMipLevel = 0;
			barrier.subresourceRange.levelCount = mipLevel;
			barrier.subresourceRange.baseArrayLayer = 0;
			barrier.subresourceRange.layerCount = layerCount;
			barrier.srcAccessMask = 0; // TODO
			barrier.dstAccessMask = 0; // TODO

			VkPipelineStageFlags sourceStage = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;
			VkPipelineStageFlags destinationStage = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;

			switch (barrier.oldLayout)
			{
			case VK_IMAGE_LAYOUT_UNDEFINED:
				//sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
				barrier.srcAccessMask = 0;
				break;

			case VK_IMAGE_LAYOUT_PREINITIALIZED:
				barrier.srcAccessMask = VK_ACCESS_HOST_WRITE_BIT;
				break;

			case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
				barrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
				break;

			case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
				barrier.srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
				break;

			case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
				barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
				break;

			case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
				//sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
				barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
				break;

			case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
				//destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
				barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
				break;
			default:
				Logger::LogError(TEXT("Unsupported layout transition!"));
				break;
			}

			switch (barrier.newLayout)
			{
			case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
				//destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
				barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
				break;

			case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
				barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
				break;

			case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
				//destinationStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
				barrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
				break;

			case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
				//destinationStage = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
				barrier.dstAccessMask = barrier.dstAccessMask | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
				break;

			case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
				if (barrier.srcAccessMask == 0)
					barrier.srcAccessMask = VK_ACCESS_HOST_WRITE_BIT | VK_ACCESS_TRANSFER_WRITE_BIT;

				barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
				//destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
				break;

			case VK_IMAGE_LAYOUT_GENERAL:
				//destinationStage = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;
				break;
			default:
				Logger::LogError(TEXT("Unsupported layout transition!"));
				break;
			}

			vkCmdPipelineBarrier(
				vCommandBuffer,
				sourceStage, destinationStage,
				0,
				0, nullptr,
				0, nullptr,
				1, &barrier
			);
		}
	}
}