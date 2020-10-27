// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GAME_LIBRARY_PROPERTY_SYSTEM_H
#define _DYNAMIK_GAME_LIBRARY_PROPERTY_SYSTEM_H

#include "Core/Types/DataTypes.h"
#include <vector>

namespace DMK
{
	namespace GameLibrary
	{
		/**
		 * The base class for the property container.
		 */
		class PropertyContainerBase {
		public:
			/**
			 * Defaut constructor.
			 */
			PropertyContainerBase() {}

			/**
			 * Default destructor.
			 */
			virtual ~PropertyContainerBase() {}

			/**
			 * Get the number of properties stored in the container.
			 */
			virtual UI64 Size() const { return 0; }
		};

		/**
		 * The property container object which contains the property.
		 */
		template<class Type>
		class PropertyContainer : public PropertyContainerBase {
		public:
			/**
			 * Default constructor.
			 */
			PropertyContainer() {}

			/**
			 * Default destructor.
			 */
			~PropertyContainer() {}

			/**
			 * Add a property to the container.
			 *
			 * @param data: The data to be added.
			 */
			DMK_FORCEINLINE void AddProperty(const Type& data) { properties.push_back(data); }

			/**
			 * Add a property to the container.
			 *
			 * @param data: The data to be added.
			 */
			DMK_FORCEINLINE void AddProperty(Type&& data) { properties.push_back(std::move(data)); }

			/**
			 * Get the number of properties stored in the container.
			 */
			DMK_FORCEINLINE virtual UI64 Size() const override final { return properties.size(); }

			/**
			 * Get a property using its index.
			 *
			 * @return: The property pointer.
			 */
			DMK_FORCEINLINE Type* GetProperty(UI64 index) const { return const_cast<Type*>(&properties[index]); }

			/**
			 * Remove a property from the container using its index.
			 *
			 * @param index: The index of the property to be removed.
			 */
			DMK_FORCEINLINE void Remove(UI64 index) { properties.erase(properties.begin() + index); }

			/**
			 * Get the memory block address of the properties array.
			 *
			 * @return: Type pointer.
			 */
			DMK_FORCEINLINE Type* Data() const { return properties.data(); }

			/**
			 * Begining of the properties array.
			 *
			 * @return: Type pointer.
			 */
			DMK_FORCEINLINE Type* Begin() const { return properties.begin(); }

			/**
			 * End of the properties array.
			 *
			 * @return: Type pointer.
			 */
			DMK_FORCEINLINE Type* End() const { return properties.end(); }

			std::vector<Type> properties;	// The vector containing the actual properties.
		};
	}
}

#endif // !_DYNAMIK_GAME_LIBRARY_PROPERTY_SYSTEM_H
