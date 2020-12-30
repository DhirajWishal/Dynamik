// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "VulkanBackend/Objects/SwapChain.h"

namespace DMK
{
	namespace VulkanBackend
	{
		/**
		 * Render Target SB3D (Screen Bound 3D).
		 */
		struct RenderTargetSB3D {
			VulkanSwapChain vSwapChain = {};

			static RenderTargetSB3D Create(const VulkanDevice& vDevice, const GraphicsCore::ViewPort& viewPort);
			static void Destroy(const VulkanDevice& vDevice, const RenderTargetSB3D& renderTarget);
		};
	}
}