#pragma once
#ifndef _DYNAMIK_THREAD_MANAGER_H
#define _DYNAMIK_THREAD_MANAGER_H

/*
 Author:    Dhiraj Wishal
 Date:      15/05/2020
*/
#include "Thread.h"
#include <thread>
#include <list>

#include "Renderer/Components/CoreTypeDefs.h"
#include "../Window/WindowHandle.h"

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
        struct DMK_API ThreadContainer {
            std::thread thread;
            ARRAY<POINTER<DMKThreadCommand>> threadCommands;
            DMKThreadType type = DMKThreadType::DMK_THREAD_TYPE_PARENT;
        } myRendererThread, myAudioThread, myPhysicsThread;

    public:
        DMKThreadManager() {}
        ~DMKThreadManager() {}

        UI32 getUseableThreadCount();

        /*
         There are some threads which are initiated by default. These are the rendering, physics, destruction,
         parent, audio and the resource thread.
        */
        void initializeBasicThreads();

        /* Dedicated thread commands */
    public:
        /* Renderer thread */
        void issueSamplesCommand(DMKSampleCount const& samples);
        void issueWindowHandleCommand(const POINTER<DMKWindowHandle>& handle);

    private:
        static void _threadFunction(POINTER<DMKThread> mySystem, POINTER<ARRAY<POINTER<DMKThreadCommand>>> commandPoolPtr);

        ARRAY<ThreadContainer> myThreads;
    };
}

#endif // !_DYNAMIK_THREAD_MANAGER_H
