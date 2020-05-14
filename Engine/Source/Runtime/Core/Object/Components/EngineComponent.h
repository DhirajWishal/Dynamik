#pragma once
#ifndef _DYNAMIK_ENGINE_COMPONENT_H
#define _DYNAMIK_ENGINE_COMPONENT_H

/*
 Engine component for the Dynamik Engine.
 All the Engine APIs available in the engine are derived from this.

 Author:    Dhiraj Wishal
 Date:      14/05/2020
*/

#include "../Component.h"

namespace Dynamik
{
    DMK_ALIGN class DMK_API DMKEngineComponent : public DMKComponent {
    public:
        DMKEngineComponent() {}
       virtual ~ DMKEngineComponent() {}
    };
}

#endif // !_DYNAMIK_ENGINE_COMPONENT_H
