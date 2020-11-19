// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_CORE_SINGLE_DATA_STORE_H
#define _DYNAMIK_CORE_SINGLE_DATA_STORE_H

#include "DataTypes.h"

namespace DMK
{
	/**
	 * A singleton object which can hold a single type of data.
	 *
	 * @tparam: The type of the data to be stored.
	 */
	template<class Type>
	class SingleDataStore {
		typedef std::vector<Type> Container;
		typedef typename Container::iterator Iterator;

		/**
		 * Private constructor.
		 */
		SingleDataStore() {}

		/**
		 * Private destructor.
		 */
		~SingleDataStore() {}

		static SingleDataStore instance;	// Static instance.

	public:
		/**
		 * Add data to the store.
		 *
		 * @param data: The data to be added.
		 */
		static void PushBack(const Type& data) { instance.mContainer.push_back(data); }

		/**
		 * Add data to the store.
		 *
		 * @param data: The data to be added.
		 */
		static void PushBack(Type&& data) { instance.mContainer.push_back(std::move(data)); }

		/**
		 * Get an element from the container.
		 *
		 * @param index: The index of the element.
		 * @return The Type reference.
		 */
		static Type& Get(const UI64& index) { return *(instance.mContainer.data() + index); }

		/**
		 * Get the location (address) of an element.
		 *
		 * @param index: The index to be accessed.
		 * @return The Type pointer.
		 */
		static Type* Location(const UI64& index) { return instance.mContainer.data() + index; }

		/**
		 * Remove an element from the container.
		 *
		 * @param index: The index of the element to be removed.
		 */
		static void Remove(const UI64& index) { instance.mContainer.erase(instance.mContainer.begin() + index); }

		/**
		 * Get the number of data stored in the container.
		 *
		 * @return The size of the container vector.
		 */
		static UI64 Size() { return instance.mContainer.size(); }

		/**
		 * Begin iterator of the store.
		 *
		 * @return std::vector<Type>::iterator object.
		 */
		static Iterator Begin() { return instance.mContainer.begin(); }

		/**
		 * End iterator of the store.
		 *
		 * @return std::vector<Type>::iterator object.
		 */
		static Iterator End() { return instance.mContainer.end(); }

		/**
		 * Get the data address of the container.
		 *
		 * @return Type pointer.
		 */
		static const Type* Data() { return instance.mContainer.data(); }

		/**
		 * Clear the container.
		 */
		static void Clear() { instance.mContainer.clear(); }

	private:
		Container mContainer;	// The data container.
	};

	/**
	 * Static instance definition.
	 */
	template<class Type>
	SingleDataStore<Type> SingleDataStore<Type>::instance;
}

#endif // !_DYNAMIK_CORE_SINGLE_DATA_STORE_H
