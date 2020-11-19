// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_BACKEND_FUNCTION_H
#define _DYNAMIK_VULKAN_BACKEND_FUNCTION_H

namespace DMK
{
	namespace VulkanBackend
	{
		/**
		 * This is the main backend function of the Dynamik Vulkan Backend module.
		 * This function is executed on a seperate thread which is done by the Graphics Engine.
		 */
		void VulkanBackendFunction();
	}
}

#endif // !_DYNAMIK_VULKAN_BACKEND_FUNCTION_H
