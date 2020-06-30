// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "PlayerObject.h"
#include "Core/Math/MathFunctions.h"

namespace Dynamik
{
	void DMKPlayerObject::setCameraPosition(const VEC3& position)
	{
		if (!cameraModule)
		{
			DMK_ERROR("Camera Module is not initialized!");
			return;
		}

		cameraModule->position = position;
	}
}