// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GAME_LIBRARY_ENTITY_STORE_H
#define _DYNAMIK_GAME_LIBRARY_ENTITY_STORE_H

#include "EntityContainer.h"
#include "Core/ErrorHandler/Logger.h"

namespace DMK
{
	namespace GameLibrary
	{
		/**
		 * Entity Store object.
		 * This object stores multiple types of entities.
		 */
		class EntityStore {
		public:
			EntityStore() {}
			virtual ~EntityStore() {}

			/**
			 * Check if an entity is registered.
			 *
			 * @tparam Type: The entity type.
			 * @return Boolean value.
			 */
			template<class Type>
			bool IsRegistered() const
			{
				UI64 counter = mRegisteredTypes.size();
				auto ptr = mRegisteredTypes.data();
				const char* pName = GetName<Type>();

				// Iterate through the array to check if the type name is present. Return true if found.
				while (counter--)
					if (*(ptr + counter) == pName)
						return true;

				return false;
			}

			/**
			 * Register a new entity to the entity store.
			 *
			 * @tparam Type: The entity type.
			 */
			template<class Type>
			void RegisterEntity()
			{
				// Check if an entity is registered. Return if true.
				if (IsRegistered<Type>())
					return;

				// Get the type name.
				const char* pName = GetName<Type>();

				// Create a new entity contianer for the entity type.
				mEntityContainers[pName] = new EntityContainer<Type>();

				// Register the entity name.
				mRegisteredTypes.insert(mRegisteredTypes.end(), pName);
			}

			/**
			 * Get the entity container pointer.
			 *
			 * @tparam Type: The type of the entity.
			 * @return EntityContainer<Type> pointer.
			 */
			template<class Type>
			EntityContainer<Type>* GetEntityContainer() const
			{
				// Check if the requested entity type is available.
				if (!IsRegistered<Type>())
				{
					Logger::LogError(TEXT("Requested entity type is not registered! Make sure to register the entity type!"));
					return nullptr;
				}

				// Get the casted container.
				return dynamic_cast<EntityContainer<Type>*>(mEntityContainers.at(GetName<Type>()));
			}

			/**
			 * Get the entity container pointer fast.
			 * This method is somewhat dangerous as it does not validate whether the entity is registered or not.
			 *
			 * @tparam Type: The type of the entity.
			 * @return EntityContainer<Type> pointer.
			 */
			template<class Type>
			EntityContainer<Type>* GetEntityContainerFast() const
			{
				// Get the casted container.
				return dynamic_cast<EntityContainer<Type>*>(mEntityContainers.at(GetName<Type>()));
			}

		protected:
			/**
			 * Get the type name of a perticular type.
			 *
			 * @tparam Type: The type to find the name.
			 * @return Const char pointer.
			 */
			template<class Type>
			const char* GetName() const { return typeid(Type).name(); }

		protected:
			std::unordered_map<const char*, EntityContainerBase*> mEntityContainers;	// Entity containers.
			std::vector<const char*> mRegisteredTypes;	// Registered entity types.
		};
	}
}

#endif // !_DYNAMIK_GAME_LIBRARY_ENTITY_STORE_H
