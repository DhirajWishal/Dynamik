// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "LevelComponent.h"

#include "Importer/Asset/MeshImporter.h"

namespace Dynamik
{
	DMKLevelComponent::DMKLevelComponent()
	{
		pCurrentGameWorld = nullptr;
		playerObject = nullptr;
	}

	void DMKLevelComponent::addEntity(DMKGameEntity* pEntity)
	{
		pEntities.pushBack(pEntity);
	}

	void DMKLevelComponent::updateEntities(F32 timeStep)
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

	DMKGameEntity* DMKLevelComponent::createHollowEntity()
	{
		pEntities.pushBack(StaticAllocator<DMKGameEntity>::allocateInit(DMKGameEntity()));
		return Cast<DMKGameEntity*>(pEntities.location(-1));
	}

	DMKCameraModule* DMKLevelComponent::getCameraModule() const
	{
		return playerObject->getCameraModule();
	}

	DMKPlayerObject* DMKLevelComponent::createHollowPlayerObject()
	{
		playerObject = StaticAllocator<DMKPlayerObject>::allocate().get();
		return playerObject;
	}
}
