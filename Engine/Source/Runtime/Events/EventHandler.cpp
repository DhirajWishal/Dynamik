#include "dmkafx.h"
#include "EventHandler.h"

#include <mutex>

namespace Dynamik
{
	std::mutex _localMutex;

	void DMKEventHandler::addKeyEventListener(const POINTER<DMKKeyEventListener>& listener)
	{
		myKeyEventListeners.pushBack(listener);
	}

	void DMKEventHandler::addMouseButtonEventListener(const POINTER<DMKMouseButtonEventListener>& listener)
	{
		myMouseButtonEventListeners.pushBack(listener);
	}

	void DMKEventHandler::addMouseScrollEventListener(const POINTER<DMKMouseScrollEventListener>& listener)
	{
		myMouseScrollEventListeners.pushBack(listener);
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

	ARRAY<POINTER<DMKKeyEventListener>> DMKEventHandler::myKeyEventListeners;
	ARRAY<POINTER<DMKMouseButtonEventListener>> DMKEventHandler::myMouseButtonEventListeners;
	ARRAY<POINTER<DMKMouseScrollEventListener>> DMKEventHandler::myMouseScrollEventListeners;

	DMKEventBuffer DMKEventHandler::eventBuffer;
}
