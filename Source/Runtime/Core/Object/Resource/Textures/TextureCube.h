// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_TEXTURE_CUBE_H
#define _DYNAMIK_TEXTURE_CUBE_H

/*
 Author:	Dhiraj Wishal
 Date:		03/07/2020
*/
#include "../Texture.h"
#include "Core/Types/Array.h"

namespace Dynamik
{
	/*
	 Dynamik Texture Cube
	*/
	class DMK_API DMKTextureCube : public DMKTexture {
	public:
		DMKTextureCube() : DMKTexture(DMKTextureType::DMK_TEXTURE_TYPE_CUBEMAP) {}
		~DMKTextureCube() {}

		void load(ARRAY<STRING> texturePaths);
		virtual void clear() override final;

	private:
		void _loadCube6(ARRAY<STRING> paths);
	};
}

#endif // !_DYNAMIK_TEXTURE_CUBE_H
