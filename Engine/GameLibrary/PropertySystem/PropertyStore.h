// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GAME_LIBRARY_PROPERTY_STORE_H
#define _DYNAMIK_GAME_LIBRARY_PROPERTY_STORE_H

#include "Core/Macros/Global.h"
#include "PropertyContainer.h"
#include <typeinfo>

namespace DMK
{
	namespace GameLibrary
	{
		/**
		 * Property store for the Dynamik Engine Game Library.
		 * This object is the base class for all the game components that use properties.
		 *
		 * In addition to properties, this object can store any type of data.
		 */
		class PropertyStore {
		public:
			/**
			 * Default constructor.
			 */
			PropertyStore() {}

			/**
			 * Default destructor.
			 */
			virtual ~PropertyStore()
			{
				// Delete all the allocated containers.
				for (auto itr = propertyContainers.begin(); itr != propertyContainers.end(); itr++)
					delete itr->second;

				// Clear containers.
				propertyContainers.clear();
				registeredProperties.clear();
			}

			/**
			 * Check if a property is registered.
			 *
			 * @tparam Type> The type of the property.
			 * @return: Boolean value.
			 */
			template<class Type>
			DMK_FORCEINLINE bool IsPropertyRegistered() const
			{
				// Get the type name.
				const char* propertyName = typeid(Type).name();

				// Iterate through the registered types to find if the type is already registered.
				auto itr = registeredProperties.begin();
				while (itr != registeredProperties.end())
				{
					if (*itr == propertyName)
						return true;

					itr++;
				}

				// Return false if not found.
				return false;
			}

			/**
			 * Register a new property to the store.
			 * If the property is already registered, it does not do anything.
			 *
			 * @tparam Type: The type of the property.
			 */
			template<class Type>
			DMK_FORCEINLINE void RegisterProperty()
			{
				// Check if the property is already registered.
				if (IsPropertyRegistered<Type>())
					return;

				// Get the property name.
				const char* propertyName = typeid(Type).name();

				// Create the container and add the name to the registered property name list.
				propertyContainers[propertyName] = new PropertyContainer<Type>();
				registeredProperties.push_back(std::move(propertyName));
			}

			/**
			 * Get the property container of a certain type.
			 *
			 * @tparam Type: The type of the property.
			 * @return: The PropertyContainer<Type> pointer.
			 */
			template<class Type>
			DMK_FORCEINLINE PropertyContainer<Type>* GetPropertyContainer()
			{
				// Check and register if the container is not available.
				RegisterProperty<Type>();

				// Return the casted container.
				return static_cast<PropertyContainer<Type>*>(propertyContainers[typeid(Type).name()]);
			}

			/**
			 * Add a property to the property container.
			 *
			 * @param data: The data to be added.
			 * @tparam Type: The type of the property.
			 * @return: The created property pointer.
			 */
			template<class Type>
			DMK_FORCEINLINE Type* AddProperty(const Type& data)
			{
				GetPropertyContainer<Type>()->AddProperty(data);
				return GetPropertyContainer<Type>()->GetProperty(GetPropertyContainer<Type>()->Size() - 1);
			}

			/**
			 * Add a property to the property container.
			 * This also returns the created property pointer.
			 *
			 * @param data: The data to be added.
			 * @tparam Type: The type of the property.
			 * @return: The created property pointer.
			 */
			template<class Type>
			DMK_FORCEINLINE Type* AddProperty(Type&& data)
			{
				GetPropertyContainer<Type>()->AddProperty(std::move(data));
				return GetPropertyContainer<Type>()->GetProperty(GetPropertyContainer<Type>()->Size() - 1);
			}

			/**
			 * Get a property from the property container.
			 *
			 * @param index: The index of the property.
			 * @tparam Type: The property type.
			 * @return: The property pointer.
			 */
			template<class Type>
			DMK_FORCEINLINE Type* GetProperty(UI64 index)
			{
				return GetPropertyContainer<Type>()->GetProperty(index);
			}

			/**
			 * Get the number of properties stored in a given container.
			 *
			 * @tparam Type: The type of the property.
			 * @return: Unsigned 64 bit integer.
			 */
			template<class Type>
			DMK_FORCEINLINE UI64 GetPropertyCount()
			{
				return GetPropertyContainer<Type>()->Size();
			}

			/**
			 * Remove a property from a given index.
			 *
			 * @param index: The index of the property to be removed.
			 * @tparam Type: The type of the property.
			 */
			template<class Type>
			DMK_FORCEINLINE void RemoveProperty(UI64 index)
			{
				GetPropertyContainer<Type>()->Remove(index);
			}

		public:
			/**
			 * Get all the registered property names.
			 *
			 * @return: std::vector<std::string> object.
			 */
			DMK_FORCEINLINE std::vector<const char*> GetRegisteredProperties() const { return registeredProperties; }

		private:
			std::vector<const char*> registeredProperties;	// Array storing all the registered properties.
			std::unordered_map<const char*, PropertyContainerBase*> propertyContainers;	// Map containing all the property containers.
		};
	}
}

#endif // !_DYNAMIK_GAME_LIBRARY_PROPERTY_STORE_H
