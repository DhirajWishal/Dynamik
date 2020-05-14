#pragma once
#ifndef _DYNAMIK_RESOURCE_H
#define _DYNAMIK_RESOURCE_H

/*
 Dynamik Resource base class for the Dynamik Engine.

 Author:    Dhiraj Wishal
 Date:      14/05/2020
*/

#include "Object.h"

namespace Dynamik
{
    DMK_ALIGN class DMK_API DMKResource : public DMKObject {
    public:
        DMKResource() {}
        virtual ~DMKResource() {}
    };
}

#endif // !_DYNAMIK_RESOURCE_H
