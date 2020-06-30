// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_TEXTURE_H
#define _DYNAMIK_RENDERER_TEXTURE_H

/*
 Author:	Dhiraj Wishal
 Date:		16/06/2020
*/
#include "RImage.h"
#include "RImageSampler.h"

namespace Dynamik
{
	/*
	 Renderer Texture object
	*/
	class DMK_API RTexture {
	public:
		RTexture() {}
		virtual ~RTexture() {}

		virtual void initialize(RCoreObject* pCoreObject, DMKTexture* pTextureObject) = 0;
		virtual void createView(RCoreObject* pCoreObject) = 0;
		virtual void createSampler(RCoreObject* pCoreObject, RImageSamplerCreateInfo createInfo) = 0;
		virtual void makeRenderable(RCoreObject* pCoreObject) = 0;
		virtual void terminate(RCoreObject* pCoreObject) = 0;

	public:		/* Internal Data */
		DMKTexture* pTexture;
		RImage* pImage;
		RImageSampler* pSampler;
		RImageLayout currentLayout = RImageLayout::IMAGE_LAYOUT_GENERAL;
	};
}

#endif // !_DYNAMIK_RENDERER_TEXTURE_H
