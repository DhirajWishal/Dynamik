// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_CONTROL_HEADER_H
#define _DYNAMIK_VULKAN_CONTROL_HEADER_H

#include "Core/Types/DataTypes.h"

#define MAX_FRAMES_IN_FLIGHT 2

namespace Backend
{
	static bool pushDescriptorsSupported = false;
	static bool checkpointsSupported = false;
	static bool meshShadingSupported = false;

	inline bool VSYNC = true;

	//#define USE_SHADER_TESSELLATION
	//#define USE_SHADER_GEOMETRY
}

#endif // !_DYNAMIK_VULKAN_CONTROL_HEADER_H
