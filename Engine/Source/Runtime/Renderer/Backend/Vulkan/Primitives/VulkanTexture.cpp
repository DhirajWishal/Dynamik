#include "dmkafx.h"
#include "VulkanTexture.h"

#include "../Primitives/VulkanBuffer.h"

namespace Dynamik
{
	namespace Backend
	{
		void VulkanTexture::initialize(const VulkanDevice& vDevice, const VulkanQueue& vQueue, POINTER<DMKTexture> textureComponent)
		{
			texture = textureComponent;

			VulkanBuffer staggingBuffer;
			staggingBuffer.initialize(vDevice, BufferType::BUFFER_TYPE_STAGGING, textureComponent->size());
			DMKMemoryFunctions::moveData(staggingBuffer.mapMemory(vDevice), textureComponent->image, textureComponent->size());
			staggingBuffer.unmapMemory(vDevice);

			VulkanImageCreateInfo initInfo;
			initInfo.imageWidth = textureComponent->width;
			initInfo.imageHeight = textureComponent->height;
			initInfo.imageDepth = textureComponent->depth;
			initInfo.imageType = textureComponent->type;
			initInfo.imageUsage = (ImageUsage)(ImageUsage::IMAGE_USAGE_RENDER | ImageUsage::IMAGE_USAGE_TRANSFER_SRC | ImageUsage::IMAGE_USAGE_TRANSFER_DST);
			initInfo.layers = textureComponent->layerCount;
			initInfo.mipLevels = textureComponent->mipLevels;
			initInfo.sampleCount = DMKSampleCount::DMK_SAMPLE_COUNT_1_BIT;
			initInfo.imageFormat = textureComponent->format;
			image.initialize(vDevice, vQueue, initInfo);

			image.copyBuffer(vDevice, vQueue, staggingBuffer);

			image.generateMipMaps(vDevice, vQueue);
		}

		VkComponentMapping getComponentMapping(DMKTexture::TextureSwizzles swizzles)
		{
			VkComponentMapping _mapping;
			_mapping.r = (VkComponentSwizzle)swizzles.componentOne;
			_mapping.g = (VkComponentSwizzle)swizzles.componentTwo;
			_mapping.b = (VkComponentSwizzle)swizzles.componentThree;
			_mapping.a = (VkComponentSwizzle)swizzles.componentFour;

			return _mapping;
		}

		void VulkanTexture::initializeView(const VulkanDevice& vDevice)
		{
			imageView.initialize(vDevice, image, getComponentMapping(texture->swizzles));
		}

		void VulkanTexture::initializeSampler(const VulkanDevice& vDevice)
		{
			VulkanImageSamplerCreateInfo initInfo;
			initInfo.addressModeU = ImageSamplerAddressMode::IMAGE_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
			initInfo.addressModeV = ImageSamplerAddressMode::IMAGE_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
			initInfo.addressModeW = ImageSamplerAddressMode::IMAGE_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
			sampler.initialize(vDevice, initInfo);
		}

		void VulkanTexture::makeRenderable(const VulkanDevice& vDevice, const VulkanQueue& vQueue)
		{
			image.setLayout(vDevice, vQueue, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
		}

		void VulkanTexture::terminate(const VulkanDevice& vDevice)
		{
			image.terminate(vDevice);
			imageView.terminate(vDevice);
			sampler.terminate(vDevice);
		}

		VkDescriptorImageInfo VulkanTexture::createDescriptorInfo()
		{
			VkDescriptorImageInfo _info;
			_info.imageLayout = VkImageLayout::VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			_info.imageView = imageView;
			_info.sampler = sampler;

			return _info;
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
