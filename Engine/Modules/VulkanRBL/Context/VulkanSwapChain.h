// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_SWAP_CHAIN_H
#define _DYNAMIK_VULKAN_SWAP_CHAIN_H

#include "Renderer/Components/Context/RSwapChain.h"

#include "../VulkanCoreObject.h"
#include "../Common/VulkanDevice.h"
#include "../Common/VulkanQueue.h"
#include "../Common/VulkanViewport.h"

#include "../Primitives/VulkanImageView.h"

    namespace Backend
    {
        /*
         Swap chain support details
        */
        struct DMK_API VulkanSwapChainSupportDetails {
            VkSurfaceCapabilitiesKHR capabilities = {};
            ARRAY<VkSurfaceFormatKHR> formats = {};
            ARRAY<VkPresentModeKHR> presentModes = {};
        };

        /*
         Vulkan Swap Chain for the Dynamik RBL
        */
        class DMK_API VulkanSwapChain : public RSwapChain {
        public:
            VulkanSwapChain() {}
            ~VulkanSwapChain() {}

            static VulkanSwapChainSupportDetails querySwapChainSupport(const VkPhysicalDevice& physicalDevice, const VkSurfaceKHR& surface);

            virtual void initialize(RCoreObject* pCoreObject, DMKViewport viewport, RSwapChainPresentMode ePresentMode) override final;
            virtual void terminate(RCoreObject* pCoreObject) override final;

            operator VkSwapchainKHR() const;

            VkSwapchainKHR swapChain = VK_NULL_HANDLE;
        };
    }

#endif // !_DYNAMIK_VULKAN_SWAP_CHAIN_H
