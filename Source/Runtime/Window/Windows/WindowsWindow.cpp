// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "WindowsWindow.h"

namespace Dynamik
{
	/* Local Mutex */
	std::mutex _myMutex;

	DMKEventType getGLFWEventType(I32 action)
	{
		if (action == GLFW_PRESS)
			return DMKEventType::DMK_EVENT_TYPE_PRESS;
		if (action == GLFW_RELEASE)
			return DMKEventType::DMK_EVENT_TYPE_RELEASE;
		if (action == GLFW_REPEAT)
			return DMKEventType::DMK_EVENT_TYPE_REPEAT;

		return DMKEventType::DMK_EVENT_TYPE_FREE;
	}

	DMKViewport WindowsWindow::createViewport(I32 width, I32 height, I32 xOffset, I32 yOffset)
	{
		DMKViewport newViewport;
		newViewport.width = width;
		newViewport.height = height;
		newViewport.xOffset = xOffset;
		newViewport.yOffset = yOffset;
		newViewport.windowHandle = this;

		return newViewport;
	}

	void WindowsWindow::initialize()
	{
		glfwSetErrorCallback(InternalEventHandler::_errorCallback);
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);

#if defined(DMK_DEBUG)
		windowHandle = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), nullptr, nullptr);

#else
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

		windowHandle = glfwCreateWindow(mode->width, mode->height, windowTitle.c_str(), monitor, NULL);
		windowWidth = mode->width;
		windowHeight = mode->height;

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

#endif

		glfwSetWindowUserPointer(windowHandle, this);
	}

	void WindowsWindow::initializeKeyBindings()
	{
#define BIND_KEY(component, KEY)  pEventPool->bindKey(pEventPool->component.name, glfwGetKeyScancode(KEY))

		BIND_KEY(KeyLeft, GLFW_KEY_LEFT);
		BIND_KEY(KeyRight, GLFW_KEY_RIGHT);
		BIND_KEY(KeyUp, GLFW_KEY_UP);
		BIND_KEY(KeyDown, GLFW_KEY_DOWN);

		BIND_KEY(KeyBackSpace, GLFW_KEY_BACKSPACE);
		BIND_KEY(KeyTab, GLFW_KEY_TAB);
		BIND_KEY(KeyEnter, GLFW_KEY_ENTER);
		BIND_KEY(KeyPause, GLFW_KEY_PAUSE);

		BIND_KEY(KeyCapsLock, GLFW_KEY_PAUSE);
		BIND_KEY(KeyEscape, GLFW_KEY_ESCAPE);
		BIND_KEY(KeySpaceBar, GLFW_KEY_SPACE);
		BIND_KEY(KeyPageUp, GLFW_KEY_PAGE_UP);
		BIND_KEY(KeyPageDown, GLFW_KEY_PAGE_DOWN);
		BIND_KEY(KeyEnd, GLFW_KEY_END);
		BIND_KEY(KeyHome, GLFW_KEY_HOME);

		BIND_KEY(KeyZero, GLFW_KEY_0);
		BIND_KEY(KeyOne, GLFW_KEY_1);
		BIND_KEY(KeyTwo, GLFW_KEY_2);
		BIND_KEY(KeyThree, GLFW_KEY_3);
		BIND_KEY(KeyFour, GLFW_KEY_4);
		BIND_KEY(KeyFive, GLFW_KEY_5);
		BIND_KEY(KeySix, GLFW_KEY_6);
		BIND_KEY(KeySeven, GLFW_KEY_7);
		BIND_KEY(KeyEight, GLFW_KEY_8);
		BIND_KEY(KeyNine, GLFW_KEY_9);

		BIND_KEY(KeyA, GLFW_KEY_A);
		BIND_KEY(KeyB, GLFW_KEY_B);
		BIND_KEY(KeyC, GLFW_KEY_C);
		BIND_KEY(KeyD, GLFW_KEY_D);
		BIND_KEY(KeyE, GLFW_KEY_E);
		BIND_KEY(KeyF, GLFW_KEY_F);
		BIND_KEY(KeyG, GLFW_KEY_G);
		BIND_KEY(KeyH, GLFW_KEY_H);
		BIND_KEY(KeyI, GLFW_KEY_I);
		BIND_KEY(KeyJ, GLFW_KEY_J);
		BIND_KEY(KeyK, GLFW_KEY_K);
		BIND_KEY(KeyL, GLFW_KEY_L);
		BIND_KEY(KeyM, GLFW_KEY_M);
		BIND_KEY(KeyN, GLFW_KEY_N);
		BIND_KEY(KeyO, GLFW_KEY_O);
		BIND_KEY(KeyP, GLFW_KEY_P);
		BIND_KEY(KeyQ, GLFW_KEY_Q);
		BIND_KEY(KeyR, GLFW_KEY_R);
		BIND_KEY(KeyS, GLFW_KEY_S);
		BIND_KEY(KeyT, GLFW_KEY_T);
		BIND_KEY(KeyU, GLFW_KEY_U);
		BIND_KEY(KeyV, GLFW_KEY_V);
		BIND_KEY(KeyW, GLFW_KEY_W);
		BIND_KEY(KeyX, GLFW_KEY_X);
		BIND_KEY(KeyY, GLFW_KEY_Y);
		BIND_KEY(KeyZ, GLFW_KEY_Z);

		BIND_KEY(KeyF1, GLFW_KEY_F1);
		BIND_KEY(KeyF2, GLFW_KEY_F2);
		BIND_KEY(KeyF3, GLFW_KEY_F3);
		BIND_KEY(KeyF4, GLFW_KEY_F4);
		BIND_KEY(KeyF5, GLFW_KEY_F5);
		BIND_KEY(KeyF6, GLFW_KEY_F6);
		BIND_KEY(KeyF7, GLFW_KEY_F7);
		BIND_KEY(KeyF8, GLFW_KEY_F8);
		BIND_KEY(KeyF9, GLFW_KEY_F9);
		BIND_KEY(KeyF10, GLFW_KEY_F10);
		BIND_KEY(KeyF11, GLFW_KEY_F11);
		BIND_KEY(KeyF12, GLFW_KEY_F12);

		BIND_KEY(KeyNumLock, GLFW_KEY_NUM_LOCK);

		BIND_KEY(KeyScrollLock, GLFW_KEY_SCROLL_LOCK);

		BIND_KEY(KeyLeftShift, GLFW_KEY_LEFT_SHIFT);
		BIND_KEY(KeyRightShift, GLFW_KEY_RIGHT_SHIFT);
		BIND_KEY(KeyLeftControl, GLFW_KEY_LEFT_CONTROL);
		BIND_KEY(KeyRightControl, GLFW_KEY_RIGHT_CONTROL);
		BIND_KEY(KeyLeftAlt, GLFW_KEY_LEFT_ALT);
		BIND_KEY(KeyRightAlt, GLFW_KEY_RIGHT_ALT);
		BIND_KEY(KeyLeftCommand, GLFW_KEY_LEFT_SUPER);
		BIND_KEY(KeyRightCommand, GLFW_KEY_RIGHT_SUPER);

		BIND_KEY(KeySemicolon, GLFW_KEY_SEMICOLON);
		BIND_KEY(KeyEqual, GLFW_KEY_EQUAL);
		BIND_KEY(KeyComma, GLFW_KEY_COMMA);
		//BIND_KEY(KeyUnderscore, GLFW_KEY_UNDERSCORE);
		BIND_KEY(KeyHyphen, GLFW_KEY_COMMA);
		BIND_KEY(KeyPeriod, GLFW_KEY_PERIOD);
		BIND_KEY(KeySlash, GLFW_KEY_SLASH);
		BIND_KEY(KeyTilde, GLFW_KEY_GRAVE_ACCENT);
		BIND_KEY(KeyLeftBracket, GLFW_KEY_LEFT_BRACKET);
		BIND_KEY(KeyBackslash, GLFW_KEY_BACKSLASH);
		BIND_KEY(KeyRightBracket, GLFW_KEY_RIGHT_BRACKET);
		BIND_KEY(KeyApostrophe, GLFW_KEY_APOSTROPHE);

		//BIND_KEY(KeyAmpersand, GLFW_KEY_AMPERSAND);
		//BIND_KEY(KeyAsterix, GLFW_KEY_APOSTROPHE);
		//BIND_KEY(KeyCaret, GLFW_KEY_APOSTROPHE);
		//BIND_KEY(KeyColon, GLFW_KEY_APOSTROPHE);
		//BIND_KEY(KeyDollar, GLFW_KEY_APOSTROPHE);
		//BIND_KEY(KeyExclamation, GLFW_KEY_APOSTROPHE);
		//BIND_KEY(KeyLeftParantheses, GLFW_KEY_APOSTROPHE);
		//BIND_KEY(KeyRightParantheses, GLFW_KEY_APOSTROPHE);
		//BIND_KEY(KeyQuote, GLFW_KEY_APOSTROPHE);

		BIND_KEY(KeyNumPadZero, GLFW_KEY_KP_0);
		BIND_KEY(KeyNumPadOne, GLFW_KEY_KP_1);
		BIND_KEY(KeyNumPadTwo, GLFW_KEY_KP_2);
		BIND_KEY(KeyNumPadThree, GLFW_KEY_KP_3);
		BIND_KEY(KeyNumPadFour, GLFW_KEY_KP_4);
		BIND_KEY(KeyNumPadFive, GLFW_KEY_KP_5);
		BIND_KEY(KeyNumPadSix, GLFW_KEY_KP_6);
		BIND_KEY(KeyNumPadSeven, GLFW_KEY_KP_7);
		BIND_KEY(KeyNumPadEight, GLFW_KEY_KP_8);
		BIND_KEY(KeyNumPadNine, GLFW_KEY_KP_9);

		BIND_KEY(KeyMultiply, GLFW_KEY_KP_MULTIPLY);
		BIND_KEY(KeyAdd, GLFW_KEY_KP_ADD);
		BIND_KEY(KeySubtract, GLFW_KEY_KP_SUBTRACT);
		BIND_KEY(KeyDecimal, GLFW_KEY_KP_DECIMAL);
		BIND_KEY(KeyDivide, GLFW_KEY_KP_DIVIDE);
	}

	void WindowsWindow::setEventCallbacks()
	{
		glfwSetKeyCallback(windowHandle, InternalEventHandler::_keyCallback);

		glfwSetCharCallback(windowHandle, InternalEventHandler::_textCallback);

		glfwSetCursorPosCallback(windowHandle, InternalEventHandler::_cursorPositionCallback);
		glfwSetMouseButtonCallback(windowHandle, InternalEventHandler::_mouseButtonCallback);
		glfwSetScrollCallback(windowHandle, InternalEventHandler::_mouseScrollCallback);
		glfwSetCursorEnterCallback(windowHandle, InternalEventHandler::_mouseCursorEnterCallback);

		glfwSetDropCallback(windowHandle, InternalEventHandler::_applicationDropPathCallback);

		glfwSetFramebufferSizeCallback(windowHandle, InternalEventHandler::_applicationResizeCallback);

		glfwSetWindowCloseCallback(windowHandle, InternalEventHandler::_windowCloseCallback);
	}

	void WindowsWindow::setWindowIcon(STRING path)
	{

	}

	void WindowsWindow::pollEvents()
	{
		glfwPollEvents();
	}

	void WindowsWindow::clean()
	{
	}

	void WindowsWindow::terminate()
	{
		glfwDestroyWindow(windowHandle);
		glfwTerminate();
	}

	B1 WindowsWindow::isVulkanCompatible()
	{
		return glfwVulkanSupported();
	}

	GLFWwindow* WindowsWindow::getHandle()
	{
		return windowHandle;
	}

	DMKExtent2D WindowsWindow::getCursorPosition()
	{
		DMKExtent2D position;
		glfwGetCursorPos(windowHandle, (D64*)&position.x, (D64*)&position.y);

		return position;
	}

	WindowsWindow WindowsWindow::instance;
	std::mutex WindowsWindow::_mutex;

	WindowsWindow::InternalEventHandler WindowsWindow::eventHandler;

	void WindowsWindow::InternalEventHandler::_keyCallback(GLFWwindow* window, I32 key, I32 scancode, I32 action, I32 mods)
	{
		((WindowsWindow*)glfwGetWindowUserPointer(window))->pEventPool->activateKey(getGLFWEventType(action), scancode);
	}

	void WindowsWindow::InternalEventHandler::_textCallback(GLFWwindow* window, UI32 codepoint)
	{
	}

	void WindowsWindow::InternalEventHandler::_cursorPositionCallback(GLFWwindow* window, D64 xOffset, D64 yOffset)
	{
		((WindowsWindow*)glfwGetWindowUserPointer(window))->pEventPool->MouseX.value = xOffset;
		((WindowsWindow*)glfwGetWindowUserPointer(window))->pEventPool->MouseY.value = yOffset;
	}

	void WindowsWindow::InternalEventHandler::_mouseButtonCallback(GLFWwindow* window, I32 button, I32 action, I32 mods)
	{
		((WindowsWindow*)glfwGetWindowUserPointer(window))->pEventPool->activateButton(getGLFWEventType(action), button);
	}

	void WindowsWindow::InternalEventHandler::_mouseScrollCallback(GLFWwindow* window, D64 xOffset, D64 yOffset)
	{
		if (yOffset > 0.0f)
			((WindowsWindow*)glfwGetWindowUserPointer(window))->pEventPool->MouseScrollUp.activate(yOffset, DMKEventType::DMK_EVENT_TYPE_FREE);
		else
			((WindowsWindow*)glfwGetWindowUserPointer(window))->pEventPool->MouseScrollDown.activate(yOffset, DMKEventType::DMK_EVENT_TYPE_FREE);
	}

	void WindowsWindow::InternalEventHandler::_mouseCursorEnterCallback(GLFWwindow* window, I32 entered)
	{
	}

	void WindowsWindow::InternalEventHandler::_applicationDropPathCallback(GLFWwindow* window, I32 count, const CHR** strings)
	{
	}

	void WindowsWindow::InternalEventHandler::_applicationResizeCallback(GLFWwindow* window, I32 width, I32 height)
	{
		auto windowHandle = (WindowsWindow*)glfwGetWindowUserPointer(window);
		windowHandle->windowWidth = width;
		windowHandle->windowHeight = height;
		windowHandle->pEventPool->frameBufferResized();
	}

	void WindowsWindow::InternalEventHandler::_windowCloseCallback(GLFWwindow* window)
	{
		((WindowsWindow*)glfwGetWindowUserPointer(window))->pEventPool->WindowCloseEvent = true;
	}

	void WindowsWindow::InternalEventHandler::_errorCallback(I32 error, CCPTR description)
	{
		DMKErrorManager::issueErrorBox(DMK_TEXT("GLFW Error: ") + STRING(description));
	}
}