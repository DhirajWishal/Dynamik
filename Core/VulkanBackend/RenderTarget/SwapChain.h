// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "RenderTargetAttachment.h"
#include "GraphicsCore/Backend/ViewPort.h"

namespace DMK
{
	namespace VulkanBackend
	{
		/**
		 * Vulkan Swap Chain object.
		 * This object stores information about a single swap chain.
		 */
		class SwapChain : public RenderTargetAttachment {
		public:
			/**
			 * Default constructor.
			 */
			SwapChain() {}

			/**
			 * Default destructor.
			 */
			~SwapChain() {}

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

			/**
			 * Get the Swap Chain handle.
			 *
			 * @return Vulkan Swap Chain handle.
			 */
			VkSwapchainKHR GetSwapChain() const { return vSwapChain; }

			GraphicsCore::ViewPort mViewPort = {};	// View port to which the swap chain is rendered.
			VkSwapchainKHR vSwapChain = VK_NULL_HANDLE;	// Vulkan Swap Chain handle.
		};

		/**
		 * The Vulkan Swap Chain Handle.
		 * The handle is just an unsigned 64 bit integer.
		 */
		typedef UI64 SwapChainHandle;
	}
}