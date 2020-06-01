#pragma once
#ifndef _DYNAMIK_THREAD_SAFE_ARRAY_H
#define _DYNAMIK_THREAD_SAFE_ARRAY_H

/*
 Author:    Dhiraj Wishal
 Date:      31/05/2020
*/
#include "Array.h"
#include <initializer_list>
#include <shared_mutex>

namespace Dynamik
{
	/* GLOBAL VARIABLE
	 * Global Thread Safe Array mutex.
	 */
	static std::shared_mutex __ts_array_mutex;

	/*
	 * Thread Safe Array for the Dynamik Engine
	 * This is a wrapper class for the ARRAY data type and this ensures thread-safe-ness to the array.
	 *
	 * @warn: This class might be slower than the traditional ARRAY class.
	 *
	 * @tparam TYPE: Data type of the array.
	 * @tparam AllocationCount: How many extra slots should be allocated. Default is 1.
	 * @tparam DestructorCallMode: Should or should not call the destructor of all the stored elements.
	 * @tparam Allocator: The allocator used to allocate the memory.
	 */
	template<class TYPE, UI64 AllocationCount = 1, DMKArrayDestructorCallMode DestructorCallMode = DMKArrayDestructorCallMode::DMK_ARRAY_DESTRUCTOR_CALL_MODE_DESTRUCT_NONE, class Allocator = StaticAllocator<TYPE>>
	class DMK_API TSArray {
		/* Main data store */
		ARRAY<TYPE, AllocationCount, DestructorCallMode, Allocator> myArray;

		/* PRIVATE DATATYPE
		 * Used as a private data type.
		 */
		using PTR = POINTER<TYPE>;

		/* PRIVATE DATATYPE
		 * Used as a raw pointer.
		 */
		using RPTR = TYPE*;

		/* PRIVATE DATATYPE
		 * Used to refer this.
		 */
		using THIS = TSArray<TYPE, AllocationCount, DestructorCallMode, Allocator>;

		/* PRIVATE DATATYPE
		 * Used to refer the array type.
		 */
		using STORE = ARRAY<TYPE, AllocationCount, DestructorCallMode, Allocator>;

		/* HELPER STRUCTURE
		 * Array locking mechanism
		 */
		struct DMK_API InternalLock {
			explicit InternalLock() { __ts_array_mutex.try_lock_shared(); }
			~InternalLock() noexcept { __ts_array_mutex.unlock_shared(); }
		};

	public:
		TSArray() = default;

		/*
		 * @param other: The other array to initailize this array with (rvalue).
		 */
		TSArray(const TSArray& other) : myArray(other.myArray), __isLocked(false) {}

		/*
		 * @param other: The other array to iniaialize this array with (lvalue).
		 */
		TSArray(TSArray&& other) : __isLocked(false)
		{
			myArray = other.myArray;
			other.myArray.clear();
		}

		/*
		 * @param other: The other ARRAY to initialize this array's store with.
		 */
		TSArray(const STORE& other) : myArray(other), __isLocked(false) {}

		/*
		 * Default constructor.
		 */
		~TSArray()
		{
			myArray.~ARRAY();
		}

		/* PRIVATE DATA TYPES */
	public:
		/* DATATYPE
		 * Iterator of the Array.
		 */
		typedef PTR ITERATOR;
		typedef ITERATOR iterator;	// for vector class compatibility

	public:
		/* FUNCTION
		 * Lock the array
		 */
		void lock()
		{
			__ts_array_mutex.lock();
			__isLocked = true;
		}

		/* FUNCTION
		 * Unlock the array
		 */
		void unlock()
		{
			__isLocked = false;
			__ts_array_mutex.unlock();
		}

	public:
		/* FUNCTION
		 * Set the Array to a pre defined one.
		 *
		 * @param arr: Array to assign this with.
		 */
		void set(const PTR arr)
		{
			InternalLock _lock;
			myArray.set(arr);
		}

		/* FUNCTION
		 * Set a value to a given index.
		 *
		 * @param index: Index where to set the value.
		 * @param value: Value to be updated.
		 */
		void set(UI64 index, const TYPE& value)
		{
			InternalLock _lock;
			myArray.set(index, value);
		}

		/* FUNCTION
		 * Set the values from an iterator to this.
		 *
		 * @param first: First iterator.
		 * @param last: Last iterator.
		 */
		void set(ITERATOR first, ITERATOR last)
		{
			InternalLock _lock;
			myArray.set(first, last);
		}

		/* FUNCTION
		 * Set values to this using an initializer list.
		 *
		 * @param list: List to be used to initialize this.
		 */
		void set(std::initializer_list<TYPE> list)
		{
			InternalLock _lock;
			myArray.set(list);
		}

		/* FUNCTION
		 * Constructs the Array by using another Array.
		 *
		 * @param array: The other array.
		 */
		void set(const STORE& other)
		{
			InternalLock _lock;
			myArray.set(other);
		}

		/* FUNCTION
		 * Push Elements to the end of the Array.
		 *
		 * @param data: Data to be added to the Array (lvalue).
		 */
		void pushBack(const TYPE& data)
		{
			InternalLock _lock;
			myArray.pushBack(data);
		}

		/* FUNCTION
		 * Push Elements to the end of the Array.
		 *
		 * @param data: Data to be added to the Array (rvalue).
		 */
		void pushBack(TYPE&& data)
		{
			InternalLock _lock;
			myArray.pushBack((TYPE&&)data);
		}

		/* FUNCTION
		 * Get the last element in the Array.
		 */
		TYPE back()
		{
			InternalLock _lock;
			return myArray.back();
		}

		/* FUNCTION
		 * Get the last element in the Array and remove it.
		 */
		TYPE popBack()
		{
			InternalLock _lock;
			return myArray.popBack();
		}

		/* FUNCTION
		 * Push Elements to the beginning of the Array.
		 *
		 * @param data: Data to be added to the Array (lvalue).
		 */
		void pushFront(const TYPE& data)
		{
			InternalLock _lock;
			myArray.pushFront(data);
		}

		/* FUNCTION
		 * Push Elements to the beginning of the Array.
		 *
		 * @param data: Data to be added to the Array (rvalue).
		 */
		void pushFront(TYPE&& data)
		{
			InternalLock _lock;
			myArray.pushFront((TYPE&&)data);
		}

		/* FUNCTION
		 * Get the first element of the Array.
		 */
		TYPE front()
		{
			InternalLock _lock;
			return myArray.front();
		}

		/* FUNCTION
		 * Get the first element in the Array and remove it.
		 */
		TYPE popFront()
		{
			InternalLock _lock;
			return myArray.popFront();
		}

		/* FUNCTION
		 * Remove an element at a given index.
		 *
		 * @param index: The element index to be removed.
		 */
		void remove(UI64 index = 0)
		{
			InternalLock _lock;
			myArray.remove(index);
		}

		/* FUNCTION
		 * Resize the Array to a set size which cannot be resized.
		 *
		 * @param size: The size to be allocated to (number of data to hold).
		 */
		void setSize(const UI64& size)
		{
			InternalLock _lock;
			myArray.setSize(size);
		}

		/* FUNCTION
		 * Resize the Array to a set size and initialize it with values which cannot be resized.
		 *
		 * @param size: The size to be allocated to (number of data to hold).
		 * @param value: The value to fill the array with.
		 */
		void setSizeAndValue(const UI64& size, const TYPE& value)
		{
			InternalLock _lock;
			myArray.setSizeAndValue(size, value);
		}

		/* FUNCTION
		 * Return the value at the given index.
		 * Flags an error if the given index is invalid.
		 *
		 * @param index: Index to be accessed.
		 */
		TYPE& at(I64 index = 0)
		{
			InternalLock _lock;
			return myArray.at(index);
		}

		/* FUNCTION
		 * Return the value at the given index.
		 * Flags an error if the given index is invalid.
		 *
		 * @param index: Index to be accessed.
		 */
		const TYPE& at(I64 index = 0) const
		{
			InternalLock _lock;
			return myArray.at(index);
		}

		/* FUNCTION
		 * Return the location of the stored data.
		 *
		 * @param index: Index of the stored data.
		 */
		const POINTER<TYPE> location(I64 index)
		{
			InternalLock _lock;
			return myArray.location(index);
		}

		/* FUNCTION
		 * Clear the whole Array.
		 */
		void clear()
		{
			InternalLock _lock;
			myArray.clear();
		}

		/* FUNCTION
		 * Resize the Array.
		 *
		 * @param size: Size to which the Array should be resized.
		 */
		void resize(UI64 size)
		{
			InternalLock _lock;
			myArray.resize(size);
		}

		/* FUNCTION
		 * Resize the Array.
		 *
		 * @param size: Size to which the Array should be resized.
		 * @param value: The value to initialize the Array with.
		 */
		void resize(UI64 size, const TYPE& value)
		{
			InternalLock _lock;
			myArray.resize(size, value);
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
			InternalLock _lock;
			myArray.fill(value, startIndex, endIndex);
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
			InternalLock _lock;
			myArray.update(value, index);
		}

		/* FUNCTION
		 * Insert the content of another Array to the current Array.
		 *
		 * @param arr: Array with the same type to be contacted.
		 */
		void insert(STORE arr)
		{
			InternalLock _lock;
			myArray.insert(arr);
		}

		/* FUNCTION
		 * Insert the content of another Array to the current Array.
		 *
		 * @param first: Starting iterator.
		 * @param last: End iterator.
		 */
		ITERATOR insert(ITERATOR first, ITERATOR last)
		{
			InternalLock _lock;
			return myArray.insert(first, last);
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
			InternalLock _lock;
			myArray.emplace(value, index);
		}

		/* FUNCTION
		 * Check if the given index is valid.
		 *
		 * @param index: Index to be checked.
		 */
		B1 isValidIndex(I32 index)
		{
			InternalLock _lock;
			return myArray.isValidIndex(index);
		}

		/* FUNCTION
		 * Check if a given index range is valid.
		 *
		 * @param first: First index.
		 * @param last: Last index.
		 */
		B1 isValidIndexRange(I32 index)
		{
			InternalLock _lock;
			return myArray.isValidIndexRange(index);
		}

		/* FUNCTION
		 * Bubble sort for the array.
		 * Sort the Array in ascending or descending order.
		 *
		 * @param isAsc = true: Sorting type (true = ascending, false = descending)
		 */
		void bubbleSort(B1 isAsc = true)
		{
			InternalLock _lock;
			myArray.bubbleSort(isAsc);
		}

		/* FUNCTION
		 * Get a sub Array from this.
		 *
		 * @param from: First index.
		 * @param toWhere: Last index.
		 */
		STORE subArray(UI64 from, UI64 toWhere)
		{
			InternalLock _lock;
			return myArray.subArray(from, toWhere);
		}

		/* FUNCTION
		 * Get a sub Array from this.
		 *
		 * @param from: First index.
		 * @param toWhere: Last index.
		 */
		STORE subArray(SI32 from, SI32 toWhere)
		{
			InternalLock _lock;
			return myArray.subArray(from, toWhere);
		}

		/* FUNCTION
		 * Convert this to a ARRAY<TYPE>.
		 */
		ARRAY<TYPE> toVector()
		{
			InternalLock _lock;
			return myArray.toVector();
		}

		/* FUNCTION
		 * Return the size of the Array.
		 *
		 * @return: Element count.
		 */
		const UI64 size() const noexcept
		{
			InternalLock _lock;
			return myArray.size();
		}

		/* FUNCTION
		 * Return the maximum size allocatable in an Array.
		 *
		 * @return: Element count.
		 */
		const UI64 maxSize() const noexcept
		{
			InternalLock _lock;
			return myArray.maxSize();
		}

		/* FUNCTION
		 * Return the number of elements that can be stored before the next allocation.
		 *
		 * @return: Element count.
		 */
		const UI64 capacity() const noexcept
		{
			InternalLock _lock;
			return myArray.capacity();
		}

		/* FUNCTION
		 * Return the size of TYPE.
		 */
		const UI64 typeSize() const noexcept
		{
			InternalLock _lock;
			return myArray.typeSize();
		}

		/* FUNCTION
		 * Return the current allocation size.
		 * This size is the size available till the next allocation.
		 *
		 * @return: Byte count.
		 */
		const UI64 allocationSize() const noexcept
		{
			InternalLock _lock;
			return myArray.allocationSize();
		}

		/* FUNCTION
		 * Check if the Array is empty.
		 */
		const B1 empty() const noexcept
		{
			InternalLock _lock;
			return myArray.empty();
		}

		/* FUNCTION
		 * Get data pointer of the Array.
		 */
		const RPTR data() const noexcept
		{
			InternalLock _lock;
			return myArray.data();
		}

		/* FUNCTION
		 * Begin iterator of the Array.
		 */
		const ITERATOR begin() const noexcept
		{
			InternalLock _lock;
			return myArray.begin();
		}

		/* FUNCTION
		 * End iterator of the Array.
		 */
		const ITERATOR end() const noexcept
		{
			InternalLock _lock;
			return myArray.end();
		}

		/* FUNCTION
		 * Find a given value in this array.
		 *
		 * @param data: Data to be searched for.
		 * @return: Array of indexes which the gived data is found.
		 */
		STORE find(const TYPE& data)
		{
			InternalLock _lock;
			return myArray.find(data);
		}

		/* FUNCTION
		 * Find a given value in this array.
		 *
		 * @param data: Data to be searched for.
		 * @return: Array of indexes which the gived data is found.
		 */
		STORE find(TYPE&& data)
		{
			InternalLock _lock;
			return myArray.find((TYPE&&)data);
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
			InternalLock _lock;
			return myArray.findFirst(key);
		}

		/* FUNCTION
		 * Returns a hash for the content stored in the array.
		 */
		UI64 hash()
		{
			InternalLock _lock;
			return myArray.hash();
		}

		/* TEMPLATED FUNCTION
		 * Casts the data stored in this array to the provided type.
		 */
		template<class SUB_TYPE>
		ARRAY<SUB_TYPE> cast()
		{
			InternalLock _lock;
			return myArray.cast<SUB_TYPE>();
		}

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
			InternalLock _lock;
			return this->myArray[index];
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
			InternalLock _lock;
			return this->myArray[index];
		}

		/* OPERATOR
		 * == operator overload.
		 * Check if the arrays are similar.
		 *
		 * @param data: Array to be checked with.
		 */
		B1 operator==(STORE& data)
		{
			InternalLock _lock;
			return this->myArray == data;
		}

		/* OPERATOR
		 * + operator overload.
		 * Concat another Array with the similar type.
		 *
		 * @param data: Array to be contacted with.
		 */
		STORE& operator+(const STORE& data)
		{
			InternalLock _lock;
			return this->myArray + data;
		}

		/* OPERATOR
		 * = operator overload.
		 * Get data from an array and initialize it to this.
		 *
		 * @para arr: Array to be initialized to this.
		 */


		 /* OPERATOR
		  * = operator overload.
		  * Get data from an array and initialize it to this.
		  *
		  * @para arr: Array to be initialized to this.
		  */
		THIS& operator=(const THIS& arr)
		{
			InternalLock _lock;
			return this->myArray = arr.myArray;
		}

		/* OPERATOR
		 * = operator overload.
		 * Get data from an array and initialize it to this.
		 *
		 * @para arr: Array to be initialized to this.
		 */
		STORE& operator=(STORE&& arr) noexcept
		{
			InternalLock _lock;
			return this->myArray = arr;
		}

		/* OPERATOR
		 * = operator overload.
		 * Get data from a raw array and initialize it to this.
		 *
		 * @para arr: Raw array to be initialized to this.
		 */
		STORE& operator=(const PTR arr)
		{
			InternalLock _lock;
			return this->myArray = arr;
		}

		/* OPERATOR
		 * = operator overload.
		 * Get data from a initializer list and initialize it to this.
		 *
		 * @para list: Raw array to be initialized to this.
		 */
		STORE& operator=(std::initializer_list<TYPE> list)
		{
			InternalLock _lock;
			return this->myArray = list;
		}

		/* STATIC FUNCTION
		 * Copy contents from one Array to another.
		 *
		 * @tparam SUB_TYPE: The type to cast to.
		 * @param source: Source Array.
		 * @param destination: Destination Array.
		 */
		template<class SUB_TYPE>
		static void copy(ARRAY<SUB_TYPE>* source, ARRAY<SUB_TYPE>* destination)
		{
			myArray::copy(source, destination);
		}
	};
}

#endif // !_DYNAMIK_THREAD_SAFE_ARRAY_H
