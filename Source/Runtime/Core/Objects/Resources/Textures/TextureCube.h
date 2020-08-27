// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_TEXTURE_CUBE_H
#define _DYNAMIK_TEXTURE_CUBE_H

#include "../Texture.h"
#include "Core/Types/Array.h"

/*
 Dynamik Texture Cube
*/
class DMK_API DMKTextureCube : public DMKTexture {
public:
	DMKTextureCube() : DMKTexture(DMKTextureType::TEXTURE_TYPE_CUBEMAP) {}
	~DMKTextureCube() {}

	virtual void clear() override final;
};

#endif // !_DYNAMIK_TEXTURE_CUBE_H
