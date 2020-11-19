// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GRAPHICS_CORE_DEVICE_HANDLE_H
#define _DYNAMIK_GRAPHICS_CORE_DEVICE_HANDLE_H

#include "Core/Types/DataTypes.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Device Init Info structure.
		 * This structure defines how a device should be created.
		 */
		struct DeviceInitInfo {
			const wchar* pWindowTitle = TEXT("Dynamik Engine");	// Window title.
			const wchar* pWindowIconPath = TEXT("");	// Window icon path.

			UI32 windowWidth = 1280;	// Window width.
			UI32 windowHeight = 720;	// Window height.

			bool tryEnableRayTracing = false;	// Try and enable ray tracing. 
			bool enableValidation = true;	// Enable validation for the device.
		};

		/**
		 * Graphics Device Handle object.
		 * This object stores basic information about the graphics device thats been used.
		 */
		class DeviceHandle {
		public:
			/**
			 * Default constructor.
			 */
			DeviceHandle() = default;

			/**
			 * Construct the device handle using the ID.
			 *
			 * @param ID: The device ID.
			 */
			DeviceHandle(const UI64& ID) : mDeviceID(ID) {}

			/**
			 * Default destructor.
			 */
			~DeviceHandle() {}

			UI64 mDeviceID = 0;	// Device ID of the API.
		};
	}
}

#endif // !_DYNAMIK_GRAPHICS_CORE_DEVICE_HANDLE_H
