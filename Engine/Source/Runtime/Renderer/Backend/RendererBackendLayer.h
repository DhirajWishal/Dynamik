#pragma once
#ifndef _DYNAMIK_RENDERER_BACKEND_LAYER_H
#define _DYNAMIK_RENDERER_BACKEND_LAYER_H

/*
 Author:    Dhiraj Wishal
 Date:      23/05/2020
*/
#include "Macros/Global.h"
#include "GameLibrary/LevelComponent.h"

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

        virtual void initializeCore() {}
        virtual void initializeRenderingContext() {}
        virtual void initializeLevel(POINTER<DMKLevelComponent> level) {}
        virtual void initializeFinalComponents() {}

        virtual void initializeDrawCall() {}
        virtual void updateRenderables() {}
        virtual void submitRenderables() {}

        virtual void terminateComponents() {}
        virtual void terminateLevelData() {}
        virtual void terminateRenderingContext() {}
        virtual void terminateCore() {}
    };
}

#endif // !_DYNAMIK_RENDERER_BACKEND_LAYER_H