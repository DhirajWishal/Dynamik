#pragma once
#ifndef _DYNAMIK_VULKAN_RENDER_ASSET_H
#define _DYNAMIK_VULKAN_RENDER_ASSET_H

/*
 Author:    Dhiraj Wishal
 Date:      31/05/2020
*/
#include "../../Components/RenderAsset.h"

#include "../Common/VulkanPipelineManager.h"
#include "../Primitives/VulkanBuffer.h"
#include "../Primitives/VulkanTexture.h"
#include "../Primitives/VulkanShader.h"

namespace Dynamik
{
    namespace Backend
    {
        /*
         Vulkan Render Asset for the Dynamik RBL
        */
        class DMK_API VulkanRenderAsset : public DMKRenderAsset {
        public:
            VulkanRenderAsset() {}
            ~VulkanRenderAsset() {}

            VulkanBuffer vertexBuffer;
            VulkanBuffer indexBuffer;
            VulkanTexture texture;
            VulkanShader shader;
            VulkanPipelineContainer pipeline;
            UI32 vertexCount = 0;
            UI32 indexCount = 0;
        };
    }
}

#endif // !_DYNAMIK_VULKAN_RENDER_ASSET_H
