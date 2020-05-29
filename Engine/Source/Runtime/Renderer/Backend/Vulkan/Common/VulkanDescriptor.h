#pragma once
#ifndef _DYNAMIK_VULKAN_DESCRIPTOR_H
#define _DYNAMIK_VULKAN_DESCRIPTOR_H

/* 
 Author:    Dhiraj Wishal
 Date:      27/05/2020

 This file contains all the necessary objects needed to create descriptor sets.
*/
#include "VulkanDevice.h"

#include "Object/Resource/Primitives.h"

namespace Dynamik
{
    namespace Backend
    {
        /*
         Vulkan Descriptor Set Layout for the Dynamik RBL
        */
        class DMK_API VulkanDescriptorSetLayout {
        public:
            VulkanDescriptorSetLayout() {}
            ~VulkanDescriptorSetLayout() {}

            void initialize(const VulkanDevice& vDevice, const ARRAY<DMKUniformBufferDescriptor>& descriptors);
            void terminate(const VulkanDevice& vDevice);

            operator VkDescriptorSetLayout() const;

            VkDescriptorSetLayout layout = VK_NULL_HANDLE;
        };

        /*
         Vulkan Descriptor Sets and Descriptor Pool for the Dynamik RBL
        */
        class DMK_API VulkanDescriptorSets {
        public:
            VulkanDescriptorSets() {}
            ~VulkanDescriptorSets() {}

            void initializePool(const VulkanDevice& vDevice, const ARRAY<DMKUniformBufferDescriptor>& descriptors);
            void initailizeSets(const VulkanDevice& vDevice, const VulkanDescriptorSetLayout& vDescriptorSetLayout);

            void terminate(const VulkanDevice& vDevice);

            operator VkDescriptorPool() const;
            const VkDescriptorSet operator[](UI32 index) const;

            ARRAY<VkDescriptorSet> sets;
            VkDescriptorPool pool = VK_NULL_HANDLE;
        };
    }
}

#endif // !_DYNAMIK_VULKAN_DESCRIPTOR_H
