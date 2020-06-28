// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "MouseScrollEventListener.h"

namespace Dynamik
{
	void DMKMouseScrollEventListener::onEvent(D64 xOffset, D64 yOffset)
	{
		DMK_INFO("On Mouse Scroll Event: X(" + std::to_string(xOffset) + ") Y(" + std::to_string(yOffset) + ")");
	}
}
