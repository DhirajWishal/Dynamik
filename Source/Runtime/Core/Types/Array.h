// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_TYPES_ARRAY_H
#define _DYNAMIK_TYPES_ARRAY_H

/*
 Dynamic Array for the Dynamik Engine.

 Author:	Dhiraj Wishal
 Project:	Dynamik Engine
 Date:		22/03/2020
 IDE:		MS Visual Studio 2019
*/

#include "Core/Memory/StaticAllocator.h"
#include "Core/Memory/MemoryFunctions.h"
#include "Core/Macros/MemoryMacro.h"

#include <vector>	/* Required when converting to ARRAY<TYPE> */

#include <future>	/* REMOVE AFTER ADDING THE THREAD MANAGER */
#include <functional>	/* Required for Lambdas */

namespace Dynamik
{
	template<class TYPE, UI64 DefaultAlignment>
	class StaticAllocator;	// Static Allocator declaration
	template<class TYPE>
	class POINTER;			// Pointer declaration

	/* GLOBAL
	 * Global Array mutex to make the array thread safe.
	 */
	static std::mutex __globalArrayMutex;

	/* PUBLIC ENUM
	 * Dynamik Array Destructor Call Modes.
	 * This either allows the destructor to call all the destructors of stored variables or orphan them all.
	 */
	enum class DMK_API DMKArrayDestructorCallMode {
		DMK_ARRAY_DESTRUCTOR_CALL_MODE_DESTRUCT_NONE,	// Does not call the destructor in data. Execution speed is high.
		DMK_ARRAY_DESTRUCTOR_CALL_MODE_DESTRUCT_ALL,	// Calls destructor in all elements. Execution speed depends on the time taken to destroy.
		DMK_ARRAY_DESTRUCTOR_CALL_MODE_DESTRUCT_ALL_THREADED,	// Calls the destructor for each element in a thread.
		DMK_ARRAY_DESTRUCTOR_CALL_MODE_DESTRUCT_UNDEFINED	// Undefined
	};

	/* TEMPLATED
	 * Dynamic Array data structure for the Dynamik Engine.
	 * This array can store any data defined in the data type TYPE and supports multiple dimensions.
	 * Tested to be faster than the ARRAY<TYPE> library/ data type.
	 * This also contains utility functions related to array and pointer manipulation.
	 *
	 * This can also be used as:
	 *     Dynamic Array
	 *     Stack
	 *     Queue
	 *     Deque (Dequeue)
	 *
	 * @warn: The Dynamic Array does not call the destructor for all the stored elements at default.
				If needed to call, DestructorCallMode must be set to either ALL or ALL THREADED.
	 *
	 * @tparam TYPE: Data type of the array.
	 * @tparam AllocationCount: How many extra slots should be allocated. Default is 1.
	 * @tparam DestructorCallMode: Should or should not call the destructor of all the stored elements.
	 * @tparam Allocator: The allocator used to allocate the memory.
	 */
	template<class TYPE, UI64 AllocationCount = 1, DMKArrayDestructorCallMode DestructorCallMode = DMKArrayDestructorCallMode::DMK_ARRAY_DESTRUCTOR_CALL_MODE_DESTRUCT_NONE, class Allocator = StaticAllocator<TYPE>>
	class  DMK_API ARRAY {
		/* DEFAULTS */

		/* STATIC ASSERT
		 * Check if the Template argument is not void.
		 * Compile time check.
		 */
		static_assert(!isType<TYPE, void>::result, "void Is Not Accepted As A Template Argument! ARRAY<TYPE, Allocator>");

		/* STATIC ASSERT
		 * Check if both the template arguments are same.
		 * Compile time check.
		 */
		static_assert(!isType<TYPE, Allocator>::result, "Invalid Template Arguments! ARRAY<TYPE, Allocator>");

		/* PRIVATE DATATYPE
		 * Used as a private data type.
		 */
		using PTR = POINTER<TYPE>;

		/* PRIVATE DATATYPE
		 * Used as a raw pointer.
		 */
		using RPTR = TYPE*;

		/* HELPER STRUCTURE
		 * Store pointer data temporarily.
		 */
		struct _pointerContainer {
			_pointerContainer() {}	// default constructor
			~_pointerContainer() {}	// default destructor

			PTR _beginPtr;	// begin pointer
			PTR _endPtr;	// end pointer
			PTR _nextPtr;	// next pointer
		};

	public:
		/* CONSTRUCTOR
		 * Default Constructor.
		 */
		ARRAY()
		{
			_setLocalDataToDefault();
		}

		/* CONSTRUCTOR
		 * Default Constructor and Initializer.
		 * Sets the size of the Array to a specified amount.
		 * Data added after the limit will not be included.
		 *
		 * @param size: Size to be allocated.
		 */
		ARRAY(UI64 size)
		{
			if (size)
			{
				if ((size + _getAllocatableSize(size)) > maxSize()) return; /* TODO: Error Flagging */

				_reAllocateBack(_getAllocatableSize(size));
			}
			else
				_reAllocateBack(_getNextSize());

			myDataCount = size;
		}

		/* CONSTRUCTOR
		 * Default Constructor and Initializer.
		 * Sets the size of the Array to a specified amount and initializes it with a value.
		 * Data added after the limit will not be included.
		 *
		 * @param size: Size to be allocated.
		 * @param value: Value to initialize the Array with.
		 */
		ARRAY(UI64 size, const TYPE& value)
		{
			setSizeAndValue(size, value);
		}

		/* CONSTRUCTOR
		 * Constructs the Array by initializing the data in another array.
		 *
		 * @param arr: Array used to initialize this.
		 */
		ARRAY(const TYPE* arr)
		{
			if (_getAllocationSize() > maxSize()) return; /* TODO: Error Flagging */

			myDataCount = _getSizeOfRawArray(arr);
			_reAllocateBack(_getNextSizeToFit(myDataCount));
			DMKMemoryFunctions::setData(myBeginPtr, 0, capacity());
		}

		/* CONSTRUCTOR
		 * Constructs the Array by initializing the data in an initializer list.
		 *
		 * @param list: Initializer list used to initialize this.
		 */
		ARRAY(std::initializer_list<TYPE> list, UI64 size = 1)
		{
			if (list.size() > maxSize()); /* TODO: Error Flagging */

			if (list.size() <= 1)
			{
				if ((list.size() + _getNextSizeToFit(_getAllocatableSize(list.size()))) > maxSize()) return; /* TODO: Error Flagging */

				if (list.size())
					_reAllocateBack(_getNextSizeToFit(_getAllocatableSize(list.size())));
				else
					_reAllocateBack(_getNextSize());

				if (list.size())
					DMKMemoryFunctions::moveData(myBeginPtr, (PTR)list.begin(), (PTR)list.end() - (PTR)list.begin());
			}
			else
			{
				_reAllocateBack(_getNextSizeToFit(_getAllocatableSize(list.size())));
				DMKMemoryFunctions::moveData(myBeginPtr, (PTR)list.begin(), (PTR)list.end() - (PTR)list.begin());
			}

			myDataCount = list.size();
			myNextPtr += myDataCount;
		}

		/* CONSTRUCTOR
		 * Constructs the Array by using another Array.
		 *
		 * @param vector: Other Array.
		 */
		ARRAY(const ARRAY<TYPE>& arr)
		{
			if (arr.size())
				_copyArrayOverride(arr.begin(), arr.size());
			else
				_reAllocateBack(_getNextSize());
		}

		/* CONSTRUCTOR
		 * Constructs the Array by using another Array.
		 *
		 * @param vector: Other Array.
		 */
		ARRAY(ARRAY<TYPE>&& arr)
		{
			_move(std::move(arr));
		}

		/* CONSTRUCTOR
		 * Constructs the Array by using ARRAY<TYPE>.
		 *
		 * @param vector: Other vector.
		 */
		ARRAY(std::vector<TYPE> vector)
		{
			if (vector.size() > maxSize()); /* TODO: Error Flagging */

			_reAllocateBack(_getAllocatableSize(vector.size()));
			DMKMemoryFunctions::moveData(myBeginPtr, (PTR)vector.begin()._Unwrapped(), (PTR)vector.end()._Unwrapped() - (PTR)vector.begin()._Unwrapped());

			myDataCount = vector.size();
			myNextPtr += myDataCount;
		}

		/* DESTRUCTOR
		 * Default Destructor.
		 */
		~ARRAY()
		{
			_terminate();
		}

		/* PRIVATE DATA TYPES */
	public:
		/* DATATYPE
		 * Iterator of the Array.
		 */
		typedef PTR ITERATOR;
		typedef ITERATOR iterator;	// for vector class compatibility

		/* PRIVATE FUNCTIONS */
	public:
		/* FUNCTION
		 * Set the Array to a pre defined one.
		 *
		 * @param arr: Array to assign this with.
		 */
		void set(const PTR arr)
		{
			if (_getAllocationSize() > maxSize()) return; /* TODO: Error Flagging */

			if (myBeginPtr.isValid())
				Allocator::deallocateRange(myBeginPtr, myEndPtr);

			myDataCount = _getSizeOfRawArray(arr);
			_reAllocateBack(_getNextSizeToFit(myDataCount));
			DMKMemoryFunctions::moveData(myBeginPtr, arr.get(), _getAllocationSize());
		}

		/* FUNCTION
		 * Set a value to a given index.
		 *
		 * @param index: Index where to set the value.
		 * @param value: Value to be updated.
		 */
		void set(UI64 index, const TYPE& value)
		{
			if (!isValidIndex(index)) return; /* TODO: Error Flagging */

			myNextPtr = &myBeginPtr[_getProcessedIndex(index)];
			myNextPtr = (TYPE)value;
			myNextPtr++;
			myDataCount++;
		}

		/* FUNCTION
		 * Set the values from an iterator to this.
		 *
		 * @param first: First iterator.
		 * @param last: Last iterator.
		 */
		void set(ITERATOR first, ITERATOR last)
		{
			UI64 _byteSize = last - first;
			if (_byteSize)
			{
				myDataCount = (_byteSize) / typeSize();
				if (_byteSize > _getAllocationSize())
					_reAllocateAssign(_getAllocatableSize(_byteSize));

				DMKMemoryFunctions::moveData(myBeginPtr, first, _byteSize);
				myNextPtr += myDataCount;
			}
			else
			{
				if (!myBeginPtr.isValid())
					_reAllocateBack(_getNextSize());
			}
		}

		/* FUNCTION
		 * Set values to this using an initializer list.
		 *
		 * @param list: List to be used to initialize this.
		 */
		void set(std::initializer_list<TYPE> list)
		{
			if (list.size() > maxSize()); /* TODO: Error Flagging */

			if (list.size() > capacity())
				_reAllocateAssign(_getAllocatableSize(list.size()));

			DMKMemoryFunctions::moveData(myBeginPtr, (PTR)list.begin(), (PTR)list.end() - (PTR)list.begin());
			myDataCount = list.size();
			myNextPtr += myDataCount;
		}

		/* FUNCTION
		 * Constructs the Array by using another Array.
		 *
		 * @param array: The other array.
		 */
		void set(const ARRAY<TYPE>& array)
		{
			set(array.begin(), array.end());
		}

		/* FUNCTION
		 * Push Elements to the end of the Array.
		 *
		 * @param data: Data to be added to the Array (lvalue).
		 */
		void pushBack(const TYPE& data)
		{
			if (myNextPtr.getPointerAsInteger() >= myEndPtr.getPointerAsInteger())
				_reAllocateAndPushBack(_getNextSize(), data);
			else
				_addDataBack(data);

			myDataCount++;
		}

		/* FUNCTION
		 * Push Elements to the end of the Array.
		 *
		 * @param data: Data to be added to the Array (rvalue).
		 */
		void pushBack(TYPE&& data)
		{
			pushBack((TYPE&)data);
		}

		/* FUNCTION
		 * Get the last element in the Array.
		 */
		TYPE back()
		{
			return myBeginPtr[myDataCount - 1];
		}

		/* FUNCTION
		 * Get the last element in the Array and remove it.
		 */
		TYPE popBack()
		{
			TYPE _data = myBeginPtr[myDataCount - 1];
			myNextPtr--;
			myDataCount--;
			return _data;
		}

		/* FUNCTION
		 * Push Elements to the beginning of the Array.
		 *
		 * @param data: Data to be added to the Array (lvalue).
		 */
		void pushFront(const TYPE& data)
		{
			if (myDataCount > (capacity() * 2))
				myDataCount = 0;

			if (myNextPtr.getPointerAsInteger() >= myEndPtr.getPointerAsInteger())
				_reAllocateAndPushFront(_getNextSize(), data);
			else
				_addDataBack(data);

			myDataCount++;
		}

		/* FUNCTION
		 * Push Elements to the beginning of the Array.
		 *
		 * @param data: Data to be added to the Array (rvalue).
		 */
		void pushFront(TYPE&& data)
		{
			pushFront((TYPE&)data);
		}

		/* FUNCTION
		 * Get the first element of the Array.
		 */
		TYPE front()
		{
			if (myBeginPtr.isValid())
				return myBeginPtr[0];

			return TYPE();
		}

		/* FUNCTION
		 * Get the first element in the Array and remove it.
		 */
		TYPE popFront()
		{
			return _popFrontReallocate();
		}

		/* FUNCTION
		 * Remove an element at a given index.
		 *
		 * @param index: The element index to be removed.
		 */
		void remove(UI64 index = 0)
		{
			if (!isValidIndex(index)) return; /* TODO: Error Flagging. */

			myBeginPtr[_getProcessedIndex(index)] = TYPE();
			_compactAfterRemove(index);
			myDataCount--;
		}

		/* FUNCTION
		 * Resize the Array to a set size which cannot be resized.
		 *
		 * @param size: The size to be allocated to (number of data to hold).
		 */
		void setSize(const UI64& size)
		{
			if (size > maxSize()) return; /* TODO: Error Flagging */

			if (myBeginPtr.isValid())
				Allocator::deallocate(myBeginPtr, _getAllocationSize());

			_reAllocateBack(_getAllocatableSize(size));
		}

		/* FUNCTION
		 * Resize the Array to a set size and initialize it with values which cannot be resized.
		 *
		 * @param size: The size to be allocated to (number of data to hold).
		 * @param value: The value to fill the array with.
		 */
		void setSizeAndValue(const UI64& size, const TYPE& value) {
			if (size)
			{
				UI64 _allocatableSize = _getAllocatableSize(size);
				if ((size + _allocatableSize) > maxSize()) return; /* TODO: Error Flagging */

				_reAllocateBack(_allocatableSize);
				_fillWithData(size, TYPE());
			}
			else
			{
				_reAllocateBack(_getNextSize());
				_fillWithData(capacity(), TYPE());
			}

			myDataCount = size;
			myNextPtr += size;
		}

		/* FUNCTION
		 * Return the value at the given index.
		 * Flags an error if the given index is invalid.
		 *
		 * @param index: Index to be accessed.
		 */
		TYPE& at(I64 index = 0)
		{
			if (index >= (I64)_getSizeOfThis() || (index <= (I64)(0 - _getSizeOfThis()))); // TODO: error handling

			return myBeginPtr[_getProcessedIndex(index)];
		}

		/* FUNCTION
		 * Return the value at the given index.
		 * Flags an error if the given index is invalid.
		 *
		 * @param index: Index to be accessed.
		 */
		const TYPE& at(I64 index = 0) const
		{
			if (index >= (I64)_getSizeOfThis() || (index <= (I64)(0 - _getSizeOfThis()))); // TODO: error handling

			return myBeginPtr[_getProcessedIndex(index)];
		}

		/* FUNCTION
		 * Return the location of the stored data.
		 *
		 * @param index: Index of the stored data.
		 */
		const TYPE* location(I64 index)
		{
			if (index >= (I64)_getSizeOfThis() || (index <= (I64)(0 - _getSizeOfThis()))); // TODO: error handling

			return &myBeginPtr[_getProcessedIndex(index)];
		}

		/* FUNCTION
		 * Clear the whole Array.
		 */
		void clear()
		{
			_terminate();
			_setLocalDataToDefault();
		}

		/* FUNCTION
		 * Resize the Array.
		 *
		 * @param size: Size to which the Array should be resized.
		 */
		void resize(UI64 size)
		{
			if (size)
			{
				if (size > maxSize()) return; /* TODO: Error Flagging */

				if (myBeginPtr.getPointerAsInteger() != myEndPtr.getPointerAsInteger())
					Allocator::deallocate(myBeginPtr.get(), _getAllocationSize());

				_reAllocateAssign(_getAllocatableSize(size));
				_fillWithData(capacity(), TYPE());

				myDataCount = size;
			}
		}

		/* FUNCTION
		 * Resize the Array.
		 *
		 * @param size: Size to which the Array should be resized.
		 * @param value: The value to initialize the Array with.
		 */
		void resize(UI64 size, const TYPE& value)
		{
			if (size > maxSize()) return; /* TODO: Error Flagging */

			if (myBeginPtr.getPointerAsInteger() != myEndPtr.getPointerAsInteger())
				Allocator::deallocate(myBeginPtr.get(), _getAllocationSize());

			_reAllocateAssign(_getAllocatableSize(size));
			_fillWithData(capacity(), (TYPE&&)value);

			_setValue(value, capacity());
		}

		/* FUNCTION
		 * Fill the array with a value.
		 * If the indexes are invalid, an error is flagged.
		 *
		 * @param value: Value to fill the array with.
		 * @param startIndex: Index of the first place.
		 * @param endIndex: Index of the last place.
		 */
		void fill(const TYPE& value, UI64 startIndex, UI64 endIndex)
		{
			if ((endIndex >= _getSizeOfThis()) || (startIndex < endIndex)); // TODO:: error handling

			while (startIndex <= endIndex)
			{
				*_getPointer(startIndex) = value;
				startIndex++;
			}
		}

		/* FUNCTION
		 * Update value in an index.
		 * Raises a flag if the index is invalid.
		 *
		 * @param value: Value to be updated.
		 * @param index: Index to be updated.
		 */
		void update(const TYPE& value, UI64 index = 0)
		{
			if (index >= _getSizeOfThis()); // TODO: error handling

			*_getPointer(index) = value;
		}

		/* FUNCTION
		 * Insert the content of another Array to the current Array.
		 *
		 * @param arr: Array with the same type to be contacted.
		 */
		void insert(ARRAY<TYPE> arr)
		{
			if (arr.size() < 1)
				return;

			if (arr.size() > capacity())
				_reAllocateAssign(_getAllocatableSize(arr.size()));

			DMKMemoryFunctions::moveData(myNextPtr, arr.begin().get(), typeSize() * arr.size());
			myDataCount += arr.size();
			myNextPtr += arr.size();
		}

		/* FUNCTION
		 * Insert the content of another Array to the current Array.
		 *
		 * @param first: Starting iterator.
		 * @param last: End iterator.
		 */
		ITERATOR insert(ITERATOR first, ITERATOR last)
		{
			if ((UI64)(last - first) > _getAllocationSize())
				_reAllocateAssign(last.getPointerAsInteger() - first.getPointerAsInteger());

			DMKMemoryFunctions::moveData(myBeginPtr, first, last - first);
			UI64 _size = (UI64)(last - first);
			myDataCount += _size;
			myNextPtr += _size;
			return myNextPtr;
		}

		/* FUNCTION
		 * Emplace a value to a given index.
		 * Raises a flag if the index is invalid.
		 *
		 * @param value: Value to be updated.
		 * @param index: Index to be updated.
		 */
		void emplace(const TYPE& value, UI64 index = 0)
		{
			if (index >= _getSizeOfThis()); // TODO: error handling

			myBeginPtr[index] = value;
		}

		/* FUNCTION
		 * Check if the given index is valid.
		 *
		 * @param index: Index to be checked.
		 */
		B1 isValidIndex(I32 index)
		{
			if (index > 0)
			{
				if (index < _getAllocationSize())
					return true;
			}
			else
			{
				index *= (-1);
				if (index > (_getAllocationSize() * (-1)))
					return true;
			}

			return false;
		}

		/* FUNCTION
		 * Check if a given index range is valid.
		 *
		 * @param first: First index.
		 * @param last: Last index.
		 */
		B1 isValidIndexRange(I32 first, I32 last)
		{
			return isValidIndex(first) && isValidIndex(last);
		}

		/* FUNCTION
		 * Bubble sort for the array.
		 * Sort the Array in ascending or descending order.
		 *
		 * @param isAsc = true: Sorting type (true = ascending, false = descending)
		 */
		void bubbleSort(B1 isAsc = true)
		{
			ARRAY<TYPE> _localArray = this;
			UI64 _indexCount = 0;
			UI64 _index, _itr;
			while (_indexCount < (_getSizeOfThis() - 1))
			{
				_index = 0;
				_itr = 1;
				while (_itr < _getSizeOfThis() - _indexCount)
				{
					if (isAsc)
					{
						if (_localArray.at(_index) > _localArray.at(_itr))
						{
							TYPE _temp = _localArray.at(_index);
							_localArray.update(_localArray.at(_itr), _index);
							_localArray.update(_temp, _itr);
						}
					}
					else
					{
						if (_localArray.at(_index) < _localArray.at(_itr))
						{
							TYPE _temp = _localArray.at(_index);
							_localArray.update(_localArray.at(_itr), _index);
							_localArray.update(_temp, _itr);
						}
					}
					_index++;
					_itr++;
				}
				_indexCount++;
			}
		}

		/* FUNCTION
		 * Get a sub Array from this.
		 *
		 * @param from: First index.
		 * @param toWhere: Last index.
		 */
		ARRAY<TYPE> subArray(UI64 from, UI64 toWhere)
		{
			if (!isValidIndexRange(from, toWhere)) return; /* TODO: Error Flagging */

			ARRAY<TYPE> _local(toWhere - from);

			for (; from <= toWhere; from++)
				_local.pushBack(at(from));

			return _local;
		}

		/* FUNCTION
		 * Get a sub Array from this.
		 *
		 * @param from: First index.
		 * @param toWhere: Last index.
		 */
		ARRAY<TYPE> subArray(SI32 from, SI32 toWhere)
		{
			if (!isValidIndexRange(from, toWhere)) return; /* TODO: Error Flagging */

			ARRAY<TYPE> _local((from - toWhere) * -1);

			for (; from <= toWhere; from++)
				_local.pushBack(at(from));

			return _local;
		}

		/* FUNCTION
		 * Convert this to a ARRAY<TYPE>.
		 */
		std::vector<TYPE> toVector()
		{
			std::vector<TYPE> _localVector;
			for (ITERATOR _itr = begin(); _itr != end(); _itr++)
				_localVector.push_back(*_itr);

			return _localVector;
		}

		/* FUNCTION
		 * Return the size of the Array.
		 *
		 * @return: Element count.
		 */
		const UI64 size() const noexcept { return _getSizeOfThis(); }

		/* FUNCTION
		 * Return the maximum size allocatable in an Array.
		 *
		 * @return: Element count.
		 */
		const UI64 maxSize() const noexcept { return ((UI64)-1) / sizeof(TYPE); }

		/* FUNCTION
		 * Return the number of elements that can be stored before the next allocation.
		 *
		 * @return: Element count.
		 */
		const UI64 capacity() const noexcept
		{
			if (_getAllocationSize() == 0 || sizeof(TYPE) == 0)
				return 0;

			return _getAllocationSize() / sizeof(TYPE);
		}

		/* FUNCTION
		 * Return the size of TYPE.
		 */
		const UI64 typeSize() const noexcept { return sizeof(TYPE); }

		/* FUNCTION
		 * Return the current allocation size.
		 * This size is the size available till the next allocation.
		 *
		 * @return: Byte count.
		 */
		const UI64 allocationSize() const noexcept { return _getAllocationSize(); }

		/* FUNCTION
		 * Check if the Array is empty.
		 */
		const B1 empty() const noexcept { return (_getSizeOfThis()) != 0; }

		/* FUNCTION
		 * Get data pointer of the Array.
		 */
		const RPTR data() const noexcept { return myBeginPtr.get(); }

		/* FUNCTION
		 * Begin iterator of the Array.
		 */
		const ITERATOR begin() const noexcept { return myBeginPtr; }

		/* FUNCTION
		 * End iterator of the Array.
		 */
		const ITERATOR end() const noexcept
		{
			if (myNextPtr.getPointerAsInteger() > myBeginPtr.getPointerAsInteger())
				return myNextPtr;

			if (myDataCount)
				return (PTR)(myBeginPtr.get() + myDataCount);

			if (myDataCount == 0)
				return myBeginPtr;

			return myEndPtr;
		}

		/* FUNCTION
		 * Find a given value in this array.
		 *
		 * @param data: Data to be searched for.
		 * @return: Array of indexes which the gived data is found.
		 */
		ARRAY<UI64> find(const TYPE& data)
		{
			ARRAY<UI64> _indexContainer;

			for (UI64 _itr = 0; _itr < size(); _itr++)
				if (this->at(_itr) == data)
					_indexContainer.pushBack(_itr);

			return _indexContainer;
		}

		/* FUNCTION
		 * Find a given value in this array.
		 *
		 * @param data: Data to be searched for.
		 * @return: Array of indexes which the gived data is found.
		 */
		ARRAY<UI64> find(TYPE&& data)
		{
			ARRAY<UI64> _indexContainer;

			for (UI64 _itr = 0; _itr < size(); _itr++)
				if (this->at(_itr) == data)
					_indexContainer.pushBack(_itr);

			return _indexContainer;
		}

		/* FUNCTION
		 * Search the current array and find the requested data and return its index and its value as a std::pair<>.
		 * Returns an empty pair if not found.
		 *
		 * @warn: Only applicable for simple types.
		 * @param key: The value to be searched for.
		 */
		std::pair<UI64, TYPE> findFirst(const TYPE& key)
		{
			for (UI64 _itr = 0; _itr < size(); _itr++)
			{
				if (this->at(_itr) == key)
				{
					return { _itr, key };
				}
			}

			return std::pair<UI64, TYPE>();
		}

		/* FUNCTION
		 * Returns a hash for the content stored in the array.
		 */
		UI64 hash()
		{
			UI64 _hashInt = 0;
			ITERATOR begin = myBeginPtr;

			while (begin != end())
			{
				_hashInt = _hashInt ^ begin.getPointerAsInteger();
				begin++;
			}

			return _hashInt;
		}

		/* TEMPLATED FUNCTION
		 * Casts the data stored in this array to the provided type.
		 */
		template<class SUB_TYPE>
		ARRAY<SUB_TYPE> cast()
		{
			ARRAY<SUB_TYPE> _newArr;

			for (auto _elem : *this)
				_newArr.push_back(Cast<SUB_TYPE>(_elem));

			return _newArr;
		}

		/* FUNCTION
		 * Return the first index of the required data.
		 * Return -1 if not found.
		 *
		 * @param data: The value to be checked.
		 */
		const I64 indexOf(const TYPE& data) const
		{
			for (I64 index = 0; index < size(); index++)
				if (at(index) == data)
					return index;

			return -1;
		}

		/* PUBLIC OPERATORS */
	public:
		/* OPERATOR
		 * [] operator overload.
		 * Return the value at the given index.
		 * Raises a flag if the index is invalid.
		 *
		 * @param index: Index to be returned.
		 */
		TYPE& operator[](I64 index)
		{
			return this->at(index);
		}

		/* OPERATOR
		 * [] operator overload.
		 * Return the value at the given index.
		 * Raises a flag if the index is invalid.
		 *
		 * @param index: Index to be returned.
		 */
		const TYPE& operator[](I64 index) const
		{
			return this->at(index);
		}

		/* OPERATOR
		 * == operator overload.
		 * Check if the arrays are similar.
		 *
		 * @param data: Array to be checked with.
		 */
		B1 operator==(ARRAY<TYPE>& data)
		{
			if (this->_getSizeOfThis() != data.size())
				return false;
			for (UI64 _itr = 0; _itr < this->_getSizeOfThis(); _itr++)
				if (this->at(_itr) != data.at(_itr))
					return false;

			return true;
		}

		/* OPERATOR
		 * + operator overload.
		 * Concat another Array with the similar type.
		 *
		 * @param data: Array to be contacted with.
		 */
		ARRAY<TYPE>& operator+(const ARRAY<TYPE>& data)
		{
			this->insert(data);
			return *this;
		}

		/* OPERATOR
		 * = operator overload.
		 * Get data from an array and initialize it to this.
		 *
		 * @para arr: Array to be initialized to this.
		 */
		ARRAY<TYPE>& operator=(const ARRAY<TYPE>& arr)
		{
			this->_copyArrayOverride(arr.begin(), arr.size());
			return *this;
		}

		/* OPERATOR
		 * = operator overload.
		 * Get data from an array and initialize it to this.
		 *
		 * @para arr: Array to be initialized to this.
		 */
		ARRAY<TYPE>& operator=(ARRAY<TYPE>&& arr) noexcept
		{
			this->_move(std::move(arr));

			return *this;
		}

		/* OPERATOR
		 * = operator overload.
		 * Get data from a raw array and initialize it to this.
		 *
		 * @para arr: Raw array to be initialized to this.
		 */
		ARRAY<TYPE>& operator=(const PTR arr)
		{
			this->set(arr);
			return *this;
		}

		/* OPERATOR
		 * = operator overload.
		 * Get data from a initializer list and initialize it to this.
		 *
		 * @para list: Raw array to be initialized to this.
		 */
		ARRAY<TYPE>& operator=(std::initializer_list<TYPE> list)
		{
			this->set(list);
			return *this;
		}

		/* STATIC FUNCTION
		 * Copy contents from one Array to another.
		 *
		 * @param source: Source Array.
		 * @param destination: Destination Array.
		 */
		template<class SUB_TYPE>
		static void copy(ARRAY<SUB_TYPE>* source, ARRAY<SUB_TYPE>* destination)
		{
			*destination = *source;
		}

		/* ARRAY MANIPULATION FUNCTIONS */
	private:
		/* PRIVATE FUNCTION
		 * Move data to this from another array.
		 *
		 * @param arr: Other array.
		 */
		inline void _move(ARRAY<TYPE>&& arr)
		{
			if (this == &arr)
				return;

			this->myBeginPtr = arr.myBeginPtr;
			this->myNextPtr = arr.myNextPtr;
			this->myEndPtr = arr.myEndPtr;
			this->myDataCount = arr.myDataCount;

			arr.myBeginPtr.turnNull();
			arr.myNextPtr.turnNull();
			arr.myEndPtr.turnNull();
			arr.myDataCount = 0;
		}

		/* PRIVATE FUNCTION
		 * Add data to the end of the Array.
		 *
		 * @param data: Data to be emplaced.
		 */
		inline void _addDataBack(const TYPE& data)
		{
			__globalArrayMutex.lock();
			Allocator::set(myNextPtr, (TYPE&&)data);
			__globalArrayMutex.unlock();
			myNextPtr++;
		}

		/* PRIVATE FUNCTION
		 * Add data to the end of the Array.
		 *
		 * @param data: Data to be emplaced.
		 */
		inline void _addDataFront(const TYPE& data)
		{
			myBeginPtr--;
			__globalArrayMutex.lock();
			Allocator::set(myBeginPtr, (TYPE&&)data);
			__globalArrayMutex.unlock();
		}

		/* PRIVATE FUNCTION
		 * Allocate a fresh buffer with a given size.
		 *
		 * @param size: Size of the buffer to be allocated.
		 */
		inline PTR _allocateBuffer(UI64 size)
		{
			return Allocator::rawAllocate(size);
		}

		/* PRIVATE FUNCTION
		 * Resize the data store and add the new space to the back.
		 *
		 * @param newSize: New size added to the pre-allocated size to be re-allocated.
		 */
		inline void _reAllocateBack(UI64 newSize)
		{
			PTR _newArr = Allocator::rawAllocate(newSize + _getAllocatableSize(capacity()));

			try
			{
				if (myBeginPtr.isValid())
				{
					DMKMemoryFunctions::moveData(_newArr, myBeginPtr, myNextPtr - myBeginPtr);
					Allocator::deallocateRange(myBeginPtr, myEndPtr);
				}
			}
			catch (...)
			{
				_destroyRange(_newArr, (TYPE*)(_newArr.getPointerAsInteger() + _getAllocationSize()));
				Allocator::deallocate(_newArr, _getAllocationSize());

				_newArr.turnNull();

				throw;
			}

			_basicInitializationBack(_newArr, capacity() + _calculateCapacityInSize(newSize), _getSizeOfThis());
		}

		/* PRIVATE FUNCTION
		 * Resize the data store.
		 *
		 * @param newSize: New size added to the pre-allocated size to be re-allocated.
		 */
		inline void _reAllocateFront(UI64 newSize)
		{
			PTR _newArr = Allocator::rawAllocate(newSize + _getAllocatableSize(capacity()));
			PTR _nxtPtr = _newArr;
			_nxtPtr += _calculateCapacityInSize(newSize);

			try
			{
				if (myBeginPtr.isValid())
				{
					DMKMemoryFunctions::moveData(_nxtPtr, myBeginPtr, myNextPtr - myBeginPtr);
					Allocator::deallocateRange(myBeginPtr, myEndPtr);
				}
			}
			catch (...)
			{
				_destroyRange(_newArr, (TYPE*)(_newArr.getPointerAsInteger() + _getAllocationSize()));
				Allocator::deallocate(_newArr, _getAllocationSize());

				_newArr.turnNull();

				throw;
			}

			_basicInitializationFront(_newArr, _calculateCapacityInSize(newSize), capacity() + _calculateCapacityInSize(newSize), _getSizeOfThis());
		}

		/* PRIVATE FUNCTION
		 * Re allocate memory and assign the size as the allocation size.
		 *
		 * @param size: The size to be allocated.
		 */
		inline void _reAllocateAssign(UI64 size)
		{
			PTR _newArr = Allocator::rawAllocate(size + _getAllocatableSize(capacity()));

			try
			{
				if (myBeginPtr.isValid())
				{
					DMKMemoryFunctions::moveData(_newArr, myBeginPtr, myNextPtr - myBeginPtr);
					Allocator::deallocateRange(myBeginPtr, myEndPtr);
				}
			}
			catch (...)
			{
				_destroyRange(_newArr, (TYPE*)(_newArr.getPointerAsInteger() + size));
				Allocator::deallocate(_newArr, _getAllocationSize());

				_newArr.turnNull();

				throw;
			}

			_basicInitializationBack(_newArr, capacity() + _calculateCapacityInSize(size), _getSizeOfThis());
		}

		/* PRIVATE FUNCTION
		 * Extend the size of the array.
		 *
		 * @param byteSize: The size to be added to the current allocation.
		 */
		inline void _extend(UI64 byteSize)
		{
			_reAllocateAssign(byteSize);
		}

		/* PRIVATE FUNCTION
		 * Create a new array and return it.
		 *
		 * @param newSize: New size added to the pre-allocated size to be re-allocated.
		 */
		inline _pointerContainer _reAllocateGetRaw(UI64 newSize)
		{
			_pointerContainer _container;
			_container._beginPtr = Allocator::rawAllocate(newSize + _getAllocatableSize(capacity()));
			_container._endPtr = _container._beginPtr;
			_container._endPtr += (capacity() + _calculateCapacityInSize(newSize));
			_container._nextPtr = _container._beginPtr;
			_container._nextPtr += _getSizeOfThis();

			return _container;
		}

		/* PRIVATE FUNCTION
		 * Resize the data store and add a value to the end.
		 *
		 * @param newSize: New size added to the pre-allocated size to be re-allocated.
		 * @param data: Data to be inserted to the end.
		 */
		inline void _reAllocateAndPushBack(UI64 newSize, const TYPE& data)
		{
			if ((newSize + _getAllocationSize()) > maxSize())
			{
				DMKErrorManager::issueErrorBox("The new allocation size is grater than the maximum allocatable size!");
				return;
			}
			_reAllocateBack(newSize);

			_addDataBack(data);
		}

		/* PRIVATE FUNCTION
		 * Resize the data store and add a value to the beginning.
		 *
		 * @param newSize: New size added to the pre-allocated size to be re-allocated.
		 * @param data: Data to be inserted to the end.
		 */
		inline void _reAllocateAndPushFront(UI64 newSize, const TYPE& data)
		{
			if (_getSizeOfThis() > (capacity() * 2))
				newSize = _getNextSize();

			if ((newSize + _getAllocationSize()) > maxSize()) return; /* TODO: Error Flagging */
			_reAllocateFront(newSize);

			_addDataFront(data);
		}

		/* PRIVATE FUNCTION
		 * Get the first value from the array and remove it.
		 * Then re allocate a new array to fit the size and move the old content to it.
		 */
		inline const TYPE& _popFrontReallocate()
		{
			if (!myBeginPtr.isValid())
				return TYPE();

			TYPE _data = front();
			DMKMemoryFunctions::setData((PTR)&myBeginPtr[0], 0, sizeof(TYPE));

			_pointerContainer _container = _reAllocateGetRaw(_getNextSize());

			PTR _localVec = &myBeginPtr[0];
			DMKMemoryFunctions::moveData(_localVec, (PTR)&myBeginPtr[0], _getSizeOfThis() - 1);

			try
			{
				if (_container._beginPtr.isValid())
				{
					DMKMemoryFunctions::moveData(_container._beginPtr, _localVec, _getSizeOfThis());
					_localVec.turnNull();
					Allocator::deallocateRange(myBeginPtr, myEndPtr);
				}
			}
			catch (...)
			{
				_destroyRange(_container._beginPtr, _container._endPtr);
				Allocator::deallocateRange(_container._beginPtr, _container._endPtr);

				_container._beginPtr.turnNull();
				_container._endPtr.turnNull();

				throw;
			}

			_basicInitializationBack(_container._beginPtr, _getAllocationSize(), _getSizeOfThis());
			return _data;
		}

		/* PRIVATE FUNCTION
		 * Remove the additional space after removal.
		 *
		 * @param removedIndex: Index where the data was removed.
		 */
		inline void _compactAfterRemove(UI64 removedIndex)
		{
			PTR _newArr = _allocateBuffer(_getAllocationSize());
			DMKMemoryFunctions::moveData(_newArr, (PTR)&myBeginPtr[removedIndex - 1], removedIndex);
			DMKMemoryFunctions::moveData((PTR)&_newArr[removedIndex], (PTR)&myBeginPtr[removedIndex + 1], myEndPtr - (PTR)&myBeginPtr[removedIndex + 1]);

			try
			{
				if (myBeginPtr.isValid())
					Allocator::deallocateRange(myBeginPtr, myEndPtr);
			}
			catch (...)
			{
				_destroyRange(_newArr, (RPTR)(_newArr.getPointerAsInteger() + _getAllocationSize()));
				Allocator::deallocateRange(_newArr, (RPTR)(_newArr.getPointerAsInteger() + _getAllocationSize()));

				_newArr.turnNull();

				throw;
			}

			_basicInitializationBack(_newArr, _getAllocationSize(), _getSizeOfThis());
		}

		/* PRIVATE FUNCTION
		 * Copy another array's data to this.
		 * Overrides previous allocation.
		 *
		 * @param beginAddr: Begin address of the other array.
		 * @param dataCount: Data count (size()) of the other array.
		 */
		inline void _copyArrayOverride(const PTR& beginAddr, const UI64& dataCount)
		{
			/* Check if the other array is empty. If true, don't do anything */
			if (!dataCount)
				return;

			/* Deallocate current array if already allocated */
			if ((myBeginPtr != myNextPtr) || myDataCount)
				_terminate();

			/* Allocate new buffer and move data from the old array */
			myBeginPtr = _allocateBuffer(dataCount * typeSize());
			DMKMemoryFunctions::moveData(myBeginPtr.get(), beginAddr.get(), dataCount * typeSize());

			/* Initialize pointers and data count */
			myDataCount = dataCount;
			myNextPtr = myBeginPtr;
			myNextPtr += myDataCount;
			myEndPtr += myDataCount;
		}

		/* POINTER MANIPULATION FUNCTIONS */
	private:
		/* PRIVATE FUNCTION
		 * Destroy all the data stored in a given range.
		 * Calls the destructor for all the data stored.
		 *
		 * @param first: Pointer to the first element.
		 * @param last: Pointer to the last element.
		 */
		inline void _destroyRange(PTR first, PTR last)
		{
			while (first.getPointerAsInteger() < last.getPointerAsInteger())
			{
				_singleDestruct(first);
				++first;
			}
		}

		///* PRIVATE STATIC
		// * Internal thread execution function.
		// *
		// * @param _thread: A n_internalThread
		// */
		// static void __internalThreadFunction(_internalThread* _thread)
		// {
		// 	_thread->_destroy();
		// }

		 /* PRIVATE FUNCTION
		  * Destroy all the data stored in a given range.
		  * Calls the destructor for all the data stored giving a thread for each.
		  *
		  * Number of threads equal to the number of logical cores in the CPU - 1.
		  * Each element is assigned to a chunk which is calculated based on the thread count.
		  * Each chunk is filled with elements and passed in to the _internalThread class.
		  * The _internalThread class executes in a single thread and calls the destructor of each element.
		  * A lock guard is placed so that memory corruption will not take place
		  *
		  * @param first: Pointer to the first element.
		  * @param last: Pointer to the last element.
		  */
		inline void _destroyRangeInThreads(PTR first, PTR last)
		{
			UI64 _passes = std::thread::hardware_concurrency() - 1;	// number of threads
			UI64 _chunks = size() / std::thread::hardware_concurrency();	// number of elements thats given for each thread
			ARRAY<std::future<void>, AllocationCount, DMKArrayDestructorCallMode::DMK_ARRAY_DESTRUCTOR_CALL_MODE_DESTRUCT_ALL> _threads(_passes);		// threads
			PTR _first;
			//_internalThread _localThread;

			while (--_passes)
			{
				_first = first;
				first += _chunks;

				//_localThread = _internalThread(_first, first);
				//add each destructor array to threads
				//_threads.push_back(std::async(std::launch::async, __internalThreadFunction, &_localThread));
			}

			// if elements are not destroyed fully, destroy them manually (in this thread)
			while (first != last)
			{
				first.dereference().~TYPE();
				first++;
			}
		}

		/* PRIVATE FUNCTION
		 * Destroy all the pointers that contained the heap data.
		 * Calls the destructor.
		 */
		inline void _destroyPointers()
		{
			myBeginPtr.~POINTER();
			myEndPtr.~POINTER();
			myNextPtr.~POINTER();
		}

		/* PRIVATE FUNCTION
		 * Call the destructor of a given destructor.
		 *
		 * @param data: Data to call the destructor.
		 */
		inline void _singleDestruct(RPTR data)
		{
			data->~TYPE();
		}

		/* PRIVATE FUNCTION
		 * Terminate the data stored in the local pointers.
		 */
		inline void _terminate()
		{
			if (DestructorCallMode == DMKArrayDestructorCallMode::DMK_ARRAY_DESTRUCTOR_CALL_MODE_DESTRUCT_ALL)
				_destroyRange(myBeginPtr, myNextPtr);
			else if (DestructorCallMode == DMKArrayDestructorCallMode::DMK_ARRAY_DESTRUCTOR_CALL_MODE_DESTRUCT_ALL_THREADED)
				_destroyRangeInThreads(myBeginPtr, myNextPtr);

			Allocator::deallocateRange(myBeginPtr, myEndPtr);
		}

		/* PRIVATE FUNCTION
		 * Clear all values and sets the local data to its default values.
		 */
		inline void _setLocalDataToDefault()
		{
			myBeginPtr.turnNull();
			myEndPtr = myBeginPtr;
			myNextPtr = myBeginPtr;
			myDataCount = 0;
		}

		/* UTILITY FUNCTIONS */
	private:
		/* PRIVATE
		 * Get the number of elements stored.
		 */
		inline const UI64 _getSizeOfThis() const
		{
			if (myDataCount > (capacity() * 2))
				return 0;

			return myDataCount;
		}

		/* PRIVATE
		 * Get the allocation size of this.
		 */
		inline const UI64 _getAllocationSize() const
		{
			return myEndPtr.getPointerAsInteger() - myBeginPtr.getPointerAsInteger();
		}

		/* PRIVATE
		 * Calculate the number of elements that can be stored in a size.
		 *
		 * @param bytes: Size of bytes.
		 */
		inline const UI64 _calculateCapacityInSize(UI64 bytes) const
		{
			if (bytes)
				return bytes / typeSize();

			return 0;
		}

		/* PRIVATE
		 * Calculate the allocatable size with raw size.
		 *
		 * @param rawSize: Size to be processed.
		 */
		inline const UI64 _getAllocatableSize(UI64 rawSize) const
		{
			return rawSize * typeSize();
		}

		/* PRIVATE FUNCTION
		 * Basic initializations.
		 * Set basic initializations for push_back function.
		 *
		 * @param dataStore: Begin address of the new Array.
		 * @param capacity: Capacity of the new allocation.
		 * @param dataCount: Number of data currently stored in the new Array.
		 */
		void _basicInitializationBack(TYPE* dataStore, UI64 capacity = 0, UI64 dataCount = 0)
		{
			myBeginPtr(dataStore);

			myEndPtr(dataStore);
			myEndPtr += capacity;

			myNextPtr(dataStore);
			myNextPtr += dataCount;
		}

		/* PRIVATE FUNCTION
		 * Basic initializations.
		 * Set basic initializations for the pushFront function.
		 *
		 * @param dataStore: Begin address of the new Array.
		 * @param capacity: Capacity of the new allocation.
		 * @param dataCount: Number of data currently stored in the new Array.
		 */
		void _basicInitializationFront(TYPE* dataStore, UI64 freeCapacity = 0, UI64 capacity = 0, UI64 dataCount = 0)
		{
			myBeginPtr(dataStore);
			myBeginPtr += freeCapacity;

			myEndPtr(dataStore);
			myEndPtr += capacity;

			myNextPtr(dataStore);
			myNextPtr += dataCount;
		}

		/* PRIVATE FUNCTION
		 * Get the next allocatable size.
		 */
		inline UI64 _getNextSize()
		{
			UI64 _oldCapacity = capacity();

			if (_oldCapacity > (maxSize() - _oldCapacity / 2))
				return AllocationCount * sizeof(TYPE);

			UI64 _nextCapacity = _oldCapacity + (_oldCapacity / 2);

			if (_nextCapacity < (AllocationCount * sizeof(TYPE)))
				return AllocationCount * sizeof(TYPE);

			return _nextCapacity;
		}

		/* PRIVATE FUNCTION
		 * Get the next allocatable size to fit a given size.
		 *
		 * @param basicSize: Size to be filled with.
		 */
		inline UI64 _getNextSizeToFit(UI64 basicSize)
		{
			UI64 _nextSize = _getNextSize();
			if ((basicSize % _nextSize))
				return (((basicSize / _nextSize) * _nextSize) + _nextSize);

			return (basicSize / _nextSize) * _nextSize;
		}

		/* PRIVATE FUNCTION
		 * Copy data from one location to another.
		 *
		 * @param source: Source address.
		 * @param destination: Destination address.
		 * @param size: Number of bytes to be copied.
		 */
		inline void _copyData(VPTR source, VPTR destination, UI64 size)
		{
			while (--size) *(TYPE*)source = *(TYPE*)destination;
		}

		/* PRIVATE FUNCTION
		 * Move data from this to another.
		 *
		 * @param newSpace: Source address.
		 * @param newSpaceSize: Number of bytes to be moved.
		 */
		inline void _moveToThis(VPTR newSpace, UI64 newSpaceSize)
		{
			DMKMemoryFunctions::moveData(myBeginPtr, (PTR)newSpace, newSpaceSize);
		}

		/* PRIVATE FUNCTION
		 * Move data from this to another.
		 *
		 * @param newSpace: Source address.
		 * @param newSpaceSize: Number of bytes to be moved.
		 */
		inline void _moveFromThis(VPTR newSpace, UI64 count)
		{
			DMKMemoryFunctions::moveData((PTR)newSpace, myBeginPtr, count);
		}

		/* PRIVATE FUNCTION
		 * Get the next pointer to data from a given index.
		 *
		 * @param index: Index of the pointer to retrieve.
		 */
		inline RPTR _getPointer(UI64 index = 0)
		{
			PTR _localPointer = myBeginPtr;
			_localPointer += index;
			return _localPointer;
		}

		/* PRIVATE FUNCTION
		 * Set a value to a number of elements.
		 *
		 * @param value: Value to be filled with.
		 * @param count: Number of elements to be filled with.
		 */
		inline void _setValue(TYPE value, UI64 count)
		{
			PTR _temp = myBeginPtr;
			while (_temp != myEndPtr)
			{
				_temp.set((TYPE&&)value);
				_temp++;
			}
		}

		/* PRIVATE FUNCTION
		 * Swap two elements.
		 *
		 * @param first: First element.
		 * @param second: Second element;
		 */
		inline void _swap(TYPE* first, TYPE* second)
		{
			TYPE _temp = *first;
			*first = *second;
			*second = _temp;
		}

		/* PRIVATE FUNCTION
		 * Get the size of a raw Array.
		 *
		 * @param arr: Raw Array.
		 */
		inline UI64 _getSizeOfRawArray(const PTR arr)
		{
			return sizeof(arr.get()) / sizeof(TYPE);
		}

		/* PRIVATE FUNCTION
		 * Process the index so that it always produce a indexable value.
		 *
		 * @param index: Index to be processed.
		 */
		inline UI64 _getProcessedIndex(I64 index) const
		{
			if (index < 0)
				index = (_getSizeOfThis() + index);

			return index;
		}

		/* PRIVATE FUNCTION
		 * Fills the allocated capacity with the constructor of the data type.
		 */
		inline void _fillWithData(UI64 capacity, TYPE&& data)
		{
			PTR _tempPtr = myBeginPtr;
			while (capacity--)
			{
				_tempPtr.set((TYPE&&)data);
				_tempPtr++;
			}
		}

		/* PRIVATE VARIABLES AND CONSTANTS */
	private:
		PTR myBeginPtr;		// begin pointer
		PTR myEndPtr = myBeginPtr;		// end pointer
		PTR myNextPtr = myBeginPtr;		// next pointer

		UI64 myDataCount = 0;	// data counter
	};
}

#endif // !_DATA_TYPES_ARRAY_H