// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Buffer.h"

namespace DMK
{
	namespace GraphicsCore
	{
		class Instance;

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
		 * Device object.
		 * This object is the base class for all the Graphics backend devices and represents a single GPU. The
		 * device is the owner of a single display/ window. This means that events which are submitted to a window
		 * is handled by the device.
		 */
		class Device : public GraphicsObject {
		public:
			Device() {}
			virtual ~Device() {}

			/**
			 * Initialize the device.
			 *
			 * @param initInfo: The initialization information.
			 * @param pInstance: The instance pointer.
			 */
			virtual void Initialize(const DeviceInitInfo& initInfo, Instance* pInstance) {}

			/**
			 * Terminate the device.
			 */
			virtual void Terminate() {}

		public:
			/**
			 * Create a buffer object.
			 *
			 * @param type: The type of the buffer.
			 * @param size: The size of the buffer in bytes.
			 * @return The buffer reference.
			 */
			virtual BufferRef CreateBuffer(BufferType type, UI64 size) { return BufferRef(); }

			/**
			 * Get the buffer pointer from the device.
			 * 
			 * @param ref: The buffer reference.
			 * @return The buffer pointer.
			 */
			virtual Buffer* GetBuffer(const BufferRef& ref) { return nullptr; }

			/**
			 * Terminate the buffer.
			 *
			 * @param ref: The buffer ref.
			 */
			virtual void TerminateBuffer(const BufferRef& ref) {}

		public:

		};

		typedef UI64 DeviceHandle;
	}
}