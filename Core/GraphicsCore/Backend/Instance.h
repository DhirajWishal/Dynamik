// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Device.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Instance object.
		 * This object is the base class for all the Graphics Backend Instances.
		 */
		class Instance : public GraphicsObject {
		public:
			Instance() {}
			virtual ~Instance() {}

			/**
			 * Initialize the instance.
			 *
			 * @param enableValidation: Boolean whether to enable API validation.
			 */
			virtual void Initialize(bool enableValidation) {}

			/**
			 * Terminate the instance.
			 */
			virtual void Terminate() {}

			/**
			 * Create a new device.
			 *
			 * @param initInfo: The device initialization information.
			 */
			virtual Device* CreateDevice(const DeviceInitInfo& initInfo) { return 0; }
		};
	}
}