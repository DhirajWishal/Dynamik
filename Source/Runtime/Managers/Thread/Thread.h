// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_THREAD_H
#define _DYNAMIK_THREAD_H

#include "ThreadCommand.h"
#include "Services/RuntimeSystems/ThreadCommandService.h"

#include <thread>

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
        virtual void processCommand(STRING commandName) {}
        virtual void onLoop() {}
        virtual void onTermination() {}

        virtual void setupCommandService(DMKThreadCommandService* pService) { pCommandService = pService; }
        
    protected:
        std::thread* pThread = nullptr;
        DMKThreadCommandService* pCommandService = nullptr;
    };
}

#endif // !_DYNAMIK_THREAD_H
