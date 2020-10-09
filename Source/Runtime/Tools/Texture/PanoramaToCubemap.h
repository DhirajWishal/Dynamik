// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_TOOLS_PANORAMA_TO_CUBEMAP_H
#define _DYNAMIK_TOOLS_PANORAMA_TO_CUBEMAP_H

#include "Core/Macros/Global.h"
#include "Core/Types/DataTypes.h"
#include "Core/Objects/Resources/Textures/TextureCube.h"

namespace Tools
{
	/*
	 Convert panoramic images to cube maps.
	*/
	class PanoramaToCubemap {
	public:
		PanoramaToCubemap(const STRING& file = TEXT("")) : imageFile(file) {}
		~PanoramaToCubemap() {}

		DMKTextureCube create();

		STRING imageFile = TEXT("");
	};
}

#endif // !_DYNAMIK_TOOLS_PANORAMA_TO_CUBEMAP_H
