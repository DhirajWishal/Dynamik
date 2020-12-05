// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GAME_ENTITY_H
#define _DYNAMIK_GAME_ENTITY_H

#include "Core/Macros/Global.h"
#include "Core/Maths/Vector/Vector3.h"

#include "Graphics/Components/StaticModel.h"

namespace DMK
{
	namespace GameLibrary
	{
		class GameModule;

		/*
		 * Game Entity object.
		 * This object defines object instances in the game world which possesses a behavior.
		 *
		 * Entities are spawned to the game world mainly by the game module. The entities can also spawn child
		 * entities and the ownership of them are managed by the entities.
		 */
		class GameEntity {
		public:
			GameEntity() {}
			virtual ~GameEntity() {}

		public:
			/**
			 * This method is called once the entity is spawned in the game world.
			 *
			 * @param pGameModule: The game module which spawned the entity.
			 * @param location: The location in the game world to which the entity is spawned to.
			 */
			virtual void OnSpawn(GameModule* pGameModule, const Vector3& location) {}

			/**
			 * This method is called when a game entity spawns a child entity.
			 *
			 * @param pParentEntity: The entity which spawned the child entity.
			 */
			virtual void OnSpawn(GameEntity* pParentEntity) {}

			/**
			 * This method is called once every new iteration.
			 *
			 * @param timeStep: The time between the last iteration and this.
			 */
			virtual void OnUpdate(const float timeStep) {}

			/**
			 * This method is called once a game entity is despawned from a game world.
			 */
			virtual void OnDespawn() {}

			/* Static Model */
		public:
			/**
			 * This method is called when a static model is initialized.
			 * This will only work with the static models created with this entity.
			 *
			 * @param pStaticModel: The static model which is to be initialized.
			 */
			virtual void OnInitialize(Graphics::StaticModel* pStaticModel) {}

			/**
			 * This method is called once a static model is being updated.
			 *
			 * @param pStaticModel: The static model pointer.
			 */
			virtual void OnUpdate(Graphics::StaticModel* pStaticModel, const float timeStep) {}

			/**
			 * This method is called once a static model is terminated from the graphics queue.
			 *
			 * @param pStaticModel: The static model entity pointer.
			 */
			virtual void OnTerminate(Graphics::StaticModel* pStaticModel) {}
		};
	}
}

#endif // !_DYNAMIK_GAME_ENTITY_H
