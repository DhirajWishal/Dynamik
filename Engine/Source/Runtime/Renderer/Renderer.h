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
#include "Managers/Thread/Thread.h"
#include "Managers/Thread/ThreadCommand.h"

#include "Components/RCoreObject.h"
#include "Components/Context/RFrameBuffer.h"
#include "Components/RCommandBufferManager.h"
#include "Components/Factories/BufferFactory.h"
#include "Components/REntity.h"

namespace Dynamik
{
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
         Process commands and call individual functions of the backend.
        */
        void processCommand(DMKThreadCommand* command) override;

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
        void setWindowHandle(const DMKWindowHandle* windowHandle);

        RCoreObject* createCore(B1 bEnableValidation);

    private:    /* Context */
        RSwapChain* createSwapChain(DMKViewport viewport, RSwapChainPresentMode presentMode);
        RRenderPass* createRenderPass(ARRAY<RSubPasses> subPasses);
        RFrameBuffer* createFrameBuffer();

        void createContext(DMKRenderContextType type, DMKViewport viewport);

    private:    /* Resource */
        RBuffer* createBuffer(const RBufferType& type, UI64 size);
        RPipelineObject* allocatePipeline();

        void createEntityResources(DMKGameEntity* pGameEntity);

    private:    /* Finals */
        void initializeBuffers();
        void initializeFinals();

    private:    /* Internal Methods */
        void terminateComponents();
        void terminateEntities();

    private:    /* Utility Methods */
        ARRAY<RColorBlendState> createBasicBlendStates();

    private:    /* Internal */
        DMKRendererCompatibility myCompatibility;

        DMKRendererCommand* myCommand;

        DMKRenderingAPI myAPI;
        DMKSampleCount mySampleCount;
        DMKWindowHandle* myWindowHandle;

        RCoreObject* myCoreObject;

        RSwapChain* mySwapChain;
        RRenderTarget* myRenderTarget;

        RCommandBufferManager* myCommandBufferManager;
        ARRAY<RCommandBuffer*> myCommandBuffers;
        B1 isInitialized = false;

        ARRAY<REntity> myEntities;
        RBuffer* myVertexBuffer;
        UI64 myVertexBufferByteSize = 0;
        RBuffer* myIndexBuffer;
        UI64 myIndexBufferByteSize = 0;

    private:    /* Factories */
        DMKBufferFactory myBufferFactory;
    };
}

#endif // !_DYNAMIK_RENDERER_THREAD_H
