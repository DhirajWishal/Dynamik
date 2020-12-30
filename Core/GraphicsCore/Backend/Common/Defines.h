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
		 * Supported anti aliasing bits enum.
		 */
		enum class AntiAliasingSamples {
			ANTI_ALIASING_SAMPLES_1_BIT = BIT_SHIFT(0),
			ANTI_ALIASING_SAMPLES_2_BIT = BIT_SHIFT(1),
			ANTI_ALIASING_SAMPLES_4_BIT = BIT_SHIFT(2),
			ANTI_ALIASING_SAMPLES_8_BIT = BIT_SHIFT(3),
			ANTI_ALIASING_SAMPLES_16_BIT = BIT_SHIFT(4),
			ANTI_ALIASING_SAMPLES_32_BIT = BIT_SHIFT(5),
			ANTI_ALIASING_SAMPLES_64_BIT = BIT_SHIFT(6),
		};
	}
}

#endif // !_DYNAMIK_GRAPHICS_CORE_DEFINES_H
