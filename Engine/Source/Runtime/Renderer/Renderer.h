#pragma once
#ifndef _DYNAMIK_RENDERER_H
#define _DYNAMIK_RENDERER_H

/*
 Author:    Dhiraj Wishal
 Date:      23/05/2020

 The rendering engine of the Dynamik Engine is of two major parts. The Renderer Abstraction Layer and the
 Renderer Backend Layer. All the global rendering calls are done through the RAL. The RAL controls and manages
 the different RBLs (VulkanRBL, OpenGLRBL, DirectX12RBL) to render all the necessary data. 
 All the RBLs contain a data structure called a RenderAsset. This contains API specific data types and objects
 to render a specific object. This also contains a pointer to the base object it belongs to (DMKGameAsset). Once
 the base object is updated, the RenderAsset will also be updated in the update phase of the draw call.

 The rendering engine supports multiple rendering contexts. A rendering context defines how an asset is rendered.
 This included 3D rendering, 2D, Default (both 3D and 2D), Debug and VR. Every game asset is bind to one of the
 rendering context at draw time. A window is bind to a rendering context and a window could have only one context
 at a given rendering instance. A rendering context could have multiple windows depending on the context type
 (eg: VR).
*/
#include "Object/System.h"
#include "GameLibrary/LevelComponent.h"

#include "Components/CoreTypeDefs.h"

#include "Backend/Vulkan/VulkanRBL.h"

namespace Dynamik
{
    using namespace Backend;

    /*
     Dynamik Rendering engine
    */
    class DMK_API DMKRenderer : public DMKSystem {
    public:
        DMKRenderer();
        ~DMKRenderer();

        void setMsaaSamples(DMKSampleCount msaaSamples);

        void initialize();
        void initializeObjects(const POINTER<DMKLevelComponent>& level);

        void initializeDraw();
        void updateObjects();
        void submitObjects();

    private:
        POINTER<DMKLevelComponent> myActiveLevel;
        POINTER<DMKLevelComponent> myNextLevel;

        VulkanRBL myBackend;
    };
}

#endif // !_DYNAMIK_RENDERER_H
