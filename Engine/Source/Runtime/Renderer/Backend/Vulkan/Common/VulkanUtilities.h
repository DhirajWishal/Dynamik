#pragma once
#ifndef _DYNAMIK_VULKAN_UTILITIES_H
#define _DYNAMIK_VULKAN_UTILITIES_H

/*
 Author:    Dhiraj Wishal
 Date:      25/05/2020
*/
#include "VulkanDevice.h"

namespace Dynamik
{
    namespace Backend 
    {
        /*
         Vulkan Utilities for the Dynamik RBL
        */
        class DMK_API VulkanUtilities {
            VulkanUtilities() {}
            ~VulkanUtilities() {}

        public:
            static VkFormat getVulkanFormat(DMKFormat format);
            static UI32 findMemoryType(UI32 typeFilter, VkMemoryPropertyFlags properties, VkPhysicalDevice physicalDevice);
        };
    }
}

#endif // !_DYNAMIK_VULKAN_UTILITIES_H
