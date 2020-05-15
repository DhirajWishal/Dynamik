/*
 This file contains all the definitions of the Dynamik Engine interface.

 Author:    Dhiraj Wishal
 Date:      15/05/2020
*/

#include "dmkafx.h"
#include "Dynamik.h"

#include "Error/ErrorManager.h"
#include "Core/Utilities/Clock.h"

namespace Dynamik
{
    /* Main singleton implementation */
    DMK_CLASS_SINGLETON_IMPL(DMKEngine);

    /* Default constructor */
    DMKEngine::DMKEngine()
    {
        DMKClock::start();
    }
    
    /* Default destructor */
    DMKEngine::~DMKEngine()
    {
        DMKClock::end();
    }
    
    /* Create the Dynamik Engine instance. */
    void DMKEngine::createInstance()
    {
        DMKErrorManager::logInfo("Welcome to the Dynamik Engine!");
    }
}