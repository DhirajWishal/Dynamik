// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "RenderTargetAttachment.h"

namespace DMK
{
	namespace VulkanBackend
	{
		/**
		 * Color Buffer object.
		 * This obect stores color images for the render target.
		 */
		class ColorBuffer : public RenderTargetAttachment {
		public:
			/**
			 * Default constructor.
			 */
			ColorBuffer() {}

			/**
			 * Default destructor.
			 */
			~ColorBuffer() {}

			/**
			 * Initialize the attachment.
			 *
			 * @param vDevice: The device in which to initialize.
			 * @param spec: The render target attachment specification.
			 */
			virtual void Initialize(const VulkanDevice& vDevice, const GraphicsCore::RenderTargetAttachmentSpecification& spec) override final;

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
		 * Vulkan Color Buffer Handle.
		 * This is just a unsigned 64 bit integer.
		 */
		typedef UI64 ColorBufferHandle;
	}
}