// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "DefaultWorld.h"
#include "../Entities/Player.h"
#include "../Entities/OceanEnv.h"

void DefaultWorld::initialize()
{
	/* Add the player entity. */
	addEntity<Player>();

	/* Add the ocean environment entity. */
	auto oceanEntity = addEntity<OceanEnv>();
	oceanEntity->setCameraModule(getEntity<Player>()->getCameraModule());
}

void DefaultWorld::onInitializeEntities()
{
	/* Initialize the player entity */
	getEntity<Player>()->onInitializePlayer();

	/* Setup player controls */
	setupPlayerConstrols<Player>();

	submitStaticModelToRenderer<Player>(0);
}

void DefaultWorld::onUpdate(const F32 timeStep)
{
}

void DefaultWorld::onMainWindowResize(DMKExtent2D newSize)
{
}
