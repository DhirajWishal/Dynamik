// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_VIEWPORT_H
#define _DYNAMIK_VULKAN_VIEWPORT_H

#include "VulkanSurface.h"
#include "Window/WindowHandle.h"

namespace Backend
{
	class DMK_API VulkanSurface;

	/*
	 Vulkan Viewport class
	*/
	class DMK_API VulkanViewport : public DMKViewport {
	public:
		VulkanViewport() {}
		~VulkanViewport() {}

		void initialize();

		VulkanSurface* surfacePtr;
		VkViewport vkViewport = {};
	};
}

#endif // !_DYNAMIK_VULKAN_VIEWPORT_H
