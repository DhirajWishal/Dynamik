#pragma once
#ifndef _DYNAMIK_GAME_OBJECT_H
#define _DYNAMIK_GAME_OBJECT_H

/*
 Dynamik Game Object for the Dynamik Engine.
 All the game library objects are derived from this.

 Author:    Dhiraj Wishal
 Date:      14/05/2020
*/

#include "Object.h"

namespace Dynamik
{
    DMK_ALIGN class DMK_API DMKGameObject : public DMKObject {
    public:
        DMKGameObject() {}
        virtual ~DMKGameObject() {}
    };
}

#endif // !_DYNAMIK_GAME_OBJECT_H
