// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "DefaultWorld.h"
#include "../Entities/Player.h"

void DefaultWorld::initialize()
{
	/* Add the player entity. */
	addEntity<Player>();
}

void DefaultWorld::onInitializeEntities()
{
	/* Initialize the player entity */
	getEntity<Player>()->onInitializePlayer();

	/* Setup player controls */
	setupPlayerConstrols<Player>();
}

void DefaultWorld::onUpdate(const F32 timeStep)
{
}

void DefaultWorld::onMainWindowResize(DMKExtent2D newSize)
{
}
