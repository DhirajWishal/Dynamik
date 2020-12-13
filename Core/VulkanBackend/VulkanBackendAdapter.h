// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GraphicsCore/Backend/BackendAdapter.h"
#include "Core/Types/SparseSet.h"
#include "Objects/Device.h"

#include <vulkan/vulkan.h>

namespace DMK
{
	namespace VulkanBackend
	{
		/**
		 * Vulkan Backend Adapter object.
		 */
		class VulkanBackendAdapter : public GraphicsCore::BackendAdapter {
		public:
			VulkanBackendAdapter() {}
			~VulkanBackendAdapter() {}

			/**
			 * Initialize the backend adapter.
			 *
			 * @param enableValidation: Whether or not to enable API validation.
			 */
			virtual void Initialize(bool enableValidation) override final;

			/**
			 * Terminate the backend adapter.
			 */
			virtual void Terminate() override final;

		public:
			/**
			 * Create a new graphcis device.
			 *
			 * @param tryEnableRayTracing: Try and enable ray tracing if available. Default is false. If it is requested
			 *	but unavailable, the device uses compute shaders to compute ray tracing.
			 * @param pInputCenter: The input center pointer. Default is nullptr. Once an input center is attached,
			 *	inputs can be streamed from the device window to the application.
			 */
			virtual GraphicsCore::DeviceHandle CreateDevice(bool tryEnableRayTracing = false, Inputs::InputCenter* pInputCenter = nullptr) override final;

		private:
			void SetupGLFW();
			void TerminateGLFW();

			void InitializeInstance();
			void TerminateInstance();

			void InitializeDebugger();
			void TerminateDebugger();

		private:
			SparseSet<VulkanDevice, UI8> mDevices;

			std::vector<const char*> mInstanceExtensions;
			std::vector<const char*> mValidationLayers;

			VkInstance vInstance = VK_NULL_HANDLE;
			VkDebugUtilsMessengerEXT vDebugMessenger = VK_NULL_HANDLE;
		};
	}
}