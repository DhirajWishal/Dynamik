// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanColorAttachment.h"

namespace Dynamik
{
	namespace Backend
	{
		void VulkanColorAttachment::initialize(RCoreObject* pCoreObject, VulkanFrameBufferAttachmentInitInfo initInfo)
		{
			RImageCreateInfo imgCreateInfo;
			imgCreateInfo.imageFormat = initInfo.format;
			imgCreateInfo.imageType = DMKTextureType::TEXTURE_TYPE_2D;
			imgCreateInfo.imageUsage = (RImageUsage)(IMAGE_USAGE_TRANSIENT_ATTACHMENT | IMAGE_USAGE_COLOR_ATTACHMENT);
			imgCreateInfo.layers = 1;
			imgCreateInfo.mipLevels = 1;
			imgCreateInfo.vDimentions.width = Cast<F32>(initInfo.imageWidth);
			imgCreateInfo.vDimentions.height = Cast<F32>(initInfo.imageHeight);
			imgCreateInfo.sampleCount = initInfo.msaaSamples;

			image = StaticAllocator<VulkanImage>::rawAllocate();
			image.initialize(pCoreObject, imgCreateInfo);

			imageView = StaticAllocator<VulkanImageView>::rawAllocate();
			imageView.initialize(pCoreObject, &image, DMKTexture::TextureSwizzles());

			image.setLayout(pCoreObject, RImageLayout::IMAGE_LAYOUT_COLOR_ATTACHMENT);
		}
	}
}
