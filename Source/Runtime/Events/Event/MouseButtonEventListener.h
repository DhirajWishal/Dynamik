// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_MOUSE_BUTTON_EVENT_LISTENER_H
#define _DYNAMIK_MOUSE_BUTTON_EVENT_LISTENER_H

/*
 Author:    Dhiraj Wishal
 Date:      19/05/2020
*/
#include "EventListener.h"

namespace Dynamik
{
    class DMKMouseButtonEventComponent : public DMKEventComponent {
    public:
        DMKMouseButtonEventComponent() : DMKEventComponent(DMKEventComponentCategory::DMK_EVENT_COMPONENT_CATEGORY_MOUSE_BUTTON){}
        ~DMKMouseButtonEventComponent() {}

        I32 action = 0;
        I32 mods = 0;
    };

    /*
     Dynamik Mouse Button Event Listener
    */
    class DMK_API DMKMouseButtonEventListener : public DMKEventListener {
    public:
        DMKMouseButtonEventListener() {}
        virtual ~DMKMouseButtonEventListener() {}

        virtual void onEvent(I32 button, I32 action, I32 mods);
    };
}

#endif // !_DYNAMIK_MOUSE_BUTTON_EVENT_LISTNER_H
