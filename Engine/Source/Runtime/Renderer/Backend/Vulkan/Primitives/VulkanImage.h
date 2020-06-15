// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_IMAGE_H
#define _DYNAMIK_VULKAN_IMAGE_H

/*
 Author:    Dhiraj Wishal
 Date:      25/05/2020
*/
#include "Renderer/Components/Primitives/RImage.h"
#include "Object/Resource/Texture.h"
#include "../Common/VulkanDevice.h"
#include "../Common/VulkanQueue.h"
#include "VulkanBuffer.h"
#include "Renderer/Components/PrimitiveTypeDefs.h"
#include "Renderer/Components/CoreTypeDefs.h"

namespace Dynamik
{
	namespace Backend
	{
		struct DMK_API VulkanImageCreateInfo {
			UI32 imageWidth = 0;
			UI32 imageHeight = 0;
			UI32 imageDepth = 1;
			DMKTextureType imageType = DMKTextureType::DMK_TEXTURE_TYPE_2D;
			ImageUsage imageUsage = ImageUsage::IMAGE_USAGE_RENDER;
			UI32 layers = 1;
			UI32 mipLevels = 1;
			DMKFormat imageFormat = DMKFormat::DMK_FORMAT_UNDEFINED;
			ResourceMemoryType memoryType = ResourceMemoryType::RESOURCE_MEMORY_TYPE_HOST_ACCESSABLE;
			DMKSampleCount sampleCount = DMKSampleCount::DMK_SAMPLE_COUNT_1_BIT;
		};

		/*
		 Vulkan Image object for the Dynamik Engine
		*/
		class DMK_API VulkanImage : public RImage {
		public:
			VulkanImage() {}
			~VulkanImage() {}

			virtual void initialize(POINTER<RCoreObject> pCoreObject, RImageCreateInfo createInfo) override final;
			virtual void copyBuffer(POINTER<RCoreObject> pCoreObject, POINTER<RBuffer> pBuffer) override final;
			virtual void generateMipMaps(POINTER<RCoreObject> pCoreObject) override final;
			virtual void setLayout(POINTER<RCoreObject> pCoreObject, ImageLayout newLayout) override final;
			virtual void createImageView(POINTER<RCoreObject> pCoreObject) override final;
			virtual void terminate(POINTER<RCoreObject> pCoreObject) override final;

			virtual void setData(POINTER<RCoreObject> pCoreObject, UI64 uSize, UI64 offset, VPTR data) override final;
			virtual VPTR getData(POINTER<RCoreObject> pCoreObject, UI64 uSize, UI64 offset) override final;
			virtual void unmapMemory(POINTER<RCoreObject> pCoreObject) override final;

			operator VkImage() const;
			operator VkDeviceMemory() const;

			VkImage image = VK_NULL_HANDLE;
			VkDeviceMemory imageMemory = VK_NULL_HANDLE;
		};
	}
}

#endif // !_DYNAMIK_VULKAN_IMAGE_H
