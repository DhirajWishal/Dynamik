// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "TextureFactory.h"

#include "Core/Objects/Resources/Textures/TextureCube.h"

#include <stb_image.h>

namespace Dynamik
{
	DMKTexture* DMKTextureFactory::create(const DMKTextureType& type, const STRING& path)
	{
		switch (type)
		{
		case Dynamik::DMKTextureType::TEXTURE_TYPE_2D:
		{
			DMKTexture2D* _texture = StaticAllocator<DMKTexture2D>::allocate();
			_texture->load(path);
			return _texture;
		}

		case Dynamik::DMKTextureType::TEXTURE_TYPE_3D:
			break;
		case Dynamik::DMKTextureType::TEXTURE_TYPE_SPRITE:
			break;
		case Dynamik::DMKTextureType::TEXTURE_TYPE_CUBEMAP:
			break;
		default:
			DMK_ERROR_BOX("Requested texture cannot be created! Use create(DMKTextureType, ARRAY<STRING>) method instead.");
			break;
		}

		return nullptr;
	}

	DMKTexture* DMKTextureFactory::createCubeMap(const ARRAY<STRING>& paths)
	{
		DMKTextureCube* _cube = StaticAllocator<DMKTextureCube>::allocate();
		_cube->load(paths);

		return _cube;
	}

	DMKTexture* DMKTextureFactory::createCubeMapFromPanorama(const STRING& file)
	{
		auto out = stbi_is_hdr(file.c_str());
		I32 width = 0, height = 0, channels = 0;
		auto image = stbi_load(file.c_str(), &width, &height, &channels, NULL);

		return nullptr;
	}
	
	void DMKTextureFactory::destroy(DMKTexture* texture)
	{
		StaticAllocator<DMKTexture>::deallocate(texture, 0);
	}
}
