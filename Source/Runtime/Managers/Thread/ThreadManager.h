// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_THREAD_MANAGER_H
#define _DYNAMIK_THREAD_MANAGER_H

#include "Thread.h"
#include "Core/Types/TSArray.h"
#include <thread>
#include <queue>

#include "Renderer/Components/CoreTypeDefs.h"
#include "Window/WindowHandle.h"

#include "Renderer/RendererCommand.h"

namespace Dynamik
{
    /*
     Dynamik Thread Manager
     The Dynamik Engine uses multiple threads to execute some of the complex and interactive systems. The 
     engine has 3 main types of threads:
     * Runtime threads
       - Parent
       - Rendering
       - Audio
       - Physics
     * Game threads
       - Update thread
     * Utility threads
       - Resource thread

     Runtime threads are permenent and will not change depending on the available threads. The Resource threads
     and the Game threads vary depending on the available thread count.
    */
    class DMK_API DMKThreadManager {
    public:
        struct DMK_API ThreadCommandBuffer {
            std::queue<DMKThreadCommand*> commands;
        };

    private:
        struct DMK_API ThreadContainer {
            std::thread thread;
            ThreadCommandBuffer commandBuffer;
            DMKThreadType type = DMKThreadType::DMK_THREAD_TYPE_PARENT;
        } myRendererThread, myAudioThread, myPhysicsThread;

    public:
        DMKThreadManager() {}
        ~DMKThreadManager();

        UI32 getUseableThreadCount();

        /*
         There are some threads which are initiated by default. These are the rendering, physics, destruction,
         parent, audio and the resource thread.
        */
        void initializeBasicThreads();

        void clearCommands();

        void terminateAll();

        /* Dedicated thread commands */
    public:
        /* Renderer thread (RT = RendererThread) */
        void pushRendererCommand(DMKRendererCommand* pCommand);
        void issueSamplesCommandRT(DMKSampleCount const& samples);
        void issueWindowHandleCommandRT(const DMKWindowHandle* handle);
        void issueInitializeCommandRT();
        void issueCreateContextCommandRT(DMKRenderContextType context, DMKViewport viewport);
        void issueInitializeCameraCommandRT(DMKCameraModule* pModule);
        void issueInitializeEnvironmentMapCommandRT(DMKEnvironmentMap* pEnvironmentMap);
        void issueInitializeEntityCommandRT(DMKGameEntity* meshComponents); /* Support for submitting objects */
        void issueInitializeLevelCommandRT(DMKLevelComponent* pLevelComponent);
        void issueInitializeFinalsCommandRT();
        void issueRawCommandRT(RendererInstruction instruction);
        void issueFrameBufferResizeCommandRT(DMKExtent2D extent);
        void issueTerminateCommand();

    private:
        static void _threadFunction(DMKThread* mySystem, ThreadCommandBuffer* commandPoolPtr);

        /*
         Overrided function.
        */
        void _pushToThread(DMKRendererCommand command);

        ARRAY<ThreadContainer> myThreads;
    };
}

#endif // !_DYNAMIK_THREAD_MANAGER_H
