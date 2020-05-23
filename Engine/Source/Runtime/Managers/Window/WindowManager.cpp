#include "dmkafx.h"
#include "WindowManager.h"

#ifdef DMK_PLATFORM_WINDOWS
	#include "Windows/WindowsWindow.h"

#endif

namespace Dynamik
{
	I32 DMKWindowManager::createWindow(I32 width, I32 height, STRING title)
	{
#ifdef DMK_PLATFORM_WINDOWS
		POINTER<WindowsWindow> _window = StaticAllocator<WindowsWindow>::allocateInit(WindowsWindow(title, width, height));
		_window->initialize();
		_window->setEventCallbacks();
		myWindowHandles.pushBack(_window);
#endif

		return myWindowHandles[myWindowHandles.size() - 1];
	}
	
	void DMKWindowManager::terminateWindow(I32 windowIndex)
	{
		myWindowHandles[windowIndex]->terminate();
		myWindowHandles.remove(windowIndex);
	}

	void DMKWindowManager::terminateAll()
	{
		for (auto _handle : myWindowHandles)
			_handle->terminate();
	}

	DMKViewport DMKWindowManager::createViewport(I32 windowIndex, I32 width, I32 height, I32 xOffset, I32 yOffset)
	{
		return myWindowHandles[windowIndex]->createViewport(width, height, xOffset, yOffset);
	}

	void DMKWindowManager::addKeyEventListener(I32 windowIndex, POINTER<DMKKeyEventListener> listener)
	{
		myWindowHandles[windowIndex]->addKeyEventListner(listener);
	}

	void DMKWindowManager::addMouseButtonEventListener(I32 windowIndex, POINTER<DMKMouseButtonEventListener> listener)
	{
		myWindowHandles[windowIndex]->addMouseButtonEventListener(listener);
	}

	void DMKWindowManager::addMouseScrollEventListener(I32 windowIndex, POINTER<DMKMouseScrollEventListener> listener)
	{
		myWindowHandles[windowIndex]->addMouseScrollEventListener(listener);
	}

	void DMKWindowManager::removeKeyEventListener(I32 windowIndex, I32 listenerIndex)
	{
		myWindowHandles[windowIndex]->removeKeyEventListener(listenerIndex);
	}

	void DMKWindowManager::removeMouseButtonEventListener(I32 windowIndex, I32 listenerIndex)
	{
		myWindowHandles[windowIndex]->removeMouseButtonEventListener(listenerIndex);
	}
	
	void DMKWindowManager::removeMouseScrollEventListener(I32 windowIndex, I32 listenerIndex)
	{
		myWindowHandles[windowIndex]->removeMouseScrollEventListener(listenerIndex);
	}
	
	void DMKWindowManager::pollEvents()
	{
		for (auto _handle : myWindowHandles)
			_handle->pollEvents();
	}
	
	void DMKWindowManager::clean()
	{
		for (auto _handle : myWindowHandles)
			_handle->clean();
	}

	ARRAY<DMKKeyEventComponent> DMKWindowManager::getKeyEventComponents(I32 windowIndex)
	{
		return myWindowHandles[windowIndex]->getKeyEvents();
	}

	ARRAY<DMKMouseButtonEventComponent> DMKWindowManager::getMouseButtonEventComponents(I32 windowIndex)
	{
		return myWindowHandles[windowIndex]->getMouseButtonEvents();
	}

	ARRAY<DMKMouseScrollEventComponent> DMKWindowManager::getMouseScrollEventComponents(I32 windowIndex)
	{
		return myWindowHandles[windowIndex]->getMouseScrollEvents();
	}
}