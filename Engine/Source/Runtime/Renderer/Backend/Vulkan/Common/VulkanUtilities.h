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
            static B1 hasStencilComponent(const VkFormat& format);
            static VkFormat findSupportedFormat(const ARRAY<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features, VkPhysicalDevice physicalDevice);
            static VkFormat findDepthFormat(const VkPhysicalDevice& physicalDevice);
        };
    }
}

#endif // !_DYNAMIK_VULKAN_UTILITIES_H
