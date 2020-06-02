#pragma once
#ifndef _DYNAMIK_VULKAN_VIEWPORT_H
#define _DYNAMIK_VULKAN_VIEWPORT_H

/*
 Author:    Dhiraj Wishal
 Date:      24/05/2020
*/
#include "VulkanSurface.h"
#include "Managers/Window/WindowHandle.h"

namespace Dynamik
{
	namespace Backend
	{
		/*
		 Vulkan Viewport class
		*/
		class DMK_API VulkanViewport : public DMKViewport {
		public:
			VulkanViewport() {}
			~VulkanViewport() {}

			void initialize();

			POINTER<VulkanSurface> surfacePtr;
			VkViewport vkViewport = {};
		};
	}
}

#endif // !_DYNAMIK_VULKAN_VIEWPORT_H
