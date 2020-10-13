// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanColorAttachment.h"

#include "../../Primitives/VulkanImage.h"

namespace Backend
{
	void VulkanColorAttachment::initialize(RCoreObject* pCoreObject, RFrameBufferAttachmentInfo initInfo)
	{
		RImageCreateInfo imgCreateInfo;
		imgCreateInfo.imageFormat = initInfo.format;
		imgCreateInfo.imageType = DMKTextureType::TEXTURE_TYPE_2D;
		imgCreateInfo.imageUsage = (RImageUsage)(IMAGE_USAGE_TRANSIENT_ATTACHMENT | IMAGE_USAGE_COLOR_ATTACHMENT);
		imgCreateInfo.layers = 1;
		imgCreateInfo.mipLevels = 1;
		imgCreateInfo.vDimentions.width = Cast<float>(initInfo.imageWidth);
		imgCreateInfo.vDimentions.height = Cast<float>(initInfo.imageHeight);
		imgCreateInfo.sampleCount = initInfo.msaaSamples;

		pImageAttachment = StaticAllocator<VulkanImage>::rawAllocate();
		pImageAttachment->initialize(pCoreObject, imgCreateInfo);

		pImageAttachment->createImageView(pCoreObject, DMKTexture::TextureSwizzles());

		pImageAttachment->setLayout(pCoreObject, RImageLayout::IMAGE_LAYOUT_COLOR_ATTACHMENT);
	}

	void VulkanColorAttachment::terminate(RCoreObject* pCoreObject)
	{
		pImageAttachment->terminate(pCoreObject);
		StaticAllocator<VulkanImage>::rawDeallocate(pImageAttachment);
	}
}
