#pragma once
#ifndef _DYNAMIK_MANAGER_OBJECT_H
#define _DYNAMIK_MANAGER_OBJECT_H

/*
 All the managers in the engine are derived from this.

 Author:    Dhiraj Wishal
 Date:      14/05/2020
*/

#include "../Component.h"

namespace Dynamik
{
    DMK_ALIGN class DMK_API DMKManagerObject : public DMKComponent {
        DMKManagerObject() {}
        virtual ~DMKManagerObject() {}
    };
}

#endif // !_DYNAMIK_MANAGER_OBJECT_H
