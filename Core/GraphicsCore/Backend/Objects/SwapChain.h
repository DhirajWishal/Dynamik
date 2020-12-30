// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GRAPHICS_CORE_SWAP_CHAIN_H
#define _DYNAMIK_GRAPHICS_CORE_SWAP_CHAIN_H

#include "GraphicsCore/Backend/Common/GObject.h"
#include "GraphicsCore/Backend/Common/GDevice.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Swap Chain object.
		 * This object stores all the frames prior to submitting them to the screen buffer.
		 */
		class SwapChain : public GObject {
		public:
			/**
			 * Default constructor.
			 */
			SwapChain() {}

			/**
			 * Default destructor.
			 */
			virtual ~SwapChain() {}

			ViewPort mViewPort = {};	// View Port to which the swap chain belongs to.
		};
	}
}

#endif // !_DYNAMIK_GRAPHICS_CORE_SWAP_CHAIN_H
