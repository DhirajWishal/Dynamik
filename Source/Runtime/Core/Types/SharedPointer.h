// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_SHARED_POINTER_H
#define _DYNAMIK_SHARED_POINTER_H

#include "Core/Memory/StaticAllocator.h"

namespace Dynamik
{
	/*
	 Shared Pointer for the Dynamik Engine.
	 Shared pointers are data structures which are capable of handling heap allocated data. Shared pointers can be
	 shared among multiple objects and when terminating, all the referenced objects must be terminated.
	*/
	template<class TYPE>
	class DMK_API SharedPointer {
	public:
		SharedPointer() {}
		~SharedPointer() {}

		/*
		 Create a new shared pointer.

		 @param initialization: The values to which the object to be initialized. The default is the default constructor.
		*/
		static SharedPointer<TYPE> create(const TYPE& initialization = Type())
		{
			return StaticAllocator<TYPE>::allocateInit(initialization);
		}

	private:
		TYPE* pMyData = nullptr;
	};
}

#endif // !_DYNAMIK_SHARED_POINTER_H
