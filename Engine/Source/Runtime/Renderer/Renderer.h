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

namespace Dynamik
{
    using namespace Backend;

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

    private:
        VulkanRBL myBackend;
        POINTER<DMKRendererCommand> myCommand;
    };
}

#endif // !_DYNAMIK_RENDERER_THREAD_H
