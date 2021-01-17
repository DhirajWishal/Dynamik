// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Types/DataTypes.h"
#include <optional>

#include <vulkan/vulkan.h>

namespace DMK
{
	namespace VulkanBackend
	{
		class VulkanQueue {
		public:
			VulkanQueue() {}
			~VulkanQueue() {}

			void Initialize(VkPhysicalDevice vPhysicalDevice, VkSurfaceKHR vSurface);
			bool IsComplete() const;

			std::optional<UI32> mGraphicsFamily;
			std::optional<UI32> mComputeFamily;
			std::optional<UI32> mTransferFamily;
		};
	}
}