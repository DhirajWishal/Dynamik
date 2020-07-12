// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_SURFACE_H
#define _DYNAMIK_VULKAN_SURFACE_H

#include "VulkanInstance.h"
#include "Core/Types/Pointer.h"

#include <GLFW/glfw3.h>
#include "Window/WindowHandle.h"

namespace Dynamik
{
    namespace Backend
    {
        /*
         Vulkan Surface object
        */
        class DMK_API VulkanSurface {
        public:
            VulkanSurface() {}
            ~VulkanSurface() {}

            void initialize(VulkanInstance vInstance, DMKWindowHandle* windowHandle);
            void terminate(VulkanInstance vInstance);

            B1 isDeviceSuitable(const VkPhysicalDevice& physicalDevice);

            operator VkSurfaceKHR() const;
            operator VkSurfaceCapabilitiesKHR() const;

            UI64 windowID = 0;
            VkSurfaceKHR surface = VK_NULL_HANDLE;
            VkSurfaceCapabilitiesKHR surfaceCapabilities = {};
            UI32 surfaceWidth = 0;
            UI32 surfaceHeight = 0;
        };
    }
}

#endif // !_DYNAMIK_VULKAN_SURFACE_H
