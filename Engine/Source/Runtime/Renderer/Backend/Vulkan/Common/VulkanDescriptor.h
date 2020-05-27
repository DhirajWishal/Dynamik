#pragma once
#ifndef _DYNAMIK_VULKAN_DESCRIPTOR_H
#define _DYNAMIK_VULKAN_DESCRIPTOR_H

/* 
 Author:    Dhiraj Wishal
 Date:      27/05/2020
*/
#include "VulkanDevice.h"

#include "Object/Resource/Primitives.h"

namespace Dynamik
{
    namespace Backend
    {
        /*
         Vulkan Descriptor for the Dynamik RBL
        */
        class DMK_API VulkanDescriptor {
        public:
            VulkanDescriptor() {}
            ~VulkanDescriptor() {}

            void initialize(const VulkanDevice& vDevice, const DMKUniformBufferDescriptor& UBODescriptor);

            void initializeLayout(const VulkanDevice& vDevice, const DMKUniformBufferDescriptor& UBODescriptor);
            void initializePool(const VulkanDevice& vDevice, const DMKUniformBufferDescriptor& UBODescriptor);

            void terminate(const VulkanDevice& vDevice);

            operator VkDescriptorSetLayout() const;
            operator VkDescriptorPool() const;
            const VkDescriptorSet operator[](UI32 index) const;

            ARRAY<VkDescriptorSet> sets;
            VkDescriptorSetLayout layout = VK_NULL_HANDLE;
            VkDescriptorPool pool = VK_NULL_HANDLE;
        };
    }
}

#endif // !_DYNAMIK_VULKAN_DESCRIPTOR_H
