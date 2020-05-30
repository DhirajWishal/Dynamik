#pragma once
#ifndef _DYNAMIK_THREAD_H
#define _DYNAMIK_THREAD_H

/*
 Author:    Dhiraj Wishal
 Date:      20/05/2020
*/
#include "Macros/Global.h"
#include "ThreadCommand.h"

namespace Dynamik
{
    /*
     Thread types enum for the Dynamik Engine
    */
    enum class DMK_API DMKThreadType {
        DMK_THREAD_TYPE_PARENT,
        DMK_THREAD_TYPE_UTILITY,
        DMK_THREAD_TYPE_RENDER,
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
        DMKThread(const DMKThreadType& ty) : type(ty) {}
        virtual ~DMKThread() {}

        virtual void processCommands() {}
        virtual void onLoop() {}
        virtual void onTermination() {}

        ARRAY<POINTER<DMKThreadCommand>> myCommands;
        DMKThreadType type = DMKThreadType::DMK_THREAD_TYPE_PARENT;
    };

    /* THREAD FUNCTION
     void thread(POINTER<ARRAY<POINTER<DMKThreadCommand>>> commandPool)
     {
         auto localPool = commandPool;
         B1 run = true;

         begin:

         do {
          // run

          if(command == terminationCommand)
              run = false;

          if(command == resetCommand)
              goto begin;

         } while(run);
     }
    */
}

#endif // !_DYNAMIK_THREAD_H
