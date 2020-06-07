#include "dmkafx.h"
#include "Texture.h"

namespace Dynamik
{
	DMKTexture::~DMKTexture()
	{
		StaticAllocator<CHR>::deallocate(image, 0);
	}
	
	void DMKTexture::load(const STRING& path)
	{
	}
}
