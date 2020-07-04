// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_EVENT_BOARD_H
#define _DYNAMIK_EVENT_BOARD_H

#include "Core/Macros/Global.h"
#include "Core/Types/DataTypes.h"
#include "EventComponent.h"

#include <unordered_map>

namespace Dynamik
{
	/*
	 Dynamik Event Board
	 This object contains all the events that occurred in one iteration.

	 Usage:
		if (DMKEventBoard::KeyF.isPressed() && DMKEventBoard::KeyU.isPressed())
			printAll("*");
	*/
	class DMK_API DMKEventBoard {
	public:
		DMKEventBoard() {}
		~DMKEventBoard() {}

		void initialize();
		void bindKey(const STRING& keyName, UI32 scanCode);
		void activateKey(DMKEventType type, UI32 scanCode);
		void activateButton(DMKEventType type, UI32 ID);
		void reasetAll();

		/* Mouse Events */
		static DMKEventComponent MouseX;
		static DMKEventComponent MouseY;
		static DMKEventComponent MouseScrollUp;
		static DMKEventComponent MouseScrollDown;
		static DMKEventComponent MouseWheel;

		static DMKButtonEventComponent MouseButtonLeft;
		static DMKButtonEventComponent MouseButtonRight;
		static DMKButtonEventComponent MouseButtonMiddle;
		static DMKButtonEventComponent MouseButton0;
		static DMKButtonEventComponent MouseButton1;

		/* Keyboard Events */
		static DMKKeyEventComponent KeyLeft;
		static DMKKeyEventComponent KeyRight;
		static DMKKeyEventComponent KeyUp;
		static DMKKeyEventComponent KeyDown;

		static DMKKeyEventComponent KeyBackSpace;
		static DMKKeyEventComponent KeyTab;
		static DMKKeyEventComponent KeyEnter;
		static DMKKeyEventComponent KeyPause;

		static DMKKeyEventComponent KeyCapsLock;
		static DMKKeyEventComponent KeyEscape;
		static DMKKeyEventComponent KeySpaceBar;
		static DMKKeyEventComponent KeyPageUp;
		static DMKKeyEventComponent KeyPageDown;
		static DMKKeyEventComponent KeyEnd;
		static DMKKeyEventComponent KeyHome;

		static DMKKeyEventComponent KeyZero;
		static DMKKeyEventComponent KeyOne;
		static DMKKeyEventComponent KeyTwo;
		static DMKKeyEventComponent KeyThree;
		static DMKKeyEventComponent KeyFour;
		static DMKKeyEventComponent KeyFive;
		static DMKKeyEventComponent KeySix;
		static DMKKeyEventComponent KeySeven;
		static DMKKeyEventComponent KeyEight;
		static DMKKeyEventComponent KeyNine;

		static DMKKeyEventComponent KeyA;
		static DMKKeyEventComponent KeyB;
		static DMKKeyEventComponent KeyC;
		static DMKKeyEventComponent KeyD;
		static DMKKeyEventComponent KeyE;
		static DMKKeyEventComponent KeyF;
		static DMKKeyEventComponent KeyG;
		static DMKKeyEventComponent KeyH;
		static DMKKeyEventComponent KeyI;
		static DMKKeyEventComponent KeyJ;
		static DMKKeyEventComponent KeyK;
		static DMKKeyEventComponent KeyL;
		static DMKKeyEventComponent KeyM;
		static DMKKeyEventComponent KeyN;
		static DMKKeyEventComponent KeyO;
		static DMKKeyEventComponent KeyP;
		static DMKKeyEventComponent KeyQ;
		static DMKKeyEventComponent KeyR;
		static DMKKeyEventComponent KeyS;
		static DMKKeyEventComponent KeyT;
		static DMKKeyEventComponent KeyU;
		static DMKKeyEventComponent KeyV;
		static DMKKeyEventComponent KeyW;
		static DMKKeyEventComponent KeyX;
		static DMKKeyEventComponent KeyY;
		static DMKKeyEventComponent KeyZ;

		static DMKKeyEventComponent KeyF1;
		static DMKKeyEventComponent KeyF2;
		static DMKKeyEventComponent KeyF3;
		static DMKKeyEventComponent KeyF4;
		static DMKKeyEventComponent KeyF5;
		static DMKKeyEventComponent KeyF6;
		static DMKKeyEventComponent KeyF7;
		static DMKKeyEventComponent KeyF8;
		static DMKKeyEventComponent KeyF9;
		static DMKKeyEventComponent KeyF10;
		static DMKKeyEventComponent KeyF11;
		static DMKKeyEventComponent KeyF12;

		static DMKKeyEventComponent KeyNumLock;

		static DMKKeyEventComponent KeyScrollLock;

		static DMKKeyEventComponent KeyLeftShift;
		static DMKKeyEventComponent KeyRightShift;
		static DMKKeyEventComponent KeyLeftControl;
		static DMKKeyEventComponent KeyRightControl;
		static DMKKeyEventComponent KeyLeftAlt;
		static DMKKeyEventComponent KeyRightAlt;
		static DMKKeyEventComponent KeyLeftCommand;
		static DMKKeyEventComponent KeyRightCommand;

		static DMKKeyEventComponent KeySemicolon;
		static DMKKeyEventComponent KeyEqual;
		static DMKKeyEventComponent KeyComma;
		static DMKKeyEventComponent KeyUnderscore;
		static DMKKeyEventComponent KeyHyphen;
		static DMKKeyEventComponent KeyPeriod;
		static DMKKeyEventComponent KeySlash;
		static DMKKeyEventComponent KeyTilde;
		static DMKKeyEventComponent KeyLeftBracket;
		static DMKKeyEventComponent KeyBackslash;
		static DMKKeyEventComponent KeyRightBracket;
		static DMKKeyEventComponent KeyApostrophe;

		static DMKKeyEventComponent KeyAmpersand;
		static DMKKeyEventComponent KeyAsterix;
		static DMKKeyEventComponent KeyCaret;
		static DMKKeyEventComponent KeyColon;
		static DMKKeyEventComponent KeyDollar;
		static DMKKeyEventComponent KeyExclamation;
		static DMKKeyEventComponent KeyLeftParantheses;
		static DMKKeyEventComponent KeyRightParantheses;
		static DMKKeyEventComponent KeyQuote;

		static DMKKeyEventComponent KeyNumPadZero;
		static DMKKeyEventComponent KeyNumPadOne;
		static DMKKeyEventComponent KeyNumPadTwo;
		static DMKKeyEventComponent KeyNumPadThree;
		static DMKKeyEventComponent KeyNumPadFour;
		static DMKKeyEventComponent KeyNumPadFive;
		static DMKKeyEventComponent KeyNumPadSix;
		static DMKKeyEventComponent KeyNumPadSeven;
		static DMKKeyEventComponent KeyNumPadEight;
		static DMKKeyEventComponent KeyNumPadNine;

		static DMKKeyEventComponent KeyMultiply;
		static DMKKeyEventComponent KeyAdd;
		static DMKKeyEventComponent KeySubtract;
		static DMKKeyEventComponent KeyDecimal;
		static DMKKeyEventComponent KeyDivide;

		std::unordered_map<STRING, DMKEventComponent*> componentMap;
		std::unordered_map<UI32, DMKKeyEventComponent*> keyMappings;
	};
}

#endif // !_DYNAMIK_EVENT_BOARD_H
