// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/RenderTarget/VulkanFrameBuffer.h"

namespace DMK
{
	namespace VulkanBackend
	{
		void VulkanFrameBuffer::Initiallize(VulkanDevice* pDevice, Vector2 extent, std::vector<VulkanRenderTargetAttachment*> pAttachments, UI32 bufferCount)
		{
		}

		void VulkanFrameBuffer::Terminate(VulkanDevice* pDevice)
		{
		}

		void VulkanFrameBuffer::CreateRenderPass()
		{
		}

		void VulkanFrameBuffer::DestroyRenderPass()
		{
		}

		void VulkanFrameBuffer::CreateFrameBuffers()
		{
		}

		void VulkanFrameBuffer::DestroyFrameBuffers()
		{
		}
	}
}