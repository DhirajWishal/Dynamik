// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GRAPHICS_BACKEND_INSTANCE_H
#define _DYNAMIK_GRAPHICS_BACKEND_INSTANCE_H

#include "Common/GDevice.h"

#include <memory>

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Structure containinf the initialization data requred to initialize the backend.
		 */
		struct BackendInitInfo {
			bool enableValidation = true;	// Enable validation. Default is true.
			bool enableRayTracing = false;	// Enable ray tracing. Default is false.
		};

		/**
		 * Backend instance object for Dynamik.
		 * This object is the main instance object of different graphics backends and is responsible of creating
		 * backend device objects.
		 */
		class BackendInstance : public GObject {
		public:
			/**
			 * Default constructor.
			 */
			BackendInstance() {}

			/**
			 * Default destructor.
			 */
			virtual ~BackendInstance() {}

			/**
			 * Initialize the backend instance.
			 */
			virtual void Initialize(BackendInitInfo intiInfo) {}

			/**
			 * Terminate the backend instance.
			 */
			virtual void Terminate() {}

		public:
			/**
			 * Create a new backend device object.
			 * Since each and every graphics window contains a device attached to it, to create multiple displays
			 * and render object to them, different devices are required.
			 *
			 * @param initInfo: Graphics Device Init Info structure.
			 * @return: Pointer to the created device object.
			 */
			virtual GDevice* CreateDeviceObject(DeviceInitInfo initInfo) { return nullptr; }

			/**
			 * Destroy a created device object.
			 *
			 * @param pDevice: The device object pointer.
			 */
			virtual void DestroyDevice(GDevice* pDevice) {}

		protected:
			BackendInitInfo initInfo = {};	// Initialize information structure.
		};
	}
}

#endif // !_DYNAMIK_GRAPHICS_BACKEND_INSTANCE_H
