#pragma once
#ifndef _DYNAMIK_WINDOW_MANAGER_H
#define _DYNAMIK_WINDOW_MANAGER_H

/*
 Author:    Dhiraj Wishal
 Date:      19/05/2020
*/
#include "WindowHandle.h"

namespace Dynamik
{
    /*
     Dynamik Window Manager
     All the windows in used by the engine is created, manages and destroyed from this class.
    */
    class DMK_API DMKWindowManager : public DMKManagerObject {
        DMKWindowManager() {}
        ~DMKWindowManager() {}

    DMK_CLASS_SINGLETON(DMKWindowManager)

    public:
        static I32 createWindow(I32 width, I32 height, STRING title = "Dynamik Engine");
        static void terminateWindow(I32 windowIndex = 0);
        static void terminateAll();

        static DMKViewport createViewport(I32 windowIndex, I32 width, I32 height, I32 xOffset, I32 yOffset);

        static void addKeyEventListener(I32 windowIndex, POINTER<DMKKeyEventListener> listener);
        static void addMouseButtonEventListener(I32 windowIndex, POINTER<DMKMouseButtonEventListener> listener);
        static void addMouseScrollEventListener(I32 windowIndex, POINTER<DMKMouseScrollEventListener> listener);
        static void removeKeyEventListener(I32 windowIndex, I32 listenerIndex);
        static void removeMouseButtonEventListener(I32 windowIndex, I32 listenerIndex);
        static void removeMouseScrollEventListener(I32 windowIndex, I32 listenerIndex);

        static void pollEvents();
        static void clean();

    private:
        ARRAY<POINTER<DMKWindowHandle>> myWindowHandles;
    };
}

#endif // !_DYNAMIK_WINDOW_MANAGER_H
