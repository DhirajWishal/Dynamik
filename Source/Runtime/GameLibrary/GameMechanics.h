// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GAME_MECHANICS_H
#define _DYNAMIK_GAME_MECHANICS_H

#include "Core/Macros/Global.h"

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
