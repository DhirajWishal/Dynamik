// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_WINDOWS_WINDOW_H
#define _DYNAMIK_WINDOWS_WINDOW_H

#include "../WindowHandle.h"
#include <GLFW/glfw3.h>
#include <mutex>

namespace Dynamik
{
	/*
	 Windows Window handle for the Dynamik Engine
	*/
	class DMK_API WindowsWindow : public DMKWindowHandle {
	public:
		WindowsWindow() {}
		WindowsWindow(const STRING& title, const I32& width, const I32 height)
			: DMKWindowHandle(title, width, height) {}
		~WindowsWindow() {}

		GLFWwindow* getWindowHandle() { return windowHandle; }

		DMKViewport createViewport(I32 width, I32 height, I32 xOffset, I32 yOffset);

		void initialize() override;
		void initializeKeyBindings() override;
		void setEventCallbacks() override;
		void setWindowIcon(STRING path) override;
		void pollEvents() override;
		void clean() override;
		void terminate() override;

		B1 isVulkanCompatible();

		GLFWwindow* getHandle();

		DMKExtent2D getCursorPosition() override;

	private:
		GLFWwindow* windowHandle = nullptr;

		class InternalEventHandler {
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

			static void _errorCallback(I32 error, CCPTR description);
		};

		static InternalEventHandler eventHandler;

		static WindowsWindow instance;
		static std::mutex _mutex;
	};
}

#endif // !_DYNAMIK_WINDOWS_WINDOW_H
