// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "GameModule.h"

#include "Importer/Asset/MeshImporter.h"

namespace Dynamik
{
	DMKGameModule::DMKGameModule()
	{
		pCurrentGameWorld = nullptr;
		playerObject = nullptr;
	}

	void DMKGameModule::updateEntities(F32 timeStep)
	{
		pCurrentGameWorld->onUpdate(timeStep);
	}

	DMKCameraModule* DMKGameModule::getCameraModule() const
	{
		return playerObject->getCameraModule();
	}

	DMKPlayerObject* DMKGameModule::createHollowPlayerObject()
	{
		playerObject = StaticAllocator<DMKPlayerObject>::allocate().get();
		return playerObject;
	}
}
