// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_TEXTURE_H
#define _DYNAMIK_TEXTURE_H

#include "Core/Macros/Global.h"
#include "Core/Types/DataTypes.h"

namespace Dynamik
{
	/*
	 Texture type
	*/
	enum class DMK_API DMKTextureType {
		TEXTURE_TYPE_2D,
		TEXTURE_TYPE_3D,
		TEXTURE_TYPE_SPRITE,
		TEXTURE_TYPE_CUBEMAP,
		TEXTURE_TYPE_2D_ARRAY,
		TEXTURE_TYPE_3D_ARRAY,
		TEXTURE_TYPE_SPRITE_ARRAY,
		TEXTURE_TYPE_CUBEMAP_ARRAY,
	};

	/*
	 Texture swizzles
	*/
	enum class DMK_API DMKTextureSwizzle {
		TEXTURE_SWIZZLE_IDENTITY,
		TEXTURE_SWIZZLE_ZERO,
		TEXTURE_SWIZZLE_ONE,
		TEXTURE_SWIZZLE_RED,
		TEXTURE_SWIZZLE_GREEN,
		TEXTURE_SWIZZLE_BLUE,
		TEXTURE_SWIZZLE_ALPHA,
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
		virtual UI64 size();

		UCPTR image = nullptr;
		UI32 width = 0;
		UI32 height = 0;
		UI32 depth = 1;
		UI32 channels = 0;
		UI32 layerCount = 1;
		UI32 mipLevels = 1;
		DMKFormat format = DMKFormat::DMK_FORMAT_UNDEFINED;
		DMKTextureType type = DMKTextureType::TEXTURE_TYPE_2D;

		/* Swizzles */
		struct DMK_API TextureSwizzles {
			DMKTextureSwizzle componentOne = DMKTextureSwizzle::TEXTURE_SWIZZLE_RED;
			DMKTextureSwizzle componentTwo = DMKTextureSwizzle::TEXTURE_SWIZZLE_GREEN;
			DMKTextureSwizzle componentThree = DMKTextureSwizzle::TEXTURE_SWIZZLE_BLUE;
			DMKTextureSwizzle componentFour = DMKTextureSwizzle::TEXTURE_SWIZZLE_ALPHA;
		} swizzles;
	};
}

#endif // !_DYNAMIK_TEXTURE_MODULE_H
