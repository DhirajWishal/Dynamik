// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "PanoramaToCubemap.h"

#include "Core/Math/Vector/Vector3F.h"
#include <stb_image.h>
#include <cmath>

#define M_PI 3.1415926

namespace Dynamik
{
	namespace Tools
	{
		DMK_FORCEINLINE Vector3F getXYZ(I32 i, I32 j, I32 face, I32 edge)
		{
			auto a = (2.0f * i) / edge;
			auto b = (2.0f * j) / edge;

			if (face == 0)
				return { -1.0f, 1.0f - a, 3.0f - b };
			else if (face == 1)
				return { a - 3.0f, -1.0f, 3.0f - b };
			else if (face == 2)
				return { 1.0f, a - 5.0f, 3.0f - b };
			else if (face == 3)
				return { 7.0f - a, 1.0f - a, 3.0f - b };
			else if (face == 4)
				return { b - 1.0f, a - 5.0f - a, 1.0f };
			else if (face == 5)
				return { 5.0f - b, a - 5.0f, -1.0f };

			return Vector3F();
		}

		DMKTextureCube PanoramaToCubemap::create()
		{
			I32 width = 0, height = 0, channels = 0;
			auto image = stbi_load(imageFile.c_str(), &width, &height, &channels, NULL);

			return DMKTextureCube();
		}
	}
}
