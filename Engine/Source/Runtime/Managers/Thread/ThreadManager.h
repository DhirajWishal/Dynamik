#pragma once
#ifndef _DYNAMIK_THREAD_MANAGER_H
#define _DYNAMIK_THREAD_MANAGER_H

/*
 Author:    Dhiraj Wishal
 Date:      15/05/2020
*/

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

     There are 2 basic types of threads:
     * Permanent threads (the threads that exist throughout the engine's runtime)
     * Temporary threads (the threads that are used to complete a specific task)

     The permenent threads run critical components of the engine (eg: Rendering engine, Physics engine, Audio engine).
     These threads have only one instance throughout the runtime.
     The temporary threads are used to do calculations. One of the main systems are the object updation systems. The
     objects are sent as packages containing a number of objects. The object number depends on the number of available 
     threads and the number of objects available. Since the engine could use all the threads available in the CPU thus
     making the system unable to run its normal tasks, we always leave 25% of the threads to the CPU. The rest is used
     by the engine.

     Thread synchronization is done on the top of every parent thread loop.
    */
    class DMK_API DMKThreadManager {
    public:
        DMKThreadManager() {}
        ~DMKThreadManager() {}

        UI32 getUseableThreadCount();
    };
}

#endif // !_DYNAMIK_THREAD_MANAGER_H
