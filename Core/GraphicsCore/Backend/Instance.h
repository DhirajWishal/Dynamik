// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Display.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Graphics Instance object.
		 */
		class Instance : public GObject {
		public:
			Instance() {}
			virtual ~Instance() {}

			/**
			 * Initialize the instance.
			 *
			 * @param enableValidation: Whether or not to enable API validation.
			 */
			virtual void Initialize(bool enableValidation) {}

			/**
			 * Terminate the instance.
			 */
			virtual void Terminate() {}

		public:
			bool IsValidationEnabled() const { return mEnableValidation; }

		public:
			/**
			 * Create a new display object.
			 *
			 * @param width: The width of the display.
			 * @param height: The height of the display.
			 * @param pTitle: The title of the display.
			 * @return The created display pointer.
			 */
			virtual Display* CreateDisplay(UI32 width, UI32 height, const char* pTitle) { return nullptr; }

			/**
			 * Destroy a created display.
			 *
			 * @param pDisplay: The display pointer.
			 */
			virtual void DestroyDisplay(Display* pDisplay) {}

		protected:
			bool mEnableValidation = true;
		};
	}
}