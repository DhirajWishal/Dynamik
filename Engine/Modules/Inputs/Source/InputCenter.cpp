// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "Inputs/InputCenter.h"
#include "Core/Error/ErrorManager.h"

#define ADD_INPUT(component) componentMap[TEXT(#component)] = &component; component.SetName(#component)

namespace DMK
{
	void InputCenter::Initialize()
	{
		ADD_INPUT(MouseX);
		ADD_INPUT(MouseY);
		ADD_INPUT(MouseScrollUp);
		ADD_INPUT(MouseScrollDown);
		ADD_INPUT(MouseWheel);

		ADD_INPUT(MouseButtonLeft);
		ADD_INPUT(MouseButtonRight);
		ADD_INPUT(MouseButtonMiddle);
		ADD_INPUT(MouseButton0);
		ADD_INPUT(MouseButton1);

		ADD_INPUT(KeyLeft);
		ADD_INPUT(KeyRight);
		ADD_INPUT(KeyUp);
		ADD_INPUT(KeyDown);

		ADD_INPUT(KeyBackSpace);
		ADD_INPUT(KeyTab);
		ADD_INPUT(KeyEnter);
		ADD_INPUT(KeyPause);

		ADD_INPUT(KeyCapsLock);
		ADD_INPUT(KeyEscape);
		ADD_INPUT(KeySpaceBar);
		ADD_INPUT(KeyPageUp);
		ADD_INPUT(KeyPageDown);
		ADD_INPUT(KeyEnd);
		ADD_INPUT(KeyHome);

		ADD_INPUT(KeyZero);
		ADD_INPUT(KeyOne);
		ADD_INPUT(KeyTwo);
		ADD_INPUT(KeyThree);
		ADD_INPUT(KeyFour);
		ADD_INPUT(KeyFive);
		ADD_INPUT(KeySix);
		ADD_INPUT(KeySeven);
		ADD_INPUT(KeyEight);
		ADD_INPUT(KeyNine);

		ADD_INPUT(KeyA);
		ADD_INPUT(KeyB);
		ADD_INPUT(KeyC);
		ADD_INPUT(KeyD);
		ADD_INPUT(KeyE);
		ADD_INPUT(KeyF);
		ADD_INPUT(KeyG);
		ADD_INPUT(KeyH);
		ADD_INPUT(KeyI);
		ADD_INPUT(KeyJ);
		ADD_INPUT(KeyK);
		ADD_INPUT(KeyL);
		ADD_INPUT(KeyM);
		ADD_INPUT(KeyN);
		ADD_INPUT(KeyO);
		ADD_INPUT(KeyP);
		ADD_INPUT(KeyQ);
		ADD_INPUT(KeyR);
		ADD_INPUT(KeyS);
		ADD_INPUT(KeyT);
		ADD_INPUT(KeyU);
		ADD_INPUT(KeyV);
		ADD_INPUT(KeyW);
		ADD_INPUT(KeyX);
		ADD_INPUT(KeyY);
		ADD_INPUT(KeyZ);

		ADD_INPUT(KeyF1);
		ADD_INPUT(KeyF2);
		ADD_INPUT(KeyF3);
		ADD_INPUT(KeyF4);
		ADD_INPUT(KeyF5);
		ADD_INPUT(KeyF6);
		ADD_INPUT(KeyF7);
		ADD_INPUT(KeyF8);
		ADD_INPUT(KeyF9);
		ADD_INPUT(KeyF10);
		ADD_INPUT(KeyF11);
		ADD_INPUT(KeyF12);

		ADD_INPUT(KeyNumLock);

		ADD_INPUT(KeyScrollLock);

		ADD_INPUT(KeyLeftShift);
		ADD_INPUT(KeyRightShift);
		ADD_INPUT(KeyLeftControl);
		ADD_INPUT(KeyRightControl);
		ADD_INPUT(KeyLeftAlt);
		ADD_INPUT(KeyRightAlt);
		ADD_INPUT(KeyLeftCommand);
		ADD_INPUT(KeyRightCommand);

		ADD_INPUT(KeySemicolon);
		ADD_INPUT(KeyEqual);
		ADD_INPUT(KeyComma);
		ADD_INPUT(KeyUnderscore);
		ADD_INPUT(KeyHyphen);
		ADD_INPUT(KeyPeriod);
		ADD_INPUT(KeySlash);
		ADD_INPUT(KeyTilde);
		ADD_INPUT(KeyLeftBracket);
		ADD_INPUT(KeyBackslash);
		ADD_INPUT(KeyRightBracket);
		ADD_INPUT(KeyApostrophe);

		ADD_INPUT(KeyAmpersand);
		ADD_INPUT(KeyAsterix);
		ADD_INPUT(KeyCaret);
		ADD_INPUT(KeyColon);
		ADD_INPUT(KeyDollar);
		ADD_INPUT(KeyExclamation);
		ADD_INPUT(KeyLeftParantheses);
		ADD_INPUT(KeyRightParantheses);
		ADD_INPUT(KeyQuote);

		ADD_INPUT(KeyNumPadZero);
		ADD_INPUT(KeyNumPadOne);
		ADD_INPUT(KeyNumPadTwo);
		ADD_INPUT(KeyNumPadThree);
		ADD_INPUT(KeyNumPadFour);
		ADD_INPUT(KeyNumPadFive);
		ADD_INPUT(KeyNumPadSix);
		ADD_INPUT(KeyNumPadSeven);
		ADD_INPUT(KeyNumPadEight);
		ADD_INPUT(KeyNumPadNine);

		ADD_INPUT(KeyMultiply);
		ADD_INPUT(KeyAdd);
		ADD_INPUT(KeySubtract);
		ADD_INPUT(KeyDecimal);
		ADD_INPUT(KeyDivide);
	}

	void InputCenter::BindKey(const STRING& keyName, UI32 scanCode)
	{
		keyMappings[scanCode] = (KeyInputComponent*)componentMap[keyName];
	}

	InputComponent* InputCenter::GetComponent(const STRING& inputName)
	{
		return componentMap[inputName];
	}

	void InputCenter::ActivateKey(InputType type, UI32 scanCode)
	{
		keyMappings[scanCode]->Activate(1.0f, type);
	}

	void InputCenter::ActivateButton(InputType type, UI32 ID)
	{
		if (ID == 0)
			MouseButtonLeft.Activate(1.0f, type);
		else if (ID == 1)
			MouseButtonRight.Activate(1.0f, type);
		else if (ID == 2)
			MouseButtonMiddle.Activate(1.0f, type);
		else if (ID == 3)
			MouseButton0.Activate(1.0f, type);
		else if (ID == 4)
			MouseButton1.Activate(1.0f, type);
		else
			DMKErrorManager::logError("Invalid Button ID!");
	}

	void InputCenter::FrameBufferResized()
	{
		FrameBufferResizeEvent = true;
	}

	void InputCenter::ReasetAll()
	{
		MouseX.Reset();
		MouseY.Reset();
		MouseScrollUp.Reset();
		MouseScrollDown.Reset();
		MouseWheel.Reset();

		MouseButtonLeft.Reset();
		MouseButtonRight.Reset();
		MouseButtonMiddle.Reset();
		MouseButton0.Reset();
		MouseButton1.Reset();

		KeyLeft.Reset();
		KeyRight.Reset();
		KeyUp.Reset();
		KeyDown.Reset();

		KeyBackSpace.Reset();
		KeyTab.Reset();
		KeyEnter.Reset();
		KeyPause.Reset();

		KeyCapsLock.Reset();
		KeyEscape.Reset();
		KeySpaceBar.Reset();
		KeyPageUp.Reset();
		KeyPageDown.Reset();
		KeyEnd.Reset();
		KeyHome.Reset();

		KeyZero.Reset();
		KeyOne.Reset();
		KeyTwo.Reset();
		KeyThree.Reset();
		KeyFour.Reset();
		KeyFive.Reset();
		KeySix.Reset();
		KeySeven.Reset();
		KeyEight.Reset();
		KeyNine.Reset();

		KeyA.Reset();
		KeyB.Reset();
		KeyC.Reset();
		KeyD.Reset();
		KeyE.Reset();
		KeyF.Reset();
		KeyG.Reset();
		KeyH.Reset();
		KeyI.Reset();
		KeyJ.Reset();
		KeyK.Reset();
		KeyL.Reset();
		KeyM.Reset();
		KeyN.Reset();
		KeyO.Reset();
		KeyP.Reset();
		KeyQ.Reset();
		KeyR.Reset();
		KeyS.Reset();
		KeyT.Reset();
		KeyU.Reset();
		KeyV.Reset();
		KeyW.Reset();
		KeyX.Reset();
		KeyY.Reset();
		KeyZ.Reset();

		KeyF1.Reset();
		KeyF2.Reset();
		KeyF3.Reset();
		KeyF4.Reset();
		KeyF5.Reset();
		KeyF6.Reset();
		KeyF7.Reset();
		KeyF8.Reset();
		KeyF9.Reset();
		KeyF10.Reset();
		KeyF11.Reset();
		KeyF12.Reset();

		KeyNumLock.Reset();

		KeyScrollLock.Reset();

		KeyLeftShift.Reset();
		KeyRightShift.Reset();
		KeyLeftControl.Reset();
		KeyRightControl.Reset();
		KeyLeftAlt.Reset();
		KeyRightAlt.Reset();
		KeyLeftCommand.Reset();
		KeyRightCommand.Reset();

		KeySemicolon.Reset();
		KeyEqual.Reset();
		KeyComma.Reset();
		KeyUnderscore.Reset();
		KeyHyphen.Reset();
		KeyPeriod.Reset();
		KeySlash.Reset();
		KeyTilde.Reset();
		KeyLeftBracket.Reset();
		KeyBackslash.Reset();
		KeyRightBracket.Reset();
		KeyApostrophe.Reset();

		KeyAmpersand.Reset();
		KeyAsterix.Reset();
		KeyCaret.Reset();
		KeyColon.Reset();
		KeyDollar.Reset();
		KeyExclamation.Reset();
		KeyLeftParantheses.Reset();
		KeyRightParantheses.Reset();
		KeyQuote.Reset();

		KeyNumPadZero.Reset();
		KeyNumPadOne.Reset();
		KeyNumPadTwo.Reset();
		KeyNumPadThree.Reset();
		KeyNumPadFour.Reset();
		KeyNumPadFive.Reset();
		KeyNumPadSix.Reset();
		KeyNumPadSeven.Reset();
		KeyNumPadEight.Reset();
		KeyNumPadNine.Reset();

		KeyMultiply.Reset();
		KeyAdd.Reset();
		KeySubtract.Reset();
		KeyDecimal.Reset();
		KeyDivide.Reset();
	}

	Vector2F InputCenter::GetMousePosition()
	{
		return Vector2F(MouseX, MouseY);
	}
}