// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_INPUTS_KEY_INPUTS_SUPPLIER_H
#define _DYNAMIK_INPUTS_KEY_INPUTS_SUPPLIER_H

#include "InputSupplier.h"

namespace DMK
{
	namespace Inputs
	{
		/**
		 * Key Input Type enum.
		 * Keys contain 3 types of inputs,
		 * - Press (When the user presses a key in the keyboard)
		 * - Release (When the user takes his/ her finger off of the keyboard)
		 * - Repeat (When the user presses and holds on to the key)
		 */
		enum class KeyInputType : UI32 {
			KEY_INPUT_Type_PRESS,
			KEY_INPUT_Type_RELEASE,
			KEY_INPUT_Type_REPEAT,
		};

		/**
		 * Key structure for the Dynamik Engine.
		 * This holds information about a single key.
		 */
		struct Key {
			/**
			 * Default constructor.
			 */
			Key() = default;

			/**
			 * Construct the key using its name.
			 */
			Key(const Char* pName) : pName(pName) {}

			/**
			 * Set the scan code of the key.
			 * Scan code is a unique number given to represent a perticular key.
			 *
			 * @param sCode: The scan code.
			 */
			void SetScanCode(UI32 sCode) { scanCode = sCode; }

			/**
			 * Get the scan code of the key.
			 *
			 * @return: Unsigned 32 bit integer.
			 */
			UI32 GetScanCode() const { return scanCode; }

			/**
			 * Activate the key using its input type.
			 *
			 * @param eInputType: The type of the input (its activation).
			 */
			void Activate(KeyInputType eInputType) { this->eInputType = eInputType; }

			/**
			 * Check if the key is pressed.
			 *
			 * @return: Boolean value.
			 */
			bool IsPressed() const { return eInputType == KeyInputType::KEY_INPUT_Type_PRESS; }

			/**
			 * Check if the key is released.
			 *
			 * @return: Boolean value.
			 */
			bool IsRelease() const { return eInputType == KeyInputType::KEY_INPUT_Type_RELEASE; }

			/**
			 * Check if the key is on repeat.
			 *
			 * @return: Boolean value.
			 */
			bool IsOnRepeat() const { return eInputType == KeyInputType::KEY_INPUT_Type_REPEAT; }

		public:
			const Char* pName = TEXT("");	// Name of the key. 
			KeyInputType eInputType = KeyInputType::KEY_INPUT_Type_RELEASE;	// Input type/ activation.
			UI32 scanCode = 0;	// The scancode of the key.
		};

		/**
		 * Key Input Supplier for the Dynamik Engine. 
		 * This is the default supplier which supplies key inputs to the engine.
		 *
		 * @required: All the keys are required to be given the scan code which is platform specific.
		 */
		class KeyInputSupplier : public InputSupplier {
		public:
			/**
			 * Default constructor.
			 */
			KeyInputSupplier() : InputSupplier(TEXT("KeyInputSupplier")) {}

			/**
			 * Default destructor.
			 */
			virtual ~KeyInputSupplier() {}

			/* All the supported keys. */
		public:
			Key KeyLeft = {};
			Key KeyRight = {};
			Key KeyUp = {};
			Key KeyDown = {};

			Key KeyBackSpace = {};
			Key KeyTab = {};
			Key KeyEnter = {};
			Key KeyPause = {};

			Key KeyCapsLock = {};
			Key KeyEscape = {};
			Key KeySpaceBar = {};
			Key KeyPageUp = {};
			Key KeyPageDown = {};
			Key KeyEnd = {};
			Key KeyHome = {};

			Key KeyZero = {};
			Key KeyOne = {};
			Key KeyTwo = {};
			Key KeyThree = {};
			Key KeyFour = {};
			Key KeyFive = {};
			Key KeySix = {};
			Key KeySeven = {};
			Key KeyEight = {};
			Key KeyNine = {};

			Key KeyA = {};
			Key KeyB = {};
			Key KeyC = {};
			Key KeyD = {};
			Key KeyE = {};
			Key KeyF = {};
			Key KeyG = {};
			Key KeyH = {};
			Key KeyI = {};
			Key KeyJ = {};
			Key KeyK = {};
			Key KeyL = {};
			Key KeyM = {};
			Key KeyN = {};
			Key KeyO = {};
			Key KeyP = {};
			Key KeyQ = {};
			Key KeyR = {};
			Key KeyS = {};
			Key KeyT = {};
			Key KeyU = {};
			Key KeyV = {};
			Key KeyW = {};
			Key KeyX = {};
			Key KeyY = {};
			Key KeyZ = {};

			Key KeyF1 = {};
			Key KeyF2 = {};
			Key KeyF3 = {};
			Key KeyF4 = {};
			Key KeyF5 = {};
			Key KeyF6 = {};
			Key KeyF7 = {};
			Key KeyF8 = {};
			Key KeyF9 = {};
			Key KeyF10 = {};
			Key KeyF11 = {};
			Key KeyF12 = {};

			Key KeyNumLock = {};

			Key KeyScrollLock = {};

			Key KeyLeftShift = {};
			Key KeyRightShift = {};
			Key KeyLeftControl = {};
			Key KeyRightControl = {};
			Key KeyLeftAlt = {};
			Key KeyRightAlt = {};
			Key KeyLeftCommand = {};
			Key KeyRightCommand = {};

			Key KeySemicolon = {};
			Key KeyEqual = {};
			Key KeyComma = {};
			Key KeyUnderscore = {};
			Key KeyHyphen = {};
			Key KeyPeriod = {};
			Key KeySlash = {};
			Key KeyTilde = {};
			Key KeyLeftBracket = {};
			Key KeyBackslash = {};
			Key KeyRightBracket = {};
			Key KeyApostrophe = {};

			Key KeyAmpersand = {};
			Key KeyAsterix = {};
			Key KeyCaret = {};
			Key KeyColon = {};
			Key KeyDollar = {};
			Key KeyExclamation = {};
			Key KeyLeftParantheses = {};
			Key KeyRightParantheses = {};
			Key KeyQuote = {};

			Key KeyNumPadZero = {};
			Key KeyNumPadOne = {};
			Key KeyNumPadTwo = {};
			Key KeyNumPadThree = {};
			Key KeyNumPadFour = {};
			Key KeyNumPadFive = {};
			Key KeyNumPadSix = {};
			Key KeyNumPadSeven = {};
			Key KeyNumPadEight = {};
			Key KeyNumPadNine = {};

			Key KeyMultiply = {};
			Key KeyAdd = {};
			Key KeySubtract = {};
			Key KeyDecimal = {};
			Key KeyDivide = {};
		};
	}
}

#endif // !_DYNAMIK_INPUTS_KEY_INPUTS_SUPPLIER_H
