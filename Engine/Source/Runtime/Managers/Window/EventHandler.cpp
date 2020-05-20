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
		keyEventComponents.pushBack(component);
	}

	void DMKEventHandler::addMouseButtonEventComponent(const DMKMouseButtonEventComponent& component)
	{
		mouseButtonEventComponents.pushBack(component);
	}

	void DMKEventHandler::addMouseScrollEventComponent(const DMKMouseScrollEventComponent& component)
	{
		mouseScrollEventComponents.pushBack(component);
	}

	void DMKEventHandler::cleanComponents()
	{
		keyEventComponents.clear();
		mouseButtonEventComponents.clear();
		mouseScrollEventComponents.clear();
	}

	ARRAY<DMKKeyEventComponent> DMKEventHandler::getKeyEvents()
	{
		return keyEventComponents;
	}

	ARRAY<DMKMouseButtonEventComponent> DMKEventHandler::getMouseButtonEvents()
	{
		return mouseButtonEventComponents;
	}

	ARRAY<DMKMouseScrollEventComponent> DMKEventHandler::getMouseScrollEvents()
	{
		return mouseScrollEventComponents;
	}

	ARRAY<POINTER<DMKKeyEventListener>> DMKEventHandler::myKeyEventListeners;
	ARRAY<POINTER<DMKMouseButtonEventListener>> DMKEventHandler::myMouseButtonEventListeners;
	ARRAY<POINTER<DMKMouseScrollEventListener>> DMKEventHandler::myMouseScrollEventListeners;

	ARRAY<DMKKeyEventComponent> DMKEventHandler::keyEventComponents;
	ARRAY<DMKMouseButtonEventComponent> DMKEventHandler::mouseButtonEventComponents;
	ARRAY<DMKMouseScrollEventComponent> DMKEventHandler::mouseScrollEventComponents;
}
