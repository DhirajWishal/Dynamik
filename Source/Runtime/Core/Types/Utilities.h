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

	/*
	 Get the byte size which can be stored in a format.
	 Since format is used to define the data entries for shaders, it is used to calculate the vertex stride.

	 @param format: The format.
	*/
	DMK_FORCEINLINE UI64 FormatSize(const DMKFormat& format)
	{
		switch (format)
		{
		case Dynamik::DMKFormat::DMK_FORMAT_UNDEFINED:						return 0;
		case Dynamik::DMKFormat::DMK_FORMAT_RG_4_UNORMAL_PACK8:				return 1;
		case Dynamik::DMKFormat::DMK_FORMAT_RGBA_4_UNORMAL_PACK16:			return 2;
		case Dynamik::DMKFormat::DMK_FORMAT_BGRA_4_UNORMAL_PACK16:			return 2;
		case Dynamik::DMKFormat::DMK_FORMAT_R5G6B5_UNORMAL_PACK16:			return 2;
		case Dynamik::DMKFormat::DMK_FORMAT_B5G6R5_UNORMAL_PACK16:			return 2;
		case Dynamik::DMKFormat::DMK_FORMAT_R5G6B5A1_UNORMAL_PACK16:		return 2;
		case Dynamik::DMKFormat::DMK_FORMAT_B5G6R5A1_UNORMAL_PACK16:		return 2;
		case Dynamik::DMKFormat::DMK_FORMAT_A1B5G6R5_UNORMAL_PACK16:		return 2;
		case Dynamik::DMKFormat::DMK_FORMAT_R_8_UNORMAL:					return 1;
		case Dynamik::DMKFormat::DMK_FORMAT_R_8_SNORMAL:					return 1;
		case Dynamik::DMKFormat::DMK_FORMAT_R_8_USCALED:					return 1;
		case Dynamik::DMKFormat::DMK_FORMAT_R_8_SSCALED:					return 1;
		case Dynamik::DMKFormat::DMK_FORMAT_R_8_UINT:						return 1;
		case Dynamik::DMKFormat::DMK_FORMAT_R_8_SINT:						return 1;
		case Dynamik::DMKFormat::DMK_FORMAT_R_8_SRGB:						return 1;
		case Dynamik::DMKFormat::DMK_FORMAT_RG_8_UNORMAL:					return 2;
		case Dynamik::DMKFormat::DMK_FORMAT_RG_8_SNORMAL:					return 2;
		case Dynamik::DMKFormat::DMK_FORMAT_RG_8_USCALED:					return 2;
		case Dynamik::DMKFormat::DMK_FORMAT_RG_8_SSCALED:					return 2;
		case Dynamik::DMKFormat::DMK_FORMAT_RG_8_UINT:						return 2;
		case Dynamik::DMKFormat::DMK_FORMAT_RG_8_SINT:						return 2;
		case Dynamik::DMKFormat::DMK_FORMAT_RG_8_SRGB:						return 2;
		case Dynamik::DMKFormat::DMK_FORMAT_RGB_8_UNORMAL:					return 3;
		case Dynamik::DMKFormat::DMK_FORMAT_RGB_8_SNORMAL:					return 3;
		case Dynamik::DMKFormat::DMK_FORMAT_RGB_8_USCALED:					return 3;
		case Dynamik::DMKFormat::DMK_FORMAT_RGB_8_SSCALED:					return 3;
		case Dynamik::DMKFormat::DMK_FORMAT_RGB_8_UINT:						return 3;
		case Dynamik::DMKFormat::DMK_FORMAT_RGB_8_SINT:						return 3;
		case Dynamik::DMKFormat::DMK_FORMAT_RGB_8_SRGB:						return 3;
		case Dynamik::DMKFormat::DMK_FORMAT_BGR_8_UNORMAL:					return 3;
		case Dynamik::DMKFormat::DMK_FORMAT_BGR_8_SNORMAL:					return 3;
		case Dynamik::DMKFormat::DMK_FORMAT_BGR_8_USCALED:					return 3;
		case Dynamik::DMKFormat::DMK_FORMAT_BGR_8_SSCALED:					return 3;
		case Dynamik::DMKFormat::DMK_FORMAT_BGR_8_UINT:						return 3;
		case Dynamik::DMKFormat::DMK_FORMAT_BGR_8_SINT:						return 3;
		case Dynamik::DMKFormat::DMK_FORMAT_BGR_8_SRGB:						return 3;
		case Dynamik::DMKFormat::DMK_FORMAT_RGBA_8_UNORMAL:					return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_RGBA_8_SNORMAL:					return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_RGBA_8_USCALED:					return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_RGBA_8_SSCALED:					return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_RGBA_8_UINT:					return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_RGBA_8_SINT:					return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_RGBA_8_SRGB:					return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_BGRA_8_UNORMAL:					return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_BGRA_8_SNORMAL:					return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_BGRA_8_USCALED:					return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_BGRA_8_SSCALED:					return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_BGRA_8_UINT:					return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_BGRA_8_SINT:					return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_BGRA_8_SRGB:					return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_RGBA_8_UNORMAL_PACK32:			return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_RGBA_8_SNORMAL_PACK32:			return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_RGBA_8_USCALED_PACK32:			return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_RGBA_8_SSCALED_PACK32:			return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_RGBA_8_UINT_PACK32:				return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_RGBA_8_SINT_PACK32:				return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_RGBA_8_SRGB_PACK32:				return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_A2R10G10B10_UNORMAL_PACK32:		return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_A2R10G10B10_SNORMAL_PACK32:		return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_A2R10G10B10_USCALED_PACK32:		return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_A2R10G10B10_SSCALED_PACK32:		return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_A2R10G10B10_UINT_PACK32:		return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_A2R10G10B10_SINT_PACK32:		return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_A2B10G10R10_UNORMAL_PACK32:		return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_A2B10G10R10_SNORMAL_PACK32:		return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_A2B10G10R10_USCALED_PACK32:		return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_A2B10G10R10_SSCALED_PACK32:		return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_A2B10G10R10_UINT_PACK32:		return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_A2B10G10R10_SINT_PACK32:		return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_R_16_UNORMAL:					return 2;
		case Dynamik::DMKFormat::DMK_FORMAT_R_16_SNORMAL:					return 2;
		case Dynamik::DMKFormat::DMK_FORMAT_R_16_USCALED:					return 2;
		case Dynamik::DMKFormat::DMK_FORMAT_R_16_SSCALED:					return 2;
		case Dynamik::DMKFormat::DMK_FORMAT_R_16_UINT:						return 2;
		case Dynamik::DMKFormat::DMK_FORMAT_R_16_SINT:						return 2;
		case Dynamik::DMKFormat::DMK_FORMAT_R_16_SF32:						return 2;
		case Dynamik::DMKFormat::DMK_FORMAT_RG_16_UNORMAL:					return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_RG_16_SNORMAL:					return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_RG_16_USCALED:					return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_RG_16_SSCALED:					return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_RG_16_UINT:						return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_RG_16_SINT:						return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_RG_16_SF32:						return 6;
		case Dynamik::DMKFormat::DMK_FORMAT_RGB_16_UNORMAL:					return 6;
		case Dynamik::DMKFormat::DMK_FORMAT_RGB_16_SNORMAL:					return 6;
		case Dynamik::DMKFormat::DMK_FORMAT_RGB_16_USCALED:					return 6;
		case Dynamik::DMKFormat::DMK_FORMAT_RGB_16_SSCALED:					return 6;
		case Dynamik::DMKFormat::DMK_FORMAT_RGB_16_UINT:					return 6;
		case Dynamik::DMKFormat::DMK_FORMAT_RGB_16_SINT:					return 6;
		case Dynamik::DMKFormat::DMK_FORMAT_RGB_16_SF32:					return 6;
		case Dynamik::DMKFormat::DMK_FORMAT_RGBA_16_UNORMAL:				return 8;
		case Dynamik::DMKFormat::DMK_FORMAT_RGBA_16_SNORMAL:				return 8;
		case Dynamik::DMKFormat::DMK_FORMAT_RGBA_16_USCALED:				return 8;
		case Dynamik::DMKFormat::DMK_FORMAT_RGBA_16_SSCALED:				return 8;
		case Dynamik::DMKFormat::DMK_FORMAT_RGBA_16_UINT:					return 8;
		case Dynamik::DMKFormat::DMK_FORMAT_RGBA_16_SINT:					return 8;
		case Dynamik::DMKFormat::DMK_FORMAT_RGBA_16_SF32:					return 8;
		case Dynamik::DMKFormat::DMK_FORMAT_R_32_UINT:						return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_R_32_SINT:						return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_R_32_SF32:						return 4;
		case Dynamik::DMKFormat::DMK_FORMAT_RG_32_UINT:						return 8;
		case Dynamik::DMKFormat::DMK_FORMAT_RG_32_SINT:						return 8;
		case Dynamik::DMKFormat::DMK_FORMAT_RG_32_SF32:						return 8;
		case Dynamik::DMKFormat::DMK_FORMAT_RGB_32_UINT:					return 12;
		case Dynamik::DMKFormat::DMK_FORMAT_RGB_32_SINT:					return 12;
		case Dynamik::DMKFormat::DMK_FORMAT_RGB_32_SF32:					return 12;
		case Dynamik::DMKFormat::DMK_FORMAT_RGBA_32_UINT:					return 16;
		case Dynamik::DMKFormat::DMK_FORMAT_RGBA_32_SINT:					return 16;
		case Dynamik::DMKFormat::DMK_FORMAT_RGBA_32_SF32:					return 16;
		case Dynamik::DMKFormat::DMK_FORMAT_R_64_UINT:						return 8;
		case Dynamik::DMKFormat::DMK_FORMAT_R_64_SINT:						return 8;
		case Dynamik::DMKFormat::DMK_FORMAT_R_64_SF32:						return 8;
		case Dynamik::DMKFormat::DMK_FORMAT_RG_64_UINT:						return 16;
		case Dynamik::DMKFormat::DMK_FORMAT_RG_64_SINT:						return 16;
		case Dynamik::DMKFormat::DMK_FORMAT_RG_64_SF32:						return 16;
		case Dynamik::DMKFormat::DMK_FORMAT_RGB_64_UINT:					return 24;
		case Dynamik::DMKFormat::DMK_FORMAT_RGB_64_SINT:					return 24;
		case Dynamik::DMKFormat::DMK_FORMAT_RGB_64_SF32:					return 24;
		case Dynamik::DMKFormat::DMK_FORMAT_RGBA_64_UINT:					return 32;
		case Dynamik::DMKFormat::DMK_FORMAT_RGBA_64_SINT:					return 32;
		case Dynamik::DMKFormat::DMK_FORMAT_RGBA_64_SF32:					return 32;
		case Dynamik::DMKFormat::DMK_FORMAT_B10G11R11_UFLOAT_PACK32:		return 4;
		default:				DMK_ERROR("Unsupported or invalid format!");	break;
		}

		return 0;
	}
}

#endif // !_DYNAMIK_UTILITIES_H
