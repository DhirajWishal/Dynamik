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
    class DMK_API DMKRendererThreadCommand : public DMKThreadCommand {
    public:
        DMKRendererThreadCommand() {}
        ~DMKRendererThreadCommand() {}
    };

    /*
     Renderer thread for the Dynamik Engine
     This unit is executed on a single thread which manages all of its rendering commands sent via the thread
     commands.
    */
    class DMK_API DMKRendererThread : public DMKThread {
    public:
        DMKRendererThread() {}
        ~DMKRendererThread() {}
    };
}

#endif // !_DYNAMIK_RENDERER_THREAD_H
