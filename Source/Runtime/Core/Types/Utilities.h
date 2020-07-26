// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_UTILITIES_H
#define _DYNAMIK_UTILITIES_H

#include "Pointer.h"

namespace Dynamik
{
	/*
	 Cast data type of one variable to another.

	 @param value: Variable value.
	 @tparam CAST_TO: To cast to.
	 @tparam CAST_FROM: To cast from.
	*/
	template<class CAST_TO, class CAST_FROM>
	DMK_FORCEINLINE constexpr CAST_TO Cast(const CAST_FROM& value)
	{
		return (CAST_TO)value;
	}

	/*
	 Cast to the required derived type and dereference it.

	 @param pBase: Base class pointer.
	 @tparam DERIVED: Class to be derived to.
	 @tparam BASE: Base class of the deriving class.
	*/
	template<class DERIVED, class BASE>
	DMK_FORCEINLINE constexpr DERIVED InheritCast(BASE* pBase)
	{
		return *(DERIVED*)pBase;
	}

	/*
	 Cast to the required derived type.

	 @param pBase: Base class pointer.
	 @tparam DERIVED: Class to be derived to.
	 @tparam BASE: Base class of the deriving class.
	*/
	template<class DERIVED, class BASE>
	DMK_FORCEINLINE constexpr DERIVED* Inherit(BASE* pBase)
	{
		return dynamic_cast<DERIVED*>(pBase);
	}

	/*
	 Get the pointer as an unsigned integer.

	 @param pointer: Pointer.
	*/
	DMK_FORCEINLINE constexpr UI64 GetPointerAsInteger(const VPTR pointer)
	{
		return (UI64)pointer;
	}

	/*
	 Add a byte offset to a given address.
	 This function does not alter the argument address or the byte size.

	 @param baseAddress: Base address to be offset.
	 @param byteCount: Offset.
	*/
	DMK_FORCEINLINE VPTR IncrementPointer(const VPTR pointer, UI64 byteCount)
	{
		return (VPTR)(((UI64)pointer) + byteCount);
	}

	/*
	 Subtract a byte offset to a given address.
	 This function does not alter the argument address or the byte size.

	 @param baseAddress: Base address to be offset.
	 @param byteCount: Offset.
	*/
	DMK_FORCEINLINE VPTR DecrementPointer(const VPTR pointer, UI64 byteCount)
	{
		return (VPTR)(((UI64)pointer) - byteCount);
	}
}

#endif // !_DYNAMIK_UTILITIES_H
