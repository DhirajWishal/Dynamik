#include "dmkafx.h"
#include "VulkanColorAttachment.h"

namespace Dynamik
{
	namespace Backend
	{
		void VulkanColorAttachment::initialize(const VulkanDevice& vDevice, const VulkanQueue& vQueue, VulkanFrameBufferAttachmentInitInfo initInfo)
		{
			VulkanImageCreateInfo imgCreateInfo;
			imgCreateInfo.imageFormat = initInfo.format;
			imgCreateInfo.imageType = ImageType::IMAGE_TYPE_2D;
			imgCreateInfo.imageUsage = (ImageUsage)(IMAGE_USAGE_TRANSIENT_ATTACHMENT | IMAGE_USAGE_COLOR_ATTACHMENT);
			imgCreateInfo.layers = 1;
			imgCreateInfo.mipLevels = 1;
			imgCreateInfo.imageWidth = initInfo.imageWidth;
			imgCreateInfo.imageHeight = initInfo.imageHeight;
			imgCreateInfo.sampleCount = initInfo.msaaSamples;
			image.initialize(vDevice, vQueue, imgCreateInfo);

			imageView.initialize(vDevice, image);

			image.setLayout(vDevice, vQueue, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);
		}
	}
}
