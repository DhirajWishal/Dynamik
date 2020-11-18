// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GAME_LIBRARY_ENTITY_CONTAINER_H
#define _DYNAMIK_GAME_LIBRARY_ENTITY_CONTAINER_H

#include "Core/Types/DataTypes.h"

#include <typeinfo>

namespace DMK
{
	namespace GameLibrary
	{
		/**
		 * Entity Container Base object.
		 * This object is the base class for all the entity containers.
		 */
		class EntityContainerBase {
		public:
			/**
			 * Default constructor.
			 */
			EntityContainerBase() {}

			/**
			 * Default destructor.
			 */
			virtual ~EntityContainerBase() {}

			/**
			 * Get the number of entities stored.
			 *
			 * @return The number of entities stored.
			 */
			virtual UI64 Size() const { return 0; }

			/**
			 * Get the type name as a  string.
			 *
			 * @return Const char pointer.
			 */
			virtual const char* TypeName() const { return nullptr; }
		};

		/**
		 * Entity Container object.
		 * This object stores multiple entities of the same type.
		 *
		 * @tparam Type: The entity type.
		 */
		template<class Type>
		class EntityContainer final : public EntityContainerBase {
			typedef std::vector<Type> Container;

		public:
			/**
			 * Default constructor.
			 */
			EntityContainer() {}

			/**
			 * Default destructor.
			 */
			~EntityContainer() {}

			/**
			 * Get the number of entities stored.
			 *
			 * @return The number of entities stored.
			 */
			virtual UI64 Size() const override { return mEntities.size(); }

			/**
			 * Get the type name as a  string.
			 *
			 * @return Const char pointer.
			 */
			virtual const char* TypeName() const override { return typeid(Type).name(); }

			/**
			 * Add an entity to the container (copy).
			 * This method also returns the pointer to the newly added entity.
			 *
			 * @param entity: The entity to be added.
			 * @return The newly added entity pointer.
			 */
			Type* Add(const Type& entity)
			{
				mEntities.push_back(entity);
				return GetEntity(mEntities.size() - 1);
			}

			/**
			 * Add an entity to the container (move).
			 * This method also returns the pointer to the newly added entity.
			 *
			 * @param entity: The entity to be added.
			 * @return The newly added entity pointer.
			 */
			Type* Add(Type&& entity)
			{
				mEntities.push_back(std::move(entity));
				return GetEntity(mEntities.size() - 1);
			}

			/**
			 * Get an entity from the container.
			 *
			 * @param index: The index of the entity.
			 * @return The entity pointer.
			 */
			Type* GetEntity(const UI64 index)
			{
				return mEntities.data() + index;
			}

			/**
			 * Remove an entity from the entity container.
			 *
			 * @param index: The index to be removed from.
			 */
			void Remove(const UI64 index)
			{
				mEntities.erase(mEntities.begin() + index);
			}

			/**
			 * Remove an entity from the entity container.
			 *
			 * @param pEntity: The entity pointer to be removed.
			 */
			void Remove(const Type* pEntity)
			{
				mEntities.erase(mEntities.begin() + (pEntity - mEntities.data()));
			}

		private:
			Container mEntities;	// Entity store.
		};
	}
}

#endif // !_DYNAMIK_GAME_LIBRARY_ENTITY_CONTAINER_H
