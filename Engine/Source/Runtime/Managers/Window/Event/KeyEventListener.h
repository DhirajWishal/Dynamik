#pragma once
#ifndef _DYNAMIK_KEY_EVENT_LISTENER_H
#define _DYNAMIK_KEY_EVENT_LISTENER_H

/*
 Author:    Dhiraj Wishal
 Date:      19/05/2020
*/
#include "EventListener.h"

namespace Dynamik
{
    struct DMK_API DMKKeyEventComponent : public DMKEventComponent {
        DMKKeyEventComponent() : DMKEventComponent(DMKEventComponentCategory::DMK_EVENT_COMPONENT_CATEGORY_KEY) {}
        ~DMKKeyEventComponent() {}

        I32 keyCode = 0;
        I32 action = 0;
        I32 mods = 0;
        I32 scanCode = 0;
    };

    /*
     Dynamik Key Event Listener
    */
    class DMK_API DMKKeyEventListener : public DMKEventListener {
    public:
        DMKKeyEventListener() {}
        virtual ~DMKKeyEventListener() {}

        virtual void onEvent(I32 keyCode, I32 action, I32 mods, I32 scanCode);
    };
}

#endif // !_DYNAMIK_KEY_EVENT_LISTNER_H
