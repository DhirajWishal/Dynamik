// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_UTILITIES_H
#define _DYNAMIK_UTILITIES_H

/*
 Author:	Dhiraj Wishal
 Date:		15/06/2020
*/
#include "Pointer.h"

namespace Dynamik
{
	/*
	 Cast to the required derived type and dereference it.

	 @param pBase: Base class pointer.
	 @tparam DERIVED: Class to be derived to.
	 @tparam BASE: Base class of the deriving class.
	*/
	template<class DERIVED, class BASE>
	inline DERIVED InheritCast(POINTER<BASE> pBase)
	{
		return *dynamic_cast<DERIVED*>(pBase.get());
	}
}

#endif // !_DYNAMIK_UTILITIES_H
