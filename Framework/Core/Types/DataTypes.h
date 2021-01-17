// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * Dynamik Data Types.
 * This file contains all the necessary data types and enums used in the Dynamik Engine.
 */

typedef unsigned char UI8;			// Unsigned 8 bit integer
typedef unsigned short UI16;		// Unsigned 16 bit integer
typedef unsigned int UI32;			// Unsigned 32 bit integer
typedef unsigned long long UI64;	// Unsigned 64 bit integer

typedef signed char SI8;			// Signed 8 bit integer
typedef signed short SI16;			// Signed 16 bit integer
typedef signed int SI32;			// Signed 32 bit integer
typedef signed long long SI64;		// Signed 64 bit integer

typedef signed char I8;				// 8 bit integer
typedef short I16;					// 16 bit integer
typedef int I32;					// 32 bit integer
typedef long long I64;				// 64 bit integer

#define TEXT(text)  L##text
typedef std::string String;
typedef std::wstring WString;
typedef wchar_t wchar;

typedef UI8 BYTE;					// Byte of data
typedef BYTE* BPTR;					// Byte pointer

namespace DMK
{
	/**
	 * This contains all the virtual data types for the Dynamik Engine.
	 */
	enum class DataType : UI8 {
		UNDEFINED = 0,		// Undefined type

		BYTE = 1,			// Translates to one byte

		I8 = 1,				// Translates to 8 bit integer
		UI8 = 1,			// Translates to 8 bit unsigned integer
		SI8 = 1,			// Translates to 8 bit signed integer
		I16 = 2,			// Translates to 16 bit integer
		UI16 = 2,			// Translates to 16 bit unsigned integer
		SI16 = 2,			// Translates to 16 bit signed integer
		I32 = 4,			// Translates to 32 bit integer
		UI32 = 4,			// Translates to 32 bit unsigned integer
		SI32 = 4,			// Translates to 32 bit signed integer
		I64 = 8,			// Translates to 64 bit integer
		UI64 = 8,			// Translates to 64 bit unsigned integer
		SI64 = 8,			// Translates to 64 bit signed integer

		FLOAT = 4,			// Translates to 32 bit float
		F64 = 4,			// Translates to 64 bit float
		D64 = 8,			// Translates to 64 bit double
		CHAR = 1,			// Translates to 8 bit char

		PTR = 8,			// Translates to 8 bit pointer (x64 architecture)
		VOID_PTR = 8,		// Translates to 8 bit void pointer (x64 architecture)

		VEC1 = 4,			// Translates to 4 bit vector (1 float)
		VEC2 = 8,			// Translates to 8 bit vector (2 floats)
		VEC3 = 16,			// Translates to 16 bit vector (3 floats)
		VEC4 = 16,			// Translates to 16 bit vector (4 floats)
		UVEC1 = 4,			// Translates to 4 bit unsigned vector (1 float)
		UVEC2 = 8,			// Translates to 8 bit unsigned vector (2 floats)
		UVEC3 = 16,			// Translates to 16 bit unsigned vector (3 floats)
		UVEC4 = 16,			// Translates to 16 bit unsigned vector (4 floats)
		SVEC1 = 4,			// Translates to 4 bit signed vector (1 float)
		SVEC2 = 8,			// Translates to 8 bit signed vector (2 floats)
		SVEC3 = 16,			// Translates to 16 bit signed vector (3 floats)
		SVEC4 = 16,			// Translates to 16 bit signed vector (4 floats)
		BVEC1 = 1,			// Translates to 4 bit boolean vector (1 float)
		BVEC2 = 2,			// Translates to 8 bit boolean vector (2 floats)
		BVEC3 = 3,			// Translates to 16 bit boolean vector (3 floats)
		BVEC4 = 4,			// Translates to 16 bit boolean vector (4 floats)

		MAT2 = 16,			// Translates to 16 bit matrix (2x2)
		MAT3 = 36,			// Translates to 36 bit matrix (3x3)
		MAT4 = 64,			// Translates to 64 bit matrix (4x4)
	};

	/**
	 * This contains all the formats supported by the Dynamik Engine.
	 * R = Red,
	 * G = Green,
	 * B = Blue,
	 * A = Alpha
	 */
	enum class Format : UI8 {
		UNDEFINED,						// Undefined format

		RG_4_UNORMAL_PACK8,
		RGBA_4_UNORMAL_PACK16,
		BGRA_4_UNORMAL_PACK16,
		R5G6B5_UNORMAL_PACK16,
		B5G6R5_UNORMAL_PACK16,
		R5G6B5A1_UNORMAL_PACK16,
		B5G6R5A1_UNORMAL_PACK16,
		A1B5G6R5_UNORMAL_PACK16,

		R_8_UNORMAL,
		R_8_SNORMAL,
		R_8_USCALED,
		R_8_SSCALED,
		R_8_UINT,
		R_8_SINT,
		R_8_SRGB,

		RG_8_UNORMAL,
		RG_8_SNORMAL,
		RG_8_USCALED,
		RG_8_SSCALED,
		RG_8_UINT,
		RG_8_SINT,
		RG_8_SRGB,

		RGB_8_UNORMAL,
		RGB_8_SNORMAL,
		RGB_8_USCALED,
		RGB_8_SSCALED,
		RGB_8_UINT,
		RGB_8_SINT,
		RGB_8_SRGB,

		BGR_8_UNORMAL,
		BGR_8_SNORMAL,
		BGR_8_USCALED,
		BGR_8_SSCALED,
		BGR_8_UINT,
		BGR_8_SINT,
		BGR_8_SRGB,

		RGBA_8_UNORMAL,
		RGBA_8_SNORMAL,
		RGBA_8_USCALED,
		RGBA_8_SSCALED,
		RGBA_8_UINT,
		RGBA_8_SINT,
		RGBA_8_SRGB,

		BGRA_8_UNORMAL,
		BGRA_8_SNORMAL,
		BGRA_8_USCALED,
		BGRA_8_SSCALED,
		BGRA_8_UINT,
		BGRA_8_SINT,
		BGRA_8_SRGB,

		RGBA_8_UNORMAL_PACK32,
		RGBA_8_SNORMAL_PACK32,
		RGBA_8_USCALED_PACK32,
		RGBA_8_SSCALED_PACK32,
		RGBA_8_UINT_PACK32,
		RGBA_8_SINT_PACK32,
		RGBA_8_SRGB_PACK32,

		A2R10G10B10_UNORMAL_PACK32,
		A2R10G10B10_SNORMAL_PACK32,
		A2R10G10B10_USCALED_PACK32,
		A2R10G10B10_SSCALED_PACK32,
		A2R10G10B10_UINT_PACK32,
		A2R10G10B10_SINT_PACK32,

		A2B10G10R10_UNORMAL_PACK32,
		A2B10G10R10_SNORMAL_PACK32,
		A2B10G10R10_USCALED_PACK32,
		A2B10G10R10_SSCALED_PACK32,
		A2B10G10R10_UINT_PACK32,
		A2B10G10R10_SINT_PACK32,

		R_16_UNORMAL,
		R_16_SNORMAL,
		R_16_USCALED,
		R_16_SSCALED,
		R_16_UINT,
		R_16_SINT,
		R_16_SFLOAT,

		RG_16_UNORMAL,
		RG_16_SNORMAL,
		RG_16_USCALED,
		RG_16_SSCALED,
		RG_16_UINT,
		RG_16_SINT,
		RG_16_SFLOAT,

		RGB_16_UNORMAL,
		RGB_16_SNORMAL,
		RGB_16_USCALED,
		RGB_16_SSCALED,
		RGB_16_UINT,
		RGB_16_SINT,
		RGB_16_SFLOAT,

		RGBA_16_UNORMAL,
		RGBA_16_SNORMAL,
		RGBA_16_USCALED,
		RGBA_16_SSCALED,
		RGBA_16_UINT,
		RGBA_16_SINT,
		RGBA_16_SFLOAT,

		R_32_UINT,
		R_32_SINT,
		R_32_SFLOAT,

		RG_32_UINT,
		RG_32_SINT,
		RG_32_SFLOAT,

		RGB_32_UINT,
		RGB_32_SINT,
		RGB_32_SFLOAT,

		RGBA_32_UINT,
		RGBA_32_SINT,
		RGBA_32_SFLOAT,

		R_64_UINT,
		R_64_SINT,
		R_64_SFLOAT,

		RG_64_UINT,
		RG_64_SINT,
		RG_64_SFLOAT,

		RGB_64_UINT,
		RGB_64_SINT,
		RGB_64_SFLOAT,

		RGBA_64_UINT,
		RGBA_64_SINT,
		RGBA_64_SFLOAT,

		B10G11R11_UFLOAT_PACK32,
		E5B9G9R9_UFLOAT_PACK32,

		D_16_UNORM,
		X8_D_24_UNORM_PACK32,
		D_32_SFLOAT,
		S_8_UINT,
		D_16_UNORM_S_8_UINT,
		D_24_UNORM_S_8_UINT,
		D_32_SFLOAT_S_8_UINT,

		BC1_RGB_UNORM_BLOCK,
		BC1_RGB_SRGB_BLOCK,
		BC1_RGBA_UNORM_BLOCK,
		BC1_RGBA_SRGB_BLOCK,

		BC2_UNORM_BLOCK,
		BC2_SRGB_BLOCK,
		BC3_UNORM_BLOCK,
		BC3_SRGB_BLOCK,

		BC4_UNORM_BLOCK,
		BC4_SNORM_BLOCK,

		BC5_UNORM_BLOCK,
		BC5_SNORM_BLOCK,

		BC6H_UFLOAT_BLOCK,
		BC6H_SFLOAT_BLOCK,

		BC7_UNORM_BLOCK,
		BC7_SRGB_BLOCK,

		ETC2_RGB_8_UNORM_BLOCK,
		ETC2_RGB_8_SRGB_BLOCK,

		ETC2_R8G8B8A1_UNORM_BLOCK,
		ETC2_R8G8B8A1_SRGB_BLOCK,

		ETC2_RGBA_8_UNORM_BLOCK,
		ETC2_RGBA_8_SRGB_BLOCK,

		EAC_R_11_UNORM_BLOCK,
		EAC_R_11_SNORM_BLOCK,

		EAC_RG_11_UNORM_BLOCK,
		EAC_RG_11_SNORM_BLOCK,

		ASTC_4x4_UNORM_BLOCK,
		ASTC_4x4_SRGB_BLOCK,

		ASTC_5x4_UNORM_BLOCK,
		ASTC_5x4_SRGB_BLOCK,

		ASTC_5x5_UNORM_BLOCK,
		ASTC_5x5_SRGB_BLOCK,

		ASTC_6x5_UNORM_BLOCK,
		ASTC_6x5_SRGB_BLOCK,

		ASTC_6x6_UNORM_BLOCK,
		ASTC_6x6_SRGB_BLOCK,

		ASTC_8x5_UNORM_BLOCK,
		ASTC_8x5_SRGB_BLOCK,

		ASTC_8x6_UNORM_BLOCK,
		ASTC_8x6_SRGB_BLOCK,

		ASTC_8x8_UNORM_BLOCK,
		ASTC_8x8_SRGB_BLOCK,

		ASTC_10x5_UNORM_BLOCK,
		ASTC_10x5_SRGB_BLOCK,

		ASTC_10x6_UNORM_BLOCK,
		ASTC_10x6_SRGB_BLOCK,

		ASTC_10x8_UNORM_BLOCK,
		ASTC_10x8_SRGB_BLOCK,

		ASTC_10x10_UNORM_BLOCK,
		ASTC_10x10_SRGB_BLOCK,

		ASTC_12x10_UNORM_BLOCK,
		ASTC_12x10_SRGB_BLOCK,

		ASTC_12x12_UNORM_BLOCK,
		ASTC_12x12_SRGB_BLOCK,
	};

	/**
	 * Compare Operator enum.
	 */
	enum class CompareOperator : UI8 {
		DONT_COMPARE,
		LESS,
		EQUAL,
		LESS_OR_EQUAL,
		GREATER,
		NOT_EQUAL,
		GREATER_OR_EQUAL,
		ALWAYS_TRUE
	};

	/**
	 * Logic Operator enum.
	 */
	enum class LogicOperator : UI8 {
		CLEAR,
		AND,
		AND_REVERSE,
		COPY,
		AND_INVERTED,
		NO_OP,
		XOR,
		OR,
		NOR,
		EQUIVALENT,
		INVERT,
		OR_REVERSE,
		COPY_INVERTED,
		OR_INVERTED,
		NAND,
		SET,
	};
}

#define INSERT_INTO_VECTOR(vector, ...)	vector.insert(vector.end(), __VA_ARGS__)
