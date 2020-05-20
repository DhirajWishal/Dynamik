#pragma once
#ifndef _DYNAMIK_THREAD_H
#define _DYNAMIK_THREAD_H

/*
 Author:    Dhiraj Wishal
 Date:      20/05/2020
*/
#include "Macros/Global.h"

namespace Dynamik
{
    /*
     Dynamik Thread handle
     All the different threads used by the engine is derived from this.
    */
    class DMK_API DMKThread {
    public:
        DMKThread() {}
        virtual ~DMKThread() {}
    };
}

#endif // !_DYNAMIK_THREAD_H
