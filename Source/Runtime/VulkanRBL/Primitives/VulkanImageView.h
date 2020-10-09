// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_IMAGE_VIEW_H
#define _DYNAMIK_VULKAN_IMAGE_VIEW_H

#include "VulkanImage.h"

namespace Backend
{
	/*
	 Vulkan Image View object for the Dynamik RBL
	*/
	class DMK_API VulkanImageView : public RImageView {
	public:
		VulkanImageView() {}
		~VulkanImageView() {}

		virtual void initialize(RCoreObject* pCoreObject, RImage* pImage, DMKTexture::TextureSwizzles swizzles) override final;
		virtual void terminate(RCoreObject* pCoreObject) override final;

		operator VkImageView() const;

		VkImageView imageView = VK_NULL_HANDLE;
	};
}

#endif // !_DYNAMIK_VULKAN_IMAGE_VIEW_H
