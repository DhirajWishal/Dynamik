// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "MouseButtonEventListener.h"

namespace Dynamik
{
	void DMKMouseButtonEventListener::onEvent(I32 button, I32 action, I32 mods)
	{
		DMK_INFO("On Button Event: " + std::to_string(button) + ((action == DMK_PRESS) ? " Button Press" : " Button Release"));
	}
}
