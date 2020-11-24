// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "RenderTargetAttachment.h"

namespace DMK
{
	namespace VulkanBackend
	{
		/**
		 * Vulkan Depth Buffer object.
		 */
		class DepthBuffer : public RenderTargetAttachment {
		public:
			/**
			 * Default constructor.
			 */
			DepthBuffer() {}

			/**
			 * Default destructor.
			 */
			~DepthBuffer() {}

			/**
			 * Initialize the attachment.
			 *
			 * @param vDevice: The device in which to initialize.
			 * @param spec: The render target attachment specification.
			 */
			virtual void Initialize(VulkanDevice& vDevice, const GraphicsCore::RenderTargetAttachmentSpecification& spec) override final;

			/**
			 * Terminate the render target attachment.
			 *
			 * @param vDevice: The device in which to initialize.
			 */
			virtual void Terminate(const VulkanDevice& vDevice) override final;

		private:
			VkDeviceMemory vBufferMemory = VK_NULL_HANDLE;	// Vulkan buffer memory handle.
		};

		/**
		 * Vulkan Depth Buffer Handle.
		 * This is just a unsigned 64 bit integer.
		 */
		typedef UI64 DepthBufferHandle;
	}
}