// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_H
#define _DYNAMIK_RENDERER_H

/*
 Author:    Dhiraj Wishal
 Date:      29/05/2020
*/
#include "RendererCommand.h"
#include "Backend/Vulkan/VulkanRBL.h"
#include "Managers/Thread/Thread.h"
#include "Managers/Thread/ThreadCommand.h"

#include "Components/RCoreObject.h"
#include "Components/Context/RFrameBuffer.h"

namespace Dynamik
{
    using namespace Backend;

    /*
     Dynamik Renderer Compatibility structure
    */
    struct DMK_API DMKRendererCompatibility {
        B1 isVulkanAvailable = false;
    };

    /*
     Renderer thread for the Dynamik Engine
     This is the base rendering API.
     This unit is executed on a single thread which manages all of its rendering commands sent via the thread
     commands.
    */
    class DMK_API DMKRenderer : public DMKThread {
    public:
        DMKRenderer() : DMKThread(DMKThreadType::DMK_THREAD_TYPE_RENDERER) {}
        ~DMKRenderer() {}

        /*
         Initialize the core components.
        */
        void initialize() override;

        /*
         Prcess commands and call individual functions of the backend.
        */
        void processCommand(POINTER<DMKThreadCommand> command) override;

        /*
         Execute the three steps of draw call.
        */
        void onLoop() override;

        /*
         Terminate the backend.
        */
        void onTermination() override;

    private:    /* Core */
        void setSamples(const DMKSampleCount& samples);
        void setWindowHandle(const POINTER<DMKWindowHandle>& windowHandle);

        POINTER<RCoreObject> createCore(B1 bEnableValidation);

    private:    /* Context */
        POINTER<RSwapChain> createSwapChain(DMKViewport viewport, RSwapChainPresentMode presentMode);
        POINTER<RRenderPass> createRenderPass(ARRAY<RSubPasses> subPasses);
        POINTER<RFrameBuffer> createFrameBuffer();

        void createContext(DMKRenderContextType type, DMKViewport viewport);

    private:    /* Resource */
        void createEntityResources(POINTER<DMKGameEntity> pGameEntity);

    private:    /* Internal */
        DMKRendererCompatibility myCompatibility;

        VulkanRBL myBackend;
        POINTER<DMKRendererCommand> myCommand;

        DMKRenderingAPI myAPI;
        DMKSampleCount mySampleCount;
        POINTER<DMKWindowHandle> myWindowHandle;

        POINTER<RCoreObject> myCoreObject;

        POINTER<RRenderPass> myRenderPass;
        POINTER<RSwapChain> mySwapChain;
        POINTER<RFrameBuffer> myFrameBuffer;
    };
}

#endif // !_DYNAMIK_RENDERER_THREAD_H
