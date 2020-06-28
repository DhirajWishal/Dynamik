// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "TextureFactory.h"

namespace Dynamik
{
	DMKTexture* DMKTextureFactory::create(const DMKTextureType& type, const STRING& path)
	{
		switch (type)
		{
		case Dynamik::DMKTextureType::DMK_TEXTURE_TYPE_2D:
		{
			DMKTexture2D* _texture = StaticAllocator<DMKTexture2D>::allocate();
			_texture->load(path);
			return _texture;
		}

		case Dynamik::DMKTextureType::DMK_TEXTURE_TYPE_3D:
			break;
		case Dynamik::DMKTextureType::DMK_TEXTURE_TYPE_SPRITE:
			break;
		case Dynamik::DMKTextureType::DMK_TEXTURE_TYPE_CUBEMAP:
			break;
		default:
			DMK_ERROR_BOX("Requested texture cannot be created! Use create(DMKTextureType, ARRAY<STRING>) method instead.");
			break;
		}

		return nullptr;
	}

	DMKTexture* DMKTextureFactory::create(const DMKTextureType& type, const ARRAY<STRING>& paths)
	{
		switch (type)
		{
		case Dynamik::DMKTextureType::DMK_TEXTURE_TYPE_2D_ARRAY:
			break;
		case Dynamik::DMKTextureType::DMK_TEXTURE_TYPE_3D_ARRAY:
			break;
		case Dynamik::DMKTextureType::DMK_TEXTURE_TYPE_SPRITE_ARRAY:
			break;
		case Dynamik::DMKTextureType::DMK_TEXTURE_TYPE_CUBEMAP_ARRAY:
			break;
		default:
			DMK_ERROR_BOX("Requested texture cannot be created! Use create(DMKTextureType, STRING) method instead.");
			break;
		}

		return nullptr;
	}
	
	void DMKTextureFactory::destroy(DMKTexture* texture)
	{
		StaticAllocator<DMKTexture>::deallocate(texture, 0);
	}
}
