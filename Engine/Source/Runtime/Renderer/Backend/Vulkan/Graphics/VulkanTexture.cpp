#include "dmkafx.h"
#include "VulkanTexture.h"

#include "../Primitives/VulkanBuffer.h"

namespace Dynamik
{
	namespace Backend
	{
		void VulkanTexture::initialize(const VulkanDevice& vDevice, const VulkanQueue& vQueue, const DMKTextureComponent& textureComponent)
		{
			image.imageSize = textureComponent.myTextureChennels * textureComponent.myTextureWidth * textureComponent.myTextureHeight;
			image.imageWidth = textureComponent.myTextureWidth;
			image.imageHeight = textureComponent.myTextureHeight;

			VulkanBuffer staggingBuffer;
			staggingBuffer.initialize(vDevice, BufferType::BUFFER_TYPE_STAGGING, image.imageSize);
		}

		void VulkanTexture::terminate(const VulkanDevice& vDevice)
		{
			image.terminate(vDevice);
			imageView.terminate(vDevice);
			sampler.terminate(vDevice);
		}

		VulkanTexture::operator VulkanImage() const
		{
			return this->image;
		}

		VulkanTexture::operator VulkanImageView() const
		{
			return this->imageView;
		}

		VulkanTexture::operator VulkanImageSampler() const
		{
			return this->sampler;
		}
	}
}
