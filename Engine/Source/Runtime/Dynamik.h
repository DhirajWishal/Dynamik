#pragma once
#ifndef _DYNAMIK_H
#define _DYNAMIK_H

/*
 Main Dynamik Engine Interface.
 This file contains all the necessary engine interfaces provided by the Dynamik Engine.

 Author:    Dhiraj Wishal
 Date:      15/05/2020
*/

#include "Object/Component.h"

namespace Dynamik
{
    /*
     This class provides all the necessary interfaces for the user to control the core components
     of the Dynamik Engine.

     This class is created as a singleton and users can create a wrapper class to fit their own design.
     
     Users are required to follow some steps to properly initialize and execute their game code from this engine.
     These steps are as follows:
     * Create the engine instance.
     * Create a window object (this is optional as the engine will create a window if not created).
     * Initialize internal components of the engine.
     * Set default camera if needed.
     * Submit level(s).

     <When rendering a scene>
     * Load scene data.
     * Generate renderables.
     * Finalize the renderables.
     * Call the main loop.

     <When shutting down>
     * Terminate renderables.
     * Unload Level.
     * Terminate engine components.
     * Terminate engine instance.
    */
    DMK_ALIGN class DMK_API DMKEngine : public DMKComponent {
        DMKEngine();
        ~DMKEngine();

        DMK_CLASS_SINGLETON(DMKEngine)
    public:
        /*
         Create a new engine instance.
         Since Dynamik only allows to instanciate one engine instance at a time, calling this function in the 
         presence of a valid instance will result to a warning and would not create a new instance. If required
         to create a new instance while the engine is instantiated, the engine must be terminated successfully
         to do so.
        */
        static void createInstance();

    };
}

#endif // !_DYNAMIK_H
