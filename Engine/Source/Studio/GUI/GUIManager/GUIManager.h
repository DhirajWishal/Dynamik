#pragma once
#ifndef _DYNAMIK_STUDIO_GUI_MANAGER_H
#define _DYNAMIK_STUDIO_GUI_MANAGER_H

/*
 Author:	Dhiraj Wishal
 Date:		04/06/2020
*/
#include "Window/WindowHandle.h"

namespace Dynamik
{
	/*
	 GUI manager for the Dynamik Studio
	*/
	class GUIManager {
	public:
		GUIManager();
		~GUIManager();

		void initialize();

		void beginFrame();
		void onUpdate();
		void endFrame();

		void terminate();

		POINTER<DMKWindowHandle> windowHandle;

		D64 time = 0.0;
	};
}

#endif // !_DYNAMIK_STUDIO_GUI_MANAGER_H
