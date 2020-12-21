// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "MouseInput.h"
#include "KeyboardInput.h"

namespace DMK
{
	namespace Inputs
	{
		/**
		 * Input Center object.
		 * This object stores all the inputs that occured.
		 */
		class InputCenter {
		public:
			InputCenter() {}
			~InputCenter() {}

			void ActivateKey(UI32 scanCode, ButtonInputState state);
			void ActivateButton(UI32 scanCode, ButtonInputState state);

			MousePointerPosition GetMousePointerPosition() const;

		public:
			MouseButtonInput MouseButtonLeft;
			MouseButtonInput MouseButtonRight;
			MouseButtonInput MouseButtonMiddle;
			MouseButtonInput MouseButton0;
			MouseButtonInput MouseButton1;

			KeyInput KeyLeft;
			KeyInput KeyRight;
			KeyInput KeyUp;
			KeyInput KeyDown;

			KeyInput KeyBackSpace;
			KeyInput KeyTab;
			KeyInput KeyEnter;
			KeyInput KeyPause;

			KeyInput KeyCapsLock;
			KeyInput KeyEscape;
			KeyInput KeySpaceBar;
			KeyInput KeyPageUp;
			KeyInput KeyPageDown;
			KeyInput KeyEnd;
			KeyInput KeyHome;

			KeyInput KeyZero;
			KeyInput KeyOne;
			KeyInput KeyTwo;
			KeyInput KeyThree;
			KeyInput KeyFour;
			KeyInput KeyFive;
			KeyInput KeySix;
			KeyInput KeySeven;
			KeyInput KeyEight;
			KeyInput KeyNine;

			KeyInput KeyA;
			KeyInput KeyB;
			KeyInput KeyC;
			KeyInput KeyD;
			KeyInput KeyE;
			KeyInput KeyF;
			KeyInput KeyG;
			KeyInput KeyH;
			KeyInput KeyI;
			KeyInput KeyJ;
			KeyInput KeyK;
			KeyInput KeyL;
			KeyInput KeyM;
			KeyInput KeyN;
			KeyInput KeyO;
			KeyInput KeyP;
			KeyInput KeyQ;
			KeyInput KeyR;
			KeyInput KeyS;
			KeyInput KeyT;
			KeyInput KeyU;
			KeyInput KeyV;
			KeyInput KeyW;
			KeyInput KeyX;
			KeyInput KeyY;
			KeyInput KeyZ;

			KeyInput KeyF1;
			KeyInput KeyF2;
			KeyInput KeyF3;
			KeyInput KeyF4;
			KeyInput KeyF5;
			KeyInput KeyF6;
			KeyInput KeyF7;
			KeyInput KeyF8;
			KeyInput KeyF9;
			KeyInput KeyF10;
			KeyInput KeyF11;
			KeyInput KeyF12;

			KeyInput KeyNumLock;

			KeyInput KeyScrollLock;

			KeyInput KeyLeftShift;
			KeyInput KeyRightShift;
			KeyInput KeyLeftControl;
			KeyInput KeyRightControl;
			KeyInput KeyLeftAlt;
			KeyInput KeyRightAlt;
			KeyInput KeyLeftCommand;
			KeyInput KeyRightCommand;

			KeyInput KeySemicolon;
			KeyInput KeyEqual;
			KeyInput KeyComma;
			KeyInput KeyUnderscore;
			KeyInput KeyHyphen;
			KeyInput KeyPeriod;
			KeyInput KeySlash;
			KeyInput KeyTilde;
			KeyInput KeyLeftBracket;
			KeyInput KeyBackslash;
			KeyInput KeyRightBracket;
			KeyInput KeyApostrophe;

			KeyInput KeyAmpersand;
			KeyInput KeyAsterix;
			KeyInput KeyCaret;
			KeyInput KeyColon;
			KeyInput KeyDollar;
			KeyInput KeyExclamation;
			KeyInput KeyLeftParantheses;
			KeyInput KeyRightParantheses;
			KeyInput KeyQuote;

			KeyInput KeyNumPadZero;
			KeyInput KeyNumPadOne;
			KeyInput KeyNumPadTwo;
			KeyInput KeyNumPadThree;
			KeyInput KeyNumPadFour;
			KeyInput KeyNumPadFive;
			KeyInput KeyNumPadSix;
			KeyInput KeyNumPadSeven;
			KeyInput KeyNumPadEight;
			KeyInput KeyNumPadNine;

			KeyInput KeyMultiply;
			KeyInput KeyAdd;
			KeyInput KeySubtract;
			KeyInput KeyDecimal;
			KeyInput KeyDivide;

			float MousePositionX = 0.0f;
			float MousePositionY = 0.0f;

			float MouseScrollUp = 0.0f;
			float MouseScrollDown = 0.0f;

			bool IsWindowOpen = true;
			bool IsWindowResized = false;
		};
	}
}