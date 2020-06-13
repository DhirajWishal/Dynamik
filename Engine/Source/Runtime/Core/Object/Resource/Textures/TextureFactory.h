// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_TEXTURE_FACTORY_H
#define _DYNAMIK_TEXTURE_FACTORY_H

/*
 Author:	Dhiraj Wishal
 Date:		08/06/2020
*/
#include "Types/Array.h"
#include "Texture2D.h"

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

		static POINTER<DMKTexture> create(const DMKTextureType& type, const STRING& path);
		static POINTER<DMKTexture> create(const DMKTextureType& type, const ARRAY<STRING>& paths);

		static void destroy(POINTER<DMKTexture> texture);
	};
}

#endif // !_DYNAMIK_TEXTURE_FACTORY_H
