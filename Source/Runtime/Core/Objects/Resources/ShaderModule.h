// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_SHADER_MODULE_H
#define _DYNAMIK_SHADER_MODULE_H

#include "Core/Macros/Global.h"
#include "Core/Types/Array.h"

namespace Dynamik
{
	/* Dynamik Shader Locations */
	enum class DMK_API DMKShaderLocation {
		DMK_SHADER_LOCATION_ALL,
		DMK_SHADER_LOCATION_VERTEX,
		DMK_SHADER_LOCATION_TESSELLATION,
		DMK_SHADER_LOCATION_GEOMETRY,
		DMK_SHADER_LOCATION_FRAGMENT,
		DMK_SHADER_LOCATION_COMPUTE,
		DMK_SHADER_LOCATION_ALL_GRAPHICS,

		/* Ray Tracing (Nvidia) */
		DMK_SHADER_LOCATION_RAY_GEN,
		DMK_SHADER_LOCATION_ANY_HIT,
		DMK_SHADER_LOCATION_CLOSEST_HIT,
		DMK_SHADER_LOCATION_MISS,
		DMK_SHADER_LOCATION_INTERSECTION,
		DMK_SHADER_LOCATION_CALLABLE,

		DMK_SHADER_LOCATION_TASK,
		DMK_SHADER_LOCATION_MESH,
	};

	/* Dynamik Shader Input Attribute */
	struct DMK_API DMKShaderInputAttribute {
		DMKShaderInputAttribute() = default;
		virtual ~DMKShaderInputAttribute() = default;

		DMKDataType dataType = DMKDataType::DMK_DATA_TYPE_VEC3;
		UI32 dataCount = 1;     /* Number of elements of data which is sent. Used for sending arrays. */
	};

	/* Shader Code Type */
	enum class DMK_API DMKShaderCodeType {
		DMK_SHADER_CODE_TYPE_GLSL,
		DMK_SHADER_CODE_TYPE_HLSL,
		DMK_SHADER_CODE_TYPE_SPIRV,
	};

	/*
	 Shader module for the Dynamik Engine
	*/
    class DMK_API DMKShaderModule {
    public:
		DMKShaderModule() = default;
        DMKShaderModule(const DMKShaderLocation& sLocation, const DMKShaderCodeType& sType) : location(sLocation), codeType(sType) {}
        ~DMKShaderModule() = default;

		/*
		 Load shader code from file.
		*/
		void loadCode(const STRING& path);

		/*
		 Set shader location.

		 @param location: Shader location.
		*/
		void setLocation(const DMKShaderLocation& location);

	public:
        ARRAY<UI32> shaderCode;
		DMKShaderLocation location = DMKShaderLocation::DMK_SHADER_LOCATION_ALL;
		DMKShaderCodeType codeType = DMKShaderCodeType::DMK_SHADER_CODE_TYPE_GLSL;
    };
}

#endif // !_DYNAMIK_SHADER_H
