#pragma once
#ifndef _DYNAMIK_GAME_COMPONENT_DESCRIPTORS_H
#define _DYNAMIK_GAME_COMPONENT_DESCRIPTORS_H

/*
 Game Component Descriptors for the Dynamik Engine.
 This file contains all the descriptors that are required by game components.

 Author:    Dhiraj Wishal
 Date:      15/05/2020
*/

#include "../Descriptor.h"
#include "Object/Resource/Primitives.h"

namespace Dynamik
{
    /* Game Object Descriptors */
    DMK_ALIGN struct DMK_API DMKAssetDesriptor {
        STRING resourcePath = DMK_TEXT("");
    };
}

#endif // !_DYNAMIK_GAME_COMPONENT_DESCRIPTORS_H
