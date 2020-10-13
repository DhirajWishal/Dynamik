// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDER_SETTINGS_H
#define _DYNAMIK_RENDER_SETTINGS_H

/*
 This header contains global renderer settings.
*/
#include "Core/Macros/Global.h"

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

/* Rendering API */
enum class DMK_API DMKRenderingAPI {
	DMK_RENDERING_API_NONE,
	DMK_RENDERING_API_VULKAN,
	DMK_RENDERING_API_DIRECTX,
	DMK_RENDERING_API_OPENGL,
};

/*
 Dynamik Renderer Description 
 This defines how the renderer needs to be initialized. 
*/
struct DMK_API DMKRendererDescription {
	STRING applicationName = TEXT("");

	DMKRenderingAPI renderingAPI = DMKRenderingAPI::DMK_RENDERING_API_VULKAN;
	DMKSampleCount msaaSampleCount = DMKSampleCount::DMK_SAMPLE_COUNT_64_BIT;

	bool enableRayTracing = false;
	bool enableValidation = true;
};

#endif // !_DYNAMIK_RENDER_SETTINGS_H
