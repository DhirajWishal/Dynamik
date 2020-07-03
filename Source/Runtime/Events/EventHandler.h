// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

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

#include "Core/Macros/Global.h"
#include "Core/Types/Array.h"

namespace Dynamik
{
	/*
	 Dynamik Event Buffer
	 This buffer contains all the events that occurred in one iteration of the main loop.
	*/
	struct DMK_API DMKEventBuffer {
		ARRAY<DMKKeyEventComponent> keyEventComponents;
		ARRAY<DMKMouseScrollEventComponent> mouseScrollEventComponents;
		ARRAY<DMKMouseButtonEventComponent> mouseButtonEventComponents;
	};

	/*
	 Dynamik Event Handler
	 Event handlers are per object. Which means that each and every window handle contains its own event handler.

	 Event Handler can have multiple listeners of the same type.
	*/
	class DMK_API DMKEventHandler {
	public:
		DMKEventHandler() {}
		virtual ~DMKEventHandler() {}

		void addKeyEventListener(const DMKKeyEventListener* listener);
		void addMouseButtonEventListener(const DMKMouseButtonEventListener* listener);
		void addMouseScrollEventListener(const DMKMouseScrollEventListener* listener);
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
		static ARRAY<DMKKeyEventListener*> myKeyEventListeners;
		static ARRAY<DMKMouseButtonEventListener*> myMouseButtonEventListeners;
		static ARRAY<DMKMouseScrollEventListener*> myMouseScrollEventListeners;

		static DMKEventBuffer eventBuffer;
	};
}

#endif // !_DYNAMIK_EVENT_HANDLER_H
