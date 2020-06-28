// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "KeyEventListener.h"

namespace Dynamik
{
	void DMKKeyEventListener::onEvent(I32 keyCode, I32 action, I32 mods, I32 scanCode)
	{
		DMK_INFO("Key Event: " + std::to_string(keyCode) + ((action == DMK_PRESS) ? " Button Press" : " Button Release"));
	}
}