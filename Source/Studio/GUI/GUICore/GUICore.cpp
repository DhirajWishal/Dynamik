// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "GUICore.h"

#include <GLEW/glew-2.1.0/include/GL/glew.h>
#include "GLFW/glfw3.h"

namespace Dynamik
{
	static GLFWwindow* myWindow;

	GUICore::GUICore() : windowWidth(1280), windowHeight(720), windowTitle(DMK_TEXT("Dynamik Studio v1"))
	{
	}

	GUICore::GUICore(I32 width, I32 height, STRING title) : windowWidth(width), windowHeight(height), windowTitle(title)
	{
	}

	GUICore::~GUICore()
	{
		glfwDestroyWindow(myWindow);
	}

	void GUICore::initialize()
	{
		glfwSetErrorCallback(_errorCallback);
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if defined(DMK_DEBUG)
		myWindow = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), nullptr, nullptr);

#else
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

		myWindow = glfwCreateWindow(mode->width, mode->height, windowTitle.c_str(), monitor, NULL);
		windowWidth = mode->width;
		windowHeight = mode->height;

		glfwSetInputMode(myWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

#endif

		if (!myWindow)
		{
			DMK_FATAL("Failed to create window!");
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(myWindow);

		if (glewInit() != GLEW_OK)
			DMK_FATAL("Failed to initialize GLEW");

		glfwWindowHint(GLFW_SAMPLES, 4);
		glEnable(GL_MULTISAMPLE);
	}

	void GUICore::initializeFrame()
	{
		glClearColor(2.0f / 255.0f, 8.0f / 255.0f, 32.0f / 255.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void GUICore::updateRenderables()
	{
	}

	void GUICore::submitRenderables()
	{
		glfwSwapBuffers(myWindow);
		glfwPollEvents();
	}

	void GUICore::_errorCallback(I32 ID, CCPTR description)
	{
		DMK_ERROR("STUDIO GUI: " + STRING(description));
	}
}