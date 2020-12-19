// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Types/DataTypes.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Instance Handle type.
		 */
		typedef UI8 InstanceHandle;

		/**
		 * Device Handle type.
		 */
		typedef UI8 DeviceHandle;

		/**
		 * Display Handle type.
		 */
		typedef UI8 DisplayHandle;

		/**
		 * Image Handle type.
		 */
		typedef UI32 ImageHandle;

		/**
		 * Render Target Type enum.
		 */
		enum class RenderTargetType : UI8 {
			UNDEFINED,

			SCREEN_BOUND_2D,
			SCREEN_BOUND_3D,
			SCREEN_BOUND_RAY_TRACING,

			OFF_SCREEN_2D,
			OFF_SCREEN_3D,
			OFF_SCREEN_RAY_TRACING
		};

		/**
		 * Render Target Handle structure.
		 */
		struct RenderTargetHandle {
			RenderTargetHandle() = default;
			RenderTargetHandle(UI64 handle, RenderTargetType type) : mHandle(handle), mType(type) {}

			UI64 mHandle = 0;
			RenderTargetType mType = RenderTargetType::UNDEFINED;
		};

		/**
		 * Buffer Type enum.
		 */
		enum class BufferType : UI8 {
			UNDEFINED,
			VERTEX,
			INDEX,
			UNIFORM,
			STAGGING,
			SCRATCH,
			TOP_LEVEL_ACCELERATION,
			BOTTOM_LEVEL_ACCELERATION,
		};

		/**
		 * Buffer Handle structure.
		 */
		struct BufferHandle {
			BufferHandle() = default;
			BufferHandle(UI32 handle, BufferType type) : mHandle(handle), mType(type) {}

			UI32 mHandle = 0;
			BufferType mType = BufferType::UNDEFINED;
		};
	}
}