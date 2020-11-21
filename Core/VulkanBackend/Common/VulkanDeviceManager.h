// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GraphicsCore/Backend/DeviceHandle.h"
#include "VulkanInstance.h"

namespace DMK
{
	namespace VulkanBackend
	{
		/**
		 * Vulkan Device Manager object.
		 * This object is responsible of creating, maintaining and destroying Vulkan Device objects.
		 */
		class VulkanDeviceManager {
		public:
			/**
			 * Default constructor.
			 */
			VulkanDeviceManager() {}

			/**
			 * Default destructor.
			 */
			~VulkanDeviceManager() {}

			/**
			 * Initialize the manager.
			 *
			 * @param pInstance: The Vulkan Instance pointer which the device manager belongs to.
			 */
			void Initialize(VulkanInstance* pInstance);

			/**
			 * Terminate the device manager.
			 * This method will automatically destroy all the created devices.
			 */
			void Terminate();

			/**
			 * Create a new Vulkan Device.
			 *
			 * @param initInfo: The Device Init Info structure.
			 * @return Device Handle object.
			 */
			GraphicsCore::DeviceHandle CreateDevice(GraphicsCore::DeviceInitInfo initInfo);

			/**
			 * Destroy a created Vulkan Device.
			 *
			 * @param deviceHandle: The device handle to be destroyed.
			 */
			void DestroyDevice(const GraphicsCore::DeviceHandle& deviceHandle);

			/**
			 * Get the Vulkan Device using its handle.
			 *
			 * @param deviceHandle: The device handle.
			 * @return Vulkan Device object.
			 */
			VulkanDevice GetDevice(const GraphicsCore::DeviceHandle& deviceHandle);

			/**
			 * Get the Vulkan Device pointer using its handle.
			 *
			 * @param deviceHandle: The device handle.
			 * @return Vulkan Device object pointer.
			 */
			VulkanDevice* GetDeviceAddress(const GraphicsCore::DeviceHandle& deviceHandle);

		public:
			/**
			 * Poll events of all windows.
			 * This is important as if not done, the window (all the windows) will be irresponsive.
			 */
			void PollInputs();

		private:
			VulkanInstance* pParentInstance = nullptr;	// Vulkan instance pointer.

			bool isInitialized = false;	// State of the manager.
		};
	}
}
