#pragma once
#ifndef _DYNAMIK_VULKAN_SHADER_H
#define _DYNAMIK_VULKAN_SHADER_H

/*
 Author:    Dhiraj Wishal
 Date:      29/05/2020
*/
#include "../Common/VulkanDevice.h"

#include "Core/Object/Resource/Primitives.h"

namespace Dynamik
{
    namespace Backend
    {
        /*
         Vulkan Shader for the Dynamik RBL
        */
        class DMK_API VulkanShader {
        public:
            VulkanShader() {}
            ~VulkanShader() {}

            void initialize(const VulkanDevice& vDevice, const DMKShaderModule& shader, DMKShaderLocation location);
            void terminate(const VulkanDevice& vDevice);

            operator VkShaderModule() const;

            VkShaderModule shaderModule = VK_NULL_HANDLE;
            VkShaderStageFlags stageFlag = VkShaderStageFlagBits::VK_SHADER_STAGE_ALL;
        };
    }
}

#endif // !_DYNAMIK_VULKAN_SHADER_H
