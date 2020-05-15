#pragma once
#ifndef _DYNAMIK_STATIC_OBJECT_H
#define _DYNAMIK_STATIC_OBJECT_H

/*
 Dynamik Static Object for the Dynamik Game Library.

 Author:    Dhiraj Wishal
 Date:      15/05/2020
*/

#include "../GameObject.h"

namespace Dynamik
{
    /*
     Static Object for the Dynamik Engine.
     These objects are the objects which the user cant directly interact with (eg: Rock, Tree, House, etc)
     but the object can be manipulated by other objects.
    */
    DMK_ALIGN class DMK_API DMKStaticObject : public DMKGameObject {
    public:
        DMKStaticObject() : DMKGameObject(DMKGameObjectType::DMK_GAME_OBJECT_TYPE_STATIC) {}
        virtual ~DMKStaticObject() {}
    };
}

#endif // !_DYNAMIK_STATIC_OBJECT_H
