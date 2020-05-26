#include "dmkafx.h"
#include "VulkanImageSampler.h"

namespace Dynamik
{
	namespace Backend
	{
		void VulkanImageSampler::initialize(const VulkanDevice& vDevice, VulkanImageSamplerCreateInfo info)
		{
			VkSamplerCreateInfo sInfo;
			sInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
			sInfo.magFilter = (VkFilter)info.magFilter;
			sInfo.minFilter = (VkFilter)info.minFilter;
			sInfo.addressModeU = (VkSamplerAddressMode)info.addressModeU;
			sInfo.addressModeV = (VkSamplerAddressMode)info.addressModeV;
			sInfo.addressModeW = (VkSamplerAddressMode)info.addressModeW;
			sInfo.anisotropyEnable = (VkBool32)info.enableAnisotropy;
			sInfo.maxAnisotropy = info.maxAntisotropy;
			sInfo.borderColor = (VkBorderColor)info.borderColor;
			sInfo.unnormalizedCoordinates = (VkBool32)info.unnormalizedCoordinates;
			sInfo.compareEnable = (VkBool32)info.compareEnable;
			sInfo.compareOp = (VkCompareOp)info.compareOp;
			sInfo.mipmapMode = (VkSamplerMipmapMode)info.mipmapMode;
			sInfo.minLod = info.minLOD;
			sInfo.maxLod = info.maxLOD;
			sInfo.mipLodBias = info.mipLODBias;

			DMK_VULKAN_ASSERT(vkCreateSampler(vDevice, &sInfo, nullptr, &sampler), "Failed to create texture sampler!");
		}

		void VulkanImageSampler::terminate(const VulkanDevice& vDevice)
		{
			vkDestroySampler(vDevice, sampler, nullptr);
		}
		
		VulkanImageSampler::operator VkSampler()
		{
			return this->sampler;
		}
	}
}