// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_TEXTURE_H
#define _DYNAMIK_RENDERER_TEXTURE_H

#include "RImage.h"
#include "RImageSampler.h"

struct DMK_API RImageSamplerCreateInfo;
class DMK_API RImageSampler;

/*
 Renderer Texture object
*/
class DMK_API RTexture {
public:
	RTexture() : pTexture(nullptr), pImage(nullptr), pSampler(nullptr) {}
	virtual ~RTexture() {}

	virtual void initialize(RCoreObject* pCoreObject, DMKTexture* pTextureObject) = 0;
	virtual void createView(RCoreObject* pCoreObject, I32 mipLevel = 1) = 0;
	virtual void createSampler(RCoreObject* pCoreObject, RImageSamplerCreateInfo createInfo) = 0;
	virtual void makeRenderable(RCoreObject* pCoreObject) = 0;
	virtual void terminate(RCoreObject* pCoreObject) = 0;

public:		/* Internal Data */
	DMKTexture* pTexture = nullptr;
	RImage* pImage = nullptr;
	RImageSampler* pSampler = nullptr;
};

#endif // !_DYNAMIK_RENDERER_TEXTURE_H
