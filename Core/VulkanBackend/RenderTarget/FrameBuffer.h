// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "RenderPass.h"

namespace DMK
{
	namespace VulkanBackend
	{
		/**
		 * Vulkan Frame Buffer object.
		 */
		class FrameBuffer {
		public:
			FrameBuffer() {}
			~FrameBuffer() {}

			/**
			 * Initialize the frame buffer.
			 *
			 * @param vDevice: The Vulkan device object.
			 * @param mRenderPassHandle: The render pass handle.
			 * @param mAttachments: The render target attachment handles.
			 * @param bufferCount: The number of frame buffers to create.
			 * @param extent: The extent of the buffers.
			 */
			void Initialize(const VulkanDevice& vDevice, const RenderPassHandle& mRenderPassHandle, const std::vector<GraphicsCore::RenderTargetAttachmentHandle>& mAttachments, UI64 bufferCount, const VkExtent2D& extent);

			/**
			 * Terminate the frame buffer.
			 *
			 * @param vDevice: The Vulkan device object.
			 */
			void Terminate(const VulkanDevice& vDevice);

			std::vector<VkFramebuffer> vFrameBuffers;	// Vulkan frame buffer handles.
			VkExtent2D vExtent = {};	// Frame buffer extent.
		};

		/**
		 * Frame Buffer Handle type.
		 */
		typedef UI64 FrameBufferHandle;
	}
}