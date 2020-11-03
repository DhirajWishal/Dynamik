// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GAME_MODULE_H
#define _DYNAMIK_GAME_MODULE_H

#include "Core/ErrorHandler/Logger.h"

#include "GameEntity.h"
#include "GameWorld.h"

#include "Graphics/GraphicsComponent.h"

#include <type_traits>

namespace DMK
{
	namespace GameLibrary
	{
		/**
		 * Game Module for the Dynamik Engine.
		 * This object contains the game logic and the game world state.
		 *
		 * Components of the game world are loaded as entities just like with the game characters. These entities
		 * are static and does not contain any functionalities.
		 *
		 * Game modules work as a network in the engine. Once a module or a level is completed, the completed level
		 * loads the next level. To make the transition seamless, you can load the next module to the memory and
		 * submit the current world state to the next level so the actual components will not be loaded again.
		 */
		class GameModule : public GameComponent, public GameWorld {
		public:
			/**
			 * Default constructor.
			 */
			GameModule() {}

			/**
			 * Default destructor.
			 */
			virtual ~GameModule() { DespawnAllEntities(); }

			// User defined.
		public:
			/**
			 * This method is called when the game module is switched to another. Meaning that this will be the
			 * method which resembles the On Initialize.
			 *
			 * @param pParentModule: The module which called the transition.
			 */
			virtual void OnModuleTransition(GameModule* pParentModule) {}

			/**
			 * This method is called prior to loading the next module.
			 */
			virtual void OnExit() {}

			// Utilities.
		public:
			/**
			 * Spawn an entity to the game world state.
			 *
			 * @param location: The location in the game world which the entity is spawned to.
			 * @param initData: The data to be initialized with. Default is Entity().
			 * @tparam Entity: The entity type.
			 * @return: The pointer to the created entity.
			 */
			template<class Entity>
			DMK_FORCEINLINE Entity* SpawnEntity(const Vector3& location, const Entity& initData = Entity())
			{
				// Check if the entity is inherited from the GameEntity object.
				if constexpr (!std::is_base_of<GameEntity, Entity>::value)
				{
					Logger::LogError(TEXT("The entity type submitted to spawn is not a derived class of the GameEntity object! Dynamik Engine only accepts entities that are a base class of GameEntity."));
					return nullptr;
				}

				// Add the entity to the world state.
				Entity* pEntity = AddEntity<Entity>(initData);

				// Add the entity to the update list.
				AddEntityToUpdateList(pEntity, typeid(Entity).name());

				// Call the on spawn method.
				pEntity->OnSpawn(location);

				// Check if the entity contains graphic component entities.
				if constexpr (std::is_base_of<Graphics::GraphicsComponent, Entity>::value)
				{
					// TODO
					// Submit the entity to the graphics engine to be initialized.
				}

				/** TODO
				 * Submit the entity to the audio engine to be initialized.
				 * Submit the entity to the physics engine to be initialized.
				 * Submit the entity to the input system to be initialized.
				 */

				 // Return the created entity pointer.
				return pEntity;
			}

			/**
			 * Despawn an entity from the game world using its index.
			 *
			 * @param index: The index of the entity.
			 * @tparam Entity: The entity type.
			 */
			template<class Entity>
			DMK_FORCEINLINE void DespawnEntity(UI64 index)
			{
				// Remove the entity from the update list.
				RemoveEntityFromUpdateList(typeid(Entity).name(), index);

				// Call the on despawn method.
				GetEntity<Entity>(index)->OnDespawn();

				// Remove the entity from the store.
				RemoveEntity<Entity>(index);
			}

			/**
			 * Load the next module.
			 * This method by default clears the world state prior to loading the next module.
			 *
			 * @param pNextModule: The next module to be loaded.
			 */
			void LoadNextModule(GameModule* pNextModule);

			/**
			 * Update all the entities spawned in the game world.
			 *
			 * @param timeStep: The time step of the current iteration.
			 */
			void UpdateEntities(float timeStep);

			/**
			 * Despawn all the spawned entities.
			 */
			void DespawnAllEntities();

		private:
			/**
			 * This method adds the entity to the update list where the entity will be updated in the given order.
			 *
			 * @param pEntity: The entity pointer.
			 * @param pEntityName: The type name of the entity.
			 */
			void AddEntityToUpdateList(GameEntity* pEntity, const char* pEntityName);

			/**
			 * Remove an entity from the update list using the entity type name.
			 *
			 * @param pEntityName: The type name of the entity.
			 * @param index: The index of the entity.
			 */
			void RemoveEntityFromUpdateList(const char* pEntityName, UI64 index);

			std::unordered_map<const char*, std::vector<GameEntity*>> updateList;	// The update list.
		};
	}
}

#endif // !_DYNAMIK_GAME_MODULE_H
