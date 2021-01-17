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

		protected:
			bool mEnableValidation = true;
		};
	}
}