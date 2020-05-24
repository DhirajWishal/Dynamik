#pragma once
#ifndef _DYNAMIK_VULKAN_SURFACE_H
#define _DYNAMIK_VULKAN_SURFACE_H

/*
 Author:    Dhiraj Wishal
 Date:      24/05/2020
*/
#include "VulkanInstance.h"
#include "Types/Pointer.h"

#include <GLFW/glfw3.h>

namespace Dynamik
{
    namespace Backend
    {
        class DMK_API VulkanSurface {
        public:
            VulkanSurface() {}
            ~VulkanSurface() {}

            void initialize(VulkanInstance vInstance, POINTER<GLFWwindow> windowHandle);
            void terminate(VulkanInstance vInstance);

            B1 isDeviceSuitable(const VkPhysicalDevice& physicalDevice);

            VkSurfaceKHR surface = VK_NULL_HANDLE;
            VkSurfaceCapabilitiesKHR surfaceCapabilities = {};
            UI32 surfaceWidth = 0;
            UI32 surfaceHeight = 0;

            operator VkSurfaceKHR() const;
            operator VkSurfaceCapabilitiesKHR() const;
        };
    }
}

#endif // !_DYNAMIK_VULKAN_SURFACE_H
