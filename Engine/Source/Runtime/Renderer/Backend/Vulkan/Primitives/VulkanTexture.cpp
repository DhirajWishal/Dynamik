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
		void VulkanTexture::initialize(POINTER<RCoreObject> pCoreObject, POINTER<DMKTexture> pTextureObject)
		{
			pTexture = pTextureObject;

			VulkanBuffer staggingBuffer;
			staggingBuffer.initialize(pCoreObject, BufferType::BUFFER_TYPE_STAGGING, pTextureObject->size());
			staggingBuffer.setData(pCoreObject, pTextureObject->size(), 0, pTextureObject->image);

			RImageCreateInfo initInfo;
			initInfo.vDimentions.width = pTextureObject->width;
			initInfo.vDimentions.height = pTextureObject->height;
			initInfo.vDimentions.depth = pTextureObject->depth;
			initInfo.imageType = pTextureObject->type;
			initInfo.imageUsage = (ImageUsage)(ImageUsage::IMAGE_USAGE_RENDER | ImageUsage::IMAGE_USAGE_TRANSFER_SRC | ImageUsage::IMAGE_USAGE_TRANSFER_DST);
			initInfo.layers = pTextureObject->layerCount;
			initInfo.mipLevels = pTextureObject->mipLevels;
			initInfo.sampleCount = DMKSampleCount::DMK_SAMPLE_COUNT_1_BIT;
			initInfo.imageFormat = pTextureObject->format;

			pImage = (POINTER<RImage>)StaticAllocator<VulkanImage>::allocate();
			pImage->initialize(pCoreObject, initInfo);

			pImage->copyBuffer(pCoreObject, &staggingBuffer);

			pImage->generateMipMaps(pCoreObject);
		}

		void VulkanTexture::createView(POINTER<RCoreObject> pCoreObject)
		{
			pImageView = (POINTER<RImageView>)StaticAllocator<VulkanImageView>::allocate();
			pImageView->initialize(pCoreObject, pImage, pTexture->swizzles);
		}

		void VulkanTexture::createSampler(POINTER<RCoreObject> pCoreObject, RImageSamplerCreateInfo createInfo)
		{
			RImageSamplerCreateInfo initInfo;
			initInfo.addressModeU = ImageSamplerAddressMode::IMAGE_SAMPLER_ADDRESS_MODE_REPEAT;
			initInfo.addressModeV = ImageSamplerAddressMode::IMAGE_SAMPLER_ADDRESS_MODE_REPEAT;
			initInfo.addressModeW = ImageSamplerAddressMode::IMAGE_SAMPLER_ADDRESS_MODE_REPEAT;
			initInfo.borderColor = ImageSamplerBorderColor::IMAGE_SAMPLER_BORDER_COLOR_I32_OPAQUE_BLACK;

			pSampler = (POINTER<RImageSampler>)StaticAllocator<VulkanImageSampler>::allocate();
			pSampler->initialize(pCoreObject, initInfo);
		}

		void VulkanTexture::makeRenderable(POINTER<RCoreObject> pCoreObject)
		{
			pImage->setLayout(pCoreObject, ImageLayout::IMAGE_LAYOUT_SHADER_READ_ONLY);
		}

		void VulkanTexture::terminate(POINTER<RCoreObject> pCoreObject)
		{
			pImage->terminate(pCoreObject);
			pImageView->terminate(pCoreObject);
			pSampler->terminate(pCoreObject);
		}

		VulkanTexture::operator VulkanImage() const
		{
			return InheritCast<VulkanImage>(this->pImage);
		}

		VulkanTexture::operator VulkanImageView() const
		{
			return InheritCast<VulkanImageView>(this->pImageView);
		}

		VulkanTexture::operator VulkanImageSampler() const
		{
			return InheritCast<VulkanImageSampler>(this->pSampler);
		}
	}
}
