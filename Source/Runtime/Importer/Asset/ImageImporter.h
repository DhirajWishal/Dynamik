// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_IMAGE_IMPORTER_H
#define _DYNAMIK_IMAGE_IMPORTER_H

#include "Core/Objects/Resources/Texture.h"
#include "Core/Types/DataTypes.h"

namespace Dynamik 
{
	/*
	 Dynamik Image Importer
	 This object uses internal and third party libraries to import image files.
	*/
	class DMK_API DMKImageImporter {
	public:
		DMKImageImporter() {}
		~DMKImageImporter() {}

		DMKTexture* loadTexture2D(const STRING& file);
	};
}

#endif // !_DYNAMIK_IMAGE_IMPORTER_H
