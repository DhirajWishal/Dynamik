// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_IMAGE_H
#define _DYNAMIK_RENDERER_IMAGE_H

#include "Core/Objects/Resources/Texture.h"
#include "RImageView.h"
#include "../PrimitiveTypeDefs.h"
#include "Core/Math/MathTypes.h"

class DMK_API RCoreObject;
class DMK_API RBuffer;

/*
 Renderer Image Create Info
*/
struct DMK_API RImageCreateInfo {
	VEC3 vDimentions = VEC3(0.0f, 0.0f, 1.0f);
	DMKTextureType imageType = DMKTextureType::TEXTURE_TYPE_2D;
	RImageUsage imageUsage = RImageUsage::IMAGE_USAGE_RENDER;
	UI32 layers = 1;
	UI32 mipLevels = 1;
	DMKFormat imageFormat = DMKFormat::DMK_FORMAT_UNDEFINED;
	RResourceMemoryType memoryType = RResourceMemoryType::RESOURCE_MEMORY_TYPE_DEVICE_LOCAL;
	DMKSampleCount sampleCount = DMKSampleCount::DMK_SAMPLE_COUNT_1_BIT;
};

/*
 Renderer Image
*/
class DMK_API RImage {
public:
	RImage() {}
	virtual ~RImage() {}

	virtual void initialize(RCoreObject* pCoreObject, RImageCreateInfo createInfo) = 0;
	virtual void copyBuffer(RCoreObject* pCoreObject, RBuffer* pBuffer) = 0;
	virtual void generateMipMaps(RCoreObject* pCoreObject) = 0;
	virtual void setLayout(RCoreObject* pCoreObject, RImageLayout newLayout) = 0;
	virtual void createImageView(RCoreObject* pCoreObject, DMKTexture::TextureSwizzles swizzles) = 0;
	virtual void terminate(RCoreObject* pCoreObject) = 0;

	virtual void setData(RCoreObject* pCoreObject, UI64 uSize, UI64 offset, void* data) = 0;
	/*
	 Automatically maps memory
	*/
	virtual void* getData(RCoreObject* pCoreObject, UI64 uSize, UI64 offset) { return nullptr; }
	virtual void unmapMemory(RCoreObject* pCoreObject) = 0;

	VEC3 extent = VEC3(0.0f);
	RImageView* pImageView = nullptr;
	DMKTextureType type = DMKTextureType::TEXTURE_TYPE_2D;
	RImageUsage usage = RImageUsage::IMAGE_USAGE_RENDER;
	UI32 size = 0;
	UI32 mipLevel = 0;
	UI32 layers = 0;
	DMKFormat format = DMKFormat::DMK_FORMAT_UNDEFINED;
	RImageLayout layout = RImageLayout::IMAGE_LAYOUT_UNDEFINED;
};

#endif // !_DYNAMIK_RENDERER_IMAGE_H
