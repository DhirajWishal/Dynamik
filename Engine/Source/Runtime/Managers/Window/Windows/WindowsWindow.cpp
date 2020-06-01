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

	void WindowsWindow::setEventCallbacks()
	{
		eventHandler.addKeyEventListener(&_defaultKeyEventListener);
		eventHandler.addMouseButtonEventListener(&_defaultMouseButtonEventListener);
		eventHandler.addMouseScrollEventListener(&_defaultMouseScrollEventListener);

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
		eventHandler.cleanComponents();
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

	void WindowsWindow::addKeyEventListner(const POINTER<DMKKeyEventListener>& listener)
	{
		eventHandler.addKeyEventListener(listener);
	}

	void WindowsWindow::addMouseButtonEventListener(const POINTER<DMKMouseButtonEventListener>& listener)
	{
		eventHandler.addMouseButtonEventListener(listener);
	}

	void WindowsWindow::addMouseScrollEventListener(const POINTER<DMKMouseScrollEventListener>& listener)
	{
		eventHandler.addMouseScrollEventListener(listener);
	}

	void WindowsWindow::removeKeyEventListener(I32 listenerIndex)
	{
		eventHandler.removeKeyEventListener(listenerIndex);
	}

	void WindowsWindow::removeMouseButtonEventListener(I32 listenerIndex)
	{
		eventHandler.removeMouseButtonEventListener(listenerIndex);
	}

	void WindowsWindow::removeMouseScrollEventListener(I32 listenerIndex)
	{
		eventHandler.removeMouseScrollEventListener(listenerIndex);
	}

	ARRAY<DMKKeyEventComponent> WindowsWindow::getKeyEvents()
	{
		return eventHandler.getKeyEvents();
	}

	ARRAY<DMKMouseButtonEventComponent> WindowsWindow::getMouseButtonEvents()
	{
		return eventHandler.getMouseButtonEvents();
	}

	ARRAY<DMKMouseScrollEventComponent> WindowsWindow::getMouseScrollEvents()
	{
		return eventHandler.getMouseScrollEvents();
	}

	POINTER<GLFWwindow> WindowsWindow::getHandle()
	{
		return windowHandle;
	}

	WindowsWindow WindowsWindow::instance;
	std::mutex WindowsWindow::_mutex;

	WindowsWindow::InternalEventHandler WindowsWindow::eventHandler;

	void WindowsWindow::InternalEventHandler::_keyCallback(GLFWwindow* window, I32 key, I32 scancode, I32 action, I32 mods)
	{
		for (auto _listener : myKeyEventListeners)
			_listener->onEvent(key, action, mods, scancode);

		DMKKeyEventComponent _component;
		_component.keyCode = key;
		_component.action = action;
		_component.mods = mods;
		_component.scanCode = scancode;

		eventHandler.addKeyEventComponent(_component);
	}

	void WindowsWindow::InternalEventHandler::_textCallback(GLFWwindow* window, UI32 codepoint)
	{
	}

	void WindowsWindow::InternalEventHandler::_cursorPositionCallback(GLFWwindow* window, D64 xOffset, D64 yOffset)
	{
	}

	void WindowsWindow::InternalEventHandler::_mouseButtonCallback(GLFWwindow* window, I32 button, I32 action, I32 mods)
	{
		for (auto _listener : myMouseButtonEventListeners)
			_listener->onEvent(button, action, mods);

		DMKMouseButtonEventComponent _component;
		_component.button = button;
		_component.action = action;
		_component.mods = mods;

		eventHandler.addMouseButtonEventComponent(_component);
	}

	void WindowsWindow::InternalEventHandler::_mouseScrollCallback(GLFWwindow* window, D64 xOffset, D64 yOffset)
	{
		for (auto _listener : myMouseScrollEventListeners)
			_listener->onEvent(xOffset, yOffset);

		DMKMouseScrollEventComponent _component;
		_component.xOffset = xOffset;
		_component.yOffset = yOffset;

		eventHandler.addMouseScrollEventComponent(_component);
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
	}
	
	void WindowsWindow::InternalEventHandler::_errorCallback(I32 error, CCPTR description)
	{
		DMKErrorManager::issueErrorBox(DMK_TEXT("GLFW Error: ") + STRING(description));
	}
}