// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanImageSampler.h"

#include "../VulkanCoreObject.h"

namespace Dynamik
{
	namespace Backend
	{
		void VulkanImageSampler::initialize(POINTER<RCoreObject> pCoreObject, RImageSamplerCreateInfo createInfo)
		{
			VkSamplerCreateInfo sInfo;
			sInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
			sInfo.pNext = VK_NULL_HANDLE;
			sInfo.flags = VK_NULL_HANDLE;
			sInfo.magFilter = (VkFilter)createInfo.magFilter;
			sInfo.minFilter = (VkFilter)createInfo.minFilter;
			sInfo.addressModeU = (VkSamplerAddressMode)createInfo.addressModeU;
			sInfo.addressModeV = (VkSamplerAddressMode)createInfo.addressModeV;
			sInfo.addressModeW = (VkSamplerAddressMode)createInfo.addressModeW;
			sInfo.anisotropyEnable = (VkBool32)createInfo.enableAnisotropy;
			sInfo.maxAnisotropy = createInfo.maxAntisotropy;
			sInfo.borderColor = (VkBorderColor)createInfo.borderColor;
			sInfo.unnormalizedCoordinates = (VkBool32)createInfo.unnormalizedCoordinates;
			sInfo.compareEnable = (VkBool32)createInfo.compareEnable;
			sInfo.compareOp = (VkCompareOp)createInfo.compareOp;
			sInfo.mipmapMode = (VkSamplerMipmapMode)createInfo.mipmapMode;
			sInfo.minLod = createInfo.minLOD;
			sInfo.maxLod = createInfo.maxLOD;
			sInfo.mipLodBias = createInfo.mipLODBias;

			DMK_VULKAN_ASSERT(vkCreateSampler(Inherit<VulkanCoreObject>(pCoreObject)->device, &sInfo, nullptr, &sampler), "Failed to create texture sampler!");
		}

		void VulkanImageSampler::terminate(POINTER<RCoreObject> pCoreObject)
		{
			vkDestroySampler(Inherit<VulkanCoreObject>(pCoreObject)->device, sampler, nullptr);
		}
		
		VulkanImageSampler::operator VkSampler()
		{
			return this->sampler;
		}
	}
}