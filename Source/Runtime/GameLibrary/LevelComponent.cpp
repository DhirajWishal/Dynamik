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

	DMKGameEntity* DMKLevelComponent::createHollowEntity()
	{
		pEntities.pushBack(StaticAllocator<DMKGameEntity>::allocateInit(DMKGameEntity()));
		return Cast<DMKGameEntity*>(pEntities.location(-1));
	}
		
	DMKPlayerObject* DMKLevelComponent::createHollowPlayerObject()
	{
		playerObject = StaticAllocator<DMKPlayerObject>::allocate().get();
		return playerObject;
	}
}
