#pragma once
#ifndef _DYNAMIK_VULKAN_VIEWPORT_H
#define _DYNAMIK_VULKAN_VIEWPORT_H

/*
 Author:    Dhiraj Wishal
 Date:      24/05/2020
*/
#include "VulkanSurface.h"

namespace Dynamik
{
    namespace Backend
    {
        /*
         Vulkan View Port class
        */
        class DMK_API VulkanViewPort {
        public:
            VulkanViewPort() {}
            ~VulkanViewPort() {}

            POINTER<VulkanSurface> surfacePtr;

            UI32 viewPortWidth = 0;
            UI32 viewPortHeight = 0;

            UI32 xOffset = 0;
            UI32 yOffset = 0;
        };
    }
}

#endif // !_DYNAMIK_VULKAN_VIEWPORT_H
