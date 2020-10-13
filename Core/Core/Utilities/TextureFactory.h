// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_TEXTURE_FACTORY_H
#define _DYNAMIK_TEXTURE_FACTORY_H

#include <vector>
#include "Core/Objects/Resources/Textures/Texture2D.h"

/*
 Texture factory for the Dynamik Engine
*/
class DMKTextureFactory {
	DMKTextureFactory() {}
	~DMKTextureFactory() {}

public:
	DMKTextureFactory(const DMKTextureFactory&) = delete;
	DMKTextureFactory(DMKTextureFactory&&) = delete;
	DMKTextureFactory& operator=(const DMKTextureFactory&) = delete;
	DMKTextureFactory& operator=(DMKTextureFactory&&) = delete;

	static DMKTexture* create(const DMKTextureType& type, const STRING& path);
	static DMKTexture* createCubeMap(const std::vector<STRING>& paths);
	static DMKTexture* createCubeMapFromPanorama(const STRING& file);

	static void destroy(DMKTexture* texture);
};

#endif // !_DYNAMIK_TEXTURE_FACTORY_H
