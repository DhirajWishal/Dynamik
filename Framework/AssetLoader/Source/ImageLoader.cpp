// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "AssetLoader/ImageLoader.h"
#include "Core/Types/DataTypes.h"

#include <stb_image.h>

#define FREEIMAGE_LIB
#include <FreeImage.h>

class ImageLoader {
public:
	ImageLoader() { FreeImage_Initialise(); }
	~ImageLoader() { FreeImage_DeInitialise(); }

	void Load(const char* pAsset)
	{
		FIBITMAP* image = FreeImage_Load(FreeImage_GetFileType(pAsset), pAsset);

		auto width = FreeImage_GetWidth(image);
		auto height = FreeImage_GetHeight(image);
		auto info = FreeImage_GetInfo(image);
		auto type = FreeImage_GetImageType(image);
		auto cType = FreeImage_GetColorType(image);

		FreeImage_Unload(image);
	}
};

namespace DMK
{
	namespace AssetLoader
	{
		GraphicsCore::Texture LoadImageData(const char* pAsset)
		{
			ImageLoader loader;
			loader.Load(pAsset);

			GraphicsCore::Texture texture;
			return texture;
		}
	}
}