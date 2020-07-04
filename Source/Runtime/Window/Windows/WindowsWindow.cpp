// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "WindowsWindow.h"

namespace Dynamik
{
	/* Local Mutex */
	std::mutex _myMutex;

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
#define BIND_KEY(component, KEY)  pEventBoard->bindKey(pEventBoard->component.name, glfwGetKeyScancode(KEY))

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

	B1 WindowsWindow::isWindowCloseEvent()
	{
		return shouldWindowClose;
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
		instance.pEventBoard->activateKey((DMKEventType)(action + 1), scancode);
	}

	void WindowsWindow::InternalEventHandler::_textCallback(GLFWwindow* window, UI32 codepoint)
	{
	}

	void WindowsWindow::InternalEventHandler::_cursorPositionCallback(GLFWwindow* window, D64 xOffset, D64 yOffset)
	{
	}

	void WindowsWindow::InternalEventHandler::_mouseButtonCallback(GLFWwindow* window, I32 button, I32 action, I32 mods)
	{
		instance.pEventBoard->activateButton((DMKEventType)(action + 1), button);
	}

	void WindowsWindow::InternalEventHandler::_mouseScrollCallback(GLFWwindow* window, D64 xOffset, D64 yOffset)
	{
	}

	void WindowsWindow::InternalEventHandler::_mouseCursorEnterCallback(GLFWwindow* window, I32 entered)
	{
	}

	void WindowsWindow::InternalEventHandler::_applicationDropPathCallback(GLFWwindow* window, I32 count, const CHR** strings)
	{
	}

	void WindowsWindow::InternalEventHandler::_applicationResizeCallback(GLFWwindow* window, I32 width, I32 height)
	{
	}

	void WindowsWindow::InternalEventHandler::_windowCloseCallback(GLFWwindow* window)
	{
		instance.shouldWindowClose = true;
	}
	
	void WindowsWindow::InternalEventHandler::_errorCallback(I32 error, CCPTR description)
	{
		DMKErrorManager::issueErrorBox(DMK_TEXT("GLFW Error: ") + STRING(description));
	}
}