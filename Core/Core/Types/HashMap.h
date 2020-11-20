// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Macros/Global.h"
#include "DataTypes.h"

namespace DMK
{
	/**
	 * Hash Map structure for the Dynamik Engine.
	 *
	 * The hash map stores an array of structures called EntryContainer. These containers are made up of two arrays,
	 * each with a set size. This size is called the Chunk Size. The two arrays are,
	 * - Entry Pair: This stores the key value and the mapped value.
	 * - Validity array: This states whether the corresponding entry pair is valid or not (meaning it has data).
	 *
	 * The hash index is an integer which denots a location in the entry container. This location is called a slot.
	 * The hash index is calculated by the following:
	 * > HashIndex = std::hash<Key>()(keyValue) % ChunkSize;
	 *
	 * The entry vector is iterated till an empty slot id found for the corresponding hash index. And when retrieving
	 * data, the hash index is calculated and the key value is compared to check if the right pair was found. This
	 * eliminates hash collisions.
	 *
	 * Since new EntryContainers are created for identical hashes, the map could contain empty slots which could be
	 * filled later on by adding data. This means that the memory complexity will be somewhat large but this alows for
	 * fast insertions and retrieval times.
	 *
	 * This also ensures locality as static arrays and dynamic arrays are used. Keeping the chunk size at an average
	 * or to fit a chache line is recommended.
	 *
	 * @tparam Key: The key value type.
	 * @tparam Value: The value type.
	 * @tparam ChunkSize: The size of a single entry chunk. Default is 10.
	 */
	template<class Key, class Value, UI64 ChunkSize = 10>
	class HashMap {
		typedef std::pair<Key, Value> EntryPair;	// Entry pair type.

		/**
		 * Entry Container structure.
		 * This structure contains the actual data.
		 * This is also known as the Entry Table.
		 */
		struct EntryContainer {
			EntryPair mEntryArray[ChunkSize] = { EntryPair() };	// Entry pair array.
			bool bValidityTable[ChunkSize] = { false };	// Validity table.
		};

		typedef std::vector<EntryContainer> EntryVector;	// Vector containing the entry containers.

	public:
		/**
		 * Default constructor.
		 */
		HashMap() = default;

		/**
		 * Copy constructor.
		 *
		 * @param other: The other hash map.
		 */
		HashMap(const HashMap<Key, Value, ChunkSize>& other) : mEntries(other.mEntries) {}

		/**
		 * Move constructor.
		 *
		 * @param other: The other hash map.
		 */
		HashMap(HashMap<Key, Value, ChunkSize>&& other) : mEntries(std::move(other.mEntries)) { other.mEntries = {}; }

		/**
		 * Default destructor.
		 */
		~HashMap() { FastClear(); }

		/**
		 * Compute the hash using std::hash<> and convert it to a local index.
		 *
		 * @param Key: The key which is used to compute the hash index.
		 * @return The index in unsigned 64 bit integer.
		 */
		DMK_FORCEINLINE UI64 GetHashIndex(const Key& key) const { return std::hash<Key>()(key) % ChunkSize; }

		/**
		 * Insert a new entry.
		 *
		 * @param key: The key value.
		 * @param value: The value to be inserted.
		 */
		DMK_FORCEINLINE void Insert(const Key& key, const Value& value)
		{
			// Compute the hash index.
			UI64 index = GetHashIndex(key);

			// Find the suitable entry table.
			auto pTable = FindEntityContainer(index);

			// Assign values to the resolved table slot.
			pTable->mEntryArray[index].first = key;
			pTable->mEntryArray[index].second = value;
			pTable->bValidityTable[index] = true;
		}

		/**
		 * Get a value reference from the hash map.
		 *
		 * @param key: The key to be accessed.
		 * @return The Value by reference.
		 */
		DMK_FORCEINLINE Value& Get(const Key& key)
		{
			// Calculate the hash index.
			UI64 index = GetHashIndex(key);

			// Find the required entry store.
			auto pTable = FindEntityContainer(index, key);

			// Setup the table slot.
			pTable->bValidityTable[index] = true;
			pTable->mEntryArray[index].first = key;

			// Return the entry store's second value.
			return pTable->mEntryArray[index].second;
		}

		/**
		 * Remove an entry from the map.
		 * This method is the fast implementation of the remove.
		 *
		 * @param key: The key of the entry to be removed from.
		 */
		DMK_FORCEINLINE void RemoveFast(const Key& key)
		{
			// Calculate the hash index.
			UI64 index = GetHashIndex(key);

			// Find the required entry store.
			auto pTable = FindEntityContainer(index, key);

			// Terminate the store.
			TerminateEntry(pTable, index);
		}

		/**
		 * Remove an entry from the map.
		 *
		 * @note This method might be slow.
		 *
		 * @param key: The key of the entry to be removed from.
		 */
		DMK_FORCEINLINE void Remove(const Key& key)
		{
			// Calculate the hash index.
			UI64 index = GetHashIndex(key);

			// Find the required entry store.
			auto pTable = FindEntityContainer(index, key);

			// Terminate the store.
			TerminateEntry(pTable, index);

			// Check and remove if the table is empty.
			CheckRemoveTable(pTable);
		}

		/**
		 * Clear all the entries in the map.
		 * This operation is slow as it will iterate through all the entries and terminates them one by one.
		 */
		DMK_FORCEINLINE void Clear()
		{
			// Iterate through and terminate each entry.
			for (auto itr = mEntries.begin(); itr != mEntries.end(); itr++)
				for (UI64 index = 0; index < ChunkSize; index++)
					TerminateEntry(itr._Ptr, index);

			// Clear the vector.
			mEntries.clear();
		}

		/**
		 * This is the fast implementation of the Clear() method.
		 * This does not iterate and terminate all the entries but will clear the underlying vector.
		 */
		DMK_FORCEINLINE void FastClear()
		{
			mEntries.clear();
		}

		/**
		 * Check if the table entry has data to a given key.
		 *
		 * @param key: The key to be checked with.
		 * @return Boolean value.
		 */
		DMK_FORCEINLINE bool IsAvailable(const Key& key)
		{
			// Find the required entry store.
			auto pPair = Find(key);

			// Check if an entry is present and return true of found.
			if (pPair)
				return true;

			return false;
		}

		/**
		 * Check to see if there is an entry to a certain key.
		 *
		 * @param key: The key to be checked.
		 * @return Entry Pair pointer.
		 */
		DMK_FORCEINLINE EntryPair* Find(const Key& key)
		{
			// Calculate the hash index.
			UI64 index = GetHashIndex(key);

			// Initialize pointers and counters.
			UI64 counter = mEntries.size();
			EntryContainer* addr = mEntries.data();
			EntryContainer* itr = nullptr;

			// Iterate and check if a table was found.
			while (counter--)
			{
				itr = addr + counter;

				// Check if a matching pair was found and return if true.
				if (itr->bValidityTable[index] && itr->mEntryArray[index].first == key)
					return &itr->mEntryArray[index];
			}

			return nullptr;
		}

		/**
		 * Find a suitable entity store from the entrier or create a new one.
		 * This method checks if theres an empty entry table and if not found, creates a new one and returnes its
		 * address.
		 *
		 * @param index: The index in the entry container.
		 * @param key: The key to be checked.
		 * @return The Entry Container pointer.
		 */
		DMK_FORCEINLINE EntryContainer* FindEntityContainer(const UI64& index, const Key& key = Key())
		{
			// Initailize pointers and counters.
			UI64 counter = 0;
			EntryContainer* addr = nullptr;
			EntryContainer* itr = nullptr;

			// Iterate till a table was found.
			while (true)
			{
				counter = mEntries.size();
				addr = mEntries.data();

				// Iterate and check if a table was found.
				while (counter--)
				{
					itr = addr + counter;

					// Check if a matching pair was found and return if true.
					if (itr->bValidityTable[index] && itr->mEntryArray[index].first == key)
						return itr;

					// Check if an empty table slot was found and return if true.
					else if (!itr->bValidityTable[index])
						return itr;
				}

				// Insert a new table if the entries does not have a free slot.
				mEntries.insert(mEntries.end(), EntryContainer());
			}

			return nullptr;
		}

	public:
		/**
		 * Index operator overload.
		 * This can be used to access and modify data to the map.
		 *
		 * @param key: The key of the entry.
		 */
		DMK_FORCEINLINE Value& operator[](const Key& key)
		{
			return Get(key);
		}

		/**
		 * Assignment operator (copy).
		 *
		 * @param other: The other hash map.
		 * @return The assigned hash map.
		 */
		DMK_FORCEINLINE HashMap<Key, Value, ChunkSize>& operator=(const HashMap<Key, Value, ChunkSize>& other)
		{
			this->mEntries = other.mEntries;
			return *this;
		}

		/**
		 * Assignment operator (move).
		 *
		 * @param other: The other hash map.
		 * @return The assigned hash map.
		 */
		DMK_FORCEINLINE HashMap<Key, Value, ChunkSize>& operator=(HashMap<Key, Value, ChunkSize>&& other)
		{
			this->mEntries = std::move(other.mEntries);
			return *this;
		}

	public:
		/**
		 * Iterator for the Hash Map.
		 * Make sure that you check whether the entry is valid before using it!
		 */
		class Iterator {
		public:
			/**
			 * Default constructor.
			 */
			Iterator() = default;

			/**
			 * Construct the iterator using the vector pointer.
			 *
			 * @param pContainer: The container pointer.
			 */
			Iterator(EntryContainer* pContainer) : pContainer(pContainer), entryIndex(0) {}

			/**
			 * Construct the iterator by initializing values.
			 *
			 * @param pContainer: The container pointer.
			 * @param entryIndex: The entry index.
			 */
			Iterator(EntryContainer* pContainer, I64 entryIndex)
				: pContainer(pContainer), entryIndex(entryIndex) {}

			/**
			 * Default destructor.
			 */
			~Iterator() {}

			/**
			 * Check if the current entry pair is valid.
			 *
			 * @return Boolean value.
			 */
			DMK_FORCEINLINE bool IsValid() const
			{
				return pContainer->bValidityTable[entryIndex];
			}

		public:
			/**
			 * Increment the iterator by a value.
			 *
			 * @param value: The value to be incremented to.
			 * @return The incremented Const Iterator.
			 */
			DMK_FORCEINLINE Iterator& operator+=(const UI64& value)
			{
				// Check if the entry index is grater than the chunk size.
				if (value > ChunkSize)
				{
					pContainer += value / ChunkSize;
					entryIndex = value % ChunkSize;
				}
				else
				{
					entryIndex += value;

					// Check if the entry index is valid.
					if (entryIndex >= ChunkSize)
					{
						pContainer += entryIndex / ChunkSize;
						entryIndex = entryIndex % ChunkSize;
					}
				}

				return *this;
			}

			/**
			 * Increment the iterator by a value.
			 * This method does not change the internal values.
			 *
			 * @return The incremented iterator reference.
			 */
			DMK_FORCEINLINE Iterator operator+(const UI64& value)
			{
				Iterator itr(pContainer, entryIndex);
				itr.entryIndex += value;

				return itr;
			}

			/**
			 * Increment the iterator by one.
			 *
			 * @return The incremented iterator reference.
			 */
			DMK_FORCEINLINE Iterator& operator++(I32)
			{
				return operator+=(1);
			}

			/**
			 * Decrement the iterator by a value.
			 *
			 * @param value: The value to be decremented to.
			 * @return The decremented Const Iterator.
			 */
			DMK_FORCEINLINE Iterator& operator-=(const UI64& value)
			{
				// Check if the value is grater than the chunk size.
				if (value > ChunkSize)
				{
					pContainer -= value / ChunkSize;
					entryIndex = value % ChunkSize;
				}
				else
				{
					entryIndex -= value;

					// Check if the entry index is valid.
					if (entryIndex < 0)
					{
						pContainer -= (std::abs(entryIndex) + value) / ChunkSize;
						entryIndex = ChunkSize - (std::abs(entryIndex) % ChunkSize);
					}
				}

				return *this;
			}

			/**
			 * Decrement the iterator by a value.
			 * This method does not change the internal values.
			 *
			 * @return The decremented iterator reference.
			 */
			DMK_FORCEINLINE Iterator operator-(const UI64& value)
			{
				Iterator itr(pContainer, entryIndex);
				itr.entryIndex -= value;

				return itr;
			}

			/**
			 * Decrement the iterator by one.
			 *
			 * @return The decremented iterator reference.
			 */
			DMK_FORCEINLINE Iterator& operator--(I32)
			{
				return operator-=(1);
			}

			/**
			 * Check if two iterators are equal.
			 *
			 * @param other: The other iterator to be checked.
			 */
			DMK_FORCEINLINE bool operator==(const Iterator& other)
			{
				return pContainer == other.pContainer;
			}

			/**
			 * Check if the iterator is not equal to another iterator.
			 *
			 * @param other: The other iterator to be checked with.
			 * @return Boolean value.
			 */
			DMK_FORCEINLINE bool operator!=(const Iterator& other)
			{
				return pContainer != other.pContainer;
			}

			/**
			 * Is grater than operator.
			 *
			 * @param other: The other iterator to be checked from.
			 * @return Boolean value.
			 */
			DMK_FORCEINLINE bool operator>(const Iterator& other)
			{
				return pContainer > other.pContainer;
			}

			/**
			 * Is grater or equal than operator.
			 *
			 * @param other: The other iterator to be checked from.
			 * @return Boolean value.
			 */
			DMK_FORCEINLINE bool operator>=(const Iterator& other)
			{
				return pContainer >= other.pContainer;
			}

			/**
			 * Is less than operator.
			 *
			 * @param other: The other iterator to be checked from.
			 * @return Boolean value.
			 */
			DMK_FORCEINLINE bool operator<(const Iterator& other)
			{
				return pContainer < other.pContainer;
			}

			/**
			 * Is less than or equal operator.
			 *
			 * @param other: The other iterator to be checked from.
			 * @return Boolean value.
			 */
			DMK_FORCEINLINE bool operator<=(const Iterator& other)
			{
				return pContainer <= other.pContainer;
			}

			/**
			 * Dereference the iterator (*).
			 *
			 * @return The dereferenced Entry Pair.
			 */
			DMK_FORCEINLINE EntryPair& operator*()
			{
				return pContainer->mEntryArray[entryIndex];
			}

			/**
			 * Dereference the iterator (->).
			 *
			 * @return The dereferenced Entry Pair.
			 */
			DMK_FORCEINLINE EntryPair* operator->()
			{
				return &pContainer->mEntryArray[entryIndex];
			}

			/**
			 * Get the stored pointer from the iterator.
			 *
			 * @return The Entry Container pointer.
			 */
			DMK_FORCEINLINE EntryContainer* GetPointer() const { return pContainer; }

		private:
			EntryContainer* pContainer = nullptr;	// Main data pointer.
			I64 entryIndex = 0;	// The entry index.
		};

		/**
		 * Begin iterator.
		 *
		 * @return Iterator object of the hash map.
		 */
		Iterator Begin() { return Iterator(mEntries.data()); }

		/**
		 * End iterator.
		 *
		 * @return Iterator object of the hash map.
		 */
		Iterator End() { return Iterator(mEntries.end()._Ptr); }

		/**
		 * Append data to the back of the map.
		 *
		 * @param begin: The begin iterator.
		 * @param end: The end iterator.
		 */
		DMK_FORCEINLINE void Append(const Iterator& begin, const Iterator& end)
		{
			mEntries.insert(mEntries.end(), begin.GetPointer(), end.GetPointer());
		}

		/**
		 * Const Iterator for the Hash Map.
		 * Make sure that you check whether the entry is valid before using it!
		 */
		class ConstIterator {
		public:
			/**
			 * Default constructor.
			 */
			ConstIterator() = default;

			/**
			 * Construct the iterator using the vector pointer.
			 *
			 * @param pContainer: The entry container pointer.
			 */
			ConstIterator(EntryContainer* pContainer) : pContainer(pContainer), entryIndex(0) {}

			/**
			 * Construct the iterator by initializing values.
			 *
			 * @param pContainer: The entry container pointer.
			 * @param entryIndex: The entry index.
			 */
			ConstIterator(EntryContainer* pContainer, I64 entryIndex)
				: pContainer(pContainer), entryIndex(entryIndex) {}

			/**
			 * Default destructor.
			 */
			~ConstIterator() {}

			/**
			 * Check if the current entry pair is valid.
			 *
			 * @return Boolean value.
			 */
			DMK_FORCEINLINE bool IsValid() const
			{
				return pContainer->bValidityTable[entryIndex];
			}

		public:
			/**
			 * Increment the iterator by a value.
			 *
			 * @param value: The value to be incremented to.
			 * @return The incremented Const Iterator.
			 */
			DMK_FORCEINLINE ConstIterator& operator+=(const UI64& value)
			{
				// Check if the entry index is grater than the chunk size.
				if (value > ChunkSize)
				{
					pContainer += value / ChunkSize;
					entryIndex = value % ChunkSize;
				}
				else
				{
					entryIndex += value;

					// Check if the entry index is valid.
					if (entryIndex >= ChunkSize)
					{
						pContainer += entryIndex / ChunkSize;
						entryIndex = entryIndex % ChunkSize;
					}
				}

				return *this;
			}

			/**
			 * Increment the iterator by a value.
			 * This method does not change the internal values.
			 *
			 * @return The incremented iterator reference.
			 */
			DMK_FORCEINLINE ConstIterator operator+(const UI64& value)
			{
				ConstIterator itr(pContainer, entryIndex);
				itr.entryIndex += value;

				return itr;
			}

			/**
			 * Increment the iterator by one.
			 *
			 * @return The incremented iterator reference.
			 */
			DMK_FORCEINLINE ConstIterator& operator++(I32)
			{
				return operator+=(1);
			}

			/**
			 * Decrement the iterator by a value.
			 *
			 * @param value: The value to be decremented to.
			 * @return The decremented Const Iterator.
			 */
			DMK_FORCEINLINE ConstIterator& operator-=(const UI64& value)
			{
				// Check if the value is grater than the chunk size.
				if (value > ChunkSize)
				{
					pContainer -= value / ChunkSize;
					entryIndex = value % ChunkSize;
				}
				else
				{
					entryIndex -= value;

					// Check if the entry index is valid.
					if (entryIndex < 0)
					{
						pContainer -= (std::abs(entryIndex) + value) / ChunkSize;
						entryIndex = ChunkSize - (std::abs(entryIndex) % ChunkSize);
					}
				}

				return *this;
			}

			/**
			 * Decrement the iterator by a value.
			 * This method does not change the internal values.
			 *
			 * @return The decremented iterator reference.
			 */
			DMK_FORCEINLINE ConstIterator operator-(const UI64& value)
			{
				ConstIterator itr(pContainer, entryIndex);
				itr.entryIndex -= value;

				return itr;
			}

			/**
			 * Decrement the iterator by one.
			 *
			 * @return The decremented iterator reference.
			 */
			DMK_FORCEINLINE ConstIterator& operator--(I32)
			{
				return operator-=(1);
			}

			/**
			 * Check if two iterators are equal.
			 *
			 * @param other: The other iterator to be checked.
			 */
			DMK_FORCEINLINE bool operator==(const ConstIterator& other)
			{
				return pContainer == other.pContainer;
			}

			/**
			 * Check if the iterator is not equal to another iterator.
			 *
			 * @param other: The other iterator to be checked with.
			 * @return Boolean value.
			 */
			DMK_FORCEINLINE bool operator!=(const ConstIterator& other)
			{
				return pContainer != other.pContainer;
			}

			/**
			 * Is grater than operator.
			 *
			 * @param other: The other iterator to be checked from.
			 * @return Boolean value.
			 */
			DMK_FORCEINLINE bool operator>(const ConstIterator& other)
			{
				return pContainer > other.pContainer;
			}

			/**
			 * Is grater or equal than operator.
			 *
			 * @param other: The other iterator to be checked from.
			 * @return Boolean value.
			 */
			DMK_FORCEINLINE bool operator>=(const ConstIterator& other)
			{
				return pContainer >= other.pContainer;
			}

			/**
			 * Is less than operator.
			 *
			 * @param other: The other iterator to be checked from.
			 * @return Boolean value.
			 */
			DMK_FORCEINLINE bool operator<(const ConstIterator& other)
			{
				return pContainer < other.pContainer;
			}

			/**
			 * Is less than or equal operator.
			 *
			 * @param other: The other iterator to be checked from.
			 * @return Boolean value.
			 */
			DMK_FORCEINLINE bool operator<=(const ConstIterator& other)
			{
				return pContainer <= other.pContainer;
			}

			/**
			 * Dereference the iterator (*).
			 *
			 * @return The dereferenced Entry Pair.
			 */
			DMK_FORCEINLINE const EntryPair& operator*() const
			{
				return pContainer->mEntryArray[entryIndex];
			}

			/**
			 * Dereference the iterator (->).
			 *
			 * @return The dereferenced Entry Pair.
			 */
			DMK_FORCEINLINE const EntryPair* operator->() const
			{
				return &pContainer->mEntryArray[entryIndex];
			}

			/**
			 * Get the stored pointer from the iterator.
			 *
			 * @return The Entry Container pointer.
			 */
			DMK_FORCEINLINE EntryContainer* GetPointer() const { return pContainer; }

		private:
			EntryContainer* pContainer = nullptr;	// Main data pointer.
			I64 entryIndex = 0;	// The entry index.
		};

		/**
		 * Begin iterator.
		 *
		 * @return Iterator object of the hash map.
		 */
		ConstIterator ConstBegin() { return ConstIterator(mEntries.data()); }

		/**
		 * End iterator.
		 *
		 * @return Iterator object of the hash map.
		 */
		ConstIterator ConstEnd() { return ConstIterator(mEntries.end()._Ptr); }

		/**
		 * Append data to the back of the map.
		 *
		 * @param begin: The begin iterator.
		 * @param end: The end iterator.
		 */
		DMK_FORCEINLINE void Append(const ConstIterator& begin, const ConstIterator& end)
		{
			mEntries.insert(mEntries.end(), begin.GetPointer(), end.GetPointer());
		}

	private:
		/**
		 * Terminate an entry from using the table pointer.
		 *
		 * @param pTable: The entry table pointer.
		 * @param index: The index to be terminated.
		 */
		DMK_FORCEINLINE void TerminateEntry(EntryContainer* pTable, const UI64& index)
		{
			// Call the destructor and reset the values to zero.
			pTable->mEntryArray[index].first.~Key(), pTable->mEntryArray[index].first = Key();
			pTable->mEntryArray[index].second.~Value(), pTable->mEntryArray[index].second = Value();

			// Set the index slot as available.
			pTable->bValidityTable[index] = false;
		}

		/**
		 * Check and remove an entry table.
		 * This checks if the table is in use and if not, this removes it from the registry.
		 *
		 * @param pTable: The entry table poitner to be checked.
		 */
		DMK_FORCEINLINE void CheckRemoveTable(EntryContainer* pTable)
		{
			// Check if the table is in use. Return if true.
			UI64 counter = ChunkSize;
			while (counter--)
				if (pTable->bValidityTable[counter])
					return;

			// Erase the table if not in use.
			mEntries.erase(mEntries.begin() + (pTable - mEntries.data()));
		}

	private:
		EntryVector mEntries;	// Entry vector.
	};
}
