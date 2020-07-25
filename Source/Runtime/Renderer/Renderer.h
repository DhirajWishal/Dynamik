// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_H
#define _DYNAMIK_RENDERER_H

#include "RendererCommand.h"
#include "Managers/Thread/Thread.h"
#include "Managers/Thread/ThreadCommand.h"

#include "Components/RCoreObject.h"
#include "Components/Context/RFrameBuffer.h"
#include "Components/RCommandBufferManager.h"
#include "Components/Factories/BufferFactory.h"
#include "Components/REntity.h"
#include "Components/RCameraComponent.h"
#include "Components/REnvironmentMap.h"
#include "Components/RDrawCallManager.h"
#include "Components/Attachments/RBoundingBox.h"

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
        void processCommand(DMKThreadCommand* pCommand) override;

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
        RRenderPass* createRenderPass(ARRAY<RSubpassAttachment> subPasses);
        RFrameBuffer* createFrameBuffer();

        void createContext(DMKRenderContextType type, DMKViewport viewport);

    private:    /* Resource */
        RBuffer* createBuffer(const RBufferType& type, UI64 size, RResourceMemoryType memoryType = (RResourceMemoryType)
            (RESOURCE_MEMORY_TYPE_HOST_VISIBLE | RESOURCE_MEMORY_TYPE_HOST_COHERENT));
        RBuffer* createVertexBuffer(UI64 size);
        RBuffer* createIndexBuffer(UI64 size);
        void copyBuffer(RBuffer* pSrcBuffer, RBuffer* pDstBuffer, UI64 size);
        void copyDataToBuffer(RBuffer* pDstBuffer, VPTR data, UI64 size, UI64 offset);

        RTexture* createTexture(const DMKTexture* pTexture);

        RBRDFTable* createBRDFTable();
        RIrradianceCube* createIrradianceCube();
        RPreFilteredCube* createPreFilteredCube();

        void initializeCamera(DMKCameraModule* pCameraModule);
        void initializeEnvironmentMap(DMKEnvironmentMap* pEnvironmentMap);
        void createEntityResources(DMKGameEntity* pGameEntity);
        void initializeGameWorld(DMKGameWorld* pGameWorld);

    private:    /* Finals */
        void updateResources();
        void initializeCommandBuffers();
        void initializeFinals();

    private:    /* Instructions */
        void resizeFrameBuffer(DMKExtent2D windowExtent);
        void beginFrameInstruction();
        void updateInstruction();
        void updateCamera();
        void updateEnvironment();
        void updateEntities();
        void updateBoundingBoxes();
        void updateDebugObjects();
        void endFrameInstruction();

    private:    /* Internal Methods */
        void terminateContext();
        void terminateComponents();
        void terminateEntities();

    private:    /* Utility Methods */
        RBoundingBox createBoundingBox(DMKBoundingBoxAttachment* pBoundingBox);
        RMeshObject loadMeshComponent(DMKStaticMeshComponent* pComponent);

    private:    /* Internal */
        DMKRendererCompatibility myCompatibility;

        DMKRendererCommand* myCommand = nullptr;

        DMKRenderingAPI myAPI;
        DMKSampleCount mySampleCount;
        DMKWindowHandle* myWindowHandle = nullptr;

        RCoreObject* myCoreObject = nullptr;
        RDrawCallManager myDrawCallManager;

        RSwapChain* mySwapChain = nullptr;
        RRenderTarget myRenderTarget = {};
        DMKRenderContextType myCurrentContextType = DMKRenderContextType::DMK_RENDER_CONTEXT_DEFAULT;

        RCommandBufferManager* myCommandBufferManager = nullptr;
        ARRAY<RCommandBuffer*> myCommandBuffers;
        B1 isReadyToRun = false;

        RCameraComponent* myCameraComponent = nullptr;
        REnvironmentMap myCurrentEnvironment;

        ARRAY<REntity> myEntities;
        ARRAY<RBoundingBox> myBoundingBoxes;
        ARRAY<RDebugMeshComponent> myDebugObjects;

        ARRAY<RMeshObject> myStaticMeshes;

        UI32 currentImageIndex = 0;

    private:    /* Factories */
        DMKBufferFactory myBufferFactory;
    };
}

#endif // !_DYNAMIK_RENDERER_THREAD_H
