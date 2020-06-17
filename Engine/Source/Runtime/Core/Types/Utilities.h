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
	DMK_FORCEINLINE DERIVED InheritCast(POINTER<BASE> pBase)
	{
		return *((DERIVED*)pBase.get());
	}

	/*
	 Cast to the required derived type.

	 @param pBase: Base class pointer.
	 @tparam DERIVED: Class to be derived to.
	 @tparam BASE: Base class of the deriving class.
	*/
	template<class DERIVED, class BASE>
	DMK_FORCEINLINE POINTER<DERIVED> Inherit(POINTER<BASE> pBase)
	{
		return ((DERIVED*)pBase.get());
	}

	/*
	 Add a byte offset to a given address.
	 This function does not alter the argument address or the byte size.

	 @param baseAddress: Base address to be offsetted.
	 @param byteSize: Offset.
	*/
	DMK_FORCEINLINE VPTR NextLocation(const VPTR baseAddress, const UI64 byteSize)
	{
		return (VPTR)(((UI64)baseAddress) + byteSize);
	}
}

#endif // !_DYNAMIK_UTILITIES_H
