#pragma once
#ifndef _DYNAMIK_STUDIO_WIN32_WINDOW_HANDLE_H
#define _DYNAMIK_STUDIO_WIN32_WINDOW_HANDLE_H

/*
 Author:    Dhiraj Wishal
 Date:      21/05/2020
*/
#include "../Window.h"

namespace Dynamik
{
    class Win32WindowHandle : public DMKWindow {
    public:
        Win32WindowHandle() {}
        ~Win32WindowHandle() {}
    };
}

#endif // !_DYNAMIK_STUDIO_WIN32_WINDOW_HANDLE_H
