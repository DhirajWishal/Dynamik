// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDER_SETTINGS_H
#define _DYNAMIK_RENDER_SETTINGS_H

/*
 This header contains global renderer settings.
*/
#include "Core/Macros/Global.h"

/* Rendering API */
enum class DMK_API DMKRenderingAPI {
	DMK_RENDERING_API_NONE,
	DMK_RENDERING_API_VULKAN,
	DMK_RENDERING_API_DIRECTX,
	DMK_RENDERING_API_OPENGL,
};

#endif // !_DYNAMIK_RENDER_SETTINGS_H
