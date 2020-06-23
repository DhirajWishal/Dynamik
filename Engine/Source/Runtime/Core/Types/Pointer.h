// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_POINTER_H
#define _DYNAMIK_POINTER_H

/*
 Pointer class or the Dynamik Engine.

 Author:	Dhiraj Wishal
 Date:		13/05/2020
*/
#include "Macros/Global.h"
#include "TypeTraits.h"

namespace Dynamik
{
	/* TEMPLATED
	 * Pointer class for the Dynamik Engine.
	 * This class stores a pointer and supports address manipulation.
	 * POINTER basically acts as '*' and '&' in C/C++ with added functionalities.
	 *
	 * @warn: TYPE should not be void (any half type). void* is accepted.
	 */
	template<class TYPE>
	class DMK_API POINTER {
		/* DEFAULTS */

		/* STATIC ASSERT
		 * Check if the Template argument is not void.
		 * Compile time check.
		 */
		static_assert(!isType<TYPE, void>::result, "POINTER<TYPE> Does not support void!");

	public:
		/* CONSTRUCTOR
		 * Default constructor.
		 */
		DMK_FORCEINLINE POINTER() : myPointer(nullptr) {}

		/* CONSTRUCTOR
		 * Default constructor.
		 *
		 * @param address: address of the data to be stored.
		 */
		DMK_FORCEINLINE POINTER(const TYPE* address) : myPointer((TYPE*)address) {}

		/* CONSTRUCTOR
		 * Default constructor.
		 *
		 * @param address: address of the data to be stored.
		 */
		DMK_FORCEINLINE POINTER(const VPTR address) : myPointer((TYPE*)address) {}

		/* DESTRUCTOR
		 * Default destructor.
		 */
		DMK_FORCEINLINE ~POINTER() {}

		/* PUBLIC FUNCTIONS */
	public:
		/* FUNCTION
		 * Get the pointer.
		 */
		DMK_FORCEINLINE TYPE* get() const { return myPointer; }

		/* FUNCTION
		 * Get the pointer address.
		 */
		DMK_FORCEINLINE TYPE** getAddress() const { return &(TYPE*)myPointer; }

		/* FUNCTION
		 * Get the pointer as a UI64 value.
		 * Converts the address stored in the pointer to a unsigned 64bit integer.
		 */
		DMK_FORCEINLINE UI64 getPointerAsInteger() const { return (UI64)myPointer; }

		/* FUNCTION
		 * Get the pointer address as a UI64 value.
		 * Converts the pointer address to a unsigned 64bit integer.
		 */
		DMK_FORCEINLINE UI64 getAddressAsInteger() const { return (UI64)&myPointer; }

		/* FUNCTION
		 * Get the type size of the pointer.
		 */
		DMK_FORCEINLINE UI64 getTypeSize() const { return sizeof(TYPE); }

		/* FUNCTION
		 * Set a value to the pointer.
		 */
		DMK_FORCEINLINE void set(TYPE&& value) { StaticAllocator<TYPE>::set(myPointer, (TYPE&&)value); }

		/* FUNCTION
		 * Set a value to the pointer at a given index.
		 *
		 * @param index: Index to be updated.
		 * @param value: Value to be set.
		 * @warn: Index is not validated before or after assignment.
		 */
		DMK_FORCEINLINE void setIndexed(const UI64& index, const TYPE& value) { myPointer[index] = value; }

		/* FUNCTION
		 * Set a value to the pointer using an index.
		 *
		 * @param value: The value to be stored.
		 * @param index: Index to where to store the value.
		 * @warn: Does not validate the index before assigning.
		 */
		DMK_FORCEINLINE void setIndexed(const TYPE& value, const UI64 index) { myPointer[index] = value; }

		/* FUNCTION
		 * Check if the pointer is valid.
		 * Returns true if the pointer has data or not a null pointer.
		 */
		DMK_FORCEINLINE B1 isValid() const { return ((myPointer != nullptr) || (sizeof(myPointer) > sizeof(TYPE*))); }

		/* FUNCTION
		 * Assign the pointer to a given pointer.
		 *
		 * @param pointer: The pointer to be assigned.
		 */
		DMK_FORCEINLINE void assign(VPTR pointer) { myPointer = (TYPE*)pointer; }

		/* FUNCTION
		 * Turn the pointer to a null pointer.
		 */
		DMK_FORCEINLINE void turnNull() { myPointer = nullptr; }

		/* FUNCTION
		 * Increment the address of the pointer by a value.
		 *
		 * @param value: Value to be incremented by.
		 */
		DMK_FORCEINLINE TYPE* increment(UI64 value)
		{
			return (this->myPointer = (TYPE*)(((UI64)this->myPointer) + (value * sizeof(TYPE))));
		}

		/* FUNCTION
		 * Decrement the address of the pointer by a value.
		 *
		 * @param value: Value to be decremented by.
		 */
		DMK_FORCEINLINE TYPE* decrement(UI64 value)
		{
			return (this->myPointer = (TYPE*)(((UI64)this->myPointer) - (value * sizeof(TYPE))));
		}

		/* FUNCTION
		 * Return the data stored at a given index in the pointer.
		 * Indexed value can be modified in the pointer.
		 *
		 * @param index: Index to be accessed.
		 * @warn: Index is not validated before or after indexing.
		 */
		DMK_FORCEINLINE TYPE& at(const UI64& index) const { return myPointer[index]; }

		/* FUNCTION
		 * Get the dereferenced value behind the pointer.
		 */
		DMK_FORCEINLINE TYPE& dereference() const { return *myPointer; }

		/* PUBLIC OPERATORS */
	public:
		/* OPERATOR
		 * Return the dereferenced pointer.
		 */
		DMK_FORCEINLINE operator TYPE() const { return *this->myPointer; }

		/* OPERATOR
		 * Return the pointer.
		 */
		DMK_FORCEINLINE operator TYPE* () const { return this->myPointer; }

		/* OPERATOR
		 * Return the pointer.
		 */
		DMK_FORCEINLINE operator const TYPE* () const { return this->myPointer; }

		///* OPERATOR
		// * Return the casted pointer.
		// */
		//operator VPTR() { return this->myPointer; }

		/* OPERATOR
		 * Return the casted pointer.
		 */
		template<class SUB_TYPE>
		DMK_FORCEINLINE operator SUB_TYPE() const { return (SUB_TYPE)this->myPointer; }

		/* OPERATOR
		 * Return the dereferenced pointer.
		 */
		DMK_FORCEINLINE TYPE operator*() const { return *this->myPointer; }

		/* OPERATOR
		 * Return the dereferenced pointer.
		 */
		DMK_FORCEINLINE TYPE* operator->() const { return this->myPointer; }

		/* OPERATOR
		 * Increment the address of the pointer by a value.
		 *
		 * @param increment: Value that is added to the pointer.
		 */
		DMK_FORCEINLINE TYPE* operator+(UI64& increment) const { return (TYPE*)(((UI64)this->myPointer) + increment); }

		/* OPERATOR
		 * Return the addition of the two pointers.
		 *
		 * @param other: The other pointer.
		 */
		DMK_FORCEINLINE UI64 operator+(const POINTER<TYPE>& other) const { return this->getPointerAsInteger() + other.getPointerAsInteger(); }

		/* OPERATOR
		 * Increment the address of the pointer by a value and assign it to this.
		 *
		 * @param increment: Value that is added to the pointer.
		 */
		DMK_FORCEINLINE TYPE* operator+=(const UI64 increment) { return this->increment(increment); }

		/* OPERATOR
		 * Decrement the address of the pointer by a value.
		 *
		 * @param decrement: Value to be subtracted to the pointer.
		 */
		DMK_FORCEINLINE TYPE* operator-(const UI64& decrement) const { return (TYPE*)(((UI64)this->myPointer) - decrement); }

		/* OPERATOR
		 * Return the difference of the two pointers.
		 *
		 * @param other: The other pointer.
		 */
		DMK_FORCEINLINE UI64 operator-(const POINTER<TYPE>& other) const { return this->getPointerAsInteger() - other.getPointerAsInteger(); }

		/* OPERATOR
		 * Decrement the address of the pointer by a value and assign to this.
		 *
		 * @param decrement: Value to be subtracted to the pointer.
		 */
		DMK_FORCEINLINE TYPE* operator-=(const UI64 decrement) { return this->decrement(decrement); }

		/* OPERATOR
		 * Increment the address of the pointer by one.
		 */
		DMK_FORCEINLINE TYPE* operator++(I32) { return this->increment(1); }

		/* OPERATOR
		 * Increment the address of the pointer by one.
		 */
		DMK_FORCEINLINE TYPE* operator++() { return this->increment(1); }

		/* OPERATOR
		 * Decrement the address of the pointer by one.
		 */
		DMK_FORCEINLINE TYPE* operator--(I32) { return this->decrement(1); }

		/* OPERATOR
		 * Decrement the address of the pointer by one.
		 */
		DMK_FORCEINLINE TYPE* operator--() { return this->decrement(1); }

		/* OPERATOR
		 * Check if the pointer is equal to this pointer.
		 *
		 * @param ptr: Pointer to be checked with.
		 */
		DMK_FORCEINLINE B1 operator==(const POINTER<TYPE>& ptr) const { return ((UI64)this->myPointer) == ((UI64)ptr.myPointer); }

		/* OPERATOR
		 * Assign the address of one POINTER to this.
		 *
		 * @param ptr: Pointer to the address to be assigned.
		 */
		DMK_FORCEINLINE void operator()(const POINTER<TYPE>& ptr) { this->myPointer = ptr.get(); }

		/* OPERATOR
		 * Assign an address to the pointer.
		 * Accepts void pointers.
		 *
		 * @param value: Value to be assigned to the pointer.
		 */
		DMK_FORCEINLINE void operator=(const VPTR address) { this->myPointer = (TYPE*)address; }

		/* OPERATOR
		 * Assign a value to the pointer.
		 *
		 * @param value: Value to be assigned to the pointer.
		 */
		DMK_FORCEINLINE void operator=(const TYPE& value) { this->set((TYPE&&)value); }

		/* OPERATOR
		 * Assign a value to the pointer.
		 *
		 * @param ptr: Pointer to be copied to the pointer.
		 */
		DMK_FORCEINLINE void operator=(const POINTER<TYPE>& ptr) { this->myPointer = ptr.myPointer; }

		/* OPERATOR
		 * Check if a pointer is not equal to this.
		 *
		 * @param ptr: Pointer to be checked with this.
		 */
		DMK_FORCEINLINE B1 operator!=(const POINTER<TYPE>& ptr) const { return this->myPointer != ptr.get(); }

		/* OPERATOR
		 * Access data at a given index in the pointer.
		 * Indexed value can be modified in the pointer.
		 *
		 * @param index: Index of the data to be retrieved.
		 * @warn: Does not validate the index before retrieving.
		 */
		DMK_FORCEINLINE TYPE& operator[](const UI64& index) { return this->myPointer[index]; }

		/* OPERATOR
		 * Access data at a given index in the pointer.
		 * Indexed value can be modified in the pointer.
		 *
		 * @param index: Index of the data to be retrieved.
		 * @warn: Does not validate the index before retrieving.
		 */
		DMK_FORCEINLINE const TYPE& operator[](const UI64& index) const { return this->myPointer[index]; }

		/* PRIVATE VARIABLES AND CONSTANTS */
	private:
		mutable TYPE* myPointer = nullptr;	// pointer data store
	};
}

#endif // !_DYNAMIK_POINTER_H
