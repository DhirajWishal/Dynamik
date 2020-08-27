// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "TextureCube.h"

#include "stb_image.h"

void DMKTextureCube::clear()
{
	StaticAllocator<UCHR>::deallocate(image, size() * 6);
}
