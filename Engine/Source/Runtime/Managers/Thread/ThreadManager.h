#pragma once
#ifndef _DYNAMIK_THREAD_MANAGER_H
#define _DYNAMIK_THREAD_MANAGER_H

/*
 Author:    Dhiraj Wishal
 Date:      15/05/2020
*/
#include "Object/Components/ManagerObject.h"

namespace Dynamik
{
    /*
     Dynamik Thread Manager
     The Dynamik Engine uses multiple threads to execute some of the complex and interactive systems. These
     threads are,
     * Parent thread
        - Game code execution
        - Thread synchronization
        - Window and Event management
        - Resource management
     * Rendering thread
        - InFlight object management
        - Rendering pipeline management
     * Physics thread
        - Dynamik Destruction calculation
        - Object simmulation
     * Audio thread
        - Audio controller 
        - Audio event handler
     * Utility thread
        - Resource loading
        - File operations
     
     Utility threads are often initiated by the parent thread when executing a demanding job.
    */
    class DMK_API DMKThreadManager : public DMKManagerObject {
        DMK_CLASS_SINGLETON(DMKThreadManager)

    public:

    };
}

#endif // !_DYNAMIK_THREAD_MANAGER_H
