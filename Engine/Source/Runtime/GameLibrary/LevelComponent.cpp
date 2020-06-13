// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "LevelComponent.h"

namespace Dynamik
{
	void DMKLevelComponent::initializeCameraModule()
	{
		for (auto _entity : myEntities)
			_entity->setupCamera(playerObject->getCameraModule());
	}
}
