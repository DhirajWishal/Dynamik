#include "dmkafx.h"
#include "VulkanDepthAttachment.h"

namespace Dynamik
{
	namespace Backend
	{
		void VulkanDepthAttachment::initialize(const VulkanDevice& vDevice, const VulkanQueue& vQueue, VulkanFrameBufferAttachmentInitInfo initInfo)
		{
			VulkanImageCreateInfo imgCreateInfo;
			imgCreateInfo.imageFormat = initInfo.format;
			imgCreateInfo.imageType = ImageType::IMAGE_TYPE_2D;
			imgCreateInfo.imageUsage = IMAGE_USAGE_DEPTH_ATTACHMENT;
			imgCreateInfo.layers = 1;
			imgCreateInfo.mipLevels = 1;
			imgCreateInfo.imageWidth = initInfo.imageWidth;
			imgCreateInfo.imageHeight = initInfo.imageHeight;
			imgCreateInfo.sampleCount = initInfo.msaaSamples;
			image.initialize(vDevice, vQueue, imgCreateInfo);

			imageView.initialize(vDevice, image);

			image.setLayout(vDevice, vQueue, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
		}
	}
}