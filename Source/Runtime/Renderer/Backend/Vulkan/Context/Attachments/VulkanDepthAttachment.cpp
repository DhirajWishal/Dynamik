// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanDepthAttachment.h"

namespace Dynamik
{
	namespace Backend
	{
		void VulkanDepthAttachment::initialize(RCoreObject* pCoreObject, VulkanFrameBufferAttachmentInitInfo initInfo)
		{
			RImageCreateInfo imgCreateInfo;
			imgCreateInfo.imageFormat = initInfo.format;
			imgCreateInfo.imageType = DMKTextureType::DMK_TEXTURE_TYPE_2D;
			imgCreateInfo.imageUsage = IMAGE_USAGE_DEPTH_ATTACHMENT;
			imgCreateInfo.layers = 1;
			imgCreateInfo.mipLevels = 1;
			imgCreateInfo.vDimentions.width = initInfo.imageWidth;
			imgCreateInfo.vDimentions.height = initInfo.imageHeight;
			imgCreateInfo.sampleCount = initInfo.msaaSamples;

			image = StaticAllocator<VulkanImage>::allocate();
			image.initialize(pCoreObject, imgCreateInfo);

			imageView = StaticAllocator<VulkanImageView>::allocate();
			imageView.initialize(pCoreObject, &image, DMKTexture::TextureSwizzles());

			image.setLayout(pCoreObject, RImageLayout::IMAGE_LAYOUT_DEPTH_STECIL_ATTACHMENT);
		}
	}
}