// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "GameWorld.h"

#include "Utilities/MeshFactory.h"
#include "Importer/Asset/MeshImporter.h"

namespace Dynamik
{
	void DMKGameWorld::setPlayerObject(const DMKPlayerObject* pPlayerObject)
	{
		this->pPlayerObject = Cast<DMKPlayerObject*>(pPlayerObject);
	}

	DMKPlayerObject* DMKGameWorld::getPlayerObject() const
	{
		return pPlayerObject;
	}

	void DMKGameWorld::setEnvironmentMap(DMKEnvironmentMap* pEnvironment)
	{
		pEnvironmentMap = pEnvironment;
	}

	void DMKGameWorld::loadEnvironmentMap(ARRAY<STRING> texturePaths)
	{
		pEnvironmentMap = StaticAllocator<DMKEnvironmentMap>::allocate();
		pEnvironmentMap->skyBox = DMKMeshFactory::createSkyBox(texturePaths);
	}

	void DMKGameWorld::loadEnvironmentMap(STRING texturePath)
	{
	}

	void DMKGameWorld::addLightComponent(DMKGameWorldLightComponent component)
	{
		globalLightComponents.pushBack(component);
	}

	DMKEnvironmentMap* DMKGameWorld::createHollowEnvironment()
	{
		return StaticAllocator<DMKEnvironmentMap>::allocate();
	}
}