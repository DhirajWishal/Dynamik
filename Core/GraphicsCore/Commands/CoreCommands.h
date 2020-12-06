// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CommandBase.h"
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
			struct InitializeBackend : public CommandBase {
				InitializeBackend() : CommandBase(CommandType::INITIALIZE_BACKEND) {}

				/**
				 * Construct the structure with the state of enableValidation.
				 *
				 * @param enableValidation: Boolean whether or not to API validation.
				 */
				InitializeBackend(bool enableValidation)
					: CommandBase(CommandType::INITIALIZE_BACKEND), enableValidation(enableValidation) {}

				bool enableValidation = true;	// Enable API validation.
			};

			/**
			 * Terminate the backend command.
			 * This command will terminate the backend and exits the thread.
			 * This contains a variable which does not need to be altered.
			 */
			struct TerminateBackend : public CommandBase {
				TerminateBackend() : CommandBase(CommandType::TERMINATE_BACKEND) {}
				const bool __terminate = true;
			};

			/**
			 * Create Device command.
			 * This command caries information and instruct the backend to create a new device and provide its ID.
			 */
			struct CreateDevice : public CommandBase {
				CreateDevice() : CommandBase(CommandType::CREATE_DEVICE) {}

				/**
				 * Create the command using the DeviceInitInfo data.
				 *
				 * @param initInfo: The device init info data.
				 */
				CreateDevice(const DeviceInitInfo& initInfo)
					: CommandBase(CommandType::CREATE_DEVICE), initInfo(initInfo) {}

				/**
				 * Create the command using the DeviceHandle pointer.
				 * The device handle pointer defines where to store the device handle data.
				 *
				 * @param pDeviceHandle: The device handle object pointer.
				 */
				CreateDevice(DeviceHandle* pDeviceHandle)
					: CommandBase(CommandType::CREATE_DEVICE), pDeviceHandle(pDeviceHandle) {}

				/**
				 * Construct the command using DeviceInitInfo and DeviceHandle pointer data.
				 * The device handle pointer defines where to store the device handle data.
				 *
				 * @param initInfo: The device init info data.
				 * @param pDeviceHandle: The device handle object pointer.
				 */
				CreateDevice(const DeviceInitInfo& initInfo, DeviceHandle* pDeviceHandle)
					: CommandBase(CommandType::CREATE_DEVICE), initInfo(initInfo), pDeviceHandle(pDeviceHandle) {}

				DeviceInitInfo initInfo = {};	// Device init info data.
				DeviceHandle* pDeviceHandle = nullptr;	// Device handle object pointer.
			};

			/**
			 * Destroy a Device command.
			 * This command instruct the backend to destroy a specific device and all the data with it.
			 */
			struct DestroyDevice : public CommandBase {
				DestroyDevice() : CommandBase(CommandType::DESTROY_DEVICE) {}

				/**
				 * Construct the command using the device handle.
				 *
				 * @param deviceHandle: The device handle of the device to be destroyed.
				 */
				DestroyDevice(const DeviceHandle& deviceHandle)
					: CommandBase(CommandType::DESTROY_DEVICE), mDeviceHandle(deviceHandle) {}

				DeviceHandle mDeviceHandle = {};	// The device handle.
			};
		}
	}
}
