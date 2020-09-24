// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_WINDOW_HANDLE_H
#define _DYNAMIK_WINDOW_HANDLE_H

#include "Events/EventPool.h"
#include "Core/Types/DataTypes.h"
#include "Core/Types/Array.h"
#include "Core/Types/ComplexTypes.h"

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

	DMKWindowHandle* windowHandle = nullptr;

	I32 width = 0;
	I32 height = 0;
	I32 xOffset = 0;
	I32 yOffset = 0;
};

/*
 Dynamik Window Handle
 Each and every window used in the Dynamik Engine is derived from this class. Every window contains its own
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
	virtual void setEventBoard(DMKEventPool* pEventPool) { this->pEventPool = pEventPool; }
	virtual void initializeKeyBindings() {}
	virtual void setEventCallbacks() {}
	virtual void setWindowIcon(STRING path) {}
	virtual void pollEvents() {}
	virtual void onUpdate() {}
	virtual void clean() {}
	virtual void terminate() {}

	DMKExtent2D getWindowExtent() { return { (F32)windowWidth, (F32)windowHeight }; }

	virtual B1 isVulkanCompatible() { return false; }

	virtual DMKViewport createViewport(I32 width, I32 height, I32 xOffset, I32 yOffset) { return DMKViewport(); }

	STRING windowTitle = TEXT("Dynamik Engine v1");
	I32 windowWidth = 0;
	I32 windowHeight = 0;

public:		/* Event Utilities */
	virtual DMKExtent2D getCursorPosition() { return DMKExtent2D(); }

protected:
	ARRAY<DMKViewport> inUseViewports;
	DMKEventPool* pEventPool = nullptr;
};

#endif // !_DYNAMIK_WINDOW_HANDLE_H
