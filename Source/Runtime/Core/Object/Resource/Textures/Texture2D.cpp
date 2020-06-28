// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "Texture2D.h"

#include <stb_image.h>

namespace Dynamik
{
	void DMKTexture2D::load(const STRING& path)
	{
		image = (UCPTR)stbi_load(path.c_str(), (I32*)&width, (I32*)&height, (I32*)&channels, NULL);

		/* Check if the texture file was successfully loaded */
		if (!image)
			DMK_ERROR_BOX("Unable to import the requested texture file!");

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
