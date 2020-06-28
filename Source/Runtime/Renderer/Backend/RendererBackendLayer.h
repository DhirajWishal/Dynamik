// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_BACKEND_LAYER_H
#define _DYNAMIK_RENDERER_BACKEND_LAYER_H

/*
 Author:    Dhiraj Wishal
 Date:      23/05/2020
*/
#include "Core/Macros/Global.h"
#include "GameLibrary/LevelComponent.h"
#include "Window/WindowHandle.h"
#include "../Components/CoreTypeDefs.h"
#include "../Components/ContextTypeDefs.h"

namespace Dynamik
{
    /*
     The Renderer Backend Layer contains 4 main parts (API agnostic). These are:
     * Core component
     * Rendering context(s)
     * Initialize renderables
     * initialize final components
    
     The draw command is of 3 parts.
     * Pre draw initialization
     * Rendering component updates
     * Submit rendering components to render

     Termination has 4 equal parts:
     * Terminate components
     * Terminate renderables
     * Terminate rendering context
     * Terminate core components
    */
    class DMK_API DMKRendererBackendLayer {
    public:
        DMKRendererBackendLayer() {}
        virtual ~DMKRendererBackendLayer() {}

        virtual void setMsaaSamples(const DMKSampleCount& samples) {}
        virtual void setWindowHandle(const DMKWindowHandle* windowHandle) {}

        virtual void initializeCore() {}
        virtual void initializeRenderingContext(const DMKRenderContextType& contextType, const DMKViewport& viewport) {}
        virtual void initializeEntity(DMKGameEntity* entity) {}
        virtual void initializeLevel(DMKLevelComponent* level) {}
        virtual void initializeFinalComponents() {}

        virtual void initializeDrawCall() {}
        virtual void updateRenderables() {}
        virtual void submitRenderables() {}

        virtual void terminateComponents() {}
        virtual void terminateLevelData() {}
        virtual void terminateRenderingContext() {}
        virtual void terminateCore() {}

    protected:      /* Protected methods */
        virtual void _initializeMeshComponents(const ARRAY<DMKComponentArray<DMKMeshComponent>>& meshComponents) {}
    };
}

#endif // !_DYNAMIK_RENDERER_BACKEND_LAYER_H
