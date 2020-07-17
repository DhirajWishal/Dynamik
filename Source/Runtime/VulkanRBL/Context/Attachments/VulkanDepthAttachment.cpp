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
			imgCreateInfo.imageType = DMKTextureType::TEXTURE_TYPE_2D;
			imgCreateInfo.imageUsage = IMAGE_USAGE_DEPTH_ATTACHMENT;
			imgCreateInfo.layers = 1;
			imgCreateInfo.mipLevels = 1;
			imgCreateInfo.vDimentions.width = Cast<F32>(initInfo.imageWidth);
			imgCreateInfo.vDimentions.height = Cast<F32>(initInfo.imageHeight);
			imgCreateInfo.sampleCount = initInfo.msaaSamples;

			image.initialize(pCoreObject, imgCreateInfo);

			imageView.initialize(pCoreObject, &image, DMKTexture::TextureSwizzles());

			image.setLayout(pCoreObject, RImageLayout::IMAGE_LAYOUT_DEPTH_STECIL_ATTACHMENT);
		}
	}
}