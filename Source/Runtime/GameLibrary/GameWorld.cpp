// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "GameWorld.h"

#include "Utilities/MeshFactory.h"
#include "Importer/Asset/MeshImporter.h"
#include "Entities/PlayerEntity.h"

void DMKGameWorld::setupPlayerConstrols(DMKPlayerEntity* pPlayerEntity)
{
	pPlayerEntity->setupPlayerControls(DMKSystemLocator::getSystem<DMKPlayerController>());
}

void DMKGameWorld::submitStaticModelToRenderer(DMKStaticModelEntity* pStaticModel, UI32* pProgressMeter)
{
	DMKSystemLocator::getSystem<DMKRenderer>()->submitStaticModelEntityCMD(pStaticModel, pProgressMeter);
}

void DMKGameWorld::removeStaticModelFromRenderer(DMKStaticModelEntity* pStaticModel)
{
	DMKSystemLocator::getSystem<DMKRenderer>()->removeStaticModelEntityCMD(pStaticModel);
}

void DMKGameWorld::submitAnimatedModelToRenderer(DMKAnimatedModelEntity* pAnimatedModel, UI32* pProgressMeter)
{
	DMKSystemLocator::getSystem<DMKRenderer>()->submitAnimatedModelEntityCMD(pAnimatedModel, pProgressMeter);
}

void DMKGameWorld::removeAnimatedModelFromRenderer(DMKAnimatedModelEntity* pAnimatedModel)
{
	DMKSystemLocator::getSystem<DMKRenderer>()->removeAnimatedModelEntityCMD(pAnimatedModel);
}

void DMKGameWorld::submitEnvironmentToRenderer(DMKEnvironmentEntity* pEnvironment, UI32* pProgressMeter)
{
	DMKSystemLocator::getSystem<DMKRenderer>()->initializeEnvironmentEntityCMD(pEnvironment, pProgressMeter);
}

void DMKGameWorld::removeEnvironmentFromRenderer(DMKEnvironmentEntity* pEnvironment)
{
	DMKSystemLocator::getSystem<DMKRenderer>()->removeEnvironmentMapEntityCMD(pEnvironment);
}

void DMKGameWorld::addLightComponent(DMKGameWorldLightComponent component)
{
	globalLightComponents.pushBack(component);
}
