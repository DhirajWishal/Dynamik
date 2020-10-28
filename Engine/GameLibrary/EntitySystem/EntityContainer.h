// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GAME_LIBRARY_ENTITY_SYSTEM_H
#define _DYNAMIK_GAME_LIBRARY_ENTITY_SYSTEM_H

#include "Core/Types/DataTypes.h"
#include <vector>

namespace DMK
{
	namespace GameLibrary
	{
		/**
		 * The base class for the entity container.
		 */
		class EntityContainerBase {
		public:
			/**
			 * Defaut constructor.
			 */
			EntityContainerBase() {}

			/**
			 * Default destructor.
			 */
			virtual ~EntityContainerBase() {}

			/**
			 * Get the number of entities stored in the container.
			 */
			virtual UI64 Size() const { return 0; }
		};

		/**
		 * The entity container object which contains the entity.
		 */
		template<class Type>
		class EntityContainer : public EntityContainerBase {
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
			 * Add a entity to the container.
			 *
			 * @param data: The data to be added.
			 */
			DMK_FORCEINLINE void AddEntity(const Type& data) { entities.push_back(data); }

			/**
			 * Add a entity to the container.
			 *
			 * @param data: The data to be added.
			 */
			DMK_FORCEINLINE void AddEntity(Type&& data) { entities.push_back(std::move(data)); }

			/**
			 * Get the number of entities stored in the container.
			 */
			DMK_FORCEINLINE virtual UI64 Size() const override final { return entities.size(); }

			/**
			 * Get a entity using its index.
			 *
			 * @return: The entity pointer.
			 */
			DMK_FORCEINLINE Type* GetEntity(UI64 index) const { return const_cast<Type*>(&entities[index]); }

			/**
			 * Remove a entity from the container using its index.
			 *
			 * @param index: The index of the entity to be removed.
			 */
			DMK_FORCEINLINE void Remove(UI64 index) { entities.erase(entities.begin() + index); }

			/**
			 * Get the memory block address of the entities array.
			 *
			 * @return: Type pointer.
			 */
			DMK_FORCEINLINE Type* Data() const { return entities.data(); }

			/**
			 * Begining of the entities array.
			 *
			 * @return: Type pointer.
			 */
			DMK_FORCEINLINE Type* Begin() const { return entities.begin(); }

			/**
			 * End of the entities array.
			 *
			 * @return: Type pointer.
			 */
			DMK_FORCEINLINE Type* End() const { return entities.end(); }

			std::vector<Type> entities;	// The vector containing the actual entities.
		};
	}
}

#endif // !_DYNAMIK_GAME_LIBRARY_ENTITY_SYSTEM_H
