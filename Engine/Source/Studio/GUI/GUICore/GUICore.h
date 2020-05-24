#pragma once
#ifndef _DYNAMIK_GUI_CORE_H
#define _DYNAMIK_GUI_CORE_H

/*
 Author:    Dhiraj Wishal
 Date:      23/05/2020
*/
#include "Macros/Global.h"

namespace Dynamik
{
    /*
     GUI Core for the Dynamik Engine
     This renderer uses OpenGL to render to a window which this class maintains. GUI elements are provided at
     drawtime.
    */
    class DMK_API GUICore {
    public:
        GUICore();
        GUICore(I32 width, I32 height, STRING title = "Dynamik Studio v1");
        ~GUICore();

        void initialize();

        void initializeFrame();
        void updateRenderables();
        void submitRenderables();

    private:
        static void _errorCallback(I32 ID, CCPTR description);
        I32 windowWidth = 0;
        I32 windowHeight = 0;
        STRING windowTitle = DMK_TEXT("");
    };
}

#endif // !_DYNAMIK_GUI_CORE_H
