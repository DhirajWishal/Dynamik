// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_STATIC_ARRAY_H
#define _DYNAMIK_STATIC_ARRAY_H

#include "DataTypes.h"
#include "Utilities.h"
#include "TypeTraits.h"
#include "Core/Memory/MemoryFunctions.h"

#include <initializer_list>

/*
 Static Array for the Dynamik Engine
*/
template<class TYPE, UI64 Size>
class DMK_API StaticArray {
	/*
	 Check if the user has provided void as a template argument.
	*/
	static_assert(!isType<TYPE, void>::result, "Static Array does not support void as a template argument!");

public:
	/* CONSTRUCTOR
	 Default constructor.
	*/
	StaticArray() = default;

	/* CONSTRUCTOR
	 Default constructor. Takes a value and initialized it to the whole array.
	*/
	StaticArray(const TYPE& data)
	{
		DMKMemoryFunctions::setData(myData, data, typeSize() * Size);
	}

	/* CONSTRUCTOR
	 Default constructor. Construct this array using the data from another array.
	*/
	StaticArray(const StaticArray<TYPE, Size>& other)
	{
		DMKMemoryFunctions::copyData(myData, other.data(), other.typeSize() * size());
	}

	/* CONSTRUCTOR
	 Default constructor. Constructs this array from an initializer list.
	*/
	StaticArray(const std::initializer_list<TYPE>& list)
	{
		if (list.size() > Size)
			DMK_ERROR("The initializer list submitted to the Static Array contains elements which are out of bound!");

		DMKMemoryFunctions::copyData(myData, Cast<VPTR>(list.begin()), typeSize() * Size);
	}

	/* DESTRUCTOR
	 Default destructor.
	*/
	~StaticArray() = default;

public:
	/* Iterator of the Static Array */
	typedef TYPE* ITERATOR;

public:
	/* FUNCTION
	 Get the size of this array.
	*/
	constexpr UI64 size() const
	{
		return Size;
	}

	/* FUNCTION
	 Get the type size of this array.
	*/
	constexpr UI64 typeSize() const
	{
		return sizeof(TYPE);
	}

	/* FUNCTION
	 Get the address of the data store.
	*/
	TYPE* data() const
	{
		return Cast<TYPE*>(myData);
	}

	/* FUNCTION
	 Get an element at a given index.

	 @param index: Index of the element.
	*/
	TYPE& at(I64 index)
	{
		return myData[_getProcessedIndex(index)];
	}

	/* FUNCTION
	 Get an element at a given index.
	 Value returned by this function cannot be modified.

	 @param index: Index of the element.
	*/
	const TYPE at(I64 index) const
	{
		return myData[_getProcessedIndex(index)];
	}

	/* FUNCTION
	 Set a value to an element at a given index.

	 @param index: Index of the element to be assigned.
	 @param data: The data to be assigned.
	*/
	void set(I64 index, const TYPE& data)
	{
		at(index) = data;
	}

	/* FUNCTION
	 Begin iterator of the array.
	*/
	ITERATOR begin() const
	{
		return Cast<ITERATOR>(&myData[0]);
	}

	/* FUNCTION
	 End iterator of the array.
	*/
	ITERATOR end() const
	{
		return Cast<ITERATOR>(&myData[Size - 1]);
	}

public:
	/* OPERATOR
	 Get an element at a given index.

	 @param index: Index of the element.
	*/
	TYPE& operator[](I64 index)
	{
		return at(index);
	}

	/* OPERATOR
	 Get an element at a given index.
	 Value returned by this function cannot be modified.

	 @param index: Index of the element.
	*/
	const TYPE operator[](I64 index) const
	{
		return at(index);
	}

	/* OPERATOR
	 Assign the data from another array to this.

	 @param other: The other array.
	*/
	StaticArray<TYPE, Size>& operator=(const StaticArray<TYPE, Size>& other)
	{
		DMKMemoryFunctions::copyData(myData, other.data(), other.typeSize() * size());
		return *this;
	}

	/* OPERATOR
	 Is-Equal-To operator.

	 @param other: The other array.
	*/
	B1 operator==(const StaticArray<TYPE, Size>& other) const
	{
		for (UI64 index = 0; index < other.size(); index++)
			if (myData[index] != other[index])
				return false;

		return true;
	}

	/* OPERATOR
	 Is-Less-Than operator.

	 @param other: The other array.
	*/
	B1 operator<(const StaticArray<TYPE, Size>& other) const
	{
		for (UI64 index = 0; index < other.size(); index++)
			if (myData[index] < other[index])
				return true;

		return false;
	}

	/* OPERATOR
	 Is-Less-Than-Or-Equal operator.

	 @param other: The other array.
	*/
	B1 operator<=(const StaticArray<TYPE, Size>& other) const
	{
		for (UI64 index = 0; index < other.size(); index++)
			if (myData[index] <= other[index])
				return true;

		return false;
	}

	/* OPERATOR
	 Is-Grater-Than operator.

	 @param other: The other array.
	*/
	B1 operator>(const StaticArray<TYPE, Size>& other) const
	{
		for (UI64 index = 0; index < other.size(); index++)
			if (myData[index] > other[index])
				return true;

		return false;
	}

	/* OPERATOR
	 Is-Grater-Than-Or-Equal operator.

	 @param other: The other array.
	*/
	B1 operator>=(const StaticArray<TYPE, Size>& other) const
	{
		for (UI64 index = 0; index < other.size(); index++)
			if (myData[index] >= other[index])
				return true;

		return false;
	}

private:
	/* PRIVATE FUNCTION
	 Get the processed index from a given index.

	 @param index: Index to be processed.
	*/
	DMK_FORCEINLINE UI64 _getProcessedIndex(I64 index) const
	{
		if (index < 0)
			return Size + index;

		return Cast<UI64>(index);
	}

private:
	TYPE myData[Size] = { TYPE() };		/* Data store */
};

#endif // !_DYNAMIK_STATIC_ARRAY_H
