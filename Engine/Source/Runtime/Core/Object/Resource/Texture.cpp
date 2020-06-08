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
	
	UI32 DMKTexture::size()
	{
		return depth * width * height * channels;
	}
}
