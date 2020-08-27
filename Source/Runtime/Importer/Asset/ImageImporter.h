// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_IMAGE_IMPORTER_H
#define _DYNAMIK_IMAGE_IMPORTER_H

#include "Core/Objects/Resources/Texture.h"
#include "Core/Types/DataTypes.h"

/*
 Dynamik Image Importer
 This object uses internal and third party libraries to import image files.
*/
class DMK_API DMKImageImporter {
public:
	DMKImageImporter() {}
	~DMKImageImporter() {}

	/*
	 Load a 2D texture to the engine.

	 @param file: The file to be imported.
	 @param requiredFormat: To format to output the texture in. Default is UNDEFINED which will output the default
	   format.
	*/
	DMKTexture* loadTexture2D(const STRING& file, DMKFormat requiredFormat = DMKFormat::DMK_FORMAT_UNDEFINED);

	/*
	 Load a KTX image file to the engine.

	 @param file: The file to be imported.
	 @param requiredFormat: To format to output the texture in. Default is UNDEFINED which will output the default
	   format.
	*/
	DMKTexture* loadKTX(const STRING& file, DMKFormat requiredFormat = DMKFormat::DMK_FORMAT_UNDEFINED);

	/*
	 Load cube map to the engine.

	 @param files: The files containing the images. If the size is grater than 1, the method expects 6 images
	   to create a successful cube map image.
	 @param requiredFormat: To format to output the texture in. Default is UNDEFINED which will output the default
	   format.
	*/
	DMKTexture* loadCube(ARRAY<STRING> files, DMKFormat requiredFormat = DMKFormat::DMK_FORMAT_UNDEFINED);
};

#endif // !_DYNAMIK_IMAGE_IMPORTER_H
