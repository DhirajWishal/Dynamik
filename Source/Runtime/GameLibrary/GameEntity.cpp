// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "GameEntity.h"

namespace Dynamik
{
	void DMKGameEntity::setupCurrentModule(DMKGameModule* pCurrentModule)
	{
		this->pCurrentModule = pCurrentModule;
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

	void DMKGameEntity::addInstance(const STRING& name, const Vector3F& position, const Quaternion& rotation, const Vector3F& scale)
	{
		instances.pushBack(DMKGameEntityInstance(name, position, rotation, scale, this));
	}

	DMKGameEntityInstance* DMKGameEntity::getInstance(I64 index)
	{
		return Cast<DMKGameEntityInstance*>(instances.location(index));
	}
}
