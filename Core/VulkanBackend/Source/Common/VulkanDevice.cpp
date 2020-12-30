// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/Common/VulkanDevice.h"

namespace DMK
{
	namespace VulkanBackend
	{
		void VulkanDevice::Initialize(VkInstance vInstance, VulkanDisplay* pDisplay)
		{
		}

		void VulkanDevice::Terminate()
		{
		}

		void VulkanDevice::InitializeSurface(VulkanDisplay* pWindow)
		{
		}

		void VulkanDevice::TerminateSurface()
		{
		}

		void VulkanDevice::InitializePhysicalDevice(VulkanDisplay* pWindow)
		{
		}

		void VulkanDevice::TerminatePhysicalDevice()
		{
		}

		void VulkanDevice::InitializeLogicalDevice()
		{
		}

		void VulkanDevice::TerminateLogicalDevice()
		{
		}

		bool VulkanDevice::IsPhysicalDeviceSuitable(VkPhysicalDevice vDevice)
		{
			return false;
		}
	}
}