#pragma once
#ifndef _DYNAMIK_RENDERER_THREAD_H
#define _DYNAMIK_RENDERER_THREAD_H

/*
 Author:    Dhiraj Wishal
 Date:      29/05/2020
*/
#include "Renderer.h"
#include "Managers/Thread/Thread.h"
#include "Managers/Thread/ThreadCommand.h"

namespace Dynamik
{
    enum class DMK_API RendererInstruction {
        RENDERER_INSTRUCTION_INITIALIZE,
        RENDERER_INSTRUCTION_INITIALIZE_OBJECTS,
        RENDERER_INSTRUCTION_SUBMIT_OBJECTS,

        RENDERER_INSTRUCTION_DRAW_INITIALIZE,
        RENDERER_INSTRUCTION_DRAW_UPDATE,
        RENDERER_INSTRUCTION_DRAW_SUBMIT,

        RENDERER_INSTRUCTION_TERMINATE_FRAME,
        RENDERER_INSTRUCTION_TERMINATE_OBJECTS,
        RENDERER_INSTRUCTION_TERMINATE,

        RENDERER_INSTRUCTION_UPDATE_OBJECTS
    };

    class DMK_API DMKRendererThreadCommand : public DMKThreadSystemCommand {
    public:
        DMKRendererThreadCommand() {}
        ~DMKRendererThreadCommand() {}

        RendererInstruction instruction = RendererInstruction::RENDERER_INSTRUCTION_INITIALIZE;
    };

    /*
     Renderer thread for the Dynamik Engine
     This unit is executed on a single thread which manages all of its rendering commands sent via the thread
     commands.
    */
    class DMK_API DMKRendererThread : public DMKThread {
    public:
        DMKRendererThread() : DMKThread(DMKThreadType::DMK_THREAD_TYPE_RENDER) {}
        ~DMKRendererThread() {}

        void processCommands() override;
        void onLoop() override;
        void onTermination() override;

    private:
        DMKRenderer myRenderer;
        POINTER<DMKRendererThreadCommand> myCommand;
    };
}

#endif // !_DYNAMIK_RENDERER_THREAD_H
