// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "EventBoard.h"

#define ADD_EVENT(component) componentMap[DMK_TEXT(#component)] = &component; component.setName(#component)

namespace Dynamik
{
	void DMKEventBoard::initialize()
	{
		ADD_EVENT(MouseX);
		ADD_EVENT(MouseY);
		ADD_EVENT(MouseScrollUp);
		ADD_EVENT(MouseScrollDown);
		ADD_EVENT(MouseWheel);

		ADD_EVENT(MouseButtonLeft);
		ADD_EVENT(MouseButtonRight);
		ADD_EVENT(MouseButtonMiddle);
		ADD_EVENT(MouseButton0);
		ADD_EVENT(MouseButton1);

		ADD_EVENT(KeyLeft);
		ADD_EVENT(KeyRight);
		ADD_EVENT(KeyUp);
		ADD_EVENT(KeyDown);

		ADD_EVENT(KeyBackSpace);
		ADD_EVENT(KeyTab);
		ADD_EVENT(KeyEnter);
		ADD_EVENT(KeyPause);

		ADD_EVENT(KeyCapsLock);
		ADD_EVENT(KeyEscape);
		ADD_EVENT(KeySpaceBar);
		ADD_EVENT(KeyPageUp);
		ADD_EVENT(KeyPageDown);
		ADD_EVENT(KeyEnd);
		ADD_EVENT(KeyHome);

		ADD_EVENT(KeyZero);
		ADD_EVENT(KeyOne);
		ADD_EVENT(KeyTwo);
		ADD_EVENT(KeyThree);
		ADD_EVENT(KeyFour);
		ADD_EVENT(KeyFive);
		ADD_EVENT(KeySix);
		ADD_EVENT(KeySeven);
		ADD_EVENT(KeyEight);
		ADD_EVENT(KeyNine);

		ADD_EVENT(KeyA);
		ADD_EVENT(KeyB);
		ADD_EVENT(KeyC);
		ADD_EVENT(KeyD);
		ADD_EVENT(KeyE);
		ADD_EVENT(KeyF);
		ADD_EVENT(KeyG);
		ADD_EVENT(KeyH);
		ADD_EVENT(KeyI);
		ADD_EVENT(KeyJ);
		ADD_EVENT(KeyK);
		ADD_EVENT(KeyL);
		ADD_EVENT(KeyM);
		ADD_EVENT(KeyN);
		ADD_EVENT(KeyO);
		ADD_EVENT(KeyP);
		ADD_EVENT(KeyQ);
		ADD_EVENT(KeyR);
		ADD_EVENT(KeyS);
		ADD_EVENT(KeyT);
		ADD_EVENT(KeyU);
		ADD_EVENT(KeyV);
		ADD_EVENT(KeyW);
		ADD_EVENT(KeyX);
		ADD_EVENT(KeyY);
		ADD_EVENT(KeyZ);

		ADD_EVENT(KeyF1);
		ADD_EVENT(KeyF2);
		ADD_EVENT(KeyF3);
		ADD_EVENT(KeyF4);
		ADD_EVENT(KeyF5);
		ADD_EVENT(KeyF6);
		ADD_EVENT(KeyF7);
		ADD_EVENT(KeyF8);
		ADD_EVENT(KeyF9);
		ADD_EVENT(KeyF10);
		ADD_EVENT(KeyF11);
		ADD_EVENT(KeyF12);

		ADD_EVENT(KeyNumLock);

		ADD_EVENT(KeyScrollLock);

		ADD_EVENT(KeyLeftShift);
		ADD_EVENT(KeyRightShift);
		ADD_EVENT(KeyLeftControl);
		ADD_EVENT(KeyRightControl);
		ADD_EVENT(KeyLeftAlt);
		ADD_EVENT(KeyRightAlt);
		ADD_EVENT(KeyLeftCommand);
		ADD_EVENT(KeyRightCommand);

		ADD_EVENT(KeySemicolon);
		ADD_EVENT(KeyEqual);
		ADD_EVENT(KeyComma);
		ADD_EVENT(KeyUnderscore);
		ADD_EVENT(KeyHyphen);
		ADD_EVENT(KeyPeriod);
		ADD_EVENT(KeySlash);
		ADD_EVENT(KeyTilde);
		ADD_EVENT(KeyLeftBracket);
		ADD_EVENT(KeyBackslash);
		ADD_EVENT(KeyRightBracket);
		ADD_EVENT(KeyApostrophe);

		ADD_EVENT(KeyAmpersand);
		ADD_EVENT(KeyAsterix);
		ADD_EVENT(KeyCaret);
		ADD_EVENT(KeyColon);
		ADD_EVENT(KeyDollar);
		ADD_EVENT(KeyExclamation);
		ADD_EVENT(KeyLeftParantheses);
		ADD_EVENT(KeyRightParantheses);
		ADD_EVENT(KeyQuote);

		ADD_EVENT(KeyNumPadZero);
		ADD_EVENT(KeyNumPadOne);
		ADD_EVENT(KeyNumPadTwo);
		ADD_EVENT(KeyNumPadThree);
		ADD_EVENT(KeyNumPadFour);
		ADD_EVENT(KeyNumPadFive);
		ADD_EVENT(KeyNumPadSix);
		ADD_EVENT(KeyNumPadSeven);
		ADD_EVENT(KeyNumPadEight);
		ADD_EVENT(KeyNumPadNine);

		ADD_EVENT(KeyMultiply);
		ADD_EVENT(KeyAdd);
		ADD_EVENT(KeySubtract);
		ADD_EVENT(KeyDecimal);
		ADD_EVENT(KeyDivide);
	}

	void DMKEventBoard::bindKey(const STRING& keyName, UI32 scanCode)
	{
		keyMappings[scanCode] = (DMKKeyEventComponent*)componentMap[keyName];
	}

	void DMKEventBoard::activateKey(DMKEventType type, UI32 scanCode)
	{
		keyMappings[scanCode]->activate(1.0f, type);
	}

	void DMKEventBoard::activateButton(DMKEventType type, UI32 ID)
	{
		if (ID == 0)
			MouseButtonLeft.activate(1.0f, type);
		else if (ID == 1)
			MouseButtonRight.activate(1.0f, type);
		else if (ID == 2)
			MouseButtonMiddle.activate(1.0f, type);
		else if (ID == 3)
			MouseButton0.activate(1.0f, type);
		else if (ID == 4)
			MouseButton1.activate(1.0f, type);
		else
			DMK_ERROR("Invalid Button ID!");
	}

	void DMKEventBoard::reasetAll()
	{
		MouseX.reset();
		MouseY.reset();
		MouseScrollUp.reset();
		MouseScrollDown.reset();
		MouseWheel.reset();

		MouseButtonLeft.reset();
		MouseButtonRight.reset();
		MouseButtonMiddle.reset();
		MouseButton0.reset();
		MouseButton1.reset();

		KeyLeft.reset();
		KeyRight.reset();
		KeyUp.reset();
		KeyDown.reset();

		KeyBackSpace.reset();
		KeyTab.reset();
		KeyEnter.reset();
		KeyPause.reset();

		KeyCapsLock.reset();
		KeyEscape.reset();
		KeySpaceBar.reset();
		KeyPageUp.reset();
		KeyPageDown.reset();
		KeyEnd.reset();
		KeyHome.reset();

		KeyZero.reset();
		KeyOne.reset();
		KeyTwo.reset();
		KeyThree.reset();
		KeyFour.reset();
		KeyFive.reset();
		KeySix.reset();
		KeySeven.reset();
		KeyEight.reset();
		KeyNine.reset();

		KeyA.reset();
		KeyB.reset();
		KeyC.reset();
		KeyD.reset();
		KeyE.reset();
		KeyF.reset();
		KeyG.reset();
		KeyH.reset();
		KeyI.reset();
		KeyJ.reset();
		KeyK.reset();
		KeyL.reset();
		KeyM.reset();
		KeyN.reset();
		KeyO.reset();
		KeyP.reset();
		KeyQ.reset();
		KeyR.reset();
		KeyS.reset();
		KeyT.reset();
		KeyU.reset();
		KeyV.reset();
		KeyW.reset();
		KeyX.reset();
		KeyY.reset();
		KeyZ.reset();

		KeyF1.reset();
		KeyF2.reset();
		KeyF3.reset();
		KeyF4.reset();
		KeyF5.reset();
		KeyF6.reset();
		KeyF7.reset();
		KeyF8.reset();
		KeyF9.reset();
		KeyF10.reset();
		KeyF11.reset();
		KeyF12.reset();

		KeyNumLock.reset();

		KeyScrollLock.reset();

		KeyLeftShift.reset();
		KeyRightShift.reset();
		KeyLeftControl.reset();
		KeyRightControl.reset();
		KeyLeftAlt.reset();
		KeyRightAlt.reset();
		KeyLeftCommand.reset();
		KeyRightCommand.reset();

		KeySemicolon.reset();
		KeyEqual.reset();
		KeyComma.reset();
		KeyUnderscore.reset();
		KeyHyphen.reset();
		KeyPeriod.reset();
		KeySlash.reset();
		KeyTilde.reset();
		KeyLeftBracket.reset();
		KeyBackslash.reset();
		KeyRightBracket.reset();
		KeyApostrophe.reset();

		KeyAmpersand.reset();
		KeyAsterix.reset();
		KeyCaret.reset();
		KeyColon.reset();
		KeyDollar.reset();
		KeyExclamation.reset();
		KeyLeftParantheses.reset();
		KeyRightParantheses.reset();
		KeyQuote.reset();

		KeyNumPadZero.reset();
		KeyNumPadOne.reset();
		KeyNumPadTwo.reset();
		KeyNumPadThree.reset();
		KeyNumPadFour.reset();
		KeyNumPadFive.reset();
		KeyNumPadSix.reset();
		KeyNumPadSeven.reset();
		KeyNumPadEight.reset();
		KeyNumPadNine.reset();

		KeyMultiply.reset();
		KeyAdd.reset();
		KeySubtract.reset();
		KeyDecimal.reset();
		KeyDivide.reset();
	}

	DMKEventComponent DMKEventBoard::MouseX;
	DMKEventComponent DMKEventBoard::MouseY;
	DMKEventComponent DMKEventBoard::MouseScrollUp;
	DMKEventComponent DMKEventBoard::MouseScrollDown;
	DMKEventComponent DMKEventBoard::MouseWheel;

	DMKButtonEventComponent DMKEventBoard::MouseButtonLeft;
	DMKButtonEventComponent DMKEventBoard::MouseButtonRight;
	DMKButtonEventComponent DMKEventBoard::MouseButtonMiddle;
	DMKButtonEventComponent DMKEventBoard::MouseButton0;
	DMKButtonEventComponent DMKEventBoard::MouseButton1;

	DMKKeyEventComponent DMKEventBoard::KeyLeft;
	DMKKeyEventComponent DMKEventBoard::KeyRight;
	DMKKeyEventComponent DMKEventBoard::KeyUp;
	DMKKeyEventComponent DMKEventBoard::KeyDown;

	DMKKeyEventComponent DMKEventBoard::KeyBackSpace;
	DMKKeyEventComponent DMKEventBoard::KeyTab;
	DMKKeyEventComponent DMKEventBoard::KeyEnter;
	DMKKeyEventComponent DMKEventBoard::KeyPause;

	DMKKeyEventComponent DMKEventBoard::KeyCapsLock;
	DMKKeyEventComponent DMKEventBoard::KeyEscape;
	DMKKeyEventComponent DMKEventBoard::KeySpaceBar;
	DMKKeyEventComponent DMKEventBoard::KeyPageUp;
	DMKKeyEventComponent DMKEventBoard::KeyPageDown;
	DMKKeyEventComponent DMKEventBoard::KeyEnd;
	DMKKeyEventComponent DMKEventBoard::KeyHome;

	DMKKeyEventComponent DMKEventBoard::KeyZero;
	DMKKeyEventComponent DMKEventBoard::KeyOne;
	DMKKeyEventComponent DMKEventBoard::KeyTwo;
	DMKKeyEventComponent DMKEventBoard::KeyThree;
	DMKKeyEventComponent DMKEventBoard::KeyFour;
	DMKKeyEventComponent DMKEventBoard::KeyFive;
	DMKKeyEventComponent DMKEventBoard::KeySix;
	DMKKeyEventComponent DMKEventBoard::KeySeven;
	DMKKeyEventComponent DMKEventBoard::KeyEight;
	DMKKeyEventComponent DMKEventBoard::KeyNine;

	DMKKeyEventComponent DMKEventBoard::KeyA;
	DMKKeyEventComponent DMKEventBoard::KeyB;
	DMKKeyEventComponent DMKEventBoard::KeyC;
	DMKKeyEventComponent DMKEventBoard::KeyD;
	DMKKeyEventComponent DMKEventBoard::KeyE;
	DMKKeyEventComponent DMKEventBoard::KeyF;
	DMKKeyEventComponent DMKEventBoard::KeyG;
	DMKKeyEventComponent DMKEventBoard::KeyH;
	DMKKeyEventComponent DMKEventBoard::KeyI;
	DMKKeyEventComponent DMKEventBoard::KeyJ;
	DMKKeyEventComponent DMKEventBoard::KeyK;
	DMKKeyEventComponent DMKEventBoard::KeyL;
	DMKKeyEventComponent DMKEventBoard::KeyM;
	DMKKeyEventComponent DMKEventBoard::KeyN;
	DMKKeyEventComponent DMKEventBoard::KeyO;
	DMKKeyEventComponent DMKEventBoard::KeyP;
	DMKKeyEventComponent DMKEventBoard::KeyQ;
	DMKKeyEventComponent DMKEventBoard::KeyR;
	DMKKeyEventComponent DMKEventBoard::KeyS;
	DMKKeyEventComponent DMKEventBoard::KeyT;
	DMKKeyEventComponent DMKEventBoard::KeyU;
	DMKKeyEventComponent DMKEventBoard::KeyV;
	DMKKeyEventComponent DMKEventBoard::KeyW;
	DMKKeyEventComponent DMKEventBoard::KeyX;
	DMKKeyEventComponent DMKEventBoard::KeyY;
	DMKKeyEventComponent DMKEventBoard::KeyZ;

	DMKKeyEventComponent DMKEventBoard::KeyF1;
	DMKKeyEventComponent DMKEventBoard::KeyF2;
	DMKKeyEventComponent DMKEventBoard::KeyF3;
	DMKKeyEventComponent DMKEventBoard::KeyF4;
	DMKKeyEventComponent DMKEventBoard::KeyF5;
	DMKKeyEventComponent DMKEventBoard::KeyF6;
	DMKKeyEventComponent DMKEventBoard::KeyF7;
	DMKKeyEventComponent DMKEventBoard::KeyF8;
	DMKKeyEventComponent DMKEventBoard::KeyF9;
	DMKKeyEventComponent DMKEventBoard::KeyF10;
	DMKKeyEventComponent DMKEventBoard::KeyF11;
	DMKKeyEventComponent DMKEventBoard::KeyF12;

	DMKKeyEventComponent DMKEventBoard::KeyNumLock;

	DMKKeyEventComponent DMKEventBoard::KeyScrollLock;

	DMKKeyEventComponent DMKEventBoard::KeyLeftShift;
	DMKKeyEventComponent DMKEventBoard::KeyRightShift;
	DMKKeyEventComponent DMKEventBoard::KeyLeftControl;
	DMKKeyEventComponent DMKEventBoard::KeyRightControl;
	DMKKeyEventComponent DMKEventBoard::KeyLeftAlt;
	DMKKeyEventComponent DMKEventBoard::KeyRightAlt;
	DMKKeyEventComponent DMKEventBoard::KeyLeftCommand;
	DMKKeyEventComponent DMKEventBoard::KeyRightCommand;

	DMKKeyEventComponent DMKEventBoard::KeySemicolon;
	DMKKeyEventComponent DMKEventBoard::KeyEqual;
	DMKKeyEventComponent DMKEventBoard::KeyComma;
	DMKKeyEventComponent DMKEventBoard::KeyUnderscore;
	DMKKeyEventComponent DMKEventBoard::KeyHyphen;
	DMKKeyEventComponent DMKEventBoard::KeyPeriod;
	DMKKeyEventComponent DMKEventBoard::KeySlash;
	DMKKeyEventComponent DMKEventBoard::KeyTilde;
	DMKKeyEventComponent DMKEventBoard::KeyLeftBracket;
	DMKKeyEventComponent DMKEventBoard::KeyBackslash;
	DMKKeyEventComponent DMKEventBoard::KeyRightBracket;
	DMKKeyEventComponent DMKEventBoard::KeyApostrophe;

	DMKKeyEventComponent DMKEventBoard::KeyAmpersand;
	DMKKeyEventComponent DMKEventBoard::KeyAsterix;
	DMKKeyEventComponent DMKEventBoard::KeyCaret;
	DMKKeyEventComponent DMKEventBoard::KeyColon;
	DMKKeyEventComponent DMKEventBoard::KeyDollar;
	DMKKeyEventComponent DMKEventBoard::KeyExclamation;
	DMKKeyEventComponent DMKEventBoard::KeyLeftParantheses;
	DMKKeyEventComponent DMKEventBoard::KeyRightParantheses;
	DMKKeyEventComponent DMKEventBoard::KeyQuote;

	DMKKeyEventComponent DMKEventBoard::KeyNumPadZero;
	DMKKeyEventComponent DMKEventBoard::KeyNumPadOne;
	DMKKeyEventComponent DMKEventBoard::KeyNumPadTwo;
	DMKKeyEventComponent DMKEventBoard::KeyNumPadThree;
	DMKKeyEventComponent DMKEventBoard::KeyNumPadFour;
	DMKKeyEventComponent DMKEventBoard::KeyNumPadFive;
	DMKKeyEventComponent DMKEventBoard::KeyNumPadSix;
	DMKKeyEventComponent DMKEventBoard::KeyNumPadSeven;
	DMKKeyEventComponent DMKEventBoard::KeyNumPadEight;
	DMKKeyEventComponent DMKEventBoard::KeyNumPadNine;

	DMKKeyEventComponent DMKEventBoard::KeyMultiply;
	DMKKeyEventComponent DMKEventBoard::KeyAdd;
	DMKKeyEventComponent DMKEventBoard::KeySubtract;
	DMKKeyEventComponent DMKEventBoard::KeyDecimal;
	DMKKeyEventComponent DMKEventBoard::KeyDivide;
}
