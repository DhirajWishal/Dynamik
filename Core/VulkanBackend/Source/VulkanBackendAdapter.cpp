// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/VulkanBackendAdapter.h"
#include "VulkanBackend/Macros.h"
#include "Core/ErrorHandler/Logger.h"
#include "Core/Types/Utilities.h"

#include <iostream>
#include <GLFW/glfw3.h>

namespace DMK
{
	namespace VulkanBackend
	{
		void VulkanBackendAdapter::Initialize(bool enableValidation)
		{
			mEnableValidation = enableValidation;

			// Setup GLFW.
			TerminateGLFW();

			// Initialize instance.
			InitializeInstance();

			// Check and initialize the debugger.
			if (mEnableValidation)
			{
				mValidationLayers.push_back("VK_LAYER_KHRONOS_validation");
				InitializeDebugger();
			}
		}

		void VulkanBackendAdapter::Terminate()
		{
			// Check and terminate the debugger.
			if (mEnableValidation)
				TerminateDebugger();

			// Terminate instance.
			TerminateInstance();

			// Terminate GLFW.
			TerminateGLFW();
		}

		GraphicsCore::DeviceHandle VulkanBackendAdapter::CreateDevice(bool tryEnableRayTracing, Inputs::InputCenter* pInputCenter)
		{
			VulkanDevice device = {};

			//return GraphicsCore::DeviceHandle(StaticSparseSet<VulkanDevice, UI8>::Insert(std::move(device)));
			return GraphicsCore::DeviceHandle();
		}

		void VulkanBackendAdapter::SetupGLFW()
		{
			InitializeGLFW();
		}

		void VulkanBackendAdapter::TerminateGLFW()
		{
			TerminateGLFW();
		}

		void VulkanBackendAdapter::InitializeInstance()
		{
			
		}

		void VulkanBackendAdapter::TerminateInstance()
		{
			vkDestroyInstance(vInstance, nullptr);
		}

		void VulkanBackendAdapter::InitializeDebugger()
		{
		}

		void VulkanBackendAdapter::TerminateDebugger()
		{
		}
	}
}