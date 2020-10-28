// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GAME_LIBRARY_GAME_WORLD_H
#define _DYNAMIK_GAME_LIBRARY_GAME_WORLD_H

#include "Core/Macros/Global.h"
#include "GameLibrary/EntitySystem/EntityContainer.h"
#include <typeinfo>

namespace DMK
{
	namespace GameLibrary
	{
		/**
		 * Game World for the Dynamik Engine Game Library.
		 * This object is the base class for all the game components that use entities.
		 *
		 * In addition to entities, this object can store any type of data.
		 */
		class GameWorld {
		public:
			/**
			 * Game World State structure.
			 * This structure contains the actual game world data.
			 */
			struct GameWorldState {
				/**
				 * Default constructor.
				 */
				GameWorldState() = default;

				/**
				 * Move constructor for the world state.
				 *
				 * @param state: The state to be set.
				 */
				GameWorldState(GameWorldState&& state) noexcept : registeredEntities(std::move(state.registeredEntities)), entityContainers(std::move(state.entityContainers)) {}

				/**
				 * Move assignment operator.
				 *
				 * @param state: The state to be set.
				 */
				GameWorldState& operator=(GameWorldState&& state) noexcept
				{
					this->registeredEntities = std::move(state.registeredEntities);
					this->entityContainers = std::move(state.entityContainers);
				}

				std::vector<const char*> registeredEntities;	// Array storing all the registered entities.
				std::unordered_map<const char*, EntityContainerBase*> entityContainers;	// Map containing all the entity containers.
			};

		public:
			/**
			 * Default constructor.
			 */
			GameWorld() {}

			/**
			 * Default destructor.
			 */
			virtual ~GameWorld() { ClearAllEntities(); }

			/**
			 * Check if a entity is registered.
			 *
			 * @tparam Type> The type of the entity.
			 * @return: Boolean value.
			 */
			template<class Type>
			DMK_FORCEINLINE bool IsEntityRegistered() const
			{
				// Get the type name.
				const char* entityName = typeid(Type).name();

				// Iterate through the registered types to find if the type is already registered.
				auto itr = currentState.registeredEntities.begin();
				while (itr != currentState.registeredEntities.end())
				{
					if (*itr == entityName)
						return true;

					itr++;
				}

				// Return false if not found.
				return false;
			}

			/**
			 * Register a new entity to the store.
			 * If the entity is already registered, it does not do anything.
			 *
			 * @tparam Type: The type of the entity.
			 */
			template<class Type>
			DMK_FORCEINLINE void RegisterEntity()
			{
				// Check if the entity is already registered.
				if (IsEntityRegistered<Type>())
					return;

				// Get the entity name.
				const char* entityName = typeid(Type).name();

				// Create the container and add the name to the registered entity name list.
				currentState.entityContainers[entityName] = new EntityContainer<Type>();
				currentState.registeredEntities.push_back(std::move(entityName));
			}

			/**
			 * Get the entity container of a certain type.
			 *
			 * @tparam Type: The type of the entity.
			 * @return: The EntityContainer<Type> pointer.
			 */
			template<class Type>
			DMK_FORCEINLINE EntityContainer<Type>* GetEntityContainer()
			{
				// Check and register if the container is not available.
				RegisterEntity<Type>();

				// Return the casted container.
				return static_cast<EntityContainer<Type>*>(currentState.entityContainers[typeid(Type).name()]);
			}

			/**
			 * Add a entity to the entity container.
			 *
			 * @param data: The data to be added.
			 * @tparam Type: The type of the entity.
			 * @return: The created entity pointer.
			 */
			template<class Type>
			DMK_FORCEINLINE Type* AddEntity(const Type& data)
			{
				GetEntityContainer<Type>()->AddEntity(data);
				return GetEntityContainer<Type>()->GetEntity(GetEntityContainer<Type>()->Size() - 1);
			}

			/**
			 * Add a entity to the entity container.
			 * This also returns the created entity pointer.
			 *
			 * @param data: The data to be added.
			 * @tparam Type: The type of the entity.
			 * @return: The created entity pointer.
			 */
			template<class Type>
			DMK_FORCEINLINE Type* AddEntity(Type&& data)
			{
				GetEntityContainer<Type>()->AddEntity(std::move(data));
				return GetEntityContainer<Type>()->GetEntity(GetEntityContainer<Type>()->Size() - 1);
			}

			/**
			 * Get a entity from the entity container.
			 *
			 * @param index: The index of the entity.
			 * @tparam Type: The entity type.
			 * @return: The entity pointer.
			 */
			template<class Type>
			DMK_FORCEINLINE Type* GetEntity(UI64 index)
			{
				return GetEntityContainer<Type>()->GetEntity(index);
			}

			/**
			 * Get the number of entities stored in a given container.
			 *
			 * @tparam Type: The type of the entity.
			 * @return: Unsigned 64 bit integer.
			 */
			template<class Type>
			DMK_FORCEINLINE UI64 GetEntityCount()
			{
				return GetEntityContainer<Type>()->Size();
			}

			/**
			 * Remove a entity from a given index.
			 *
			 * @param index: The index of the entity to be removed.
			 * @tparam Type: The type of the entity.
			 */
			template<class Type>
			DMK_FORCEINLINE void RemoveEntity(UI64 index)
			{
				GetEntityContainer<Type>()->Remove(index);
			}

		public:
			/**
			 * Get all the registered entity names.
			 *
			 * @return: std::vector<std::string> object.
			 */
			DMK_FORCEINLINE std::vector<const char*> GetRegisteredProperties() const { return currentState.registeredEntities; }

			/**
			 * Move the world state to another game world.
			 *
			 * @param pGameWorld: The game world to be set to.
			 */
			DMK_FORCEINLINE void MoveWorldState(GameWorld* pGameWorld)
			{
				pGameWorld->currentState = std::move(this->currentState);
			}

			/**
			 * Clear all the allocated entities.
			 */
			void ClearAllEntities()
			{
				// Delete all the allocated containers.
				for (auto itr = currentState.entityContainers.begin(); itr != currentState.entityContainers.end(); itr++)
					delete itr->second;

				// Clear containers.
				currentState.entityContainers.clear();
				currentState.registeredEntities.clear();
			}

		private:
			GameWorldState currentState = {};	// The current game world state.
		};
	}
}

#endif // !_DYNAMIK_GAME_LIBRARY_GAME_WORLD_H
