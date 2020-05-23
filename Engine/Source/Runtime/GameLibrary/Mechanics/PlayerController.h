#pragma once
#ifndef _DYNAMIK_PLAYER_CONTROLLER_H
#define _DYNAMIK_PLAYER_CONTROLLER_H

/*
 Author:    Dhiraj Wishal
 Date:      23/05/2020
*/
#include "../GameMechanics.h"
#include "Managers/Window/EventHandler.h"

namespace Dynamik
{
    /*
     Player controller for the Dynamik Engine
     The player camera is controlled by this object.
    */
    class DMK_API DMKPlayerController : public DMKGameMechanics {
    public:
        DMKPlayerController() {}
        virtual ~DMKPlayerController() {}

        virtual void onUpdate(const DMKEventBuffer& events, const UI32& tick);
    };
}

#endif // !_DYNAMIK_PLAYER_CONTROLLER_H
