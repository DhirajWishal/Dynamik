// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "InputCenter.h"
#include "Core/ErrorHandler/Logger.h"

namespace DMK
{
	namespace Inputs
	{
		void InputCenter::ActivateKey(UI32 scanCode, ButtonInputState state)
		{
			for (UI32 i = 5; i < 113; i++)
			{
				if ((reinterpret_cast<KeyInput*>(this) + i)->GetID() == scanCode)
				{
					(reinterpret_cast<KeyInput*>(this) + i)->SetState(state);
					return;
				}
			}

			Logger::LogError(TEXT("Invalid or unregistered scan code!"));
		}

		void InputCenter::ActivateButton(UI32 scanCode, ButtonInputState state)
		{
			for (UI32 i = 0; i < 5; i++)
			{
				if ((reinterpret_cast<MouseButtonInput*>(this) + i)->GetID() == scanCode)
				{
					(reinterpret_cast<MouseButtonInput*>(this) + i)->SetState(state);
					return;
				}
			}

			Logger::LogError(TEXT("Invalid or unregistered scan code!"));
		}

		MousePointerPosition InputCenter::GetMousePointerPosition() const
		{
			return MousePointerPosition(MousePositionX, MousePositionY);
		}
	}
}
