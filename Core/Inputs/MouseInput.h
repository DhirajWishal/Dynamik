// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "ButtonInput.h"

namespace DMK
{
	namespace Inputs
	{
		struct MousePointerPosition {
			MousePointerPosition() = default;
			MousePointerPosition(float xOffset, float yOffset) : mXOffset(xOffset), mYOffset(yOffset) {}

			float mXOffset = 0.0f;
			float mYOffset = 0.0f;
		};

		/**
		 * Mouse Button Input object.
		 */
		class MouseButtonInput : public ButtonInput {
		public:
			MouseButtonInput() {}
			~MouseButtonInput() {}
		};
	}
}