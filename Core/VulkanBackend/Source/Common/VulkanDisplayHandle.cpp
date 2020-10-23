// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/Common/VulkanDisplayHandle.h"
#include "ErrorHandler/Logger.h"

#include <GLFW/glfw3.h>

namespace DMK
{
	namespace GraphicsCore
	{
		namespace VulkanBackend
		{
			/**
			 * Helper object to help with inputs.
			 */
			class VulkanDisplayHandleHelper : public VulkanDisplayHandle {
			public:
				/**
				 * Default constructor.
				 *
				 */
				VulkanDisplayHandleHelper() {}

				/**
				 * Default destructor.
				 *
				 */
				~VulkanDisplayHandleHelper() {}

				/**
				 * Set the extent of the display.
				 * This method is called by the input callbacks.
				 *
				 * @param width: Width of the window.
				 * @param height: Height of the window.
				 */
				void setExtent(UI32 width, UI32 height)
				{
					createInfo.extent.width = width;
					createInfo.extent.height = height;
				}
			};

			/**
			 * Convert GLFW event types to EDK Input types.
			 *
			 * @param action: GLFW action.
			 * <returns> The EDK Input type. </returns>
			 */
			DMK_FORCEINLINE Inputs::InputType GetGLFWEventType(I32 action)
			{
				if (action == GLFW_PRESS)
					return Inputs::InputType::INPUT_TYPE_PRESS;
				if (action == GLFW_RELEASE)
					return Inputs::InputType::INPUT_TYPE_RELEASE;
				if (action == GLFW_REPEAT)
					return Inputs::InputType::INPUT_TYPE_REPEAT;

				return Inputs::InputType::INPUT_TYPE_FREE;
			}

			/**
			 * Key input callback.
			 *
			 * @param window: The GLFW window pointer.
			 * @param key: The key ID.
			 * @param scancode: The key scancode.
			 * @param action: The action of the key.
			 * @param mods: Mods of the key.
			 */
			void KeyCallback(GLFWwindow* window, I32 key, I32 scancode, I32 action, I32 mods)
			{
				Cast<VulkanDisplayHandle*>(glfwGetWindowUserPointer(window))->GetInputCenter()->ActivateKey(GetGLFWEventType(action), scancode);
			}

			/**
			 * Text input callback.
			 *
			 * @param window: The GLFW window pointer.
			 * @param codepoint: Codepoint of the text input.
			 */
			void TextCallback(GLFWwindow* window, UI32 codepoint)
			{
			}

			/**
			 * Cursor position callback.
			 *
			 * @param window: The GLFW window pointer.
			 * @param xOffset: The X Offset.
			 * @param yOffset: The Y Offset.
			 */
			void CursorPositionCallback(GLFWwindow* window, double xOffset, double yOffset)
			{
				Cast<VulkanDisplayHandle*>(glfwGetWindowUserPointer(window))->GetInputCenter()->MouseX.value = Cast<float>(xOffset);
				Cast<VulkanDisplayHandle*>(glfwGetWindowUserPointer(window))->GetInputCenter()->MouseY.value = Cast<float>(yOffset);
			}

			/**
			 * The mouse button callback.
			 *
			 * @param window: The GLFW window pointer.
			 * @param button: The button ID.
			 * @param action: The button action.
			 * @param mods: Mods applied to the button action.
* 			 */
			void MouseButtonCallback(GLFWwindow* window, I32 button, I32 action, I32 mods)
			{
				Cast<VulkanDisplayHandle*>(glfwGetWindowUserPointer(window))->GetInputCenter()->ActivateButton(GetGLFWEventType(action), button);
			}

			/**
			 * Mouse scroll callback.
			 *
			 * @param window: The GLFW window pointer.
			 * @param xOffset: The X Offset.
			 * @param yOffset: The Y Offset.
			 */
			void MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
			{
				if (yOffset > 0.0f)
					Cast<VulkanDisplayHandle*>(glfwGetWindowUserPointer(window))->GetInputCenter()->MouseScrollUp.Activate(Cast<float>(yOffset), Inputs::InputType::INPUT_TYPE_FREE);
				else
					Cast<VulkanDisplayHandle*>(glfwGetWindowUserPointer(window))->GetInputCenter()->MouseScrollDown.Activate(Cast<float>(yOffset), Inputs::InputType::INPUT_TYPE_FREE);
			}

			/**
			 * The mouse curson enter callback.
			 * This function is called when the cursor enters the window.
			 *
			 * @param window: The GLFW window pointer.
			 * @param entered: Boolean stating if true or false.
			 */
			void MouseCursorEnterCallback(GLFWwindow* window, I32 entered)
			{
			}

			/**
			 * Application drop path.
			 * This method is called when a file is droppen on top of the window.
			 *
			 * @param window: The GLFW window pointer.
			 * @param count: The number of files dropped.
			 * @param strings: The array of paths.
			 */
			void ApplicationDropPathCallback(GLFWwindow* window, I32 count, const CHR** strings)
			{
			}

			/**
			 * Applciation resize callback.
			 *
			 * @param window: The GLFW window pointer.
			 * @param width: With of the resize.
			 * @param height: Height of the resize.
			 */
			void ApplicationResizeCallback(GLFWwindow* window, I32 width, I32 height)
			{
				auto pWindowHandle = Cast<VulkanDisplayHandle*>(glfwGetWindowUserPointer(window));
				Cast<VulkanDisplayHandleHelper*>(pWindowHandle)->setExtent(width, height);
				Cast<VulkanDisplayHandle*>(pWindowHandle)->GetInputCenter()->FrameBufferResized();
			}

			/**
			 * Window close input callback.
			 *
			 * @param window: The GLFW window pointer.
			 */
			void WindowCloseCallback(GLFWwindow* window)
			{
				Cast<VulkanDisplayHandle*>(glfwGetWindowUserPointer(window))->GetInputCenter()->WindowCloseEvent = true;
			}

			/**
			 * GLFW error callback.
			 * This method is called if an error was encountered by GLFW.
			 *
			 * @param error: The error ID.
			 * @param description: The error description.
			 */
			void ErrorCallback(I32 error, CCPTR description)
			{
				ErrorHandler::Logger::LogError(TEXT("GLFW Error: ") + std::string(description));
			}

			///////////////////////////////////////////////////////////////////////////////////////////////////
			////	Class Definitions
			///////////////////////////////////////////////////////////////////////////////////////////////////
			void VulkanDisplayHandle::Initialize(const DisplayCreateInfo& createInfo)
			{
				glfwSetErrorCallback(ErrorCallback);
				glfwInit();

				glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
				glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);

#if defined(DMK_DEBUG) || defined(DMK_RELEASE)
				pWindowHandle = glfwCreateWindow(createInfo.extent.width, createInfo.extent.height, createInfo.title.c_str(), nullptr, nullptr);

#else
				GLFWmonitor* monitor = glfwGetPrimaryMonitor();
				const GLFWvidmode* mode = glfwGetVideoMode(monitor);

				glfwWindowHint(GLFW_RED_BITS, mode->redBits);
				glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
				glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
				glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

				pWindowHandle = glfwCreateWindow(mode->width, mode->height, createInfo.title.c_str(), monitor, NULL);
				createInfo.extent.width = mode->width;
				createInfo.extent.height = mode->height;

				glfwSetInputMode(pWindowHandle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

#endif

				glfwSetWindowUserPointer(Cast<GLFWwindow*>(pWindowHandle), this);
			}

			void VulkanDisplayHandle::SetIcon(const STRING& file)
			{
			}

			void VulkanDisplayHandle::Terminate()
			{
				glfwDestroyWindow(Cast<GLFWwindow*>(pWindowHandle));
				glfwTerminate();
			}

			void VulkanDisplayHandle::SetupInputCenter()
			{
				// Initialize the input center. 
				inputCenter.Initialize();

				// Bind keys.
#define BIND_KEY(component, KEY)  inputCenter.BindKey(#component, glfwGetKeyScancode(KEY))

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

				// Setup callbacks.
				{
					glfwSetKeyCallback(Cast<GLFWwindow*>(pWindowHandle), KeyCallback);

					glfwSetCharCallback(Cast<GLFWwindow*>(pWindowHandle), TextCallback);

					glfwSetCursorPosCallback(Cast<GLFWwindow*>(pWindowHandle), CursorPositionCallback);
					glfwSetMouseButtonCallback(Cast<GLFWwindow*>(pWindowHandle), MouseButtonCallback);
					glfwSetScrollCallback(Cast<GLFWwindow*>(pWindowHandle), MouseScrollCallback);
					glfwSetCursorEnterCallback(Cast<GLFWwindow*>(pWindowHandle), MouseCursorEnterCallback);

					glfwSetDropCallback(Cast<GLFWwindow*>(pWindowHandle), ApplicationDropPathCallback);

					glfwSetFramebufferSizeCallback(Cast<GLFWwindow*>(pWindowHandle), ApplicationResizeCallback);

					glfwSetWindowCloseCallback(Cast<GLFWwindow*>(pWindowHandle), WindowCloseCallback);
				}
			}

			void VulkanDisplayHandle::PollInputs()
			{
				glfwPollEvents();
			}

			void VulkanDisplayHandle::Resize(const DisplayExtent& extent)
			{
				glfwSetWindowSize(Cast<GLFWwindow*>(pWindowHandle), extent.width, extent.height);

				createInfo.extent = extent;
			}

			VkSurfaceKHR VulkanDisplayHandle::CreateSurface(VkInstance vInstance)
			{
				if (vSurface == VK_NULL_HANDLE)
					glfwCreateWindowSurface(vInstance, Cast<GLFWwindow*>(pWindowHandle), nullptr, &vSurface);

				return vSurface;
			}

			VkSurfaceKHR VulkanDisplayHandle::GetSurface() const
			{
				return vSurface;
			}

			void VulkanDisplayHandle::DestroySurface(VkInstance vInstance)
			{
				vkDestroySurfaceKHR(vInstance, GetSurface(), nullptr);
			}

			bool VulkanDisplayHandle::IsDeviceCompatible(VkPhysicalDevice vPhysicalDevice)
			{
				VulkanQueue _queue;
				_queue.findQueueFamilies(physicalDevice, surface);

				bool extensionsSupported = checkDeviceExtensionSupport(physicalDevice);
				bool swapChainAdequate = false;
				if (extensionsSupported)
				{
					VulkanSwapChainSupportDetails swapChainSupport = VulkanSwapChain::querySwapChainSupport(physicalDevice, surface);
					swapChainAdequate = (!swapChainSupport.formats.empty()) && (!swapChainSupport.presentModes.empty());
				}

				VkPhysicalDeviceFeatures supportedFeatures;
				vkGetPhysicalDeviceFeatures(physicalDevice, &supportedFeatures);

				return _queue.isComplete()
					&& extensionsSupported
					&& swapChainAdequate
					&& supportedFeatures.samplerAnisotropy;
			}
		}
	}
}