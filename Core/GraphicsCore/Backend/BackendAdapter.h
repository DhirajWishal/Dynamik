// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Device.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Backend Adapter class.
		 * This object is the base class for the backend instances and is used by the graphics engine to create
		 * GPU bound objects.
		 */
		class BackendAdapter {
		public:
			BackendAdapter() {}
			virtual ~BackendAdapter() {}

			/**
			 * Initialize the backend adapter.
			 *
			 * @param enableValidation: Whether or not to enable API validation.
			 */
			virtual void Initialize(bool enableValidation) {}

			/**
			 * Terminate the backend adapter.
			 */
			virtual void Terminate() {}

		public:
			/**
			 * Create a new graphcis device.
			 *
			 * @param tryEnableRayTracing: Try and enable ray tracing if available. Default is false. If it is requested 
			 *	but unavailable, the device uses compute shaders to compute ray tracing.
			 * @param pInputCenter: The input center pointer. Default is nullptr. Once an input center is attached,
			 *	inputs can be streamed from the device window to the application.
			 */
			virtual DeviceHandle CreateDevice(bool tryEnableRayTracing = false, Inputs::InputCenter* pInputCenter = nullptr) { return DeviceHandle(); }

		protected:
			DeviceHandle mDefaultDevice = {};

			bool mEnableValidation = true;
		};
	}
}