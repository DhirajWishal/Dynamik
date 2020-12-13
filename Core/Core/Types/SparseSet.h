// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "DataTypes.h"

namespace DMK
{
	/**
	 * Sparse Set object.
	 * This object stores entries in a vector and returns an index of the entry. This index is unique for an entry
	 * and is maintained even after removing or adding multiple entries.
	 *
	 * @tparam Type: The type of the entries to be stored.
	 * @tparam IndexType: The type of the index and must be an integral type. Default is UI64.
	 */
	template<class Type, class IndexType = UI64>
	class SparseSet {
		/**
		 * Check if the IndexType is valid.
		 */
		static_assert(
			std::is_integral<IndexType>::value,
			"SparseSet<Type, IndexType> requires the 'IndexType' to be an integral type!"
			);

		typedef std::vector<Type, std::allocator<Type>>				EntryContainer;
		typedef std::vector<IndexType, std::allocator<IndexType>>	IndexContainer;

	public:
		typedef typename EntryContainer::iterator					Iterator;
		typedef typename EntryContainer::const_iterator				ConstIterator;
		typedef typename EntryContainer::reverse_iterator			ReverseIterator;
		typedef typename EntryContainer::const_reverse_iterator		ConstReverseIterator;

	public:
		SparseSet() = default;
		SparseSet(const SparseSet& other);
		SparseSet(SparseSet&& other);
		~SparseSet() = default;

		/**
		 * Insert data to the set.
		 *
		 * @param data: The data to be added.
		 * @return The index of the entry.
		 */
		IndexType Insert(const Type& data);

		/**
		 * Insert data to the set.
		 *
		 * @param data: The data to be added.
		 * @return The index of the entry.
		 */
		IndexType Insert(Type&& data);

		/**
		 * Get an entry from the set.
		 *
		 * @param index: The index of the entry.
		 * @return The Type reference.
		 */
		Type& Get(const IndexType& index);

		/**
		 * Get an entry from the set.
		 *
		 * @param index: The index of the entry.
		 * @return The Type reference.
		 */
		const Type Get(const IndexType& index) const;

		/**
		 * Remove an entry from the set.
		 * This method removes the element from the entry vector but does not remove the respective entry from the
		 * index vector. This means that the index vector does not shrink. The index place value of the entry vector
		 * will be set to the numeric limit of that integer type.
		 *
		 * @param index: The index of the entry to be removed.
		 */
		void Remove(const IndexType& index);

		/**
		 * Clear all the entries.
		 */
		void Clear();

	public:
		/**
		 * Get the number of entries stored.
		 *
		 * @return The number of entries.
		 */
		UI64 Size() const;

		/**
		 * Get the capacity of the entry vector.
		 *
		 * @return The capacity.
		 */
		UI64 Capacity() const;

		/**
		 * Check if the index is valid.
		 *
		 * @param index: The index to be checked.
		 * @return Boolean value.
		 */
		bool IsValidIndex(const IndexType& index) const;

		/**
		 * Get the begin iterator.
		 *
		 * @return The container iterator.
		 */
		Iterator Begin();

		/**
		 * Get the begin iterator.
		 *
		 * @return The container const iterator.
		 */
		ConstIterator Begin() const;

		/**
		 * Get the end iterator.
		 *
		 * @return The container iterator.
		 */
		Iterator End();

		/**
		 * Get the end iterator.
		 *
		 * @return The container iterator.
		 */
		ConstIterator End() const;

		/**
		 * Get the reverse begin iterator.
		 *
		 * @return The container reverse iterator.
		 */
		ReverseIterator RBegin();

		/**
		 * Get the reverse begin iterator.
		 *
		 * @return The container const reverse iterator.
		 */
		ConstReverseIterator RBegin() const;

		/**
		 * Get the end reverse iterator.
		 *
		 * @return The container reverse iterator.
		 */
		ReverseIterator REnd();

		/**
		 * Get the end reverse iterator.
		 *
		 * @return The container const reverse iterator.
		 */
		ConstReverseIterator REnd() const;

	public:
		/**
		 * Copy values to this using another dense set.
		 *
		 * @param other: The other dense set.
		 * @return This set reference.
		 */
		SparseSet& operator=(const SparseSet& other);

		/**
		 * Move values to this using another dense set.
		 *
		 * @param other: The other dense set.
		 * @return This set reference.
		 */
		SparseSet& operator=(SparseSet&& other);

		/**
		 * Get an entry from the set using the index.
		 *
		 * @param index: The index of the entry.
		 * @return The entry reference.
		 */
		Type& operator[](const IndexType& index);

		/**
		 * Get an entry from the set using the index.
		 *
		 * @param index: The index of the entry.
		 * @return The const entry.
		 */
		const Type operator[](const IndexType& index) const;

	private:
		EntryContainer mEntries;
		IndexContainer mIndexes;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////
	////	Definitions
	///////////////////////////////////////////////////////////////////////////////////////////////////

	template<class Type, class IndexType>
	inline SparseSet<Type, IndexType>::SparseSet(const SparseSet& other)
		: mEntries(other.mEntries), mIndexes(other.mIndexes)
	{
	}

	template<class Type, class IndexType>
	inline SparseSet<Type, IndexType>::SparseSet(SparseSet&& other)
		: mEntries(std::move(other.mEntries)), mIndexes(std::move(other.mIndexes))
	{
	}

	template<class Type, class IndexType>
	inline IndexType SparseSet<Type, IndexType>::Insert(const Type& data)
	{
		IndexType index = static_cast<IndexType>(mIndexes.size());

		mEntries.insert(mEntries.end(), data);
		mIndexes.insert(mIndexes.end(), index);

		return index;
	}

	template<class Type, class IndexType>
	inline IndexType SparseSet<Type, IndexType>::Insert(Type&& data)
	{
		IndexType index = static_cast<IndexType>(mIndexes.size());

		mEntries.insert(mEntries.end(), std::move(data));
		mIndexes.insert(mIndexes.end(), index);

		return index;
	}

	template<class Type, class IndexType>
	inline Type& SparseSet<Type, IndexType>::Get(const IndexType& index)
	{
		return mEntries[static_cast<UI64>(mIndexes[static_cast<UI64>(index)])];
	}

	template<class Type, class IndexType>
	inline const Type SparseSet<Type, IndexType>::Get(const IndexType& index) const
	{
		return mEntries[static_cast<UI64>(mIndexes[static_cast<UI64>(index)])];
	}

	template<class Type, class IndexType>
	inline void SparseSet<Type, IndexType>::Remove(const IndexType& index)
	{
		mEntries.erase(mEntries.begin() + mIndexes[index]);
		mIndexes[index] = std::numeric_limits<IndexType>::max();

		for (IndexType itr = index + 1; itr != mIndexes.size(); itr++)
			mIndexes[itr]--;
	}

	template<class Type, class IndexType>
	inline void SparseSet<Type, IndexType>::Clear()
	{
		mEntries.clear();
		mIndexes.clear();
	}

	template<class Type, class IndexType>
	inline UI64 SparseSet<Type, IndexType>::Size() const
	{
		return mEntries.size();
	}

	template<class Type, class IndexType>
	inline UI64 SparseSet<Type, IndexType>::Capacity() const
	{
		return mEntries.capacity();
	}

	template<class Type, class IndexType>
	inline bool SparseSet<Type, IndexType>::IsValidIndex(const IndexType& index) const
	{
		if (index >= mIndexes.size() || index >= mEntries.size() || mIndexes[index] >= mEntries.size())
			return false;

		return true;
	}

	template<class Type, class IndexType>
	inline typename SparseSet<Type, IndexType>::Iterator SparseSet<Type, IndexType>::Begin()
	{
		return mEntries.begin();
	}

	template<class Type, class IndexType>
	inline typename SparseSet<Type, IndexType>::ConstIterator SparseSet<Type, IndexType>::Begin() const
	{
		return mEntries.begin();
	}

	template<class Type, class IndexType>
	inline typename SparseSet<Type, IndexType>::Iterator SparseSet<Type, IndexType>::End()
	{
		return mEntries.end();
	}

	template<class Type, class IndexType>
	inline typename SparseSet<Type, IndexType>::ConstIterator SparseSet<Type, IndexType>::End() const
	{
		return mEntries.end();
	}

	template<class Type, class IndexType>
	inline typename SparseSet<Type, IndexType>::ReverseIterator SparseSet<Type, IndexType>::RBegin()
	{
		return mEntries.rbegin();
	}

	template<class Type, class IndexType>
	inline typename SparseSet<Type, IndexType>::ConstReverseIterator SparseSet<Type, IndexType>::RBegin() const
	{
		return mEntries.crbegin();
	}

	template<class Type, class IndexType>
	inline typename SparseSet<Type, IndexType>::ReverseIterator SparseSet<Type, IndexType>::REnd()
	{
		return mEntries.rend();
	}

	template<class Type, class IndexType>
	inline typename SparseSet<Type, IndexType>::ConstReverseIterator SparseSet<Type, IndexType>::REnd() const
	{
		return mEntries.crend();
	}

	template<class Type, class IndexType>
	inline SparseSet<Type, IndexType>& SparseSet<Type, IndexType>::operator=(const SparseSet& other)
	{
		this->mEntries = other.mEntries;
		this->mIndexes = other.mIndexes;

		return *this;
	}

	template<class Type, class IndexType>
	inline SparseSet<Type, IndexType>& SparseSet<Type, IndexType>::operator=(SparseSet&& other)
	{
		this->mEntries = std::move(other.mEntries);
		this->mIndexes = std::move(other.mIndexes);

		return *this;
	}

	template<class Type, class IndexType>
	inline Type& SparseSet<Type, IndexType>::operator[](const IndexType& index)
	{
		return Get(index);
	}

	template<class Type, class IndexType>
	inline const Type SparseSet<Type, IndexType>::operator[](const IndexType& index) const
	{
		return Get(index);
	}
}