#pragma once
#ifndef _DYNAMIK_WINDOW_HANDLE_H
#define _DYNAMIK_WINDOW_HANDLE_H

/*
 Author:    Dhiraj Wishal
 Date:      19/05/2020
*/
#include "EventHandler.h"
#include "Types/DataTypes.h"
#include "Types/Array.h"

namespace Dynamik
{
	class DMK_API DMKWindowHandle;

	/*
	 Dynamik Viewport class
	 Each viewport contains a pointer to its parent window, window extent (width, height) and the offsets
	 (x and y).
	 Rendering APIs can use this to derive API specific viewport types.
	*/
	class DMK_API DMKViewport {
	public:
		DMKViewport() {}
		virtual ~DMKViewport() {}

		POINTER<DMKWindowHandle> windowHandle;

		I32 width = 0;
		I32 height = 0;
		I32 xOffset = 0;
		I32 yOffset = 0;
	};

	/*
	 Dynamik Window Handle
	 Each and every window used in the Dynamik Engine is derived from this class. Evary window contains its own
	 Event Handler to handle events. A window could have multiple viewports and one viewport is bound to one
	 rendering context. Rendering contexts can have multiple viewports from one or from different window
	 handles.
	*/
	class DMK_API DMKWindowHandle {
	public:
		DMKWindowHandle() : windowTitle("Dynamik Engine v1"), windowWidth(1280), windowHeight(720) {}
		DMKWindowHandle(const STRING& title, const I32& width, const I32& height)
			: windowTitle(title), windowWidth(width), windowHeight(height) {}
		virtual ~DMKWindowHandle() {}

		virtual void initialize() {}
		virtual void setEventCallbacks() {}
		virtual void setWindowIcon(STRING path) {}
		virtual void pollEvents() {}
		virtual void clean() {}
		virtual void terminate() {}

		virtual void addKeyEventListner(const POINTER<DMKKeyEventListener>& listener) {}
		virtual void addMouseButtonEventListener(const POINTER<DMKMouseButtonEventListener>& listener) {}
		virtual void addMouseScrollEventListener(const POINTER<DMKMouseScrollEventListener>& listener) {}
		virtual void removeKeyEventListener(I32 listenerIndex) {}
		virtual void removeMouseButtonEventListener(I32 listenerIndex) {}
		virtual void removeMouseScrollEventListener(I32 listenerIndex) {}

		virtual B1 isVulkanCompatible() { return false; }

		virtual DMKViewport createViewport(I32 width, I32 height, I32 xOffset, I32 yOffset) { return DMKViewport(); }

		virtual ARRAY<DMKKeyEventComponent> getKeyEvents() { return ARRAY<DMKKeyEventComponent>(); }
		virtual ARRAY<DMKMouseButtonEventComponent> getMouseButtonEvents() { return ARRAY<DMKMouseButtonEventComponent>(); }
		virtual ARRAY<DMKMouseScrollEventComponent> getMouseScrollEvents() { return ARRAY<DMKMouseScrollEventComponent>(); }

		STRING windowTitle = DMK_TEXT("Dynamik Engine v1");
		I32 windowWidth = 0;
		I32 windowHeight = 0;

	protected:
		ARRAY<DMKViewport> inUseViewports;
	};
}

#endif // !_DYNAMIK_WINDOW_HANDLE_H
