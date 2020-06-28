// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_RENDER_TARGET_H
#define _DYNAMIK_VULKAN_RENDER_TARGET_H

/*
 Author:	Dhiraj Wishal
 Date:		16/06/2020
*/
#include "Renderer/Components/RRenderTarget.h"

namespace Dynamik
{
	/*
	 Vulkan Render Target
	*/
	class DMK_API VulkanRenderTarget : public RRenderTarget {
	public:
		VulkanRenderTarget() {}
		virtual ~VulkanRenderTarget() {}
	};
}

#endif // !_DYNAMIK_VULKAN_RENDER_TARGET_H
