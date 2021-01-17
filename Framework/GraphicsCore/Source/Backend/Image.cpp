// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "GraphicsCore/Backend/Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace DMK
{
	namespace GraphicsCore
	{
		unsigned char* Image::LoadImageData(const char* pAsset)
		{
			I32 components = 0, width = 0, height = 0, depth = 1;
			unsigned char* pData = stbi_load(pAsset, &width, &height, &components, STBI_rgb_alpha);

			mExtent.x = static_cast<float>(width);
			mExtent.y = static_cast<float>(height);
			mExtent.z = static_cast<float>(depth);

			return pData;
		}
	}
}