// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GAME_MODULE_H
#define _DYNAMIK_GAME_MODULE_H

#include "GameEntity.h"
#include "EntityStore/EntityStore.h"

namespace DMK
{
	namespace GameLibrary
	{
		/**
		 * Game module for the Dynamik Engine.
		 * This object represents a single level in a game and contains the main game logic.
		 */
		class GameModule : public EntityStore {
		public:
			GameModule() {}
			virtual ~GameModule() {}

			/**
			 * This method is called once a module is loaded.
			 *
			 * @param pParentModule: The old module which loaded this module.
			 */
			virtual void OnInitialize(GameModule* pParentModule) {}

		public:
			/**
			 * Spawn an entity to the game world.
			 * This method only accepts entities which are derived from the DMK::GameLibrary::GaemEntity class.
			 *
			 * @tparam Type: The type of the entity.
			 * @param location: The location in the game world to which the entity is being spawned.
			 * @param constructor: The data to be initialized with. Default is Type().
			 */
			template<class Type>
			Type* SpawnEntity(const Vector3& location, const Type& constructor = Type())
			{
				// Check if the entity is derived from the GameEntity class.
				static_assert(std::is_base_of<GameEntity, Type>::value,
					"The submitted entity is not derived from DMK::GameLibrary::GameEntity! "
					"Dynamik requires all the entities to be derived from the DMK::GameLibrary::GameEntity class.");

				// Register the entity.
				RegisterEntity<Type>();

				// Add eht entity to the container.
				auto pEntity = GetEntityContainerFast<Type>()->Add(constructor);

				// Call the OnSpawn method.
				pEntity->OnSpawn(this, location);

				// Return the created entity pointer.
				return pEntity;
			}

			/**
			 * Despawn an entity from the game world.
			 *
			 * @tparam Type: The type of the entity.
			 * @param index: The index of the entity which is to be despawned.
			 */
			template<class Type>
			void DespawnEntity(const UI64 index)
			{
				// Get the entity container.
				auto pEntityContainer = GetEntityContainer<Type>();

				// Check if the entity container is valid. Return if invalid.
				if (!pEntityContainer)
					return;

				// Get the required entity.
				auto pEntity = pEntityContainer->GetEntity(index);

				// Call the OnDespawn method.
				pEntity->OnDespawn();

				// Remove the entity.
				pEntityContainer->Remove(index);
			}

			/**
			 * Despawn an entity from the game world.
			 *
			 * @tparam Type: The type of the entity.
			 * @param pEntity: The entity pointer to be despawned.
			 */
			template<class Type>
			void DespawnEntity(Type* pEntity)
			{
				// Check if the entity pointer is valid.
				if (!pEntity)
				{
					Logger::LogError(TEXT("Submitted entity pointer is invalid!"));
					return;
				}

				// Call the OnDespawn method.
				pEntity->OnDespawn();

				// Get the entity container.
				auto pEntityContainer = GetEntityContainer<Type>();

				// Check if the entity container is valid. Return if invalid.
				if (!pEntityContainer)
					return;

				// Remove the entity.
				pEntityContainer->Remove(pEntity);
			}
		};
	}
}

#endif // !_DYNAMIK_GAME_MODULE_H
