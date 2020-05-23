#pragma once
#ifndef _DYNAMIK_EVENT_HANDLER_H
#define _DYNAMIK_EVENT_HANDLER_H

/*
 Author:    Dhiraj Wishal
 Date:      19/05/2020
*/
#include "Event/EventListener.h"
#include "Event/KeyEventListener.h"
#include "Event/MouseButtonEventListener.h"
#include "Event/MouseScrollEventListener.h"

#include "Macros/Global.h"
#include "Types/Array.h"

namespace Dynamik
{
	/*
	 Dynamik Event Handler
	 Event handlers are per object. Which means that each and every window handle contains its own event handler.

	 Event Handler can have multiple listeners of the same type.
	*/
	class DMK_API DMKEventHandler {
	public:
		DMKEventHandler() {}
		virtual ~DMKEventHandler() {}

		void addKeyEventListener(const POINTER<DMKKeyEventListener>& listener);
		void addMouseButtonEventListener(const POINTER<DMKMouseButtonEventListener>& listener);
		void addMouseScrollEventListener(const POINTER<DMKMouseScrollEventListener>& listener);
		void removeKeyEventListener(I32 listenerIndex);
		void removeMouseButtonEventListener(I32 listenerIndex);
		void removeMouseScrollEventListener(I32 listenerIndex);

		void addKeyEventComponent(const DMKKeyEventComponent& component);
		void addMouseButtonEventComponent(const DMKMouseButtonEventComponent& component);
		void addMouseScrollEventComponent(const DMKMouseScrollEventComponent& component);
		void cleanComponents();

		ARRAY<DMKKeyEventComponent> getKeyEvents();
		ARRAY<DMKMouseButtonEventComponent> getMouseButtonEvents();
		ARRAY<DMKMouseScrollEventComponent> getMouseScrollEvents();

	protected:
		static ARRAY<POINTER<DMKKeyEventListener>> myKeyEventListeners;
		static ARRAY<POINTER<DMKMouseButtonEventListener>> myMouseButtonEventListeners;
		static ARRAY<POINTER<DMKMouseScrollEventListener>> myMouseScrollEventListeners;

		static ARRAY<DMKKeyEventComponent> keyEventComponents;
		static ARRAY<DMKMouseButtonEventComponent> mouseButtonEventComponents;
		static ARRAY<DMKMouseScrollEventComponent> mouseScrollEventComponents;
	};
}

#endif // !_DYNAMIK_EVENT_HANDLER_H
