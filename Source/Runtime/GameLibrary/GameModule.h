// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_LEVEL_COMPONENT_H
#define _DYNAMIK_LEVEL_COMPONENT_H

#include "GameMechanics.h"
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
	class DMK_API DMKGameServer;

	/*
	 Dynamik Game Module act as a level for the Dynamik Engine.
	 Level component directly translates to a level in the game. A level can also be interpreted as a player.

	 By default, this class can be used as an internal level component.
	*/
	class DMK_API DMKGameModule {
	public:
		DMKGameModule();
		virtual ~DMKGameModule() {}

		virtual void onLoad() {}
		virtual void onInitialize() {}
		virtual void onUpdate(const DMKEventPool* pEventPool) {}
		virtual void onUnoad() {}

		/* 
		 On submit data to systems method.
		 Users are allowed to create their own components but are required to send their data to the relevant systems
		 using the primitives which those systems require. 
		 For example, the rendering engine expects mesh objects to 
		 create a proper renderable object. For this, all the user defined renderable components must submit their 
		 mesh objects via this method. As an optimization, submit all the mesh objects in one command.

		 These custom made components are allowed to be added to an entity using the component system.

		 This method will be called after submitting all of the internally defined components.
		*/
		virtual void onSubmitDataToSystems() {}

	public:		/* Level Data Store */
		/*
		 Pointer to the current (active) game world.
		 A level can cycle through multiple game worlds at times.
		*/
		DMKGameWorld* pCurrentGameWorld = nullptr;

		/*
		 Get the current game world.
		*/
		DMKGameWorld* getCurrentGameWorld() const { return pCurrentGameWorld; }

		/*
		 Update all the entities in the game world.

		 @param timeStep: The time step of the current call.
		*/
		void updateEntities(F32 timeStep);

		/*
		 Allocates a user defined Game World and initializes it.

		 @param world: Initialization values.
		 @tparam WORLD: The world type.
		*/
		template<class WORLD>
		DMK_FORCEINLINE void createUserGameWorld(const WORLD& world = DefaultWorld())
		{
			pCurrentGameWorld = StaticAllocator<WORLD>::allocate();
			pCurrentGameWorld->initialize();
		}

		/* Game Mechanics */
		ARRAY<DMKGameMechanics*> gameMechanics;

		/*
		 Get the game server which the module is currently active.
		*/
		DMKGameServer* getGameServer() const { return this->pServer; }

		/*
		 Set the game server which the module is begin played on. 

		 @param pServer: The pointer to the game server.
		*/
		void setGameServer(const DMKGameServer* pServer) { this->pServer = Cast<DMKGameServer*>(pServer); }

		/* Global game data */
	public:
		/* The current score of the game */
		F32 score = 0.0f;

		/*
		 Set the score of the game.

		 @param score: The score to be set.
		*/
		void setScore(const F32 score) { this->score = score; }

		/*
		 Get the current score of the game.
		*/
		const F32 getScore() const { score; }

		DMKGameServer* pServer = nullptr;
	};
}

#endif // !_DYNAMIK_LEVEL_COMPONENT_H
