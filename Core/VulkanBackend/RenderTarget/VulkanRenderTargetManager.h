// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "VulkanSwapChain.h"

namespace DMK
{
	namespace VulkanBackend
	{
		/**
		 * Render Target Manager object.
		 * This object creates, maintains and destroys render targets and its attachments.
		 */
		class RenderTargetManager {
		public:
			/**
			 * Default constructor.
			 */
			RenderTargetManager() {}

			/**
			 * Default destructor.
			 */
			~RenderTargetManager() {}

			void Initialize();

		private:
			GraphicsCore::DeviceHandle mDeviceHandle = {};	// The device handle in which the 
		};
	}
}