// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/VulkanDisplay.h"
#include "VulkanBackend/Macros.h"
#include "VulkanBackend/VulkanInstance.h"
#include "VulkanBackend/VulkanDevice.h"

namespace DMK
{
	namespace VulkanBackend
	{
		namespace _Callbacks
		{
			Inputs::ButtonInputState getGLFWEventState(I32 action)
			{
				if (action == GLFW_PRESS)
					return Inputs::ButtonInputState::PRESSED;
				if (action == GLFW_RELEASE)
					return Inputs::ButtonInputState::RELEASED;
				if (action == GLFW_REPEAT)
					return Inputs::ButtonInputState::ON_REPEAT;

				return Inputs::ButtonInputState::RELEASED;
			}

			void KeyCallback(GLFWwindow* window, I32 key, I32 scancode, I32 action, I32 mods)
			{
				static_cast<VulkanDisplay*>(glfwGetWindowUserPointer(window))->GetInputCenter()->ActivateKey(scancode, getGLFWEventState(action));
			}

			void TextCallback(GLFWwindow* window, UI32 codepoint)
			{
			}

			void CursorPositionCallback(GLFWwindow* window, double xOffset, double yOffset)
			{
				VulkanDisplay* pWindow = static_cast<VulkanDisplay*>(glfwGetWindowUserPointer(window));
				pWindow->GetInputCenter()->MousePositionX = static_cast<float>(xOffset);
				pWindow->GetInputCenter()->MousePositionY = static_cast<float>(yOffset);
			}

			void MouseButtonCallback(GLFWwindow* window, I32 button, I32 action, I32 mods)
			{
				static_cast<VulkanDisplay*>(glfwGetWindowUserPointer(window))->GetInputCenter()->ActivateButton(button, getGLFWEventState(action));
			}

			void MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
			{
				if (yOffset > 0.0f)
					static_cast<VulkanDisplay*>(glfwGetWindowUserPointer(window))->GetInputCenter()->MouseScrollUp = static_cast<float>(yOffset);
				else
					static_cast<VulkanDisplay*>(glfwGetWindowUserPointer(window))->GetInputCenter()->MouseScrollDown = static_cast<float>(yOffset);
			}

			void MouseCursorEnterCallback(GLFWwindow* window, I32 entered)
			{
			}

			void ApplicationDropPathCallback(GLFWwindow* window, I32 count, const char** strings)
			{
			}

			void ApplicationResizeCallback(GLFWwindow* window, I32 width, I32 height)
			{
				VulkanDisplay* pWindow = static_cast<VulkanDisplay*>(glfwGetWindowUserPointer(window));
				pWindow->GetInputCenter()->IsWindowResized = true;
				//pWindow->UpdateWindowExtent(width, height);
			}

			void WindowCloseCallback(GLFWwindow* window)
			{
				static_cast<VulkanDisplay*>(glfwGetWindowUserPointer(window))->GetInputCenter()->IsWindowOpen = false;
			}
		}

		void VulkanDisplay::Initialize(GraphicsCore::Instance* pInstance, UI32 width, UI32 height, const char* pTitle)
		{
			this->pInstance = pInstance;

			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			pWindowHandle = glfwCreateWindow(width, height, pTitle, nullptr, nullptr);

			glfwSetWindowUserPointer(pWindowHandle, this);

			CreateSurface();
			SetupInputs();
			SetupCallbacks();
		}

		void VulkanDisplay::Terminate()
		{
			DestroySurface();
			glfwDestroyWindow(pWindowHandle);
		}

		GraphicsCore::Device* VulkanDisplay::CreateDevice()
		{
			VulkanDevice* pDevice = new VulkanDevice();
			pDevice->Initialize(this);

			return pDevice;
		}

		void VulkanDisplay::DestroyDevice(GraphicsCore::Device* pDevice)
		{
			pDevice->Terminate();
			delete pDevice;
		}

		void VulkanDisplay::SetupInputs()
		{
#define BIND_KEY(component, KEY)  GetInputCenter()->component.Register(glfwGetKeyScancode(KEY))

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

			GetInputCenter()->MouseButtonLeft.Register(GLFW_MOUSE_BUTTON_LEFT);
			GetInputCenter()->MouseButtonRight.Register(GLFW_MOUSE_BUTTON_RIGHT);
			GetInputCenter()->MouseButtonMiddle.Register(GLFW_MOUSE_BUTTON_MIDDLE);
			GetInputCenter()->MouseButton0.Register(GLFW_MOUSE_BUTTON_4);
			GetInputCenter()->MouseButton1.Register(GLFW_MOUSE_BUTTON_5);
		}

		void VulkanDisplay::SetupCallbacks()
		{
			glfwSetKeyCallback(pWindowHandle, _Callbacks::KeyCallback);

			glfwSetCharCallback(pWindowHandle, _Callbacks::TextCallback);

			glfwSetCursorPosCallback(pWindowHandle, _Callbacks::CursorPositionCallback);
			glfwSetMouseButtonCallback(pWindowHandle, _Callbacks::MouseButtonCallback);
			glfwSetScrollCallback(pWindowHandle, _Callbacks::MouseScrollCallback);
			glfwSetCursorEnterCallback(pWindowHandle, _Callbacks::MouseCursorEnterCallback);

			glfwSetDropCallback(pWindowHandle, _Callbacks::ApplicationDropPathCallback);

			glfwSetFramebufferSizeCallback(pWindowHandle, _Callbacks::ApplicationResizeCallback);

			glfwSetWindowCloseCallback(pWindowHandle, _Callbacks::WindowCloseCallback);
		}

		void VulkanDisplay::CreateSurface()
		{
			DMK_VK_ASSERT(glfwCreateWindowSurface(pInstance->Derive<VulkanInstance>()->GetInstance(), pWindowHandle, nullptr, &vSurface), "Failed to create the Vulkan Surface!");
		}

		void VulkanDisplay::DestroySurface()
		{
			vkDestroySurfaceKHR(pInstance->Derive<VulkanInstance>()->GetInstance(), vSurface, nullptr);
		}
	}
}