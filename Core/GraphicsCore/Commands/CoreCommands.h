// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Types/DataTypes.h"
#include "GraphicsCore/Backend/DeviceHandle.h"

namespace DMK
{
	namespace GraphicsCore
	{
		namespace Commands
		{
			/**
			 * Initialize Backend command.
			 * This command carry the information to initialize the selected graphics backend.
			 */
			struct InitializeBackend {
				InitializeBackend() = default;

				/**
				 * Construct the structure with the state of enableValidation.
				 *
				 * @param enableValidation: Boolean whether or not to API validation.
				 */
				InitializeBackend(bool enableValidation) : enableValidation(enableValidation) {}

				bool enableValidation = true;	// Enable API validation.
			};

			/**
			 * Terminate the backend command.
			 * This command will terminate the backend and exits the thread.
			 * This contains a variable which does not need to be altered.
			 */
			struct TerminateBackend { const bool __terminate = true; };

			/**
			 * Create Device command.
			 * This command caries information and instruct the backend to create a new device and provide its ID.
			 */
			struct CreateDevice {
				CreateDevice() = default;

				/**
				 * Create the command using the DeviceInitInfo data.
				 *
				 * @param initInfo: The device init info data.
				 */
				CreateDevice(const DeviceInitInfo& initInfo) : initInfo(initInfo) {}

				/**
				 * Create the command using the DeviceHandle pointer.
				 * The device handle pointer defines where to store the device handle data.
				 *
				 * @param pDeviceHandle: The device handle object pointer.
				 */
				CreateDevice(DeviceHandle* pDeviceHandle) : pDeviceHandle(pDeviceHandle) {}

				/**
				 * Construct the command using DeviceInitInfo and DeviceHandle pointer data.
				 * The device handle pointer defines where to store the device handle data.
				 *
				 * @param initInfo: The device init info data.
				 * @param pDeviceHandle: The device handle object pointer.
				 */
				CreateDevice(const DeviceInitInfo& initInfo, DeviceHandle* pDeviceHandle)
					: initInfo(initInfo), pDeviceHandle(pDeviceHandle) {}

				DeviceInitInfo initInfo = {};	// Device init info data.
				DeviceHandle* pDeviceHandle = nullptr;	// Device handle object pointer.
			};

			/**
			 * Destroy a Device command.
			 * This command instruct the backend to destroy a specific device and all the data with it.
			 */
			struct DestroyDevice {
				DestroyDevice() = default;

				/**
				 * Construct the command using the device handle.
				 *
				 * @param deviceHandle: The device handle of the device to be destroyed.
				 */
				DestroyDevice(const DeviceHandle& deviceHandle) : mDeviceHandle(deviceHandle) {}

				DeviceHandle mDeviceHandle = {};	// The device handle.
			};
		}
	}
}
