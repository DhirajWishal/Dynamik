// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDER_CORE_TYPE_DEFINES_H
#define _DYNAMIK_RENDER_CORE_TYPE_DEFINES_H

/*
 Author:    Dhiraj Wishal
 Date:      26/05/2020

 This file contains all the necessary type defines to create a rendering core. Since the engine supports Vulkan
 by default, these types are directly Vulkan compatible.
*/
#include "Macros/Global.h"

namespace Dynamik
{
	/* Sample Count */
	enum DMK_API DMKSampleCount {
		DMK_SAMPLE_COUNT_1_BIT = BIT_SHIFT(0),
		DMK_SAMPLE_COUNT_2_BIT = BIT_SHIFT(1),
		DMK_SAMPLE_COUNT_4_BIT = BIT_SHIFT(2),
		DMK_SAMPLE_COUNT_8_BIT = BIT_SHIFT(3),
		DMK_SAMPLE_COUNT_16_BIT = BIT_SHIFT(4),
		DMK_SAMPLE_COUNT_32_BIT = BIT_SHIFT(5),
		DMK_SAMPLE_COUNT_64_BIT = BIT_SHIFT(6),
	};

	/*
	 Dynamik Render Pipeline
	 This defines how the renderer renders a given scene.
	*/
	enum class DMK_API DMKRenderPipeline {
		DMK_RENDER_PIPELINE_DEBUG,
		DMK_RENDER_PIPELINE_PBR,
	};
}

#endif // !_DYNAMIK_RENDER_CORE_TYPE_DEFINES_H
