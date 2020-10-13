// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanTexture.h"

#include "VulkanBuffer.h"
#include "../VulkanUtilities.h"

#include <cmath>

namespace Backend
{
	void VulkanTexture::initialize(RCoreObject* pCoreObject, DMKTexture* pTextureObject)
	{
		RImageCreateInfo initInfo;
		initInfo.vDimentions.width = (float)pTextureObject->width;
		initInfo.vDimentions.height = (float)pTextureObject->height;
		initInfo.vDimentions.depth = (float)pTextureObject->depth;
		initInfo.imageType = pTextureObject->type;
		initInfo.imageUsage = (RImageUsage)(RImageUsage::IMAGE_USAGE_RENDER | RImageUsage::IMAGE_USAGE_TRANSFER_SRC | RImageUsage::IMAGE_USAGE_TRANSFER_DST);
		initInfo.layers = pTextureObject->layerCount;
		initInfo.mipLevels = pTextureObject->mipLevels;
		initInfo.sampleCount = DMKSampleCount::DMK_SAMPLE_COUNT_1_BIT;
		initInfo.imageFormat = pTextureObject->format;

		pImage = (RImage*)StaticAllocator<VulkanImage>::rawAllocate();
		pImage->initialize(pCoreObject, initInfo);

		if (pImage->format != pTextureObject->format)
		{
			DMK_WARN("The specified texture format was not supported! The format was updated internally!");
			pTextureObject->format = pImage->format;
			pTextureObject->channels = 4;	/* TODO */
		}

		pTexture = pTextureObject;

		VulkanBuffer staggingBuffer;
		staggingBuffer.initialize(pCoreObject, RBufferType::BUFFER_TYPE_STAGGING, pTextureObject->size() * pTextureObject->layerCount);
		staggingBuffer.setData(pCoreObject, pTextureObject->size() * pTextureObject->layerCount, 0, pTextureObject->image);

		pImage->setLayout(pCoreObject, RImageLayout::IMAGE_LAYOUT_TRANSFER_DST);
		pImage->copyBuffer(pCoreObject, &staggingBuffer);

		pImage->generateMipMaps(pCoreObject);

		staggingBuffer.terminate(pCoreObject);
	}

	void VulkanTexture::createView(RCoreObject* pCoreObject, I32 mipLevel)
	{
		pImage->createImageView(pCoreObject, pTexture->swizzles);
	}

	void VulkanTexture::createSampler(RCoreObject* pCoreObject, RImageSamplerCreateInfo createInfo)
	{
		pSampler = (RImageSampler*)StaticAllocator<VulkanImageSampler>::rawAllocate();

		createInfo.maxLOD = Cast<float>(pImage->mipLevel);
		pSampler->initialize(pCoreObject, createInfo);
	}

	void VulkanTexture::makeRenderable(RCoreObject* pCoreObject)
	{
		pImage->setLayout(pCoreObject, RImageLayout::IMAGE_LAYOUT_SHADER_READ_ONLY);
	}

	void VulkanTexture::terminate(RCoreObject* pCoreObject)
	{
		if (pImage)
		{
			pImage->terminate(pCoreObject);
			StaticAllocator<VulkanImage>::rawDeallocate(pImage);
		}

		if (pSampler)
		{
			pSampler->terminate(pCoreObject);
			StaticAllocator<VulkanImageSampler>::rawDeallocate(pSampler);
		}
	}

	VulkanTexture::operator VulkanImage() const
	{
		return InheritCast<VulkanImage>(this->pImage);
	}

	VulkanTexture::operator VulkanImageView() const
	{
		return InheritCast<VulkanImageView>(this->pImage->pImageView);
	}

	VulkanTexture::operator VulkanImageSampler() const
	{
		return InheritCast<VulkanImageSampler>(this->pSampler);
	}
}