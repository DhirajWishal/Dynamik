// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "GameModule.h"
#include "GameEntity.h"

#include "Importer/Asset/MeshImporter.h"

namespace Dynamik
{
	DMKGameModule::DMKGameModule()
	{
		pCurrentGameWorld = nullptr;
		playerObject = nullptr;
	}

	void DMKGameModule::addEntity(DMKGameEntity* pEntity)
	{
		pEntities.pushBack(pEntity);
	}

	void DMKGameModule::updateEntities(F32 timeStep)
	{
		for (auto entity : pEntities)
			entity->onUpdate(timeStep);

		if (pCurrentGameWorld)
		{
			for (auto entity : pCurrentGameWorld->entities)
				entity->onUpdate(timeStep);

			if (pCurrentGameWorld->pEnvironmentMap)
				pCurrentGameWorld->pEnvironmentMap->onUpdate(timeStep);
		}
	}

	DMKGameEntity* DMKGameModule::createHollowEntity()
	{
		pEntities.pushBack(StaticAllocator<DMKGameEntity>::allocateInit(DMKGameEntity()));
		return Cast<DMKGameEntity*>(pEntities.location(-1));
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
