// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _ENGINE_DEV_KIT_INPUT_CENTER_H
#define _ENGINE_DEV_KIT_INPUT_CENTER_H

#include "InputComponent.h"
#include "Core/Math/Vector/Vector2F.h"

namespace DMK
{
	namespace Inputs
	{
		/**
		 * This object contains all the events that occurred in one iteration.
		 */
		class DMK_API InputCenter {
		public:
			/**
			 * Default constructor.
			 */
			InputCenter() {}

			/**
			 * Default destructor.
			 */
			~InputCenter() {}

			/**
			 * Initialize the input center.
			 */
			void Initialize();

			/**
			 * Bind a key to the input center.
			 *
			 * @param keyName: The name of the key.
			 * @param scanCode: The scan code of the key.
			 */
			void BindKey(const STRING& keyName, UI32 scanCode);

			/**
			 * Get an input component using the input name.
			 *
			 * @param eventName: The name of the input.
			 */
			InputComponent* GetComponent(const STRING& inputName);

			/**
			 * Activate a key component.
			 *
			 * @param type: Type of the activation.
			 * @param scanCode: Scan code of the key to be activated.
			 */
			void ActivateKey(InputType type, UI32 scanCode);

			/**
			 * Activate a button component.
			 *
			 * @param type: Type of the activation.
			 * @param ID: The button ID of the button to be activated.
			 */
			void ActivateButton(InputType type, UI32 ID);

			/**
			 * This method sets FrameBufferResizeEvent = true.
			 */
			void FrameBufferResized();

			/**
			 * Reset all the input components to its normal state/ activation.
			 */
			void ReasetAll();

			/**
			 * Get the current mouse position.
			 */
			Vector2F GetMousePosition();

			/* Mouse Events */
		public:
			InputComponent MouseX = {};
			InputComponent MouseY = {};
			InputComponent MouseScrollUp = {};
			InputComponent MouseScrollDown = {};
			InputComponent MouseWheel = {};

			ButtonInputComponent MouseButtonLeft = {};
			ButtonInputComponent MouseButtonRight = {};
			ButtonInputComponent MouseButtonMiddle = {};
			ButtonInputComponent MouseButton0 = {};
			ButtonInputComponent MouseButton1 = {};

			/* Keyboard Events */
		public:
			KeyInputComponent KeyLeft = {};
			KeyInputComponent KeyRight = {};
			KeyInputComponent KeyUp = {};
			KeyInputComponent KeyDown = {};

			KeyInputComponent KeyBackSpace = {};
			KeyInputComponent KeyTab = {};
			KeyInputComponent KeyEnter = {};
			KeyInputComponent KeyPause = {};

			KeyInputComponent KeyCapsLock = {};
			KeyInputComponent KeyEscape = {};
			KeyInputComponent KeySpaceBar = {};
			KeyInputComponent KeyPageUp = {};
			KeyInputComponent KeyPageDown = {};
			KeyInputComponent KeyEnd = {};
			KeyInputComponent KeyHome = {};

			KeyInputComponent KeyZero = {};
			KeyInputComponent KeyOne = {};
			KeyInputComponent KeyTwo = {};
			KeyInputComponent KeyThree = {};
			KeyInputComponent KeyFour = {};
			KeyInputComponent KeyFive = {};
			KeyInputComponent KeySix = {};
			KeyInputComponent KeySeven = {};
			KeyInputComponent KeyEight = {};
			KeyInputComponent KeyNine = {};

			KeyInputComponent KeyA = {};
			KeyInputComponent KeyB = {};
			KeyInputComponent KeyC = {};
			KeyInputComponent KeyD = {};
			KeyInputComponent KeyE = {};
			KeyInputComponent KeyF = {};
			KeyInputComponent KeyG = {};
			KeyInputComponent KeyH = {};
			KeyInputComponent KeyI = {};
			KeyInputComponent KeyJ = {};
			KeyInputComponent KeyK = {};
			KeyInputComponent KeyL = {};
			KeyInputComponent KeyM = {};
			KeyInputComponent KeyN = {};
			KeyInputComponent KeyO = {};
			KeyInputComponent KeyP = {};
			KeyInputComponent KeyQ = {};
			KeyInputComponent KeyR = {};
			KeyInputComponent KeyS = {};
			KeyInputComponent KeyT = {};
			KeyInputComponent KeyU = {};
			KeyInputComponent KeyV = {};
			KeyInputComponent KeyW = {};
			KeyInputComponent KeyX = {};
			KeyInputComponent KeyY = {};
			KeyInputComponent KeyZ = {};

			KeyInputComponent KeyF1 = {};
			KeyInputComponent KeyF2 = {};
			KeyInputComponent KeyF3 = {};
			KeyInputComponent KeyF4 = {};
			KeyInputComponent KeyF5 = {};
			KeyInputComponent KeyF6 = {};
			KeyInputComponent KeyF7 = {};
			KeyInputComponent KeyF8 = {};
			KeyInputComponent KeyF9 = {};
			KeyInputComponent KeyF10 = {};
			KeyInputComponent KeyF11 = {};
			KeyInputComponent KeyF12 = {};

			KeyInputComponent KeyNumLock = {};

			KeyInputComponent KeyScrollLock = {};

			KeyInputComponent KeyLeftShift = {};
			KeyInputComponent KeyRightShift = {};
			KeyInputComponent KeyLeftControl = {};
			KeyInputComponent KeyRightControl = {};
			KeyInputComponent KeyLeftAlt = {};
			KeyInputComponent KeyRightAlt = {};
			KeyInputComponent KeyLeftCommand = {};
			KeyInputComponent KeyRightCommand = {};

			KeyInputComponent KeySemicolon = {};
			KeyInputComponent KeyEqual = {};
			KeyInputComponent KeyComma = {};
			KeyInputComponent KeyUnderscore = {};
			KeyInputComponent KeyHyphen = {};
			KeyInputComponent KeyPeriod = {};
			KeyInputComponent KeySlash = {};
			KeyInputComponent KeyTilde = {};
			KeyInputComponent KeyLeftBracket = {};
			KeyInputComponent KeyBackslash = {};
			KeyInputComponent KeyRightBracket = {};
			KeyInputComponent KeyApostrophe = {};

			KeyInputComponent KeyAmpersand = {};
			KeyInputComponent KeyAsterix = {};
			KeyInputComponent KeyCaret = {};
			KeyInputComponent KeyColon = {};
			KeyInputComponent KeyDollar = {};
			KeyInputComponent KeyExclamation = {};
			KeyInputComponent KeyLeftParantheses = {};
			KeyInputComponent KeyRightParantheses = {};
			KeyInputComponent KeyQuote = {};

			KeyInputComponent KeyNumPadZero = {};
			KeyInputComponent KeyNumPadOne = {};
			KeyInputComponent KeyNumPadTwo = {};
			KeyInputComponent KeyNumPadThree = {};
			KeyInputComponent KeyNumPadFour = {};
			KeyInputComponent KeyNumPadFive = {};
			KeyInputComponent KeyNumPadSix = {};
			KeyInputComponent KeyNumPadSeven = {};
			KeyInputComponent KeyNumPadEight = {};
			KeyInputComponent KeyNumPadNine = {};

			KeyInputComponent KeyMultiply = {};
			KeyInputComponent KeyAdd = {};
			KeyInputComponent KeySubtract = {};
			KeyInputComponent KeyDecimal = {};
			KeyInputComponent KeyDivide = {};

			/* Application Events */
		public:
			bool WindowCloseEvent = false;
			bool FrameBufferResizeEvent = false;

		private:
			std::unordered_map<STRING, InputComponent*> componentMap;
			std::unordered_map<UI32, KeyInputComponent*> keyMappings;
		};
	}
}

#endif // !_ENGINE_DEV_KIT_INPUT_CENTER_H
