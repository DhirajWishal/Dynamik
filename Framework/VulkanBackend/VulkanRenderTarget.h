// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "RenderTarget/VulkanFrameBuffer.h"

namespace DMK
{
	namespace VulkanBackend
	{
		class VulkanRenderTarget : public GraphicsCore::RenderTarget {
		public:
			VulkanRenderTarget(GraphicsCore::RenderTargetType type) : RenderTarget(type) {}
			virtual ~VulkanRenderTarget() {}

			VulkanFrameBuffer mFrameBuffer = {};
		};
	}
}