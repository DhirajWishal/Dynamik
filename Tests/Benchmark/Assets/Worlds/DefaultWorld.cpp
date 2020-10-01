// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "DefaultWorld.h"

#include "../Entities/Player.h"
#include "../Entities/OceanEnv.h"
#include "../Entities/VenusModel.h"
#include "../Entities/CerberusModel.h"

#include "GameLibrary/Utilities/EntityFactory.h"

void DefaultWorld::initialize()
{
	/* Add the player entity. */
	auto player = addEntity<Player>();

	/* Add the ocean environment entity. */
	auto oceanEntity = addEntity<OceanEnv>();
	oceanEntity->setCameraModule(player->getCameraModule());

	/* Add the Venus model entity */
	auto venusModel = addEntity<VenusModel>();
	venusModel->setCameraModule(player->getCameraModule());

	/* Add the Cerberus model entity */
	auto cerberusModel = addEntity<CerberusModel>();
	cerberusModel->setCameraModule(player->getCameraModule());

	/* Load a pure static entity. */
	addEntity<DMKStaticModelEntity>(
		Cast<const DMKStaticModelEntity&>(
			EntityFactory::CreateStaticEntity(
				TEXT("E:\\Dynamik\\Game Repository\\assets\\assets\\moon\\Moon 2K.fbx"),
				{ "E:\\Dynamik\\Game Repository\\assets\\assets\\moon\\Diffuse_2K.png" },
				player->getCameraModule())
			)
		);
}

void DefaultWorld::onUpdate(const float timeStep)
{
	auto playerObject = getEntity<Player>();

	if (!areEntitiesInitialized)
	{
		UI32 progress = 0;

		/* Initialize the player entity */
		playerObject->onInitializePlayer();

		/* Setup player controls */
		setupPlayerConstrols(getEntity<Player>());

		/* Submit the environment map entity. */
		submitEnvironmentToRenderer(getEntity<OceanEnv>(), &progress);
		while (progress != 12);
		getEntity<OceanEnv>()->clearEnvironmentMap();
		progress = 0;

		/* Submit the Venus model to the renderer. */
		//submitStaticModelToRenderer(getEntity<VenusModel>());

		/* submit the Cerberus model to the renderer. */
		submitStaticModelToRenderer(getEntity<CerberusModel>(), &progress);
		while (progress != 7);
		getEntity<CerberusModel>()->clearStaticModel();

		/* load the pure static entity. */
		//submitStaticModelToRenderer(getEntity<DMKStaticModelEntity>());
		
		areEntitiesInitialized = true;
	}

	static bool refresh = false;

	if (DMKEventPool::MouseButtonLeft.isPressed())
	{
		playerObject->processMouseControl(DMKEventPool::getMousePosition(), 0.1f, refresh, true);
		refresh = false;
	}

	if (DMKEventPool::MouseButtonLeft.isReleased())
		refresh = true;

	if (DMKEventPool::KeyUp.isPressed() || DMKEventPool::KeyUp.isOnRepeat())
		playerObject->addUpVector(0.001f);

	if (DMKEventPool::KeyDown.isPressed() || DMKEventPool::KeyDown.isOnRepeat())
		playerObject->addDownVector(0.001f);

	if (DMKEventPool::KeyX.isPressed())
		removeStaticModelFromRenderer(getEntity<CerberusModel>());

	if (DMKEventPool::KeyY.isPressed())
		submitStaticModelToRenderer(getEntity<CerberusModel>());

	playerObject->updateCamera();
}

void DefaultWorld::onMainWindowResize(DMKExtent2D newSize)
{
	getEntity<Player>()->setCameraViewPort(newSize);
}
