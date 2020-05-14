#pragma once
#ifndef _DYNAMIK_SERVER_COMPONENT_H
#define _DYNAMIK_SERVER_COMPONENT_H

/*
 Server component for the Dynamik Engine.
 All the internal simmulations (Physics engine, Destruction engine, etc..) will have a server - client 
 interface.

 Author:    Dhiraj Wishal
 Date:      14/05/2020
*/

#include "../Component.h"

namespace Dynamik 
{
    DMK_ALIGN class DMK_API DMKServerComponent : public DMKComponent {
    public:
        DMKServerComponent() {}
        virtual ~DMKServerComponent() {}
    };
}

#endif // !_DYNAMIK_SERVER_COMPONENT_H
