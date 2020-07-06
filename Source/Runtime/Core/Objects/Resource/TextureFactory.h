// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_TEXTURE_FACTORY_H
#define _DYNAMIK_TEXTURE_FACTORY_H

#include "Core/Types/Array.h"
#include "Textures/Texture2D.h"

namespace Dynamik
{
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
		static DMKTexture* createCubeMap(const ARRAY<STRING>& paths);

		static void destroy(DMKTexture* texture);
	};
}

#endif // !_DYNAMIK_TEXTURE_FACTORY_H
