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
			/**
			 * Create a new render target.
			 *
			 * By default the buffer count is set to 0. If the buffer count is DMK_RT_BUFFER_COUNT_MAX, the maximum
			 * supported buffer count is set. If the count is 0, the minimum supported is set. We recommend keeping
			 * it at 0 for screen bound RTs and 1 or 2 for off screen RTs.
			 *
			 * @param pDevice: The device pointer.
			 * @param extent: The extent of the render target area.
			 * @param bufferCount: The number of frame buffers. Default is 0.
			 * @return The created render target pointer.
			 */
			virtual RenderTarget* CreateRenderTarget(RenderTargetType type, Vector2 extent, UI32 bufferCount = 0) { return nullptr; }

			/**
			 * Destroy a created render target.
			 * 
			 * @param pRenderTarget: The render target pointer to be terminated.
			 */
			virtual void DestroyRenderTarget(RenderTarget* pRenderTarget) {}

		public:
			Display* GetDisplay() const { return pDisplay; }

		protected:
			Display* pDisplay = nullptr;
		};
	}
}