#pragma once
#ifndef _DYNAMIK_VULKAN_RBL_H
#define _DYNAMIK_VULKAN_RBL_H

/*
 Author:    Dhiraj Wishal
 Date:      23/05/2020
*/
#include "../RendererBackendLayer.h"

namespace Dynamik
{
    class DMK_API VulkanRBL : public DMKRendererBackendLayer {
    public:
        VulkanRBL() {}
        ~VulkanRBL() {}
    };
}

#endif // !_DYNAMIK_VULKAN_RBL_H
