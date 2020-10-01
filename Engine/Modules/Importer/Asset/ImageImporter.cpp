// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "ImageImporter.h"

#include "Core/Objects/Resources/Textures/Texture2D.h"
#include "Core/Objects/Resources/Textures/TextureCube.h"

#include <stb_image.h>
#include <gli/gli.hpp>

#define FREEIMAGE_LIB
#include <FreeImage.h>

	/* Convert gli::format to DMKFormat. */
DMK_FORCEINLINE DMKFormat GetFormat(gli::format format)
{
	switch (format)
	{
	case gli::FORMAT_UNDEFINED:						return DMKFormat::DMK_FORMAT_UNDEFINED;
	case gli::FORMAT_R8_UNORM_PACK8:				return DMKFormat::DMK_FORMAT_R_8_UNORMAL;
	case gli::FORMAT_R8_SNORM_PACK8:				return DMKFormat::DMK_FORMAT_R_8_SNORMAL;
	case gli::FORMAT_R8_USCALED_PACK8:				return DMKFormat::DMK_FORMAT_R_8_USCALED;
	case gli::FORMAT_R8_SSCALED_PACK8:				return DMKFormat::DMK_FORMAT_R_8_SSCALED;
	case gli::FORMAT_R8_UINT_PACK8:					return DMKFormat::DMK_FORMAT_R_8_UINT;
	case gli::FORMAT_R8_SINT_PACK8:					return DMKFormat::DMK_FORMAT_R_8_SINT;
	case gli::FORMAT_R8_SRGB_PACK8:					return DMKFormat::DMK_FORMAT_R_8_SRGB;
	case gli::FORMAT_RG8_UNORM_PACK8:				return DMKFormat::DMK_FORMAT_RG_8_UNORMAL;
	case gli::FORMAT_RG8_SNORM_PACK8:				return DMKFormat::DMK_FORMAT_RG_8_SNORMAL;
	case gli::FORMAT_RG8_USCALED_PACK8:				return DMKFormat::DMK_FORMAT_RG_8_USCALED;
	case gli::FORMAT_RG8_SSCALED_PACK8:				return DMKFormat::DMK_FORMAT_RG_8_SSCALED;
	case gli::FORMAT_RG8_UINT_PACK8:				return DMKFormat::DMK_FORMAT_RG_8_UINT;
	case gli::FORMAT_RG8_SINT_PACK8:				return DMKFormat::DMK_FORMAT_RG_8_SINT;
	case gli::FORMAT_RG8_SRGB_PACK8:				return DMKFormat::DMK_FORMAT_RG_8_SRGB;
	case gli::FORMAT_RGB8_UNORM_PACK8:				return DMKFormat::DMK_FORMAT_RGB_8_UNORMAL;
	case gli::FORMAT_RGB8_SNORM_PACK8:				return DMKFormat::DMK_FORMAT_RGB_8_SNORMAL;
	case gli::FORMAT_RGB8_USCALED_PACK8:			return DMKFormat::DMK_FORMAT_RGB_8_USCALED;
	case gli::FORMAT_RGB8_SSCALED_PACK8:			return DMKFormat::DMK_FORMAT_RGB_8_SSCALED;
	case gli::FORMAT_RGB8_UINT_PACK8:				return DMKFormat::DMK_FORMAT_RGB_8_UINT;
	case gli::FORMAT_RGB8_SINT_PACK8:				return DMKFormat::DMK_FORMAT_RGB_8_SINT;
	case gli::FORMAT_RGB8_SRGB_PACK8:				return DMKFormat::DMK_FORMAT_RGB_8_SRGB;
	case gli::FORMAT_BGR8_UNORM_PACK8:				return DMKFormat::DMK_FORMAT_BGR_8_UNORMAL;
	case gli::FORMAT_BGR8_SNORM_PACK8:				return DMKFormat::DMK_FORMAT_BGR_8_SNORMAL;
	case gli::FORMAT_BGR8_USCALED_PACK8:			return DMKFormat::DMK_FORMAT_BGR_8_USCALED;
	case gli::FORMAT_BGR8_SSCALED_PACK8:			return DMKFormat::DMK_FORMAT_BGR_8_SSCALED;
	case gli::FORMAT_BGR8_UINT_PACK8:				return DMKFormat::DMK_FORMAT_BGR_8_UINT;
	case gli::FORMAT_BGR8_SINT_PACK8:				return DMKFormat::DMK_FORMAT_BGR_8_SINT;
	case gli::FORMAT_BGR8_SRGB_PACK8:				return DMKFormat::DMK_FORMAT_BGR_8_SRGB;
	case gli::FORMAT_RGBA8_UNORM_PACK8:				return DMKFormat::DMK_FORMAT_RGBA_8_UNORMAL;
	case gli::FORMAT_RGBA8_SNORM_PACK8:				return DMKFormat::DMK_FORMAT_RGBA_8_SNORMAL;
	case gli::FORMAT_RGBA8_USCALED_PACK8:			return DMKFormat::DMK_FORMAT_RGBA_8_USCALED;
	case gli::FORMAT_RGBA8_SSCALED_PACK8:			return DMKFormat::DMK_FORMAT_RGBA_8_SSCALED;
	case gli::FORMAT_RGBA8_UINT_PACK8:				return DMKFormat::DMK_FORMAT_RGBA_8_UINT;
	case gli::FORMAT_RGBA8_SINT_PACK8:				return DMKFormat::DMK_FORMAT_RGBA_8_SINT;
	case gli::FORMAT_RGBA8_SRGB_PACK8:				return DMKFormat::DMK_FORMAT_RGBA_8_SRGB;
	case gli::FORMAT_BGRA8_UNORM_PACK8:				return DMKFormat::DMK_FORMAT_BGRA_8_UNORMAL;
	case gli::FORMAT_BGRA8_SNORM_PACK8:				return DMKFormat::DMK_FORMAT_BGRA_8_SNORMAL;
	case gli::FORMAT_BGRA8_USCALED_PACK8:			return DMKFormat::DMK_FORMAT_BGRA_8_USCALED;
	case gli::FORMAT_BGRA8_SSCALED_PACK8:			return DMKFormat::DMK_FORMAT_BGRA_8_SSCALED;
	case gli::FORMAT_BGRA8_UINT_PACK8:				return DMKFormat::DMK_FORMAT_BGRA_8_UINT;
	case gli::FORMAT_BGRA8_SINT_PACK8:				return DMKFormat::DMK_FORMAT_BGRA_8_SINT;
	case gli::FORMAT_BGRA8_SRGB_PACK8:				return DMKFormat::DMK_FORMAT_BGRA_8_SRGB;
	case gli::FORMAT_RGBA8_UNORM_PACK32:			return DMKFormat::DMK_FORMAT_RGBA_8_UNORMAL_PACK32;
	case gli::FORMAT_RGBA8_SNORM_PACK32:			return DMKFormat::DMK_FORMAT_RGBA_8_SNORMAL_PACK32;
	case gli::FORMAT_RGBA8_USCALED_PACK32:			return DMKFormat::DMK_FORMAT_RGBA_8_USCALED_PACK32;
	case gli::FORMAT_RGBA8_SSCALED_PACK32:			return DMKFormat::DMK_FORMAT_RGBA_8_SSCALED_PACK32;
	case gli::FORMAT_RGBA8_UINT_PACK32:				return DMKFormat::DMK_FORMAT_RGBA_8_UINT_PACK32;
	case gli::FORMAT_RGBA8_SINT_PACK32:				return DMKFormat::DMK_FORMAT_RGBA_8_SINT_PACK32;
	case gli::FORMAT_RGBA8_SRGB_PACK32:				return DMKFormat::DMK_FORMAT_RGBA_8_SRGB_PACK32;
	case gli::FORMAT_RGB10A2_UNORM_PACK32:			return DMKFormat::DMK_FORMAT_A2R10G10B10_UNORMAL_PACK32;
	case gli::FORMAT_RGB10A2_SNORM_PACK32:			return DMKFormat::DMK_FORMAT_A2R10G10B10_SNORMAL_PACK32;
	case gli::FORMAT_RGB10A2_USCALED_PACK32:		return DMKFormat::DMK_FORMAT_A2R10G10B10_USCALED_PACK32;
	case gli::FORMAT_RGB10A2_SSCALED_PACK32:		return DMKFormat::DMK_FORMAT_A2R10G10B10_SSCALED_PACK32;
	case gli::FORMAT_RGB10A2_UINT_PACK32:			return DMKFormat::DMK_FORMAT_A2R10G10B10_UINT_PACK32;
	case gli::FORMAT_RGB10A2_SINT_PACK32:			return DMKFormat::DMK_FORMAT_A2R10G10B10_SINT_PACK32;
	case gli::FORMAT_BGR10A2_UNORM_PACK32:			return DMKFormat::DMK_FORMAT_A2B10G10R10_UNORMAL_PACK32;
	case gli::FORMAT_BGR10A2_SNORM_PACK32:			return DMKFormat::DMK_FORMAT_A2B10G10R10_SNORMAL_PACK32;
	case gli::FORMAT_BGR10A2_USCALED_PACK32:		return DMKFormat::DMK_FORMAT_A2B10G10R10_USCALED_PACK32;
	case gli::FORMAT_BGR10A2_SSCALED_PACK32:		return DMKFormat::DMK_FORMAT_A2B10G10R10_SSCALED_PACK32;
	case gli::FORMAT_BGR10A2_UINT_PACK32:			return DMKFormat::DMK_FORMAT_A2B10G10R10_UINT_PACK32;
	case gli::FORMAT_BGR10A2_SINT_PACK32:			return DMKFormat::DMK_FORMAT_A2B10G10R10_SINT_PACK32;
	case gli::FORMAT_R16_UNORM_PACK16:				return DMKFormat::DMK_FORMAT_R_16_UNORMAL;
	case gli::FORMAT_R16_SNORM_PACK16:				return DMKFormat::DMK_FORMAT_R_16_SNORMAL;
	case gli::FORMAT_R16_USCALED_PACK16:			return DMKFormat::DMK_FORMAT_R_16_USCALED;
	case gli::FORMAT_R16_SSCALED_PACK16:			return DMKFormat::DMK_FORMAT_R_16_SSCALED;
	case gli::FORMAT_R16_UINT_PACK16:				return DMKFormat::DMK_FORMAT_R_16_UINT;
	case gli::FORMAT_R16_SINT_PACK16:				return DMKFormat::DMK_FORMAT_R_16_SINT;
	case gli::FORMAT_R16_SFLOAT_PACK16:				return DMKFormat::DMK_FORMAT_R_16_SF32;
	case gli::FORMAT_RG16_UNORM_PACK16:				return DMKFormat::DMK_FORMAT_RG_16_UNORMAL;
	case gli::FORMAT_RG16_SNORM_PACK16:				return DMKFormat::DMK_FORMAT_RG_16_SNORMAL;
	case gli::FORMAT_RG16_USCALED_PACK16:			return DMKFormat::DMK_FORMAT_RG_16_USCALED;
	case gli::FORMAT_RG16_SSCALED_PACK16:			return DMKFormat::DMK_FORMAT_RG_16_SSCALED;
	case gli::FORMAT_RG16_UINT_PACK16:				return DMKFormat::DMK_FORMAT_RG_16_UINT;
	case gli::FORMAT_RG16_SINT_PACK16:				return DMKFormat::DMK_FORMAT_RG_16_SINT;
	case gli::FORMAT_RG16_SFLOAT_PACK16:			return DMKFormat::DMK_FORMAT_RG_16_SF32;
	case gli::FORMAT_RGB16_UNORM_PACK16:			return DMKFormat::DMK_FORMAT_RGB_16_UNORMAL;
	case gli::FORMAT_RGB16_SNORM_PACK16:			return DMKFormat::DMK_FORMAT_RGB_16_SNORMAL;
	case gli::FORMAT_RGB16_USCALED_PACK16:			return DMKFormat::DMK_FORMAT_RGB_16_USCALED;
	case gli::FORMAT_RGB16_SSCALED_PACK16:			return DMKFormat::DMK_FORMAT_RGB_16_SSCALED;
	case gli::FORMAT_RGB16_UINT_PACK16:				return DMKFormat::DMK_FORMAT_RGB_16_UINT;
	case gli::FORMAT_RGB16_SINT_PACK16:				return DMKFormat::DMK_FORMAT_RGB_16_SINT;
	case gli::FORMAT_RGB16_SFLOAT_PACK16:			return DMKFormat::DMK_FORMAT_RGB_16_SF32;
	case gli::FORMAT_RGBA16_UNORM_PACK16:			return DMKFormat::DMK_FORMAT_RGBA_16_UNORMAL;
	case gli::FORMAT_RGBA16_SNORM_PACK16:			return DMKFormat::DMK_FORMAT_RGBA_16_SNORMAL;
	case gli::FORMAT_RGBA16_USCALED_PACK16:			return DMKFormat::DMK_FORMAT_RGBA_16_USCALED;
	case gli::FORMAT_RGBA16_SSCALED_PACK16:			return DMKFormat::DMK_FORMAT_RGBA_16_SSCALED;
	case gli::FORMAT_RGBA16_UINT_PACK16:			return DMKFormat::DMK_FORMAT_RGBA_16_UINT;
	case gli::FORMAT_RGBA16_SINT_PACK16:			return DMKFormat::DMK_FORMAT_RGBA_16_SINT;
	case gli::FORMAT_RGBA16_SFLOAT_PACK16:			return DMKFormat::DMK_FORMAT_RGBA_16_SF32;
	case gli::FORMAT_RG32_SINT_PACK32:				return DMKFormat::DMK_FORMAT_R_32_UINT;
	case gli::FORMAT_RG32_SFLOAT_PACK32:			return DMKFormat::DMK_FORMAT_R_32_SINT;
	case gli::FORMAT_RGB32_UINT_PACK32:				return DMKFormat::DMK_FORMAT_R_32_SF32;
	case gli::FORMAT_RGBA32_SFLOAT_PACK32:			return DMKFormat::DMK_FORMAT_RG_32_UINT;
	case gli::FORMAT_D16_UNORM_PACK16:				return DMKFormat::DMK_FORMAT_D_16_UNORM;
	case gli::FORMAT_D24_UNORM_PACK32:				return DMKFormat::DMK_FORMAT_X8_D_24_UNORM_PACK32;
	case gli::FORMAT_D32_SFLOAT_PACK32:				return DMKFormat::DMK_FORMAT_D_32_SF32;
	case gli::FORMAT_S8_UINT_PACK8:					return DMKFormat::DMK_FORMAT_S_8_UINT;
	case gli::FORMAT_D16_UNORM_S8_UINT_PACK32:		return DMKFormat::DMK_FORMAT_D_16_UNORM_S_8_UINT;
	case gli::FORMAT_D24_UNORM_S8_UINT_PACK32:		return DMKFormat::DMK_FORMAT_X8_D_24_UNORM_PACK32;
	case gli::FORMAT_D32_SFLOAT_S8_UINT_PACK64:		return DMKFormat::DMK_FORMAT_D_32_SF32_S_8_UINT;
	case gli::FORMAT_RGB_ETC2_UNORM_BLOCK8:			return DMKFormat::DMK_FORMAT_ETC2_RGB_8_UNORM_BLOCK;
	case gli::FORMAT_RGB_ETC2_SRGB_BLOCK8:			return DMKFormat::DMK_FORMAT_ETC2_RGB_8_UNORM_BLOCK;
	case gli::FORMAT_RGBA_ETC2_UNORM_BLOCK8:		return DMKFormat::DMK_FORMAT_ETC2_RGBA_8_UNORM_BLOCK;
	case gli::FORMAT_RGBA_ETC2_SRGB_BLOCK8:			return DMKFormat::DMK_FORMAT_ETC2_RGBA_8_SRGB_BLOCK;
	case gli::FORMAT_RGBA_ASTC_4X4_UNORM_BLOCK16:	return DMKFormat::DMK_FORMAT_ASTC_4x4_UNORM_BLOCK;
	case gli::FORMAT_RGBA_ASTC_4X4_SRGB_BLOCK16:	return DMKFormat::DMK_FORMAT_ASTC_4x4_SRGB_BLOCK;
	case gli::FORMAT_RGBA_ASTC_5X4_UNORM_BLOCK16:	return DMKFormat::DMK_FORMAT_ASTC_5x4_UNORM_BLOCK;
	case gli::FORMAT_RGBA_ASTC_5X4_SRGB_BLOCK16:	return DMKFormat::DMK_FORMAT_ASTC_5x4_SRGB_BLOCK;
	case gli::FORMAT_RGBA_ASTC_5X5_UNORM_BLOCK16:	return DMKFormat::DMK_FORMAT_ASTC_5x5_UNORM_BLOCK;
	case gli::FORMAT_RGBA_ASTC_5X5_SRGB_BLOCK16:	return DMKFormat::DMK_FORMAT_ASTC_5x5_SRGB_BLOCK;
	case gli::FORMAT_RGBA_ASTC_6X5_UNORM_BLOCK16:	return DMKFormat::DMK_FORMAT_ASTC_6x5_UNORM_BLOCK;
	case gli::FORMAT_RGBA_ASTC_6X5_SRGB_BLOCK16:	return DMKFormat::DMK_FORMAT_ASTC_6x5_SRGB_BLOCK;
	case gli::FORMAT_RGBA_ASTC_6X6_UNORM_BLOCK16:	return DMKFormat::DMK_FORMAT_ASTC_6x6_UNORM_BLOCK;
	case gli::FORMAT_RGBA_ASTC_6X6_SRGB_BLOCK16:	return DMKFormat::DMK_FORMAT_ASTC_6x6_SRGB_BLOCK;
	case gli::FORMAT_RGBA_ASTC_8X5_UNORM_BLOCK16:	return DMKFormat::DMK_FORMAT_ASTC_8x5_UNORM_BLOCK;
	case gli::FORMAT_RGBA_ASTC_8X5_SRGB_BLOCK16:	return DMKFormat::DMK_FORMAT_ASTC_8x5_SRGB_BLOCK;
	case gli::FORMAT_RGBA_ASTC_8X6_UNORM_BLOCK16:	return DMKFormat::DMK_FORMAT_ASTC_8x6_UNORM_BLOCK;
	case gli::FORMAT_RGBA_ASTC_8X6_SRGB_BLOCK16:	return DMKFormat::DMK_FORMAT_ASTC_8x6_SRGB_BLOCK;
	case gli::FORMAT_RGBA_ASTC_8X8_UNORM_BLOCK16:	return DMKFormat::DMK_FORMAT_ASTC_8x8_UNORM_BLOCK;
	case gli::FORMAT_RGBA_ASTC_8X8_SRGB_BLOCK16:	return DMKFormat::DMK_FORMAT_ASTC_8x8_SRGB_BLOCK;
	case gli::FORMAT_RGBA_ASTC_10X5_UNORM_BLOCK16:	return DMKFormat::DMK_FORMAT_ASTC_10x5_UNORM_BLOCK;
	case gli::FORMAT_RGBA_ASTC_10X5_SRGB_BLOCK16:	return DMKFormat::DMK_FORMAT_ASTC_10x5_SRGB_BLOCK;
	case gli::FORMAT_RGBA_ASTC_10X6_UNORM_BLOCK16:	return DMKFormat::DMK_FORMAT_ASTC_10x6_UNORM_BLOCK;
	case gli::FORMAT_RGBA_ASTC_10X6_SRGB_BLOCK16:	return DMKFormat::DMK_FORMAT_ASTC_10x6_SRGB_BLOCK;
	case gli::FORMAT_RGBA_ASTC_10X8_UNORM_BLOCK16:	return DMKFormat::DMK_FORMAT_ASTC_10x8_UNORM_BLOCK;
	case gli::FORMAT_RGBA_ASTC_10X8_SRGB_BLOCK16:	return DMKFormat::DMK_FORMAT_ASTC_10x8_SRGB_BLOCK;
	case gli::FORMAT_RGBA_ASTC_10X10_UNORM_BLOCK16:	return DMKFormat::DMK_FORMAT_ASTC_10x10_UNORM_BLOCK;
	case gli::FORMAT_RGBA_ASTC_10X10_SRGB_BLOCK16:	return DMKFormat::DMK_FORMAT_ASTC_10x10_SRGB_BLOCK;
	case gli::FORMAT_RGBA_ASTC_12X10_UNORM_BLOCK16:	return DMKFormat::DMK_FORMAT_ASTC_12x10_UNORM_BLOCK;
	case gli::FORMAT_RGBA_ASTC_12X10_SRGB_BLOCK16:	return DMKFormat::DMK_FORMAT_ASTC_12x10_SRGB_BLOCK;
	case gli::FORMAT_RGBA_ASTC_12X12_UNORM_BLOCK16:	return DMKFormat::DMK_FORMAT_ASTC_12x12_UNORM_BLOCK;
	case gli::FORMAT_RGBA_ASTC_12X12_SRGB_BLOCK16:	return DMKFormat::DMK_FORMAT_ASTC_12x12_SRGB_BLOCK;
	case gli::FORMAT_RGB_ETC_UNORM_BLOCK8:			return DMKFormat::DMK_FORMAT_ETC2_RGB_8_UNORM_BLOCK;
	case gli::FORMAT_BGR8_UNORM_PACK32:				return DMKFormat::DMK_FORMAT_BGR_8_UNORMAL;
	case gli::FORMAT_BGR8_SRGB_PACK32:				return DMKFormat::DMK_FORMAT_BGR_8_SRGB;
	case gli::FORMAT_R_EAC_UNORM_BLOCK8:			return DMKFormat::DMK_FORMAT_EAC_R_11_UNORM_BLOCK;
	case gli::FORMAT_R_EAC_SNORM_BLOCK8:			return DMKFormat::DMK_FORMAT_EAC_R_11_SNORM_BLOCK;
	case gli::FORMAT_RG_EAC_UNORM_BLOCK16:			return DMKFormat::DMK_FORMAT_EAC_RG_11_UNORM_BLOCK;
	case gli::FORMAT_RG_EAC_SNORM_BLOCK16:			return DMKFormat::DMK_FORMAT_EAC_RG_11_SNORM_BLOCK;
	case gli::FORMAT_R64_UINT_PACK64:				return DMKFormat::DMK_FORMAT_R_64_UINT;
	case gli::FORMAT_R64_SINT_PACK64:				return DMKFormat::DMK_FORMAT_R_64_SINT;
	case gli::FORMAT_R64_SFLOAT_PACK64:				return DMKFormat::DMK_FORMAT_R_64_SF32;
	case gli::FORMAT_RG64_UINT_PACK64:				return DMKFormat::DMK_FORMAT_RG_64_UINT;
	case gli::FORMAT_RG64_SINT_PACK64:				return DMKFormat::DMK_FORMAT_RG_64_SINT;
	case gli::FORMAT_RG64_SFLOAT_PACK64:			return DMKFormat::DMK_FORMAT_RG_64_SF32;
	case gli::FORMAT_RGB64_UINT_PACK64:				return DMKFormat::DMK_FORMAT_RGB_64_UINT;
	case gli::FORMAT_RGB64_SINT_PACK64:				return DMKFormat::DMK_FORMAT_RGB_64_SINT;
	case gli::FORMAT_RGB64_SFLOAT_PACK64:			return DMKFormat::DMK_FORMAT_RGB_64_SF32;
	case gli::FORMAT_RGBA64_UINT_PACK64:			return DMKFormat::DMK_FORMAT_RGBA_64_UINT;
	case gli::FORMAT_RGBA64_SINT_PACK64:			return DMKFormat::DMK_FORMAT_RGBA_64_SINT;
	case gli::FORMAT_RGBA64_SFLOAT_PACK64:			return DMKFormat::DMK_FORMAT_RGBA_64_SF32;
	default:
		DMK_ERROR("Invalid or unsupported gli texture format!");
		break;
	}

	return DMKFormat::DMK_FORMAT_UNDEFINED;
}

/* Get the number of channels stored in the image. */
DMK_FORCEINLINE UI32 GetFreeImageChannelCount(FREE_IMAGE_COLOR_TYPE colorType)
{
	switch (colorType)
	{
	case FIC_MINISWHITE:
		return 1;
	case FIC_MINISBLACK:
		return 1;
	case FIC_RGB:
		return 3;
	case FIC_PALETTE:
		return 3;
	case FIC_RGBALPHA:
		return 4;
	case FIC_CMYK:
		return 4;
	default:
		return 0;
		break;
	}

	return 0;
}

/* Get the DMKFormat from FREE_IMAGE_TYPE. */
DMK_FORCEINLINE DMKFormat GetFormat(FREE_IMAGE_TYPE type, UI32 channels)
{
	switch (type)
	{
	case FIT_UNKNOWN:
		return DMKFormat::DMK_FORMAT_UNDEFINED;
	case FIT_BITMAP:
		if (channels == 1)
			return DMKFormat::DMK_FORMAT_R_8_UNORMAL;
		else if (channels == 2)
			return DMKFormat::DMK_FORMAT_RG_8_UNORMAL;
		else if (channels == 3)
			return DMKFormat::DMK_FORMAT_RGB_8_UNORMAL;
		else if (channels == 4)
			return DMKFormat::DMK_FORMAT_RGBA_8_UNORMAL;

	case FIT_UINT16:
		if (channels == 1)
			return DMKFormat::DMK_FORMAT_R_16_SINT;
		else if (channels == 2)
			return DMKFormat::DMK_FORMAT_RG_16_SINT;
		else if (channels == 3)
			return DMKFormat::DMK_FORMAT_RGB_16_SINT;
		else if (channels == 4)
			return DMKFormat::DMK_FORMAT_RGBA_16_SINT;

	case FIT_INT16:
		if (channels == 1)
			return DMKFormat::DMK_FORMAT_R_16_UINT;
		else if (channels == 2)
			return DMKFormat::DMK_FORMAT_RG_16_UINT;
		else if (channels == 3)
			return DMKFormat::DMK_FORMAT_RGB_16_UINT;
		else if (channels == 4)
			return DMKFormat::DMK_FORMAT_RGBA_16_UINT;

	case FIT_UINT32:
		if (channels == 1)
			return DMKFormat::DMK_FORMAT_R_32_UINT;
		else if (channels == 2)
			return DMKFormat::DMK_FORMAT_RG_32_UINT;
		else if (channels == 3)
			return DMKFormat::DMK_FORMAT_RGB_32_UINT;
		else if (channels == 4)
			return DMKFormat::DMK_FORMAT_RGBA_32_UINT;

	case FIT_INT32:
		if (channels == 1)
			return DMKFormat::DMK_FORMAT_R_32_UINT;
		else if (channels == 2)
			return DMKFormat::DMK_FORMAT_RG_32_UINT;
		else if (channels == 3)
			return DMKFormat::DMK_FORMAT_RGB_32_UINT;
		else if (channels == 4)
			return DMKFormat::DMK_FORMAT_RGBA_32_UINT;

	case FIT_FLOAT:
		if (channels == 1)
			return DMKFormat::DMK_FORMAT_R_32_SF32;
		else if (channels == 2)
			return DMKFormat::DMK_FORMAT_RG_32_SF32;
		else if (channels == 3)
			return DMKFormat::DMK_FORMAT_RGB_32_SF32;
		else if (channels == 4)
			return DMKFormat::DMK_FORMAT_RGBA_32_SF32;

	case FIT_DOUBLE:
		if (channels == 1)
			return DMKFormat::DMK_FORMAT_R_64_SF32;
		else if (channels == 2)
			return DMKFormat::DMK_FORMAT_RG_64_SF32;
		else if (channels == 3)
			return DMKFormat::DMK_FORMAT_RGB_64_SF32;
		else if (channels == 4)
			return DMKFormat::DMK_FORMAT_RGBA_64_SF32;

	case FIT_COMPLEX:
		return DMKFormat::DMK_FORMAT_RG_64_SF32;

	case FIT_RGB16:
		return DMKFormat::DMK_FORMAT_RGB_16_UNORMAL;

	case FIT_RGBA16:
		return DMKFormat::DMK_FORMAT_RGBA_16_UNORMAL;

	default:
		DMK_ERROR("Invalid Format!");
		break;
	}

	return DMKFormat::DMK_FORMAT_UNDEFINED;
}

DMKTexture* DMKImageImporter::loadTexture2D(const STRING& file, DMKFormat requiredFormat)
{
	if (file.find(".ktx") != STRING::npos)
		return loadKTX(file, requiredFormat);

	DMKTexture2D* pTexture = StaticAllocator<DMKTexture2D>::allocate();
	pTexture->image = stbi_load(file.c_str(), Cast<I32*>(&pTexture->width), Cast<I32*>(&pTexture->height), Cast<I32*>(&pTexture->channels), STBI_rgb_alpha);

	if (!pTexture->image)
	{
		DMK_ERROR("The image file could not be loaded!");
		return nullptr;
	}

	if (pTexture->channels == 1)
		pTexture->format = DMKFormat::DMK_FORMAT_R_8_UNORMAL;
	else if (pTexture->channels == 2)
		pTexture->format = DMKFormat::DMK_FORMAT_RG_8_UNORMAL;
	else if (pTexture->channels == 3)
		pTexture->format = DMKFormat::DMK_FORMAT_RGB_8_UNORMAL;
	else if (pTexture->channels == 4)
		pTexture->format = DMKFormat::DMK_FORMAT_RGBA_8_UNORMAL;

	pTexture->resolveChannels();

	return pTexture;
}

DMKTexture* DMKImageImporter::loadKTX(const STRING& file, DMKFormat requiredFormat)
{
	gli::texture texture = gli::load_ktx(file);
	if (!texture.data())
	{
		DMK_ERROR("Failed to load the required texture file!");
		return nullptr;
	}

	DMKTexture2D* pTexture = StaticAllocator<DMKTexture2D>::allocate();
	pTexture->width = texture.extent().x;
	pTexture->height = texture.extent().y;
	pTexture->depth = texture.extent().z;
	pTexture->format = GetFormat(texture.format());
	pTexture->layerCount = Cast<UI32>(texture.layers());
	pTexture->resolveChannels();

	pTexture->image = StaticAllocator<unsigned char>::allocate(pTexture->size() * pTexture->layerCount);
	DMKMemoryFunctions::copyData(pTexture->image, texture.data(), pTexture->size() * pTexture->layerCount);

	return pTexture;
}

DMKTexture* DMKImageImporter::loadCube(std::vector<STRING> files, DMKFormat requiredFormat)
{
	DMKTextureCube* pTexture = StaticAllocator<DMKTextureCube>::allocate();
	pTexture->layerCount = 6;

	UCPTR textures[6] = { nullptr };

	for (UI8 index = 0; index < 6; index++)
	{
		textures[index] = Cast<UCPTR>(stbi_load(files[index].c_str(), (I32*)&pTexture->width, (I32*)&pTexture->height, (I32*)&pTexture->channels, STBI_rgb_alpha));

		if (!textures[index])
			DMK_FATAL("Unable to load texture!");
	}

	pTexture->channels = 4;
	pTexture->image = StaticAllocator<unsigned char>::allocate(pTexture->width * pTexture->height * pTexture->depth * pTexture->channels * 6);
	POINTER<BYTE> _imgPtr = pTexture->image;

	for (auto ptr : textures)
	{
		DMKMemoryFunctions::moveData(_imgPtr.get(), ptr, pTexture->size());
		_imgPtr += pTexture->size();
	}

	if (pTexture->channels == 1)
		pTexture->format = DMKFormat::DMK_FORMAT_R_8_UNORMAL;
	else if (pTexture->channels == 2)
		pTexture->format = DMKFormat::DMK_FORMAT_RG_8_UNORMAL;
	else if (pTexture->channels == 3)
		pTexture->format = DMKFormat::DMK_FORMAT_RGB_8_UNORMAL;
	else if (pTexture->channels == 4)
		pTexture->format = DMKFormat::DMK_FORMAT_RGBA_8_UNORMAL;
	else
		DMK_ERROR_BOX("Invalid texture format!");

	pTexture->mipLevels = Cast<UI32>(std::floor(std::log2(std::max(pTexture->width, pTexture->height))) + 1);
	pTexture->resolveChannels();

	return pTexture;
}
