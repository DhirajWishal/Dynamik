// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanDepthAttachment.h"

#include "../../Primitives/VulkanImage.h"

namespace Backend
{
	void VulkanDepthAttachment::initialize(RCoreObject* pCoreObject, RFrameBufferAttachmentInfo initInfo)
	{
		RImageCreateInfo imgCreateInfo;
		imgCreateInfo.imageFormat = initInfo.format;
		imgCreateInfo.imageType = DMKTextureType::TEXTURE_TYPE_2D;
		imgCreateInfo.imageUsage = IMAGE_USAGE_DEPTH_ATTACHMENT;
		imgCreateInfo.layers = 1;
		imgCreateInfo.mipLevels = 1;
		imgCreateInfo.vDimentions.width = Cast<float>(initInfo.imageWidth);
		imgCreateInfo.vDimentions.height = Cast<float>(initInfo.imageHeight);
		imgCreateInfo.sampleCount = initInfo.msaaSamples;

		pImageAttachment = StaticAllocator<VulkanImage>::rawAllocate();
		pImageAttachment->initialize(pCoreObject, imgCreateInfo);
		pImageAttachment->createImageView(pCoreObject, DMKTexture::TextureSwizzles());

		pImageAttachment->setLayout(pCoreObject, RImageLayout::IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT);
	}

	void VulkanDepthAttachment::terminate(RCoreObject* pCoreObject)
	{
		pImageAttachment->terminate(pCoreObject);
		StaticAllocator<VulkanImage>::rawDeallocate(pImageAttachment);
	}
}
