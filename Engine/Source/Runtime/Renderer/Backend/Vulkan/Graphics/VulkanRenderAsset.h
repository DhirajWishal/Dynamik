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
         Vulkan renderable mesh
        */
        struct DMK_API VulkanRenderableMesh {
            VulkanDescriptorContainer descriptor;
            VulkanPipelineContainer pipeline;
            VulkanBuffer vertexBuffer;
            VulkanBuffer indexBuffer;
            UI32 vertexCount = 0;
            UI32 indexCount = 0;
        };

        /*
         Vulkan Render Asset for the Dynamik RBL
        */
        class DMK_API VulkanRenderAsset : public DMKRenderAsset {
        public:
            VulkanRenderAsset() {}
            ~VulkanRenderAsset() {}

            ARRAY<VulkanRenderableMesh> meshes;
        };
    }
}

#endif // !_DYNAMIK_VULKAN_RENDER_ASSET_H
