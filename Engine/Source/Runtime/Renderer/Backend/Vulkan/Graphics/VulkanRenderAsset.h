// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_RENDER_ASSET_H
#define _DYNAMIK_VULKAN_RENDER_ASSET_H

/*
 Author:    Dhiraj Wishal
 Date:      31/05/2020
*/
#include "../../Components/RenderAsset.h"

#include "../Common/VulkanDescriptorSetManager.h"
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
            VulkanDescriptor descriptor;
            ARRAY<VulkanTexture> textures;
            VulkanPipelineContainer pipeline;
            ARRAY<VulkanBuffer> uniformBuffers;
            POINTER<DMKMeshComponent> meshComponent;
            UI64 vertexOffset = 0;
            UI64 indexOffset = 0;
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
