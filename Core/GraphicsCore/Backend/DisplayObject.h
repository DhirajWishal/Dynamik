// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Inputs/InputCenter.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Display Object.
		 * This object manages a single display/ window object. These displays are created by the individual backends
		 * and
		 */
		class DisplayObject {
		public:
			DisplayObject() {}
			virtual ~DisplayObject() {}

			virtual void Initialize(UI32 width, UI32 height, const char* pTitle, Inputs::InputCenter* pInputCenter = nullptr) {}
			virtual void Terminate() {}
		};
	}
}