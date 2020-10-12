// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GRAPHICS_CORE_DEFINES_H
#define _DYNAMIK_GRAPHICS_CORE_DEFINES_H

#include "Core/Macros/Global.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Graphics Backend API for the Dynamik Engine.
		 * This enum contains all the available backend the engine contains.
		 */
		enum class DMK_API BackendAPI {
			BACKEND_API_VULKAN,
			BACKEND_API_DIRECTX_12,
			BACKEND_API_WEB_GPU,
		};

		/**
		 * Anti aliasing samples.
		 * Samples are represented as bits.
		 */
		enum class DMK_API AntiAliasingSample {
			ANTI_ALIASING_SAMPLE_1 = BIT_SHIFT(0),
			ANTI_ALIASING_SAMPLE_2 = BIT_SHIFT(1),
			ANTI_ALIASING_SAMPLE_4 = BIT_SHIFT(2),
			ANTI_ALIASING_SAMPLE_8 = BIT_SHIFT(3),
			ANTI_ALIASING_SAMPLE_16 = BIT_SHIFT(4),
			ANTI_ALIASING_SAMPLE_32 = BIT_SHIFT(5),
			ANTI_ALIASING_SAMPLE_64 = BIT_SHIFT(6),
		};

		/**
		 * Graphics memory properties.
		 */
		enum class DMK_API MemoryProperty {
			MEMORY_PROPERTY_DEVICE_LOCAL = BIT_SHIFT(0),
			MEMORY_PROPERTY_HOST_VISIBLE = BIT_SHIFT(1),
			MEMORY_PROPERTY_HOST_COHERENT = BIT_SHIFT(2),
			MEMORY_PROPERTY_HOST_CACHED = BIT_SHIFT(3),
			MEMORY_PROPERTY_PROTECTED = BIT_SHIFT(5),
		};
	}
}

#endif // !_DYNAMIK_GRAPHICS_CORE_DEFINES_H
