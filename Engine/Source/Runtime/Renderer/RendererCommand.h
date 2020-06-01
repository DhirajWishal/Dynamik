#pragma once
#ifndef _DYNAMIK_RENDERER_COMMANDS_H
#define _DYNAMIK_RENDERER_COMMANDS_H

/*
 Author:	Dhiraj Wishal
 Date:		01/06/2020
*/
#include "Managers/Thread/ThreadCommand.h"
#include "Core/Types/DataTypes.h"
#include "Managers/Window/WindowHandle.h"
#include "Components/ContextTypeDefs.h"

namespace Dynamik
{
    /* Renderer Instructions */
    enum class DMK_API RendererInstruction {
        RENDERER_INSTRUCTION_INITIALIZE,
        RENDERER_INSTRUCTION_CREATE_CONTEXT,
        RENDERER_INSTRUCTION_INITIALIZE_OBJECTS,
        RENDERER_INSTRUCTION_INITIALIZE_FINALS,
        RENDERER_INSTRUCTION_SUBMIT_OBJECTS,

        RENDERER_INSTRUCTION_DRAW_INITIALIZE,
        RENDERER_INSTRUCTION_DRAW_UPDATE,
        RENDERER_INSTRUCTION_DRAW_SUBMIT,

        RENDERER_INSTRUCTION_TERMINATE_FRAME,
        RENDERER_INSTRUCTION_TERMINATE_OBJECTS,
        RENDERER_INSTRUCTION_TERMINATE,

        RENDERER_INSTRUCTION_UPDATE_OBJECTS,

        RENDERER_INSTRUCTION_SET_SAMPLES,
        RENDERER_INSTRUCTION_SET_WINDOW_HANDLE,
    };

    /*
     Renderer Command object for the Dynamik Engine
    */
    class DMK_API DMKRendererCommand : public DMKThreadSystemCommand {
    public:
        DMKRendererCommand() {}
        DMKRendererCommand(RendererInstruction ins) : instruction(ins) {}
        virtual ~DMKRendererCommand() {}

        RendererInstruction instruction = RendererInstruction::RENDERER_INSTRUCTION_INITIALIZE;
        VPTR data = nullptr;
    };

    class DMK_API RenderContextCommand : public DMKRendererCommand {
    public:
        RenderContextCommand() : DMKRendererCommand(RendererInstruction::RENDERER_INSTRUCTION_CREATE_CONTEXT) {}
        ~RenderContextCommand() {}

        DMKViewport viewport;
        DMKRenderContextType contextType;
    };
}

#endif // !_DYNAMIK_RENDERER_COMMANDS_H
