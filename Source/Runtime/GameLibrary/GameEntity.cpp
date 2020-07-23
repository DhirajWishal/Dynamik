// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "GameEntity.h"

namespace Dynamik
{
	void DMKGameEntity::setupCurrentLevel(DMKLevelComponent* pCurrentLevel)
	{
		this->pCurrentLevel = pCurrentLevel;
	}
	
	void DMKGameEntity::setupCamera(const DMKCameraModule* pCameraModule)
	{
		if (isCameraAvailable)
		{
			DMK_ERROR("Camera Module is already attached!");
			return;
		}

		this->pCameraModule = Cast<DMKCameraModule*>(pCameraModule);
		isCameraAvailable = true;
	}
}
