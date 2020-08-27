// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_IMAGE_H
#define _DYNAMIK_VULKAN_IMAGE_H

#include "Renderer/Components/Primitives/RImage.h"
#include "Core/Objects/Resources/Texture.h"
#include "../Common/VulkanDevice.h"
#include "../Common/VulkanQueue.h"
#include "VulkanBuffer.h"
#include "Renderer/Components/PrimitiveTypeDefs.h"
#include "Renderer/Components/CoreTypeDefs.h"

namespace Backend
{
	/*
	 Vulkan Image object for the Dynamik Engine
	*/
	class DMK_API VulkanImage : public RImage {
	public:
		VulkanImage() {}
		~VulkanImage() {}

		virtual void initialize(RCoreObject* pCoreObject, RImageCreateInfo createInfo) override final;
		virtual void copyBuffer(RCoreObject* pCoreObject, RBuffer* pBuffer) override final;
		virtual void generateMipMaps(RCoreObject* pCoreObject) override final;
		virtual void setLayout(RCoreObject* pCoreObject, RImageLayout newLayout) override final;
		virtual void createImageView(RCoreObject* pCoreObject, DMKTexture::TextureSwizzles swizzles) override final;
		virtual void terminate(RCoreObject* pCoreObject) override final;

		virtual void setData(RCoreObject* pCoreObject, UI64 uSize, UI64 offset, VPTR data) override final;
		virtual VPTR getData(RCoreObject* pCoreObject, UI64 uSize, UI64 offset) override final;
		virtual void unmapMemory(RCoreObject* pCoreObject) override final;

		operator VkImage() const;
		operator VkDeviceMemory() const;

		VkImage image = VK_NULL_HANDLE;
		VkDeviceMemory imageMemory = VK_NULL_HANDLE;
	};
}

#endif // !_DYNAMIK_VULKAN_IMAGE_H
