// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GObject.h"
#include "Core/Macros/Global.h"
#include "Core/Maths/Vector/Vector2.h"

#define DMK_RT_SWAP_CHAIN_ATTACHMENT		BIT_SHIFT(0)
#define DMK_RT_COLOR_BUFFER_ATTACHMENT		BIT_SHIFT(1)
#define DMK_RT_DEPTH_BUFFER_ATTACHMENT		BIT_SHIFT(2)
#define DMK_RT_RAY_TRACER_ATTACHMENT		BIT_SHIFT(3)
#define DMK_RT_BUFFER_COUNT_MAX				std::numeric_limits<UI32>::max()

namespace DMK
{
	namespace GraphicsCore
	{
		class Device;

		/**
		 * Render Target Type enum.
		 * This defines the type of the render target.
		 */
		enum class RenderTargetType : UI8 {
			UNDEFINED = 0,

			SCREEN_BOUND_2D = DMK_RT_SWAP_CHAIN_ATTACHMENT | DMK_RT_COLOR_BUFFER_ATTACHMENT,
			SCREEN_BOUND_3D = DMK_RT_SWAP_CHAIN_ATTACHMENT | DMK_RT_COLOR_BUFFER_ATTACHMENT | DMK_RT_DEPTH_BUFFER_ATTACHMENT,
			SCREEN_BOUND_RAY_TRACED = DMK_RT_SWAP_CHAIN_ATTACHMENT | DMK_RT_RAY_TRACER_ATTACHMENT,

			OFF_SCREEN_2D = DMK_RT_COLOR_BUFFER_ATTACHMENT,
			OFF_SCREEN_3D = DMK_RT_COLOR_BUFFER_ATTACHMENT | DMK_RT_DEPTH_BUFFER_ATTACHMENT,
			OFF_SCREEN_RAY_TRACED = DMK_RT_RAY_TRACER_ATTACHMENT
		};

		/**
		 * Render Target base object.
		 * Render targets are where the render data are drawn to.
		 */
		class RenderTarget : public GObject {
		public:
			RenderTarget(RenderTargetType type) : mType(type) {}
			virtual ~RenderTarget() {}

			/**
			 * Initialize the render target.
			 *
			 * By default the buffer count is set to 0. If the buffer count is DMK_RT_BUFFER_COUNT_MAX, the maximum
			 * supported buffer count is set. If the count is 0, the minimum supported is set. We recommend keeping
			 * it at 0 for screen bound RTs and 1 or 2 for off screen RTs.
			 *
			 * @param pDevice: The device pointer.
			 * @param extent: The extent of the render target area.
			 * @param bufferCount: The number of frame buffers. Default is 0.
			 */
			virtual void Initialize(Device* pDevice, Vector2 extent, UI32 bufferCount = 0) {}

			/**
			 * Terminate the render target.
			 */
			virtual void Terminate() {}

		public:
			Vector2 GetExtent() const { return mExtent; }
			UI32 GetBufferCount() const { return mBufferCount; }
			RenderTargetType GetType() const { return mType; }

		protected:
			Vector2 mExtent = Vector2::ZeroAll;
			UI32 mBufferCount = 0;

			RenderTargetType mType = RenderTargetType::UNDEFINED;
		};
	}
}