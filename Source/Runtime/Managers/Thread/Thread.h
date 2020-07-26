// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_THREAD_H
#define _DYNAMIK_THREAD_H

#include "Core/Macros/Global.h"
#include "ThreadCommand.h"

#include <thread>
#include <queue>

#define MAX_COMMANDS_PER_THREAD     10

namespace Dynamik
{
    /*
     Thread types enum for the Dynamik Engine
    */
    enum class DMK_API DMKThreadType {
        DMK_THREAD_TYPE_PARENT,
        DMK_THREAD_TYPE_UTILITY,
        DMK_THREAD_TYPE_RENDERER,
        DMK_THREAD_TYPE_AUDIO,
        DMK_THREAD_TYPE_PHYSICS,
        DMK_THREAD_TYPE_DESTRUCTION,
        DMK_THREAD_TYPE_COMBINED,
        DMK_THREAD_TYPE_RESOURCE,
        DMK_THREAD_TYPE_CUSTOM,
    };

    /*
     Dynamik Thread handle
     All the different threads used by the engine is derived from this.
    */
    class DMK_API DMKThread {
    public:
        DMKThread() {}
        virtual ~DMKThread() {}

        virtual void initializeThread() {}
        virtual void terminateThread() {}

        virtual void onInitialize() {}
        virtual void processCommand(DMKThreadCommand* pCommand) {}
        virtual void onLoop() {}
        virtual void onTermination() {}
        
    protected:
        std::thread* pThread = nullptr;
        std::queue<DMKThreadCommand*> pThreadCommands;
    };
}

#endif // !_DYNAMIK_THREAD_H
