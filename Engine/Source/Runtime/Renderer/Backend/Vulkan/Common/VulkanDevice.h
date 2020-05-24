#pragma once
#ifndef _DYNAMIK_VULKAN_DEVICE_H
#define _DYNAMIK_VULKAN_DEVICE_H

/*
 Author:    Dhiraj Wishal
 Date:      24/05/2020
*/
#include "VulkanInstance.h"
#include "VulkanSurface.h"

namespace Dynamik
{
    namespace Backend
    {
        class DMK_API VulkanDevice {
        public:
            VulkanDevice() {}
            ~VulkanDevice() {}

            void initialize(VulkanInstance vInstance, VulkanSurface vSurface);
            void initializePhysicalDevice(VulkanInstance vInstance, VulkanSurface vSurface);
            void initializeLogicalDevice(VulkanInstance vInstance, VulkanSurface vSurface);
            void terminate(VulkanInstance vInstance);

            VkSampleCountFlagBits getMaxUsableSampleCount();

            VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
            VkDevice logicalDevice = VK_NULL_HANDLE;

            VkPhysicalDeviceProperties physicalDeviceProperties = {};

            operator VkPhysicalDevice() const;
            operator VkDevice() const;
            operator VkPhysicalDeviceProperties() const;
        };
    }
}

#endif // !_DYNAMIK_VULKAN_DEVICE_H
