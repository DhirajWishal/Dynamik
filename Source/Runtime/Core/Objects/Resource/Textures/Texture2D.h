// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_TEXTURE_2D_H
#define _DYNAMIK_TEXTURE_2D_H

#include "../Texture.h"

namespace Dynamik
{
	/*
	 2D texture for the Dynamik Engine
	*/
	class DMK_API DMKTexture2D : public DMKTexture {
	public:
		DMKTexture2D() : DMKTexture(DMKTextureType::DMK_TEXTURE_TYPE_2D) {}
		~DMKTexture2D() {}

		void load(const STRING& path);
	};
}

#endif // !_DYNAMIK_TEXTURE_2D_H
