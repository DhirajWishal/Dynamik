// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GraphicsCore/Backend/RenderTarget.h"

namespace DMK
{
	namespace VulkanBackend
	{
		class VulkanRenderTarget : public GraphicsCore::RenderTarget {
		public:
			VulkanRenderTarget(GraphicsCore::RenderTargetType type) : RenderTarget(type) {}
			virtual ~VulkanRenderTarget() {}
		};
	}
}