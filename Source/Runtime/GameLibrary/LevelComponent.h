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
#include "GameWorld.h"
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
		/*
		 Pointer to the current (active) game world.
		 A level can cycle through multiple game worlds at times.
		*/
		DMKGameWorld* pCurrentGameWorld = nullptr;

		/*
		 Allocates a user defined Game World and initializes it.
		*/
		template<class WORLD>
		DMK_FORCEINLINE void createUserGameWorld()
		{
			pCurrentGameWorld = StaticAllocator<WORLD>::allocate();
		}

		/* Game Mechanics */
		ARRAY<DMKGameMechanics*> gameMechanics;

		/* Player Object */
		DMKPlayerObject* playerObject = nullptr;

		/* Environment Map */
		DMKEnvironmentMap* environmentMap = nullptr;

		/* Additional Components */
		DMKComponentManager sceneComponentManager;

	protected:	/* Helper methods */
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
	};
}

#endif // !_DYNAMIK_LEVEL_COMPONENT_H
