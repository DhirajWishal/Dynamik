// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_LEVEL_COMPONENT_H
#define _DYNAMIK_LEVEL_COMPONENT_H

/*
 Dynamik Level Component.

 Author:	Dhiraj Wishal
 Date:		15/05/2020
*/
#include "GameEntity.h"
#include "GameMechanics.h"
#include "PlayerObject.h"
#include "EnvironmentMap.h"

#include "Core/Macros/Global.h"
#include "Core/Types/Array.h"

namespace Dynamik
{
	/*
	 Dynamik Level Component act as a level for the Dynamik Engine.
	 All the scenes are loaded and presented as a level to the engine. Multiple levels can be loaded to the
	 memory at a given 

	 By default, this class can be used as an internal level component.
	*/
	class DMK_API DMKLevelComponent {
	public:
		DMKLevelComponent()  {}
		virtual ~DMKLevelComponent() {}

		virtual void onLoad() {}
		virtual void initializeComponents() {}
		virtual void onUnoad() {}

		/* Game Assets */
		ARRAY<DMKGameEntity*> myEntities;

		/* Game Mechanics */
		ARRAY<DMKGameMechanics*> myMechanics;

		/* Player Object */
		DMKPlayerObject* playerObject;

		/* Environment Map */
		DMKEnvironmentMap* environmentMap;

		/* Additional Components */
		DMKComponentManager sceneComponentManager;

	public:		/* Constant methods */
		void initializeCameraModule();

	protected:	/* Helper methods */
		/*
		 Create a basic hollow entity.
		 These entities does not have any functionalities and are basically empty.
		 By default, this adds the entity to the entity array.
		*/
		DMKGameEntity* createHollowEntity();

		/*
		 Create static entity.
		 This entity contains a static mesh without any other functionality attached to it by default.
		 By default, this adds the entity to the entity array.
		*/
		DMKGameEntity* createStaticEntity(const STRING& assetPath);

		/*
		 Create static entity.
		 This entity contains a static mesh without any other functionality attached to it by default.
		 By default, this adds the entity to the entity array.
		*/
		DMKGameEntity* createStaticEntity(const STRING& assetPath, const DMKVertexLayout& vertexLayout);
	};
}

#endif // !_DYNAMIK_LEVEL_COMPONENT_H
