// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "GameWorld.h"

#include "Utilities/MeshFactory.h"
#include "Importer/Asset/MeshImporter.h"
#include "Entities/PlayerEntity.h"

namespace Dynamik
{
	void DMKGameWorld::setupPlayerConstrols(DMKPlayerEntity* pPlayerEntity)
	{
		pPlayerEntity->setupPlayerControls(DMKSystemLocator::getSystem<DMKPlayerController>());
	}

	void DMKGameWorld::submitStaticModelToRenderer(DMKStaticModelEntity* pStaticModel)
	{
		DMKSystemLocator::getSystem<DMKRenderer>()->submitStaticModelEntityCMD(pStaticModel);
	}

	void DMKGameWorld::submitAnimatedModelToRenderer(DMKAnimatedModelEntity* pAnimatedModel)
	{
		DMKSystemLocator::getSystem<DMKRenderer>()->submitAnimatedModelEntityCMD(pAnimatedModel);
	}

	void DMKGameWorld::submitEnvironmentToRenderer(DMKEnvironmentEntity* pEnvironment)
	{
		if (!pEnvironment->skyBoxMesh.vertexBuffer.byteSize() || !pEnvironment->skyBoxMesh.indexBuffer.byteSize())
			pEnvironment->onInitializeEnvironment();

		DMKSystemLocator::getSystem<DMKRenderer>()->initializeEnvironmentEntityCMD(pEnvironment);
	}
	
	void DMKGameWorld::addLightComponent(DMKGameWorldLightComponent component)
	{
		globalLightComponents.pushBack(component);
	}
}