// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "TextureFactory.h"

#include "Core/Objects/Resources/Textures/TextureCube.h"

#include "Importer/Asset/ImageImporter.h"

DMKTexture* DMKTextureFactory::create(const DMKTextureType& type, const STRING& path)
{
	DMKImageImporter importer;

	switch (type)
	{
	case DMKTextureType::TEXTURE_TYPE_2D:
		return importer.loadTexture2D(path);
	case DMKTextureType::TEXTURE_TYPE_3D:
		break;
	case DMKTextureType::TEXTURE_TYPE_SPRITE:
		break;
	case DMKTextureType::TEXTURE_TYPE_CUBEMAP:
		break;
	default:
		DMK_ERROR_BOX("Requested texture cannot be created! Use create(DMKTextureType, std::vector<STRING>) method instead.");
		break;
	}

	return nullptr;
}

DMKTexture* DMKTextureFactory::createCubeMap(const std::vector<STRING>& paths)
{
	DMKImageImporter importer;
	return importer.loadCube(paths);
}

DMKTexture* DMKTextureFactory::createCubeMapFromPanorama(const STRING& file)
{
	return nullptr;
}

void DMKTextureFactory::destroy(DMKTexture* texture)
{
	StaticAllocator<DMKTexture>::deallocate(texture, 0);
}
