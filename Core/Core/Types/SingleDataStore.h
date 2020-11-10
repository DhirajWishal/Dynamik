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
		static void PushBack(const Type& data)
		{
			instance.container.push_back(data);
		}

		/**
		 * Add data to the store.
		 *
		 * @param data: The data to be added.
		 */
		static void PushBack(Type&& data)
		{
			instance.container.push_back(std::move(data));
		}

	private:
		std::vector<Type> container;	// The data container.
	};

	/**
	 * Static instance definition.
	 */
	template<class Type>
	SingleDataStore<Type> SingleDataStore<Type>::instance;
}

#endif // !_DYNAMIK_CORE_SINGLE_DATA_STORE_H
