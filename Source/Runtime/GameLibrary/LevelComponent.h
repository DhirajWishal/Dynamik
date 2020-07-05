// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_LEVEL_COMPONENT_H
#define _DYNAMIK_LEVEL_COMPONENT_H

/*
 Dynamik Level Component.
*/
#include "GameEntity.h"
#include "GameMechanics.h"
#include "PlayerObject.h"
#include "EnvironmentMap.h"
#include "Utilities/MeshFactory.h"

#include "Core/Macros/Global.h"
#include "Core/Types/Utilities.h"
#include "Core/Types/Array.h"
#include "Core/FileSystem/FileSystem.h"
#include "Events/EventPool.h"
#include "Mechanics/PlayerController.h"

namespace Dynamik
{

	/*
	 Dynamik Level Component act as a level for the Dynamik Engine.
	 Level component directly translates to a level in the game. A level can also be interpreted as a player.

	 By default, this class can be used as an internal level component.
	*/
	class DMK_API DMKLevelComponent {
	public:
		DMKLevelComponent()  {}
		virtual ~DMKLevelComponent() {}

		virtual void onLoad() {}
		virtual void initializeComponents() {}
		virtual void setupPlayerControls(DMKPlayerController* pController) {}
		virtual void setupCameraControls() {}
		virtual void onUpdate(const DMKEventPool* pEventPool) {}
		virtual void onUnoad() {}

	public:		/* Player Methods */
		virtual void onPlayerMoveForward() {}
		virtual void onPlayerMoveBackward() {}
		virtual void onPlayerMoveLeft() {}
		virtual void onPlayerMoveRight() {}

		virtual void onPlayerJump() {}
		virtual void onPlayerCrouch() {}
		virtual void onPlayerSprint() {}
		virtual void onPlayerSlide() {}

		virtual void onPlayerAim() {}
		virtual void onPlayerTrigger() {}
		virtual void onPlayerReload() {}
		virtual void onPlayerLookAt() {}	/* eg: Looking at a scene. */
		virtual void onPlayerView() {}	/* eg: Looking at a gun. */

		VEC3 getPlayerPosition();

	public:		/* Level Data Store */

		/* Game Assets */
		ARRAY<DMKGameEntity*> entities;

		/* Game Mechanics */
		ARRAY<DMKGameMechanics*> gameMechanics;

		/* Player Object */
		DMKPlayerObject* playerObject = nullptr;

		/* Environment Map */
		DMKEnvironmentMap* environmentMap = nullptr;

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

		/* TEMPLATED
		 Create user defined entity.
		 This creates a user defined entity, adds it to the entity list and returns its address.

		 @tparam ENTITY: The user defined entity
		*/
		template<class ENTITY>
		DMK_FORCEINLINE DMKGameEntity* createUserEntity()
		{
			DMKGameEntity* entity = Cast<DMKGameEntity*>(StaticAllocator<ENTITY>::allocate().get());

			entities.pushBack(entity);
			return entity;
		}

		/*
		 Add an entity to the entity array.

		 @param pEntity: Pointer to the entity.
		*/
		void addEntity(DMKGameEntity* pEntity);

		/*
		 Create an empty player object.
		*/
		DMKPlayerObject* createHollowPlayerObject();

		/*
		 Create a user defined player object.
		*/
		template<class PLAYER>
		DMK_FORCEINLINE DMKPlayerObject* createUserPlayer()
		{
			playerObject = Cast<DMKPlayerObject*>(StaticAllocator<PLAYER>::allocate().get());
			return playerObject;
		}

		/*
		 Create an empty environment.
		*/
		DMKEnvironmentMap* createHollowEnvironment();
	};
}

#endif // !_DYNAMIK_LEVEL_COMPONENT_H
