// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_CONTROL_HEADER_H
#define _DYNAMIK_VULKAN_CONTROL_HEADER_H

/*
 Author:    Dhiraj Wishal
 Date:      24/05/2020
*/
#include "Types/DataTypes.h"

#define MAX_FRAMES_IN_FLIGHT 2

namespace Dynamik
{
    namespace Backend 
	{
		static B1 pushDescriptorsSupported = false;
		static B1 checkpointsSupported = false;
		static B1 meshShadingSupported = false;

		inline B1 VSYNC = true;

		//#define USE_SHADER_TESSELLATION
		//#define USE_SHADER_GEOMETRY
    }
}

#endif // !_DYNAMIK_VULKAN_CONTROL_HEADER_H
