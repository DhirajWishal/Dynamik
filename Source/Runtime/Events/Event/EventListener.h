// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_EVENT_LISTENER_H
#define _DYNAMIK_EVENT_LISTENER_H

/*
 Author:    Dhiraj Wishal
 Date:      19/05/2020
*/
#include "KeyCodes.h"
#include "Core/Macros/Global.h"

namespace Dynamik
{
    /*
     Event listner base class for the Dynamik Engine.
     There are multiple types of event listeners,
     * Key Event listner
     * Mouse Event listner
        - Mouse Button event
        - Mouse Scroll event
        - Mouse Moved event
     * Joystick Event
     * Application Evnet
        - Window Resize Event
        - Window Drop Path Event
        - Cursor On Current Event
    */
    class DMK_API DMKEventListener {
    public:
        DMKEventListener() {}
        virtual ~DMKEventListener() {}
    };

    /* Dynamik Event Component Category enum */
    enum class DMK_API DMKEventComponentCategory {
        DMK_EVENT_COMPONENT_CATEGORY_APPLICATION,
        DMK_EVENT_COMPONENT_CATEGORY_KEY,
        DMK_EVENT_COMPONENT_CATEGORY_MOUSE_BUTTON,
        DMK_EVENT_COMPONENT_CATEGORY_MOUSE_SCROLL,
        DMK_EVENT_COMPONENT_CATEGORY_MOUSE_POSITION,
    };

    /* Dynamik Event Type enum */
    enum class DMK_API DMKEventType {
        DMK_EVENT_TYPE_PRESS,
        DMK_EVENT_TYPE_RELEASE,
        DMK_EVENT_TYPE_REPEAT,
    };

    /*
     Event Component structure for the Dynamik Engine.
     By default all the events are buffered by the event manager which is tied to a window handle. These 
     components then later can be accessed by polling events. This event buffer will be cleared at the end of
     each main loop iteration.
    */
    class DMK_API DMKEventComponent {
    public:
        DMKEventComponent(DMKEventComponentCategory cat) : eventCategory(cat) {}
        virtual ~DMKEventComponent() {}

        DMKEventComponentCategory eventCategory = DMKEventComponentCategory::DMK_EVENT_COMPONENT_CATEGORY_KEY;
        DMKEventType eventType = DMKEventType::DMK_EVENT_TYPE_PRESS;
        DMKEvent event = DMKEvent::DMK_EVENT_KEY_UNKNOWN;
    };
}

#endif // !_DYNAMIK_EVENT_LISTNER_H
