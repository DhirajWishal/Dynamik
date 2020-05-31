#pragma once
#ifndef _DYNAMIK_THREAD_SAFE_ARRAY_H
#define _DYNAMIK_THREAD_SAFE_ARRAY_H

/*
 Author:    Dhiraj Wishal
 Date:      31/05/2020
*/
#include "Array.h"
#include <initializer_list>

#define __PREPARE			_validate();			\
							InternalLock _lock(this)

namespace Dynamik
{
	/*
	 Thread Safe Array for the Dynamik Engine
	 This is a wrapper class for the ARRAY data type and this ensures thread-safe-ness to the array.

	 @warn: This class might be slower than the traditional ARRAY class.
	*/
	template<class TYPE, UI64 AllocationCount = 1, DMKArrayDestructorCallMode DestructorCallMode = DMKArrayDestructorCallMode::DMK_ARRAY_DESTRUCTOR_CALL_MODE_DESTRUCT_NONE, class Allocator = StaticAllocator<TYPE>>
	class DMK_API TSArray {
		/* Main data store */
		ARRAY<TYPE, AllocationCount, DestructorCallMode, Allocator> myArray;

		using PTR = POINTER<TYPE>;
		using STORE = ARRAY<TYPE, AllocationCount, DestructorCallMode, Allocator>;

		/* Array lock */
		B1 __isLocked = false;

		/*
		 Array locking mechanism
		*/
		struct DMK_API InternalLock {
			InternalLock(TSArray<TYPE, AllocationCount, DestructorCallMode, Allocator>* arr) : myArray(arr)
			{
				myArray->__isLocked = true;
			}
			~InternalLock()
			{
				myArray->__isLocked = false;
			}

		private:
			TSArray<TYPE, AllocationCount, DestructorCallMode, Allocator>* myArray = nullptr;
		};

	public:
		TSArray() {}
		TSArray(const TSArray& other) : myArray(other.myArray) {}
		TSArray(TSArray&& other)
		{
			myArray = other.myArray;
			other.myArray.clear();
		}
		TSArray(const STORE& other) : myArray(other) {}
		~TSArray()
		{
			myArray.~ARRAY();
		}

	public:
		void set(const PTR arr)
		{
			__PREPARE;
			myArray.set(arr);
		}

		void set(UI64 index, const TYPE& value)
		{
			__PREPARE;
			myArray.set(index, value);
		}

		void set(STORE::ITERATOR first, STORE::ITERATOR last)
		{
			__PREPARE;
			myArray.set(first, last);
		}

		void set(std::initializer_list<TYPE> list)
		{
			__PREPARE;
			myArray.set(list);
		}

		void set(const STORE& other)
		{
			__PREPARE;
			myArray.set(other);
		}

		void pushBack(const TYPE& data)
		{
			__PREPARE;
			myArray.pushBack(data);
		}

		void pushBack(TYPE&& data)
		{
			__PREPARE;
			myArray.pushBack((TYPE&&)data);
		}

		TYPE back()
		{
			__PREPARE;
			return myArray.back();
		}

	private:
		/*
		 Checkes if the array is locked and if true, wait till the array is open.
		*/
		inline void _validate()
		{
			while (__isLocked);
		}
	};
}

#endif // !_DYNAMIK_THREAD_SAFE_ARRAY_H
