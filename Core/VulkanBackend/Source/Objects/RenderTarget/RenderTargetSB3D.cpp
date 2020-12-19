// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/Objects/RenderTarget/RenderTargetSB3D.h"
#include "VulkanBackend/Objects/Device.h"

namespace DMK
{
	namespace VulkanBackend
	{
		RenderTargetSB3D RenderTargetSB3D::Create(const VulkanDevice& vDevice, const GraphicsCore::ViewPort& viewPort)
		{
			RenderTargetSB3D renderTarget = {};
			renderTarget.vSwapChain = VulkanSwapChain::Create(vDevice, viewPort);

			return renderTarget;
		}

		void RenderTargetSB3D::Destroy(const VulkanDevice& vDevice, const RenderTargetSB3D& renderTarget)
		{
		}
	}
}
