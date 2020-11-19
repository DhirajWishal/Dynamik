// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_STATIC_QUEUE_H
#define _DYNAMIK_STATIC_QUEUE_H

#include "DataTypes.h"
#include "Core/Memory/Functions.h"

namespace DMK
{
	/**
	 * Static Queue structure.
	 * This object is a queue which uses a static array to store elements.
	 *
	 * @tparam Type: The type of the static queue.
	 * @tparam ElementCount: The size of the array.
	 */
	template<class Type, UI64 ElementCount>
	class StaticQueue {
	public:
		/**
		 * Default constructor.
		 */
		StaticQueue() = default;

		/**
		 * Default destructor.
		 */
		~StaticQueue() {}

		/**
		 * Add an element to the last available slot.
		 * This method returns true if inserted successfully. Returns false if not.
		 *
		 * @param data: The data to be added.
		 * @return Boolean value.
		 */
		bool Push(const Type& data)
		{
			// Check if the size is valid.
			if (entryCounter >= ElementCount)
				return false;

			// Add the entry to the last remaining slot.
			mEntries[entryCounter] = data;
			entryCounter++;

			// Return true.
			return true;
		}

		/**
		 * Add an element to the last available slot.
		 * This method returns true if inserted successfully. Returns false if not.
		 *
		 * @param data: The data to be added.
		 * @return Boolean value.
		 */
		bool Push(Type&& data)
		{
			// Check if the size is valid.
			if (entryCounter >= ElementCount)
				return false;

			// Add the entry to the last remaining slot.
			mEntries[entryCounter] = std::move(data);
			entryCounter++;

			// Return true.
			return true;
		}

		/**
		 * Get the first element from the queue.
		 *
		 * @return Type reference.
		 */
		Type& Get()
		{
			return mEntries[0];
		}

		/**
		 * Get the first element from the queue.
		 *
		 * @return Type reference.
		 */
		const Type Get() const
		{
			return mEntries[0];
		}

		/**
		 * Pop the first element of the queue.
		 */
		void Pop()
		{
			// Create a new buffer.
			Type buffer[ElementCount] = {};

			// Add the existing data to it.
			for (UI64 i = 1; i < entryCounter; i++)
				buffer[i - 1] = mEntries[i];

			// Assign the new valued.
			entryCounter--;
			MemoryFunctions::MoveData(mEntries, buffer, sizeof(Type) * ElementCount);
		}

		/**
		 * Get the first element and pop it from the queue. Return it afterwards.
		 *
		 * @return The first element.
		 */
		Type GetAndPop()
		{
			// Copy the first element temporarily.
			auto temp = mEntries[0];

			// Pop the first element.
			Pop();

			// Return the first element.
			return temp;
		}

		/**
		 * Get the number of entries stored.
		 *
		 * @return The number of entries currently stored.
		 */
		UI64 Size() const { return entryCounter; }

		/**
		 * Get the size of the Type.
		 *
		 * @return The size of the type in bytes.
		 */
		constexpr UI64 TypeSize() const { return sizeof(Type); }

		/**
		 * Get the total number of elements that can be stored.
		 *
		 * @return The size of the array.
		 */
		constexpr UI64 Capacity() const { return ElementCount; }

	private:
		Type mEntries[ElementCount] = {};	// The entry store.
		UI64 entryCounter = 0;	// Keeps track of the number of elements stored.
	};
}

#endif // !_DYNAMIK_STATIC_QUEUE_H
