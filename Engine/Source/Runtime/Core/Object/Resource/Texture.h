// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_TEXTURE_H
#define _DYNAMIK_TEXTURE_H

/*
 Author:	Dhiraj Wishal
 Date:		07/06/2020
*/
#include "Macros/Global.h"
#include "Types/DataTypes.h"

namespace Dynamik
{
	/*
	 Texture type
	*/
	enum class DMK_API DMKTextureType {
		DMK_TEXTURE_TYPE_2D,
		DMK_TEXTURE_TYPE_3D,
		DMK_TEXTURE_TYPE_SPRITE,
		DMK_TEXTURE_TYPE_CUBEMAP,
		DMK_TEXTURE_TYPE_2D_ARRAY,
		DMK_TEXTURE_TYPE_3D_ARRAY,
		DMK_TEXTURE_TYPE_SPRITE_ARRAY,
		DMK_TEXTURE_TYPE_CUBEMAP_ARRAY,
	};

	/*
	 Texture swizzles
	*/
	enum class DMK_API DMKTextureSwizzle {
		DMK_TEXTURE_SWIZZLE_IDENTITY,
		DMK_TEXTURE_SWIZZLE_ZERO,
		DMK_TEXTURE_SWIZZLE_ONE,
		DMK_TEXTURE_SWIZZLE_RED,
		DMK_TEXTURE_SWIZZLE_GREEN,
		DMK_TEXTURE_SWIZZLE_BLUE,
		DMK_TEXTURE_SWIZZLE_ALPHA,
	};

	/*
	 Texture object for the Dynamik Engine
	*/
	class DMK_API DMKTexture {
	public:
		DMKTexture() {}
		DMKTexture(const DMKTextureType& ty) : type(ty) {}
		virtual ~DMKTexture() {}

		virtual void clear();
		virtual UI32 size();

		UCPTR image = nullptr;
		UI32 width = 0;
		UI32 height = 0;
		UI32 depth = 1;
		UI32 channels = 0;
		UI32 layerCount = 1;
		UI32 mipLevels = 1;
		DMKFormat format = DMKFormat::DMK_FORMAT_UNDEFINED;
		DMKTextureType type = DMKTextureType::DMK_TEXTURE_TYPE_2D;

		/* Swizzles */
		struct DMK_API TextureSwizzles {
			DMKTextureSwizzle componentOne = DMKTextureSwizzle::DMK_TEXTURE_SWIZZLE_RED;
			DMKTextureSwizzle componentTwo = DMKTextureSwizzle::DMK_TEXTURE_SWIZZLE_GREEN;
			DMKTextureSwizzle componentThree = DMKTextureSwizzle::DMK_TEXTURE_SWIZZLE_BLUE;
			DMKTextureSwizzle componentFour = DMKTextureSwizzle::DMK_TEXTURE_SWIZZLE_ALPHA;
		} swizzles;
	};
}

#endif // !_DYNAMIK_TEXTURE_MODULE_H
