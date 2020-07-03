// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "TextureCube.h"

#include "stb_image.h"

namespace Dynamik
{
	void DMKTextureCube::load(ARRAY<STRING> texturePaths)
	{
		if (texturePaths.size() != 6)
		{
			DMK_FATAL("Dynamik Only Supports 6-image Sky Boxes Only! (For now)");
			return;
		}

		_loadCube6(texturePaths);
	}

	void DMKTextureCube::clear()
	{
		StaticAllocator<UCHR>::deallocate(image, size() * 6);
	}

	void DMKTextureCube::_loadCube6(ARRAY<STRING> paths)
	{
		layerCount = 6;

		UCPTR textures[6] = { nullptr };

		for (UI8 index = 0; index < 6; index++)
		{
			textures[index] = (UCHR*)stbi_load(paths[index].c_str(), (I32*)&width, (I32*)&height, (I32*)&channels, STBI_rgb_alpha);

			if (!textures[index])
				DMK_FATAL("Unable to load texture!");
		}

		channels = 4;
		image = StaticAllocator<UCHR>::allocate(width * height * depth * channels * 6);
		POINTER<BYTE> _imgPtr = image;

		for (auto ptr : textures)
		{
			DMKMemoryFunctions::moveData(_imgPtr.get(), ptr, size());
			_imgPtr += size();
		}

		if (channels == 1)
			format = DMKFormat::DMK_FORMAT_R_8_UNORMAL;
		else if (channels == 2)
			format = DMKFormat::DMK_FORMAT_RG_8_UNORMAL;
		else if (channels == 3)
			format = DMKFormat::DMK_FORMAT_RGB_8_UNORMAL;
		else if (channels == 4)
			format = DMKFormat::DMK_FORMAT_RGBA_8_UNORMAL;
		else
			DMK_ERROR_BOX("Invalid texture format!");
	}
}
