// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "RenderTarget.h"

namespace DMK
{
	namespace GraphicsCore
	{
		class Display;

		/**
		 * Graphics Device object.
		 */
		class Device : public GObject {
		public:
			Device() {}
			virtual ~Device() {}

			/**
			 * Initialize the device.
			 *
			 * @param pDisplay: The display pointer.
			 */
			virtual void Initialize(Display* pDisplay) {}

			/**
			 * Termiante the device.
			 */
			virtual void Terminate() {}

		public:
			Display* GetDisplay() const { return pDisplay; }

		protected:
			Display* pDisplay = nullptr;
		};
	}
}