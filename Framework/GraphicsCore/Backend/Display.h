// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Device.h"
#include "Inputs/InputCenter.h"

namespace DMK
{
	namespace GraphicsCore
	{
		class Instance;

		/**
		 * Graphcis Display object.
		 */
		class Display : public GObject {
		public:
			Display() {}
			virtual ~Display() {}

			/**
			 * Initialize the display.
			 *
			 * @param pInstance: The instance pointer.
			 * @param width: The display width.
			 * @param height: The height of the display.
			 * @param pTitle: The display title.
			 */
			virtual void Initialize(Instance* pInstance, UI32 width, UI32 height, const char* pTitle) {}

			/**
			 * Terminate the display.
			 */
			virtual void Terminate() {}

		public:
			Instance* GetInstance() const { return pInstance; }
			Inputs::InputCenter* GetInputCenter() const { return const_cast<Inputs::InputCenter*>(&mInputCenter); }

		protected:
			Instance* pInstance = nullptr;
			Inputs::InputCenter mInputCenter = {};
		};
	}
}