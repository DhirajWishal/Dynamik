#pragma once
#ifndef _DYNAMIK_MOUSE_SCROLL_EVENT_LISTENER_H
#define _DYNAMIK_MOUSE_SCROLL_EVENT_LISTENER_H

/*
 Author:    Dhiraj Wishal
 Date:      19/05/2020
*/
#include "EventListener.h"

namespace Dynamik
{
    struct DMK_API DMKMouseScrollEventComponent : public DMKEventComponent {
        DMKMouseScrollEventComponent() : DMKEventComponent(DMKEventComponentCategory::DMK_EVENT_COMPONENT_CATEGORY_MOUSE_SCROLL) {}
        ~DMKMouseScrollEventComponent() {}

        D64 xOffset = 0.0;
        D64 yOffset = 0.0;
    };

    /*
     Dynamik Mouse Scroll Event Listener
    */
    class DMK_API DMKMouseScrollEventListener : public DMKEventListener {
    public:
        DMKMouseScrollEventListener() {}
        virtual ~DMKMouseScrollEventListener() {}

        virtual void onEvent(D64 xOffset, D64 yOffset);
    };
}

#endif // !_DYNAMIK_MOUSE_SCROLL_EVENT_LISTENER_H
