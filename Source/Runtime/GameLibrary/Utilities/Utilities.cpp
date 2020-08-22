// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "Utilities.h"

namespace Dynamik
{
	DMKRenderer* GetRenderer()
	{
		return DMKSystemLocator::getSystem<DMKRenderer>();
	}
	
	DMKPlayerController* GetPlayerController()
	{
		return DMKSystemLocator::getSystem<DMKPlayerController>();
	}
}
