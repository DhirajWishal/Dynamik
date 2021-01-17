// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "SparseSet.h"

namespace DMK
{
	/**
	 * Statis Sparse Set.
	 * This is just a singleton class wrapper for a sparse set which enables to store data and retrieve them easily.
	 *
	 * @tparam Type: The type of the data to be stored.
	 * @param IndexType: The index type. Default is UI64. This type must be an integral type.
	 */
	template<class Type, class IndexType = UI64>
	class StaticSparseSet {
		StaticSparseSet() {}
		~StaticSparseSet() {}

		static StaticSparseSet mInstance;

	public:
		StaticSparseSet(const StaticSparseSet&) = delete;
		StaticSparseSet(StaticSparseSet&&) = delete;
		StaticSparseSet& operator=(const StaticSparseSet&) = delete;
		StaticSparseSet& operator=(StaticSparseSet&&) = delete;

		/**
		 * Insert data into the sparse set.
		 * 
		 * @param data: The data to be inserted.
		 * @return The index of the inserted data.
		 */
		static constexpr IndexType Insert(const Type& data);

		/**
		 * Insert data into the sparse set.
		 *
		 * @param data: The data to be inserted.
		 * @return The index of the inserted data.
		 */
		static constexpr IndexType Insert(Type&& data);

		/**
		 * Get an entry from the set.
		 *
		 * @param index: The index of the entry.
		 * @return The Type reference.
		 */
		static constexpr Type& Get(const IndexType& index);

		/**
		 * Remove an entry from the set.
		 * This method removes the element from the entry vector but does not remove the respective entry from the
		 * index vector. This means that the index vector does not shrink. The index place value of the entry vector
		 * will be set to the numeric limit of that integer type.
		 *
		 * @param index: The index of the entry to be removed.
		 */
		static constexpr void Remove(const IndexType& index);

		/**
		 * Clear all the entries.
		 */
		static constexpr void Clear();

	public:
		/**
		 * Get the number of entries stored.
		 *
		 * @return The number of entries.
		 */
		static constexpr UI64 Size();

		/**
		 * Get the capacity of the entry vector.
		 *
		 * @return The capacity.
		 */
		static constexpr UI64 Capacity();

		/**
		 * Check if the index is valid.
		 *
		 * @param index: The index to be checked.
		 * @return Boolean value.
		 */
		static constexpr bool IsValidIndex(const IndexType& index);

		/**
		 * Get the begin iterator.
		 *
		 * @return The container iterator.
		 */
		static constexpr typename SparseSet<Type, IndexType>::Iterator Begin();

		/**
		 * Get the end iterator.
		 *
		 * @return The container iterator.
		 */
		static constexpr typename SparseSet<Type, IndexType>::Iterator End();

		/**
		 * Get the reverse begin iterator.
		 *
		 * @return The container reverse iterator.
		 */
		static constexpr typename SparseSet<Type, IndexType>::ReverseIterator RBegin();

		/**
		 * Get the end reverse iterator.
		 *
		 * @return The container reverse iterator.
		 */
		static constexpr typename SparseSet<Type, IndexType>::ReverseIterator REnd();

	private:
		SparseSet<Type, IndexType> mSparseSet;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////
	////	Definitions
	///////////////////////////////////////////////////////////////////////////////////////////////////

	template<class Type, class IndexType>
	StaticSparseSet<Type, IndexType> StaticSparseSet<Type, IndexType>::mInstance;

	template<class Type, class IndexType>
	inline constexpr IndexType StaticSparseSet<Type, IndexType>::Insert(const Type& data)
	{
		return mInstance.mSparseSet.Insert(data);
	}

	template<class Type, class IndexType>
	inline constexpr IndexType StaticSparseSet<Type, IndexType>::Insert(Type&& data)
	{
		return mInstance.mSparseSet.Insert(std::move(data));
	}

	template<class Type, class IndexType>
	inline constexpr Type& StaticSparseSet<Type, IndexType>::Get(const IndexType& index)
	{
		return mInstance.mSparseSet.Get(index);
	}

	template<class Type, class IndexType>
	inline constexpr void StaticSparseSet<Type, IndexType>::Remove(const IndexType& index)
	{
		mInstance.mSparseSet.Remove(index);
	}

	template<class Type, class IndexType>
	inline constexpr void StaticSparseSet<Type, IndexType>::Clear()
	{
		mInstance.mSparseSet.Clear();
	}

	template<class Type, class IndexType>
	inline constexpr UI64 StaticSparseSet<Type, IndexType>::Size() 
	{
		return mInstance.mSparseSet.Size();
	}

	template<class Type, class IndexType>
	inline constexpr UI64 StaticSparseSet<Type, IndexType>::Capacity()
	{
		return mInstance.mSparseSet.Capacity();
	}

	template<class Type, class IndexType>
	inline constexpr bool StaticSparseSet<Type, IndexType>::IsValidIndex(const IndexType& index)
	{
		return mInstance.mSparseSet.IsValidIndex(index);
	}

	template<class Type, class IndexType>
	inline constexpr typename SparseSet<Type, IndexType>::Iterator StaticSparseSet<Type, IndexType>::Begin()
	{
		return mInstance.mSparseSet.Begin();
	}

	template<class Type, class IndexType>
	inline constexpr typename SparseSet<Type, IndexType>::Iterator StaticSparseSet<Type, IndexType>::End()
	{
		return mInstance.mSparseSet.End();
	}

	template<class Type, class IndexType>
	inline constexpr typename SparseSet<Type, IndexType>::ReverseIterator StaticSparseSet<Type, IndexType>::RBegin()
	{
		return mInstance.mSparseSet.RBegin();
	}

	template<class Type, class IndexType>
	inline constexpr typename SparseSet<Type, IndexType>::ReverseIterator StaticSparseSet<Type, IndexType>::REnd()
	{
		return mInstance.mSparseSet.REnd();
	}
}
