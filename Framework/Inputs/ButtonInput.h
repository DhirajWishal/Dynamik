// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Types/DataTypes.h"

namespace DMK
{
	namespace Inputs
	{
		enum class ButtonInputState : UI8 {
			PRESSED, RELEASED, ON_REPEAT
		};

		class ButtonInput {
		public:
			ButtonInput() {}
			virtual ~ButtonInput() {}

			void Register(UI32 scanCode) { mButtonID = scanCode; }
			UI32 GetID() const { return mButtonID; }

			void SetState(ButtonInputState state) { mState = state; }
			ButtonInputState GetState() const { return mState; }

			bool IsPressed() const { return mState == ButtonInputState::PRESSED; }
			bool IsReleased() const { return mState == ButtonInputState::RELEASED; }
			bool IsOnRepeat() const { return mState == ButtonInputState::ON_REPEAT; }

			UI32 mButtonID = 0;
			ButtonInputState mState = ButtonInputState::RELEASED;
		};
	}
}