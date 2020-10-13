// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "WindowManager.h"

#ifdef DMK_PLATFORM_WINDOWS
#include "Window/Windows/WindowsWindow.h"

#endif

I32 DMKWindowManager::createWindow(I32 width, I32 height, STRING title)
{
#ifdef DMK_PLATFORM_WINDOWS
	WindowsWindow* _window = StaticAllocator<WindowsWindow>::allocateInit(WindowsWindow(title, width, height));
	_window->initialize();
	_window->setEventCallbacks();
	myWindowHandles.push_back(_window);
#endif

	return Cast<I32>(windowIDs++);
}

DMKWindowHandle* DMKWindowManager::getWindowHandle(I32 windowID)
{
	return myWindowHandles[windowID];
}

void DMKWindowManager::terminateWindow(I32 windowIndex)
{
	myWindowHandles[windowIndex]->terminate();
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
