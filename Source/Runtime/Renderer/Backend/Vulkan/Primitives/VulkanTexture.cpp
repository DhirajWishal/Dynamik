// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanTexture.h"

#include "VulkanBuffer.h"
#include "../VulkanUtilities.h"

namespace Dynamik
{
	namespace Backend
	{
		void VulkanTexture::initialize(RCoreObject* pCoreObject, DMKTexture* pTextureObject)
		{
			pTexture = pTextureObject;

			VulkanBuffer staggingBuffer;
			staggingBuffer.initialize(pCoreObject, RBufferType::BUFFER_TYPE_STAGGING, pTextureObject->size());
			staggingBuffer.setData(pCoreObject, pTextureObject->size(), 0, pTextureObject->image);

			RImageCreateInfo initInfo;
			initInfo.vDimentions.width = pTextureObject->width;
			initInfo.vDimentions.height = pTextureObject->height;
			initInfo.vDimentions.depth = pTextureObject->depth;
			initInfo.imageType = pTextureObject->type;
			initInfo.imageUsage = (RImageUsage)(RImageUsage::IMAGE_USAGE_RENDER | RImageUsage::IMAGE_USAGE_TRANSFER_SRC | RImageUsage::IMAGE_USAGE_TRANSFER_DST);
			initInfo.layers = pTextureObject->layerCount;
			initInfo.mipLevels = pTextureObject->mipLevels;
			initInfo.sampleCount = DMKSampleCount::DMK_SAMPLE_COUNT_1_BIT;
			initInfo.imageFormat = pTextureObject->format;

			pImage = (RImage*)StaticAllocator<VulkanImage>::allocate();
			pImage->initialize(pCoreObject, initInfo);

			pImage->copyBuffer(pCoreObject, &staggingBuffer);

			pImage->generateMipMaps(pCoreObject);
		}

		void VulkanTexture::createView(RCoreObject* pCoreObject)
		{
			pImage->createImageView(pCoreObject, pTexture->swizzles);
		}

		void VulkanTexture::createSampler(RCoreObject* pCoreObject, RImageSamplerCreateInfo createInfo)
		{
			pSampler = (RImageSampler*)StaticAllocator<VulkanImageSampler>::allocate();
			pSampler->initialize(pCoreObject, createInfo);
		}

		void VulkanTexture::makeRenderable(RCoreObject* pCoreObject)
		{
			pImage->setLayout(pCoreObject, RImageLayout::IMAGE_LAYOUT_SHADER_READ_ONLY);
		}

		void VulkanTexture::terminate(RCoreObject* pCoreObject)
		{
			pImage->terminate(pCoreObject);
			pSampler->terminate(pCoreObject);
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
}
