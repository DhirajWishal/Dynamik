// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_WINDOW_MANAGER_H
#define _DYNAMIK_WINDOW_MANAGER_H

/*
 Author:    Dhiraj Wishal
 Date:      19/05/2020
*/
#include "Window/WindowHandle.h"
#include "Core/Macros/Global.h"
#include "Core/Types/DataTypes.h"
#include "Core/Types/Array.h"

namespace Dynamik
{
	/*
	 Dynamik Window Manager
	 All the windows in used by the engine is created, manages and destroyed from this class.
	*/
	class DMK_API DMKWindowManager {
	public:
		DMKWindowManager() {}
		~DMKWindowManager() {}

		I32 createWindow(I32 width, I32 height, STRING title = "Dynamik Engine");
		DMKWindowHandle* getWindowHandle(I32 windowID);
		void terminateWindow(I32 windowIndex = 0);
		void terminateAll();

		DMKViewport createViewport(I32 windowIndex, I32 width, I32 height, I32 xOffset, I32 yOffset);

		void addKeyEventListener(I32 windowIndex, DMKKeyEventListener* listener);
		void addMouseButtonEventListener(I32 windowIndex, DMKMouseButtonEventListener* listener);
		void addMouseScrollEventListener(I32 windowIndex, DMKMouseScrollEventListener* listener);
		void removeKeyEventListener(I32 windowIndex, I32 listenerIndex);
		void removeMouseButtonEventListener(I32 windowIndex, I32 listenerIndex);
		void removeMouseScrollEventListener(I32 windowIndex, I32 listenerIndex);

		void pollEvents();
		void clean();

		ARRAY<DMKKeyEventComponent> getKeyEventComponents(I32 windowIndex);
		ARRAY<DMKMouseButtonEventComponent> getMouseButtonEventComponents(I32 windowIndex);
		ARRAY<DMKMouseScrollEventComponent> getMouseScrollEventComponents(I32 windowIndex);

	private:
		ARRAY<DMKWindowHandle*> myWindowHandles;
		UI64 windowIDs = 0;
	};
}

#endif // !_DYNAMIK_WINDOW_MANAGER_H
