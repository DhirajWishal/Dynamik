// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_BACKEND_FUNCTION_H
#define _DYNAMIK_VULKAN_BACKEND_FUNCTION_H

#include "Thread/Commands/CommandQueue.h"

namespace DMK
{
	namespace VulkanBackend
	{
		/**
		 * This is the main backend function of the Dynamik Vulkan Backend module.
		 * This function is executed on a seperate thread which is done by the Graphics Engine.
		 *
		 * @param pCommandQueu: The command queue object pointer.
		 */
		void VulkanBackendFunction(Threads::CommandQueue<THREAD_MAX_COMMAND_COUNT>* pCommandQueue);
	}
}

#endif // !_DYNAMIK_VULKAN_BACKEND_FUNCTION_H
