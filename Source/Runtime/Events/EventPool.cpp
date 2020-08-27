// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "EventPool.h"

#define ADD_EVENT(component) componentMap[TEXT(#component)] = &component; component.setName(#component)

void DMKEventPool::initialize()
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

void DMKEventPool::bindKey(const STRING& keyName, UI32 scanCode)
{
	keyMappings[scanCode] = (DMKKeyEventComponent*)componentMap[keyName];
}

DMKEventComponent* DMKEventPool::getComponent(const STRING& eventName)
{
	return componentMap[eventName];
}

void DMKEventPool::activateKey(DMKEventType type, UI32 scanCode)
{
	keyMappings[scanCode]->activate(1.0f, type);
}

void DMKEventPool::activateButton(DMKEventType type, UI32 ID)
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

void DMKEventPool::frameBufferResized()
{
	FrameBufferResizeEvent = true;
}

void DMKEventPool::reasetAll()
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

DMKExtent2D DMKEventPool::getMousePosition()
{
	return DMKExtent2D(MouseX, MouseY);
}

DMKEventComponent DMKEventPool::MouseX;
DMKEventComponent DMKEventPool::MouseY;
DMKEventComponent DMKEventPool::MouseScrollUp;
DMKEventComponent DMKEventPool::MouseScrollDown;
DMKEventComponent DMKEventPool::MouseWheel;

DMKButtonEventComponent DMKEventPool::MouseButtonLeft;
DMKButtonEventComponent DMKEventPool::MouseButtonRight;
DMKButtonEventComponent DMKEventPool::MouseButtonMiddle;
DMKButtonEventComponent DMKEventPool::MouseButton0;
DMKButtonEventComponent DMKEventPool::MouseButton1;

DMKKeyEventComponent DMKEventPool::KeyLeft;
DMKKeyEventComponent DMKEventPool::KeyRight;
DMKKeyEventComponent DMKEventPool::KeyUp;
DMKKeyEventComponent DMKEventPool::KeyDown;

DMKKeyEventComponent DMKEventPool::KeyBackSpace;
DMKKeyEventComponent DMKEventPool::KeyTab;
DMKKeyEventComponent DMKEventPool::KeyEnter;
DMKKeyEventComponent DMKEventPool::KeyPause;

DMKKeyEventComponent DMKEventPool::KeyCapsLock;
DMKKeyEventComponent DMKEventPool::KeyEscape;
DMKKeyEventComponent DMKEventPool::KeySpaceBar;
DMKKeyEventComponent DMKEventPool::KeyPageUp;
DMKKeyEventComponent DMKEventPool::KeyPageDown;
DMKKeyEventComponent DMKEventPool::KeyEnd;
DMKKeyEventComponent DMKEventPool::KeyHome;

DMKKeyEventComponent DMKEventPool::KeyZero;
DMKKeyEventComponent DMKEventPool::KeyOne;
DMKKeyEventComponent DMKEventPool::KeyTwo;
DMKKeyEventComponent DMKEventPool::KeyThree;
DMKKeyEventComponent DMKEventPool::KeyFour;
DMKKeyEventComponent DMKEventPool::KeyFive;
DMKKeyEventComponent DMKEventPool::KeySix;
DMKKeyEventComponent DMKEventPool::KeySeven;
DMKKeyEventComponent DMKEventPool::KeyEight;
DMKKeyEventComponent DMKEventPool::KeyNine;

DMKKeyEventComponent DMKEventPool::KeyA;
DMKKeyEventComponent DMKEventPool::KeyB;
DMKKeyEventComponent DMKEventPool::KeyC;
DMKKeyEventComponent DMKEventPool::KeyD;
DMKKeyEventComponent DMKEventPool::KeyE;
DMKKeyEventComponent DMKEventPool::KeyF;
DMKKeyEventComponent DMKEventPool::KeyG;
DMKKeyEventComponent DMKEventPool::KeyH;
DMKKeyEventComponent DMKEventPool::KeyI;
DMKKeyEventComponent DMKEventPool::KeyJ;
DMKKeyEventComponent DMKEventPool::KeyK;
DMKKeyEventComponent DMKEventPool::KeyL;
DMKKeyEventComponent DMKEventPool::KeyM;
DMKKeyEventComponent DMKEventPool::KeyN;
DMKKeyEventComponent DMKEventPool::KeyO;
DMKKeyEventComponent DMKEventPool::KeyP;
DMKKeyEventComponent DMKEventPool::KeyQ;
DMKKeyEventComponent DMKEventPool::KeyR;
DMKKeyEventComponent DMKEventPool::KeyS;
DMKKeyEventComponent DMKEventPool::KeyT;
DMKKeyEventComponent DMKEventPool::KeyU;
DMKKeyEventComponent DMKEventPool::KeyV;
DMKKeyEventComponent DMKEventPool::KeyW;
DMKKeyEventComponent DMKEventPool::KeyX;
DMKKeyEventComponent DMKEventPool::KeyY;
DMKKeyEventComponent DMKEventPool::KeyZ;

DMKKeyEventComponent DMKEventPool::KeyF1;
DMKKeyEventComponent DMKEventPool::KeyF2;
DMKKeyEventComponent DMKEventPool::KeyF3;
DMKKeyEventComponent DMKEventPool::KeyF4;
DMKKeyEventComponent DMKEventPool::KeyF5;
DMKKeyEventComponent DMKEventPool::KeyF6;
DMKKeyEventComponent DMKEventPool::KeyF7;
DMKKeyEventComponent DMKEventPool::KeyF8;
DMKKeyEventComponent DMKEventPool::KeyF9;
DMKKeyEventComponent DMKEventPool::KeyF10;
DMKKeyEventComponent DMKEventPool::KeyF11;
DMKKeyEventComponent DMKEventPool::KeyF12;

DMKKeyEventComponent DMKEventPool::KeyNumLock;

DMKKeyEventComponent DMKEventPool::KeyScrollLock;

DMKKeyEventComponent DMKEventPool::KeyLeftShift;
DMKKeyEventComponent DMKEventPool::KeyRightShift;
DMKKeyEventComponent DMKEventPool::KeyLeftControl;
DMKKeyEventComponent DMKEventPool::KeyRightControl;
DMKKeyEventComponent DMKEventPool::KeyLeftAlt;
DMKKeyEventComponent DMKEventPool::KeyRightAlt;
DMKKeyEventComponent DMKEventPool::KeyLeftCommand;
DMKKeyEventComponent DMKEventPool::KeyRightCommand;

DMKKeyEventComponent DMKEventPool::KeySemicolon;
DMKKeyEventComponent DMKEventPool::KeyEqual;
DMKKeyEventComponent DMKEventPool::KeyComma;
DMKKeyEventComponent DMKEventPool::KeyUnderscore;
DMKKeyEventComponent DMKEventPool::KeyHyphen;
DMKKeyEventComponent DMKEventPool::KeyPeriod;
DMKKeyEventComponent DMKEventPool::KeySlash;
DMKKeyEventComponent DMKEventPool::KeyTilde;
DMKKeyEventComponent DMKEventPool::KeyLeftBracket;
DMKKeyEventComponent DMKEventPool::KeyBackslash;
DMKKeyEventComponent DMKEventPool::KeyRightBracket;
DMKKeyEventComponent DMKEventPool::KeyApostrophe;

DMKKeyEventComponent DMKEventPool::KeyAmpersand;
DMKKeyEventComponent DMKEventPool::KeyAsterix;
DMKKeyEventComponent DMKEventPool::KeyCaret;
DMKKeyEventComponent DMKEventPool::KeyColon;
DMKKeyEventComponent DMKEventPool::KeyDollar;
DMKKeyEventComponent DMKEventPool::KeyExclamation;
DMKKeyEventComponent DMKEventPool::KeyLeftParantheses;
DMKKeyEventComponent DMKEventPool::KeyRightParantheses;
DMKKeyEventComponent DMKEventPool::KeyQuote;

DMKKeyEventComponent DMKEventPool::KeyNumPadZero;
DMKKeyEventComponent DMKEventPool::KeyNumPadOne;
DMKKeyEventComponent DMKEventPool::KeyNumPadTwo;
DMKKeyEventComponent DMKEventPool::KeyNumPadThree;
DMKKeyEventComponent DMKEventPool::KeyNumPadFour;
DMKKeyEventComponent DMKEventPool::KeyNumPadFive;
DMKKeyEventComponent DMKEventPool::KeyNumPadSix;
DMKKeyEventComponent DMKEventPool::KeyNumPadSeven;
DMKKeyEventComponent DMKEventPool::KeyNumPadEight;
DMKKeyEventComponent DMKEventPool::KeyNumPadNine;

DMKKeyEventComponent DMKEventPool::KeyMultiply;
DMKKeyEventComponent DMKEventPool::KeyAdd;
DMKKeyEventComponent DMKEventPool::KeySubtract;
DMKKeyEventComponent DMKEventPool::KeyDecimal;
DMKKeyEventComponent DMKEventPool::KeyDivide;

B1 DMKEventPool::WindowCloseEvent = false;
B1 DMKEventPool::FrameBufferResizeEvent = false;
