#pragma once
#ifndef _DYNAMIK_GAME_MECHANICS_H
#define _DYNAMIK_GAME_MECHANICS_H

/*
 Author:    Dhiraj Wishal
 Date:      23/05/2020
*/
#include "Macros/Global.h"

namespace Dynamik
{
    /*
     Dynamik Game Mechanics object
     All the game mechanics, logic, player controls are derived from this object.
    */
    class DMK_API DMKGameMechanics  {
    public:
        DMKGameMechanics() {}
        virtual ~DMKGameMechanics() {}
    };
}

#endif // !_DYNAMIK_GAME_MECHANICS_H
