// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_UNIQUE_POINTER_H
#define _DYNAMIK_UNIQUE_POINTER_H

#include "Core/Memory/StaticAllocator.h"

namespace Dynamik
{
	/*
	 Unique Pointer for the Dynamik Engine.
	 Unique pointers will only have one instance of itself and cannot be copies but moved.
	*/
	template<class TYPE>
	class DMK_API UniquePointer {
	public:
		/* CONSTRUCTOR
		 Default constructor.
		*/
		UniquePointer() : pMyData(nullptr) {}

		/* CONSTRUCTOR
 		 Assigns a value to the internally stored pointer.
		*/
		UniquePointer(const TYPE* pointer)
		{
			if (!isNull())
			{
				DMK_ERROR("The object aready contains a value!");
				return;
			}

			pMyData = Cast<TYPE*>(pointer);
		}

		/* CONSTRUCTOR
		 Move constructor of the unique pointer.

		 @param other: The other pointer to be assigned.
		*/
		UniquePointer(UniquePointer<TYPE>&& other)
		{
			if (!isNull())
			{
				DMK_ERROR("The object aready contains a value!");
				return;
			}

			this->pMyData = other.pMyData;
			other.pMyData;
		}

		/* CONSTRUCTOR
		 The copy constructor of unique pointer is deleted.
		*/
		UniquePointer(const UniquePointer<TYPE>&) = delete;

		/* DESTRUCTOR
		 Default destructor.
		*/
		~UniquePointer()
		{
			terminate();
		}

		/*
		 Create a new unique pointer.

		 @param initialization: The values to which the object to be initialized. The default is the default constructor.
		*/
		static UniquePointer<TYPE> create(const TYPE& initialization = Type())
		{
			return StaticAllocator<TYPE>::allocateInit(initialization);
		}

	public:
		/*
		 Get the stored pointer.

		 @warn: Value cannot be modified.
		*/
		const TYPE* get() const { return pMyData; }

		/*
		 Get the stored pointer.
		*/
		TYPE* get() { return pMyData; }

		/*
		 Check if the stored pointer is null.
		*/
		const B1 isNull() const { return pMyData == nullptr; }

		/*
		 Terminate the stored memory buffer.
		*/
		void terminate()
		{
			if (pMyData)
				StaticAllocator<TYPE>::rawDeallocate(pMyData, sizeof(TYPE));
		}

	public:
		/* OPERATOR
		 Move operator of the unique pointer.

		 @param other: The other pointer.
		*/
		UniquePointer<TYPE>& operator=(UniquePointer<TYPE>&& other) noexcept
		{
			pMyData = other.pMyData;
			other.pMyData = nullptr;

			return *this;
		}

		UniquePointer<TYPE>& operator=(const UniquePointer<TYPE>& other) = delete;

		/* OPERATOR
		 Is Equal To operator.

		 @param other: The other pointer.
		*/
		UniquePointer<TYPE>& operator==(UniquePointer<TYPE>&& other)
		{
			return this->pMyData == other.pMyData;
		}

		/* OPERATOR
		 The arrow operator.
		*/
		TYPE* operator->()
		{
			return pMyData;
		}
		
		/* OPERATOR
		 Cast this object to another object.
		*/
		template<class OTHER>
		operator UniquePointer<OTHER>()
		{
			UniquePointer<OTHER> uniquePtr = Cast<OTHER*>(pMyData);
			pMyData = nullptr;
			return uniquePtr;
		}

	private:
		TYPE* pMyData = nullptr;	/* The data pointer. */
	};
}

#endif // !_DYNAMIK_UNIQUE_POINTER_H
