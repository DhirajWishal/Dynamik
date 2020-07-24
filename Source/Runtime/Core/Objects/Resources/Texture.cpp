// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Dynamik
{
	void DMKTexture::clear()
	{
		StaticAllocator<UCHR>::deallocate(image, 0);
	}

	UI64 DMKTexture::size()
	{
		return depth * width * height * channels;
	}

	void DMKTexture::resolveChannels()
	{
		UI32 formatValue = Cast<UI32>(format);

		if (
			(formatValue > 8) && (formatValue < 16) ||
			(formatValue > 69) && (formatValue < 77) ||
			(formatValue > 97) && (formatValue < 101) ||
			(formatValue > 109) && (formatValue < 113))
		{
			channels = 1;
			return;
		}
		else if (
			(formatValue > 15) && (formatValue < 23) ||
			(formatValue > 76) && (formatValue < 84) ||
			(formatValue > 100) && (formatValue < 104) ||
			(formatValue > 112) && (formatValue < 116))
		{
			channels = 2;
			return;
		}
		else if (
			(formatValue > 22) && (formatValue < 37) ||
			(formatValue > 83) && (formatValue < 91) ||
			(formatValue > 103) && (formatValue < 107) ||
			(formatValue > 112) && (formatValue < 124) ||
			(formatValue > 115) && (formatValue < 119))
		{
			channels = 3;
			return;
		}
		else if (
			(formatValue > 36) && (formatValue < 44) ||
			(formatValue > 50) && (formatValue < 98) ||
			(formatValue > 106) && (formatValue < 110) ||
			(formatValue > 118) && (formatValue < 122))
		{
			channels = 4;
			return;
		}

		channels = 1;
	}
}
