#pragma once
#ifndef _DYNAMIK_WINDOWS_WINDOW_H
#define _DYNAMIK_WINDOWS_WINDOW_H

/*
 Author:    Dhiraj Wishal
 Date:      19/05/2020
*/
#include "../WindowHandle.h"
#include <GLFW/glfw3.h>
#include <mutex>

namespace Dynamik
{
	class DMK_API WindowsWindow : public DMKWindowHandle {
	public:
		WindowsWindow() {}
		WindowsWindow(const STRING& title, const I32& width, const I32 height)
			: DMKWindowHandle(title, width, height) {}
		~WindowsWindow() {}

		POINTER<GLFWwindow> getWindowHandle() { return windowHandle; }

		void initialize() override;
		void setEventCallbacks() override;
		void setWindowIcon(STRING path) override;
		void pollEvents() override;
		void clean() override;
		void terminate() override;

		B1 isVulkanCompatible();

		void addKeyEventListner(const POINTER<DMKKeyEventListener>& listener) override;
		void addMouseButtonEventListener(const POINTER<DMKMouseButtonEventListener>& listener) override;
		void addMouseScrollEventListener(const POINTER<DMKMouseScrollEventListener>& listener) override;
		void removeKeyEventListener(I32 listenerIndex) override;
		void removeMouseButtonEventListener(I32 listenerIndex) override;
		void removeMouseScrollEventListener(I32 listenerIndex) override;

		ARRAY<DMKKeyEventComponent> getKeyEvents() override;
		ARRAY<DMKMouseButtonEventComponent> getMouseButtonEvents() override;
		ARRAY<DMKMouseScrollEventComponent> getMouseScrollEvents() override;

	private:
		POINTER<GLFWwindow> windowHandle;

		class InternalEventHandler : public DMKEventHandler {
		public:
			InternalEventHandler() {}
			~InternalEventHandler() {}

			static void _keyCallback(GLFWwindow* window, I32 key, I32 scancode, I32 action, I32 mods);
			static void _textCallback(GLFWwindow* window, UI32 codepoint);
			static void _cursorPositionCallback(GLFWwindow* window, D64 xOffset, D64 yOffset);
			static void _mouseButtonCallback(GLFWwindow* window, I32 button, I32 action, I32 mods);
			static void _mouseScrollCallback(GLFWwindow* window, D64 xOffset, D64 yOffset);
			static void _mouseCursorEnterCallback(GLFWwindow* window, I32 entered);
			static void _applicationDropPathCallback(GLFWwindow* window, I32 count, const CHR** strings);
			static void _applicationResizeCallback(GLFWwindow* window, I32 width, I32 height);

			static void _windowCloseCallback(GLFWwindow* window);
		};

		static InternalEventHandler eventHandler;

		static WindowsWindow instance;
		static std::mutex _mutex;

		DMKKeyEventListener _defaultKeyEventListener;
		DMKMouseButtonEventListener _defaultMouseButtonEventListener;
		DMKMouseScrollEventListener _defaultMouseScrollEventListener;
	};
}

#endif // !_DYNAMIK_WINDOWS_WINDOW_H
