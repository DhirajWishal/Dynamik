// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "ImageImporter.h"

#include "Core/Objects/Resources/Textures/Texture2D.h"
#include "Core/Objects/Resources/Textures/TextureCube.h"

#include <stb_image.h>
#include <gli/gli.hpp>
#include <FreeImage.h>

#include <filesystem>

namespace Dynamik
{
	DMK_FORCEINLINE DMKFormat getFormat(gli::format format)
	{
		switch (format)
		{
		case gli::FORMAT_UNDEFINED:						return Dynamik::DMKFormat::DMK_FORMAT_UNDEFINED;
		case gli::FORMAT_R8_UNORM_PACK8:				return Dynamik::DMKFormat::DMK_FORMAT_R_8_UNORMAL;
		case gli::FORMAT_R8_SNORM_PACK8:				return Dynamik::DMKFormat::DMK_FORMAT_R_8_SNORMAL;
		case gli::FORMAT_R8_USCALED_PACK8:				return Dynamik::DMKFormat::DMK_FORMAT_R_8_USCALED;
		case gli::FORMAT_R8_SSCALED_PACK8:				return Dynamik::DMKFormat::DMK_FORMAT_R_8_SSCALED;
		case gli::FORMAT_R8_UINT_PACK8:					return Dynamik::DMKFormat::DMK_FORMAT_R_8_UINT;
		case gli::FORMAT_R8_SINT_PACK8:					return Dynamik::DMKFormat::DMK_FORMAT_R_8_SINT;
		case gli::FORMAT_R8_SRGB_PACK8:					return Dynamik::DMKFormat::DMK_FORMAT_R_8_SRGB;
		case gli::FORMAT_RG8_UNORM_PACK8:				return Dynamik::DMKFormat::DMK_FORMAT_RG_8_UNORMAL;
		case gli::FORMAT_RG8_SNORM_PACK8:				return Dynamik::DMKFormat::DMK_FORMAT_RG_8_SNORMAL;
		case gli::FORMAT_RG8_USCALED_PACK8:				return Dynamik::DMKFormat::DMK_FORMAT_RG_8_USCALED;
		case gli::FORMAT_RG8_SSCALED_PACK8:				return Dynamik::DMKFormat::DMK_FORMAT_RG_8_SSCALED;
		case gli::FORMAT_RG8_UINT_PACK8:				return Dynamik::DMKFormat::DMK_FORMAT_RG_8_UINT;
		case gli::FORMAT_RG8_SINT_PACK8:				return Dynamik::DMKFormat::DMK_FORMAT_RG_8_SINT;
		case gli::FORMAT_RG8_SRGB_PACK8:				return Dynamik::DMKFormat::DMK_FORMAT_RG_8_SRGB;
		case gli::FORMAT_RGB8_UNORM_PACK8:				return Dynamik::DMKFormat::DMK_FORMAT_RGB_8_UNORMAL;
		case gli::FORMAT_RGB8_SNORM_PACK8:				return Dynamik::DMKFormat::DMK_FORMAT_RGB_8_SNORMAL;
		case gli::FORMAT_RGB8_USCALED_PACK8:			return Dynamik::DMKFormat::DMK_FORMAT_RGB_8_USCALED;
		case gli::FORMAT_RGB8_SSCALED_PACK8:			return Dynamik::DMKFormat::DMK_FORMAT_RGB_8_SSCALED;
		case gli::FORMAT_RGB8_UINT_PACK8:				return Dynamik::DMKFormat::DMK_FORMAT_RGB_8_UINT;
		case gli::FORMAT_RGB8_SINT_PACK8:				return Dynamik::DMKFormat::DMK_FORMAT_RGB_8_SINT;
		case gli::FORMAT_RGB8_SRGB_PACK8:				return Dynamik::DMKFormat::DMK_FORMAT_RGB_8_SRGB;
		case gli::FORMAT_BGR8_UNORM_PACK8:				return Dynamik::DMKFormat::DMK_FORMAT_BGR_8_UNORMAL;
		case gli::FORMAT_BGR8_SNORM_PACK8:				return Dynamik::DMKFormat::DMK_FORMAT_BGR_8_SNORMAL;
		case gli::FORMAT_BGR8_USCALED_PACK8:			return Dynamik::DMKFormat::DMK_FORMAT_BGR_8_USCALED;
		case gli::FORMAT_BGR8_SSCALED_PACK8:			return Dynamik::DMKFormat::DMK_FORMAT_BGR_8_SSCALED;
		case gli::FORMAT_BGR8_UINT_PACK8:				return Dynamik::DMKFormat::DMK_FORMAT_BGR_8_UINT;
		case gli::FORMAT_BGR8_SINT_PACK8:				return Dynamik::DMKFormat::DMK_FORMAT_BGR_8_SINT;
		case gli::FORMAT_BGR8_SRGB_PACK8:				return Dynamik::DMKFormat::DMK_FORMAT_BGR_8_SRGB;
		case gli::FORMAT_RGBA8_UNORM_PACK8:				return Dynamik::DMKFormat::DMK_FORMAT_RGBA_8_UNORMAL;
		case gli::FORMAT_RGBA8_SNORM_PACK8:				return Dynamik::DMKFormat::DMK_FORMAT_RGBA_8_SNORMAL;
		case gli::FORMAT_RGBA8_USCALED_PACK8:			return Dynamik::DMKFormat::DMK_FORMAT_RGBA_8_USCALED;
		case gli::FORMAT_RGBA8_SSCALED_PACK8:			return Dynamik::DMKFormat::DMK_FORMAT_RGBA_8_SSCALED;
		case gli::FORMAT_RGBA8_UINT_PACK8:				return Dynamik::DMKFormat::DMK_FORMAT_RGBA_8_UINT;
		case gli::FORMAT_RGBA8_SINT_PACK8:				return Dynamik::DMKFormat::DMK_FORMAT_RGBA_8_SINT;
		case gli::FORMAT_RGBA8_SRGB_PACK8:				return Dynamik::DMKFormat::DMK_FORMAT_RGBA_8_SRGB;
		case gli::FORMAT_BGRA8_UNORM_PACK8:				return Dynamik::DMKFormat::DMK_FORMAT_BGRA_8_UNORMAL;
		case gli::FORMAT_BGRA8_SNORM_PACK8:				return Dynamik::DMKFormat::DMK_FORMAT_BGRA_8_SNORMAL;
		case gli::FORMAT_BGRA8_USCALED_PACK8:			return Dynamik::DMKFormat::DMK_FORMAT_BGRA_8_USCALED;
		case gli::FORMAT_BGRA8_SSCALED_PACK8:			return Dynamik::DMKFormat::DMK_FORMAT_BGRA_8_SSCALED;
		case gli::FORMAT_BGRA8_UINT_PACK8:				return Dynamik::DMKFormat::DMK_FORMAT_BGRA_8_UINT;
		case gli::FORMAT_BGRA8_SINT_PACK8:				return Dynamik::DMKFormat::DMK_FORMAT_BGRA_8_SINT;
		case gli::FORMAT_BGRA8_SRGB_PACK8:				return Dynamik::DMKFormat::DMK_FORMAT_BGRA_8_SRGB;
		case gli::FORMAT_RGBA8_UNORM_PACK32:			return Dynamik::DMKFormat::DMK_FORMAT_RGBA_8_UNORMAL_PACK32;
		case gli::FORMAT_RGBA8_SNORM_PACK32:			return Dynamik::DMKFormat::DMK_FORMAT_RGBA_8_SNORMAL_PACK32;
		case gli::FORMAT_RGBA8_USCALED_PACK32:			return Dynamik::DMKFormat::DMK_FORMAT_RGBA_8_USCALED_PACK32;
		case gli::FORMAT_RGBA8_SSCALED_PACK32:			return Dynamik::DMKFormat::DMK_FORMAT_RGBA_8_SSCALED_PACK32;
		case gli::FORMAT_RGBA8_UINT_PACK32:				return Dynamik::DMKFormat::DMK_FORMAT_RGBA_8_UINT_PACK32;
		case gli::FORMAT_RGBA8_SINT_PACK32:				return Dynamik::DMKFormat::DMK_FORMAT_RGBA_8_SINT_PACK32;
		case gli::FORMAT_RGBA8_SRGB_PACK32:				return Dynamik::DMKFormat::DMK_FORMAT_RGBA_8_SRGB_PACK32;
		case gli::FORMAT_RGB10A2_UNORM_PACK32:			return Dynamik::DMKFormat::DMK_FORMAT_A2R10G10B10_UNORMAL_PACK32;
		case gli::FORMAT_RGB10A2_SNORM_PACK32:			return Dynamik::DMKFormat::DMK_FORMAT_A2R10G10B10_SNORMAL_PACK32;
		case gli::FORMAT_RGB10A2_USCALED_PACK32:		return Dynamik::DMKFormat::DMK_FORMAT_A2R10G10B10_USCALED_PACK32;
		case gli::FORMAT_RGB10A2_SSCALED_PACK32:		return Dynamik::DMKFormat::DMK_FORMAT_A2R10G10B10_SSCALED_PACK32;
		case gli::FORMAT_RGB10A2_UINT_PACK32:			return Dynamik::DMKFormat::DMK_FORMAT_A2R10G10B10_UINT_PACK32;
		case gli::FORMAT_RGB10A2_SINT_PACK32:			return Dynamik::DMKFormat::DMK_FORMAT_A2R10G10B10_SINT_PACK32;
		case gli::FORMAT_BGR10A2_UNORM_PACK32:			return Dynamik::DMKFormat::DMK_FORMAT_A2B10G10R10_UNORMAL_PACK32;
		case gli::FORMAT_BGR10A2_SNORM_PACK32:			return Dynamik::DMKFormat::DMK_FORMAT_A2B10G10R10_SNORMAL_PACK32;
		case gli::FORMAT_BGR10A2_USCALED_PACK32:		return Dynamik::DMKFormat::DMK_FORMAT_A2B10G10R10_USCALED_PACK32;
		case gli::FORMAT_BGR10A2_SSCALED_PACK32:		return Dynamik::DMKFormat::DMK_FORMAT_A2B10G10R10_SSCALED_PACK32;
		case gli::FORMAT_BGR10A2_UINT_PACK32:			return Dynamik::DMKFormat::DMK_FORMAT_A2B10G10R10_UINT_PACK32;
		case gli::FORMAT_BGR10A2_SINT_PACK32:			return Dynamik::DMKFormat::DMK_FORMAT_A2B10G10R10_SINT_PACK32;
		case gli::FORMAT_R16_UNORM_PACK16:				return Dynamik::DMKFormat::DMK_FORMAT_R_16_UNORMAL;
		case gli::FORMAT_R16_SNORM_PACK16:				return Dynamik::DMKFormat::DMK_FORMAT_R_16_SNORMAL;
		case gli::FORMAT_R16_USCALED_PACK16:			return Dynamik::DMKFormat::DMK_FORMAT_R_16_USCALED;
		case gli::FORMAT_R16_SSCALED_PACK16:			return Dynamik::DMKFormat::DMK_FORMAT_R_16_SSCALED;
		case gli::FORMAT_R16_UINT_PACK16:				return Dynamik::DMKFormat::DMK_FORMAT_R_16_UINT;
		case gli::FORMAT_R16_SINT_PACK16:				return Dynamik::DMKFormat::DMK_FORMAT_R_16_SINT;
		case gli::FORMAT_R16_SFLOAT_PACK16:				return Dynamik::DMKFormat::DMK_FORMAT_R_16_SF32;
		case gli::FORMAT_RG16_UNORM_PACK16:				return Dynamik::DMKFormat::DMK_FORMAT_RG_16_UNORMAL;
		case gli::FORMAT_RG16_SNORM_PACK16:				return Dynamik::DMKFormat::DMK_FORMAT_RG_16_SNORMAL;
		case gli::FORMAT_RG16_USCALED_PACK16:			return Dynamik::DMKFormat::DMK_FORMAT_RG_16_USCALED;
		case gli::FORMAT_RG16_SSCALED_PACK16:			return Dynamik::DMKFormat::DMK_FORMAT_RG_16_SSCALED;
		case gli::FORMAT_RG16_UINT_PACK16:				return Dynamik::DMKFormat::DMK_FORMAT_RG_16_UINT;
		case gli::FORMAT_RG16_SINT_PACK16:				return Dynamik::DMKFormat::DMK_FORMAT_RG_16_SINT;
		case gli::FORMAT_RG16_SFLOAT_PACK16:			return Dynamik::DMKFormat::DMK_FORMAT_RG_16_SF32;
		case gli::FORMAT_RGB16_UNORM_PACK16:			return Dynamik::DMKFormat::DMK_FORMAT_RGB_16_UNORMAL;
		case gli::FORMAT_RGB16_SNORM_PACK16:			return Dynamik::DMKFormat::DMK_FORMAT_RGB_16_SNORMAL;
		case gli::FORMAT_RGB16_USCALED_PACK16:			return Dynamik::DMKFormat::DMK_FORMAT_RGB_16_USCALED;
		case gli::FORMAT_RGB16_SSCALED_PACK16:			return Dynamik::DMKFormat::DMK_FORMAT_RGB_16_SSCALED;
		case gli::FORMAT_RGB16_UINT_PACK16:				return Dynamik::DMKFormat::DMK_FORMAT_RGB_16_UINT;
		case gli::FORMAT_RGB16_SINT_PACK16:				return Dynamik::DMKFormat::DMK_FORMAT_RGB_16_SINT;
		case gli::FORMAT_RGB16_SFLOAT_PACK16:			return Dynamik::DMKFormat::DMK_FORMAT_RGB_16_SF32;
		case gli::FORMAT_RGBA16_UNORM_PACK16:			return Dynamik::DMKFormat::DMK_FORMAT_RGBA_16_UNORMAL;
		case gli::FORMAT_RGBA16_SNORM_PACK16:			return Dynamik::DMKFormat::DMK_FORMAT_RGBA_16_SNORMAL;
		case gli::FORMAT_RGBA16_USCALED_PACK16:			return Dynamik::DMKFormat::DMK_FORMAT_RGBA_16_USCALED;
		case gli::FORMAT_RGBA16_SSCALED_PACK16:			return Dynamik::DMKFormat::DMK_FORMAT_RGBA_16_SSCALED;
		case gli::FORMAT_RGBA16_UINT_PACK16:			return Dynamik::DMKFormat::DMK_FORMAT_RGBA_16_UINT;
		case gli::FORMAT_RGBA16_SINT_PACK16:			return Dynamik::DMKFormat::DMK_FORMAT_RGBA_16_SINT;
		case gli::FORMAT_RGBA16_SFLOAT_PACK16:			return Dynamik::DMKFormat::DMK_FORMAT_RGBA_16_SF32;
		case gli::FORMAT_RG32_SINT_PACK32:				return Dynamik::DMKFormat::DMK_FORMAT_R_32_UINT;
		case gli::FORMAT_RG32_SFLOAT_PACK32:			return Dynamik::DMKFormat::DMK_FORMAT_R_32_SINT;
		case gli::FORMAT_RGB32_UINT_PACK32:				return Dynamik::DMKFormat::DMK_FORMAT_R_32_SF32;
		case gli::FORMAT_RGBA32_SFLOAT_PACK32:			return Dynamik::DMKFormat::DMK_FORMAT_RG_32_UINT;
		case gli::FORMAT_D16_UNORM_PACK16:				return Dynamik::DMKFormat::DMK_FORMAT_D_16_UNORM;
		case gli::FORMAT_D24_UNORM_PACK32:				return Dynamik::DMKFormat::DMK_FORMAT_X8_D_24_UNORM_PACK32;
		case gli::FORMAT_D32_SFLOAT_PACK32:				return Dynamik::DMKFormat::DMK_FORMAT_D_32_SF32;
		case gli::FORMAT_S8_UINT_PACK8:					return Dynamik::DMKFormat::DMK_FORMAT_S_8_UINT;
		case gli::FORMAT_D16_UNORM_S8_UINT_PACK32:		return Dynamik::DMKFormat::DMK_FORMAT_D_16_UNORM_S_8_UINT;
		case gli::FORMAT_D24_UNORM_S8_UINT_PACK32:		return Dynamik::DMKFormat::DMK_FORMAT_X8_D_24_UNORM_PACK32;
		case gli::FORMAT_D32_SFLOAT_S8_UINT_PACK64:		return Dynamik::DMKFormat::DMK_FORMAT_D_32_SF32_S_8_UINT;
		case gli::FORMAT_RGB_ETC2_UNORM_BLOCK8:			return Dynamik::DMKFormat::DMK_FORMAT_ETC2_RGB_8_UNORM_BLOCK;
		case gli::FORMAT_RGB_ETC2_SRGB_BLOCK8:			return Dynamik::DMKFormat::DMK_FORMAT_ETC2_RGB_8_UNORM_BLOCK;
		case gli::FORMAT_RGBA_ETC2_UNORM_BLOCK8:		return Dynamik::DMKFormat::DMK_FORMAT_ETC2_RGBA_8_UNORM_BLOCK;
		case gli::FORMAT_RGBA_ETC2_SRGB_BLOCK8:			return Dynamik::DMKFormat::DMK_FORMAT_ETC2_RGBA_8_SRGB_BLOCK;
		case gli::FORMAT_RGBA_ASTC_4X4_UNORM_BLOCK16:	return Dynamik::DMKFormat::DMK_FORMAT_ASTC_4x4_UNORM_BLOCK;
		case gli::FORMAT_RGBA_ASTC_4X4_SRGB_BLOCK16:	return Dynamik::DMKFormat::DMK_FORMAT_ASTC_4x4_SRGB_BLOCK;
		case gli::FORMAT_RGBA_ASTC_5X4_UNORM_BLOCK16:	return Dynamik::DMKFormat::DMK_FORMAT_ASTC_5x4_UNORM_BLOCK;
		case gli::FORMAT_RGBA_ASTC_5X4_SRGB_BLOCK16:	return Dynamik::DMKFormat::DMK_FORMAT_ASTC_5x4_SRGB_BLOCK;
		case gli::FORMAT_RGBA_ASTC_5X5_UNORM_BLOCK16:	return Dynamik::DMKFormat::DMK_FORMAT_ASTC_5x5_UNORM_BLOCK;
		case gli::FORMAT_RGBA_ASTC_5X5_SRGB_BLOCK16:	return Dynamik::DMKFormat::DMK_FORMAT_ASTC_5x5_SRGB_BLOCK;
		case gli::FORMAT_RGBA_ASTC_6X5_UNORM_BLOCK16:	return Dynamik::DMKFormat::DMK_FORMAT_ASTC_6x5_UNORM_BLOCK;
		case gli::FORMAT_RGBA_ASTC_6X5_SRGB_BLOCK16:	return Dynamik::DMKFormat::DMK_FORMAT_ASTC_6x5_SRGB_BLOCK;
		case gli::FORMAT_RGBA_ASTC_6X6_UNORM_BLOCK16:	return Dynamik::DMKFormat::DMK_FORMAT_ASTC_6x6_UNORM_BLOCK;
		case gli::FORMAT_RGBA_ASTC_6X6_SRGB_BLOCK16:	return Dynamik::DMKFormat::DMK_FORMAT_ASTC_6x6_SRGB_BLOCK;
		case gli::FORMAT_RGBA_ASTC_8X5_UNORM_BLOCK16:	return Dynamik::DMKFormat::DMK_FORMAT_ASTC_8x5_UNORM_BLOCK;
		case gli::FORMAT_RGBA_ASTC_8X5_SRGB_BLOCK16:	return Dynamik::DMKFormat::DMK_FORMAT_ASTC_8x5_SRGB_BLOCK;
		case gli::FORMAT_RGBA_ASTC_8X6_UNORM_BLOCK16:	return Dynamik::DMKFormat::DMK_FORMAT_ASTC_8x6_UNORM_BLOCK;
		case gli::FORMAT_RGBA_ASTC_8X6_SRGB_BLOCK16:	return Dynamik::DMKFormat::DMK_FORMAT_ASTC_8x6_SRGB_BLOCK;
		case gli::FORMAT_RGBA_ASTC_8X8_UNORM_BLOCK16:	return Dynamik::DMKFormat::DMK_FORMAT_ASTC_8x8_UNORM_BLOCK;
		case gli::FORMAT_RGBA_ASTC_8X8_SRGB_BLOCK16:	return Dynamik::DMKFormat::DMK_FORMAT_ASTC_8x8_SRGB_BLOCK;
		case gli::FORMAT_RGBA_ASTC_10X5_UNORM_BLOCK16:	return Dynamik::DMKFormat::DMK_FORMAT_ASTC_10x5_UNORM_BLOCK;
		case gli::FORMAT_RGBA_ASTC_10X5_SRGB_BLOCK16:	return Dynamik::DMKFormat::DMK_FORMAT_ASTC_10x5_SRGB_BLOCK;
		case gli::FORMAT_RGBA_ASTC_10X6_UNORM_BLOCK16:	return Dynamik::DMKFormat::DMK_FORMAT_ASTC_10x6_UNORM_BLOCK;
		case gli::FORMAT_RGBA_ASTC_10X6_SRGB_BLOCK16:	return Dynamik::DMKFormat::DMK_FORMAT_ASTC_10x6_SRGB_BLOCK;
		case gli::FORMAT_RGBA_ASTC_10X8_UNORM_BLOCK16:	return Dynamik::DMKFormat::DMK_FORMAT_ASTC_10x8_UNORM_BLOCK;
		case gli::FORMAT_RGBA_ASTC_10X8_SRGB_BLOCK16:	return Dynamik::DMKFormat::DMK_FORMAT_ASTC_10x8_SRGB_BLOCK;
		case gli::FORMAT_RGBA_ASTC_10X10_UNORM_BLOCK16:	return Dynamik::DMKFormat::DMK_FORMAT_ASTC_10x10_UNORM_BLOCK;
		case gli::FORMAT_RGBA_ASTC_10X10_SRGB_BLOCK16:	return Dynamik::DMKFormat::DMK_FORMAT_ASTC_10x10_SRGB_BLOCK;
		case gli::FORMAT_RGBA_ASTC_12X10_UNORM_BLOCK16:	return Dynamik::DMKFormat::DMK_FORMAT_ASTC_12x10_UNORM_BLOCK;
		case gli::FORMAT_RGBA_ASTC_12X10_SRGB_BLOCK16:	return Dynamik::DMKFormat::DMK_FORMAT_ASTC_12x10_SRGB_BLOCK;
		case gli::FORMAT_RGBA_ASTC_12X12_UNORM_BLOCK16:	return Dynamik::DMKFormat::DMK_FORMAT_ASTC_12x12_UNORM_BLOCK;
		case gli::FORMAT_RGBA_ASTC_12X12_SRGB_BLOCK16:	return Dynamik::DMKFormat::DMK_FORMAT_ASTC_12x12_SRGB_BLOCK;
		case gli::FORMAT_RGB_ETC_UNORM_BLOCK8:			return Dynamik::DMKFormat::DMK_FORMAT_ETC2_RGB_8_UNORM_BLOCK;
		case gli::FORMAT_BGR8_UNORM_PACK32:				return Dynamik::DMKFormat::DMK_FORMAT_BGR_8_UNORMAL;
		case gli::FORMAT_BGR8_SRGB_PACK32:				return Dynamik::DMKFormat::DMK_FORMAT_BGR_8_SRGB;
		case gli::FORMAT_R_EAC_UNORM_BLOCK8:			return Dynamik::DMKFormat::DMK_FORMAT_EAC_R_11_UNORM_BLOCK;
		case gli::FORMAT_R_EAC_SNORM_BLOCK8:			return Dynamik::DMKFormat::DMK_FORMAT_EAC_R_11_SNORM_BLOCK;
		case gli::FORMAT_RG_EAC_UNORM_BLOCK16:			return Dynamik::DMKFormat::DMK_FORMAT_EAC_RG_11_UNORM_BLOCK;
		case gli::FORMAT_RG_EAC_SNORM_BLOCK16:			return Dynamik::DMKFormat::DMK_FORMAT_EAC_RG_11_SNORM_BLOCK;
		case gli::FORMAT_R64_UINT_PACK64:				return Dynamik::DMKFormat::DMK_FORMAT_R_64_UINT;
		case gli::FORMAT_R64_SINT_PACK64:				return Dynamik::DMKFormat::DMK_FORMAT_R_64_SINT;
		case gli::FORMAT_R64_SFLOAT_PACK64:				return Dynamik::DMKFormat::DMK_FORMAT_R_64_SF32;
		case gli::FORMAT_RG64_UINT_PACK64:				return Dynamik::DMKFormat::DMK_FORMAT_RG_64_UINT;
		case gli::FORMAT_RG64_SINT_PACK64:				return Dynamik::DMKFormat::DMK_FORMAT_RG_64_SINT;
		case gli::FORMAT_RG64_SFLOAT_PACK64:			return Dynamik::DMKFormat::DMK_FORMAT_RG_64_SF32;
		case gli::FORMAT_RGB64_UINT_PACK64:				return Dynamik::DMKFormat::DMK_FORMAT_RGB_64_UINT;
		case gli::FORMAT_RGB64_SINT_PACK64:				return Dynamik::DMKFormat::DMK_FORMAT_RGB_64_SINT;
		case gli::FORMAT_RGB64_SFLOAT_PACK64:			return Dynamik::DMKFormat::DMK_FORMAT_RGB_64_SF32;
		case gli::FORMAT_RGBA64_UINT_PACK64:			return Dynamik::DMKFormat::DMK_FORMAT_RGBA_64_UINT;
		case gli::FORMAT_RGBA64_SINT_PACK64:			return Dynamik::DMKFormat::DMK_FORMAT_RGBA_64_SINT;
		case gli::FORMAT_RGBA64_SFLOAT_PACK64:			return Dynamik::DMKFormat::DMK_FORMAT_RGBA_64_SF32;
		default:
			DMK_ERROR("Invalid or unsupported gli texture format!");
			break;
		}

		return DMKFormat::DMK_FORMAT_UNDEFINED;
	}

	DMKTexture* Dynamik::DMKImageImporter::loadTexture2D(const STRING& file)
	{
		DMKTexture2D* pTexture = StaticAllocator<DMKTexture2D>::allocate();

		return nullptr;
	}
}
