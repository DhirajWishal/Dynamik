// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_UTILITIES_H
#define _DYNAMIK_UTILITIES_H

#include "Core/Macros/Global.h"
#include "Core/ErrorHandler/Logger.h"

namespace DMK
{
	/**
	 * Cast (C++ - Style) data type of one variable to another.
	 *
	 * @param value: Variable value.
	 * @tparam CastTo: To cast to.
	 * @tparam CastFrom: To cast from.
	 */
	template<class CastTo, class CastFrom>
	DMK_FORCEINLINE constexpr CastTo Cast(const CastFrom& value)
	{
		return static_cast<CastTo>(value);
	}

	/**
	 * Raw cast (C - Style) data type of one variable to another.
	 *
	 * @param value: Variable value.
	 * @tparam CastTo: To cast to.
	 * @tparam CastFrom: To cast from.
	 */
	template<class CastTo, class CastFrom>
	DMK_FORCEINLINE constexpr CastTo RawCast(const CastFrom& value)
	{
		return (CastTo)value;
	}

	/**
	 * Cast to the required derived type and dereference it.
	 *
	 * @param pBase: Base class pointer.
	 * @tparam Derived: Class to be derived to.
	 * @tparam Base: Base class of the deriving class.
	 */
	template<class Derived, class Base>
	DMK_FORCEINLINE constexpr Derived InheritCast(Base* pBase)
	{
		return dynamic_cast<Derivev*>(pBase);
	}

	/**
	 * Cast to the required derived type.
	 *
	 * @param pBase: Base class pointer.
	 * @tparam Derived: Class to be derived to.
	 * @tparam Base: Base class of the deriving class.
	 */
	template<class Derived, class Base>
	DMK_FORCEINLINE constexpr Derived* Inherit(Base* pBase)
	{
		return dynamic_cast<Derived*>(pBase);
	}

	/**
	 * Get the pointer as an unsigned integer.
	 *
	 * @param pointer: Pointer.
	 */
	DMK_FORCEINLINE constexpr UI64 GetPointerAsInteger(const void* pointer)
	{
		return (UI64)pointer;
	}

	/**
	 * Add a byte offset to a given address.
	 * This function does not alter the argument address or the byte size.
	 *
	 * @param baseAddress: Base address to be offset.
	 * @param byteCount: Offset.
	 */
	DMK_FORCEINLINE void* IncrementPointer(const void* pointer, UI64 byteCount)
	{
		return (void*)(((UI64)pointer) + byteCount);
	}

	/**
	 * Subtract a byte offset to a given address.
	 * This function does not alter the argument address or the byte size.
	 *
	 * @param baseAddress: Base address to be offset.
	 * @param byteCount: Offset.
	 */
	DMK_FORCEINLINE void* DecrementPointer(const void* pointer, UI64 byteCount)
	{
		return (void*)(((UI64)pointer) - byteCount);
	}

	/**
	 * Check if a class is inherited from another class.
	 * This function determines it at compile time.
	 *
	 * @tparam Base: The base class to be checked from.
	 * @tparam Derived: The class to test from.
	 */
	template<class Base, class Derived>
	DMK_FORCEINLINE constexpr bool IsInheritedFrom_C(const Derived& v)
	{
		return std::is_base_of<Base, Derived>::value;
	}

	/**
	 * Check if a class is inherited from another class.
	 * This function determines it at runtime.
	 *
	 * @tparam Base: The base class to be checked from.
	 * @tparam Derived: The class to test from.
	 */
	template<class Base, class Derived>
	DMK_FORCEINLINE bool IsInheritedFrom_R(const Derived& v)
	{
		return dynamic_cast<Base*>(&v) != nullptr;
	}

	/**
	 * Get the byte size which can be stored in a format.
	 * Since format is used to define the data entries for shaders, it is used to calculate the vertex stride.
	 *
	 * @param format: The format.
	 */
	DMK_FORCEINLINE UI64 FormatSize(const Format& format)
	{
		switch (format)
		{
		case Format::FORMAT_UNDEFINED:						return 0;
		case Format::FORMAT_RG_4_UNORMAL_PACK8:				return 1;
		case Format::FORMAT_RGBA_4_UNORMAL_PACK16:			return 2;
		case Format::FORMAT_BGRA_4_UNORMAL_PACK16:			return 2;
		case Format::FORMAT_R5G6B5_UNORMAL_PACK16:			return 2;
		case Format::FORMAT_B5G6R5_UNORMAL_PACK16:			return 2;
		case Format::FORMAT_R5G6B5A1_UNORMAL_PACK16:		return 2;
		case Format::FORMAT_B5G6R5A1_UNORMAL_PACK16:		return 2;
		case Format::FORMAT_A1B5G6R5_UNORMAL_PACK16:		return 2;
		case Format::FORMAT_R_8_UNORMAL:					return 1;
		case Format::FORMAT_R_8_SNORMAL:					return 1;
		case Format::FORMAT_R_8_USCALED:					return 1;
		case Format::FORMAT_R_8_SSCALED:					return 1;
		case Format::FORMAT_R_8_UINT:						return 1;
		case Format::FORMAT_R_8_SINT:						return 1;
		case Format::FORMAT_R_8_SRGB:						return 1;
		case Format::FORMAT_RG_8_UNORMAL:					return 2;
		case Format::FORMAT_RG_8_SNORMAL:					return 2;
		case Format::FORMAT_RG_8_USCALED:					return 2;
		case Format::FORMAT_RG_8_SSCALED:					return 2;
		case Format::FORMAT_RG_8_UINT:						return 2;
		case Format::FORMAT_RG_8_SINT:						return 2;
		case Format::FORMAT_RG_8_SRGB:						return 2;
		case Format::FORMAT_RGB_8_UNORMAL:					return 3;
		case Format::FORMAT_RGB_8_SNORMAL:					return 3;
		case Format::FORMAT_RGB_8_USCALED:					return 3;
		case Format::FORMAT_RGB_8_SSCALED:					return 3;
		case Format::FORMAT_RGB_8_UINT:						return 3;
		case Format::FORMAT_RGB_8_SINT:						return 3;
		case Format::FORMAT_RGB_8_SRGB:						return 3;
		case Format::FORMAT_BGR_8_UNORMAL:					return 3;
		case Format::FORMAT_BGR_8_SNORMAL:					return 3;
		case Format::FORMAT_BGR_8_USCALED:					return 3;
		case Format::FORMAT_BGR_8_SSCALED:					return 3;
		case Format::FORMAT_BGR_8_UINT:						return 3;
		case Format::FORMAT_BGR_8_SINT:						return 3;
		case Format::FORMAT_BGR_8_SRGB:						return 3;
		case Format::FORMAT_RGBA_8_UNORMAL:					return 4;
		case Format::FORMAT_RGBA_8_SNORMAL:					return 4;
		case Format::FORMAT_RGBA_8_USCALED:					return 4;
		case Format::FORMAT_RGBA_8_SSCALED:					return 4;
		case Format::FORMAT_RGBA_8_UINT:					return 4;
		case Format::FORMAT_RGBA_8_SINT:					return 4;
		case Format::FORMAT_RGBA_8_SRGB:					return 4;
		case Format::FORMAT_BGRA_8_UNORMAL:					return 4;
		case Format::FORMAT_BGRA_8_SNORMAL:					return 4;
		case Format::FORMAT_BGRA_8_USCALED:					return 4;
		case Format::FORMAT_BGRA_8_SSCALED:					return 4;
		case Format::FORMAT_BGRA_8_UINT:					return 4;
		case Format::FORMAT_BGRA_8_SINT:					return 4;
		case Format::FORMAT_BGRA_8_SRGB:					return 4;
		case Format::FORMAT_RGBA_8_UNORMAL_PACK32:			return 4;
		case Format::FORMAT_RGBA_8_SNORMAL_PACK32:			return 4;
		case Format::FORMAT_RGBA_8_USCALED_PACK32:			return 4;
		case Format::FORMAT_RGBA_8_SSCALED_PACK32:			return 4;
		case Format::FORMAT_RGBA_8_UINT_PACK32:				return 4;
		case Format::FORMAT_RGBA_8_SINT_PACK32:				return 4;
		case Format::FORMAT_RGBA_8_SRGB_PACK32:				return 4;
		case Format::FORMAT_R_16_UNORMAL:					return 2;
		case Format::FORMAT_R_16_SNORMAL:					return 2;
		case Format::FORMAT_R_16_USCALED:					return 2;
		case Format::FORMAT_R_16_SSCALED:					return 2;
		case Format::FORMAT_R_16_UINT:						return 2;
		case Format::FORMAT_R_16_SINT:						return 2;
		case Format::FORMAT_RG_16_UNORMAL:					return 4;
		case Format::FORMAT_RG_16_SNORMAL:					return 4;
		case Format::FORMAT_RG_16_USCALED:					return 4;
		case Format::FORMAT_RG_16_SSCALED:					return 4;
		case Format::FORMAT_RG_16_UINT:						return 4;
		case Format::FORMAT_RG_16_SINT:						return 4;
		case Format::FORMAT_RGB_16_UNORMAL:					return 6;
		case Format::FORMAT_RGB_16_SNORMAL:					return 6;
		case Format::FORMAT_RGB_16_USCALED:					return 6;
		case Format::FORMAT_RGB_16_SSCALED:					return 6;
		case Format::FORMAT_RGB_16_UINT:					return 6;
		case Format::FORMAT_RGB_16_SINT:					return 6;
		case Format::FORMAT_RGBA_16_UNORMAL:				return 8;
		case Format::FORMAT_RGBA_16_SNORMAL:				return 8;
		case Format::FORMAT_RGBA_16_USCALED:				return 8;
		case Format::FORMAT_RGBA_16_SSCALED:				return 8;
		case Format::FORMAT_RGBA_16_UINT:					return 8;
		case Format::FORMAT_RGBA_16_SINT:					return 8;
		case Format::FORMAT_R_32_UINT:						return 4;
		case Format::FORMAT_R_32_SINT:						return 4;
		case Format::FORMAT_RG_32_UINT:						return 8;
		case Format::FORMAT_RG_32_SINT:						return 8;
		case Format::FORMAT_RGB_32_UINT:					return 12;
		case Format::FORMAT_RGB_32_SINT:					return 12;
		case Format::FORMAT_RGBA_32_UINT:					return 16;
		case Format::FORMAT_RGBA_32_SINT:					return 16;
		case Format::FORMAT_R_64_UINT:						return 8;
		case Format::FORMAT_R_64_SINT:						return 8;
		case Format::FORMAT_RG_64_UINT:						return 16;
		case Format::FORMAT_RG_64_SINT:						return 16;
		case Format::FORMAT_RGB_64_UINT:					return 24;
		case Format::FORMAT_RGB_64_SINT:					return 24;
		case Format::FORMAT_RGBA_64_UINT:					return 32;
		case Format::FORMAT_RGBA_64_SINT:					return 32;
		default:	Logger::LogError(TEXT("Unsupported or invalid format!"));	break;
		}

		return 0;
	}

	/**
	 * Convert wchar string to a char string.
	 *
	 * @param string: The const wchar* string.
	 * @return std::string object.
	 */
	std::string WStringToString(const std::wstring& string);

	/**
	 * Convert char string to a wchar string.
	 *
	 * @param string: The const char* string.
	 * @return std::wstring object.
	 */
	std::wstring StringToWString(const std::string& string);
}

#endif // !_DYNAMIK_UTILITIES_H