#include "dmkafx.h"
#include "VulkanFrameBufferAttachment.h"

namespace Dynamik
{
	namespace Backend
	{
		void VulkanFrameBufferAttachment::terminate(const VulkanDevice& vDevice)
		{
			image.terminate(vDevice);
			imageView.terminate(vDevice);
		}
		
		VulkanFrameBufferAttachment::operator VulkanImage() const
		{
			return this->image;
		}

		VulkanFrameBufferAttachment::operator VulkanImageView() const
		{
			return this->imageView;
		}
	}
}