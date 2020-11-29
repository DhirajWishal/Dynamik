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
			/**
			 * Default constructor.
			 */
			FrameBuffer() {}

			/**
			 * Default destructor.
			 */
			~FrameBuffer() {}

			/**
			 * Initialize the frame buffer.
			 *
			 * @param vDevice: The Vulkan device object.
			 * @param mRenderPassHandle: The render pass handle.
			 * @param mAttachments: The render target attachment handles.
			 */
			void Initialize(const VulkanDevice& vDevice, const RenderPassHandle& mRenderPassHandle, const std::vector<GraphicsCore::RenderTargetAttachmentHandle>& mAttachments);

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