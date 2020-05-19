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

	void DMKEventHandler::addEventComponent(POINTER<DMKEventComponent> component)
	{
		myEventComponents.pushBack(component);
	}

	void DMKEventHandler::cleanComponents()
	{
		std::lock_guard<std::mutex> _guard(_localMutex);

		for (auto _component : myEventComponents)
			StaticAllocator<DMKEventComponent>::deallocate(_component, 0);

		myEventComponents.clear();
	}

	ARRAY<POINTER<DMKKeyEventListener>> DMKEventHandler::myKeyEventListeners;
	ARRAY<POINTER<DMKMouseButtonEventListener>> DMKEventHandler::myMouseButtonEventListeners;
	ARRAY<POINTER<DMKMouseScrollEventListener>> DMKEventHandler::myMouseScrollEventListeners;

	ARRAY<POINTER<DMKEventComponent>> DMKEventHandler::myEventComponents;
}