// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "EventHandler.h"

#include <mutex>

namespace Dynamik
{
	std::mutex _localMutex;

	void DMKEventHandler::addKeyEventListener(const DMKKeyEventListener* listener)
	{
		myKeyEventListeners.pushBack((DMKKeyEventListener*)listener);
	}

	void DMKEventHandler::addMouseButtonEventListener(const DMKMouseButtonEventListener* listener)
	{
		myMouseButtonEventListeners.pushBack((DMKMouseButtonEventListener*)listener);
	}

	void DMKEventHandler::addMouseScrollEventListener(const DMKMouseScrollEventListener* listener)
	{
		myMouseScrollEventListeners.pushBack((DMKMouseScrollEventListener*)listener);
	}

	void DMKEventHandler::removeKeyEventListener(I32 listenerIndex)
	{
		myKeyEventListeners.remove(listenerIndex);
	}

	void DMKEventHandler::removeMouseButtonEventListener(I32 listenerIndex)
	{
		myMouseButtonEventListeners.remove(listenerIndex);
	}

	void DMKEventHandler::removeMouseScrollEventListener(I32 listenerIndex)
	{
		myMouseScrollEventListeners.remove(listenerIndex);
	}

	void DMKEventHandler::addKeyEventComponent(const DMKKeyEventComponent& component)
	{
		eventBuffer.keyEventComponents.pushBack(component);
	}

	void DMKEventHandler::addMouseButtonEventComponent(const DMKMouseButtonEventComponent& component)
	{
		eventBuffer.mouseButtonEventComponents.pushBack(component);
	}

	void DMKEventHandler::addMouseScrollEventComponent(const DMKMouseScrollEventComponent& component)
	{
		eventBuffer.mouseScrollEventComponents.pushBack(component);
	}

	void DMKEventHandler::cleanComponents()
	{
		eventBuffer.keyEventComponents.clear();
		eventBuffer.mouseButtonEventComponents.clear();
		eventBuffer.mouseScrollEventComponents.clear();
	}

	ARRAY<DMKKeyEventComponent> DMKEventHandler::getKeyEvents()
	{
		return eventBuffer.keyEventComponents;
	}

	ARRAY<DMKMouseButtonEventComponent> DMKEventHandler::getMouseButtonEvents()
	{
		return eventBuffer.mouseButtonEventComponents;
	}

	ARRAY<DMKMouseScrollEventComponent> DMKEventHandler::getMouseScrollEvents()
	{
		return eventBuffer.mouseScrollEventComponents;
	}

	ARRAY<DMKKeyEventListener*> DMKEventHandler::myKeyEventListeners;
	ARRAY<DMKMouseButtonEventListener*> DMKEventHandler::myMouseButtonEventListeners;
	ARRAY<DMKMouseScrollEventListener*> DMKEventHandler::myMouseScrollEventListeners;

	DMKEventBuffer DMKEventHandler::eventBuffer;
}
