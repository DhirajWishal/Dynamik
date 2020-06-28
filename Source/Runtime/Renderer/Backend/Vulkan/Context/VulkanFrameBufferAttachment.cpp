// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanFrameBufferAttachment.h"

namespace Dynamik
{
	namespace Backend
	{
		void VulkanFrameBufferAttachment::terminate(RCoreObject* pCoreObject)
		{
			image.terminate(pCoreObject);
			imageView.terminate(pCoreObject);
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