#pragma once
#ifndef _DYNAMIK_SHADER_MODULE_H
#define _DYNAMIK_SHADER_MODULE_H

/*
 Author:    Dhiraj Wishal
 Date:      29/05/2020
*/
#include "Macros/Global.h"
#include "Types/Array.h"
#include "Primitives.h"

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

	/* Shader Code Type */
	enum class DMK_API DMKShaderCodeType {
		DMK_SHADER_CODE_TYPE_GLSL,
		DMK_SHADER_CODE_TYPE_HLSL,
		DMK_SHADER_CODE_TYPE_SPIRV,
	};

	/*
	 Shader Resources
	*/
	struct DMK_API DMKShaderResource {
		DMKUniformType type = DMKUniformType::DMK_UNIFORM_TYPE_UNIFORM_BUFFER;
		UI32 binding = 0;
		UI32 offset = 0;
	};

	/*
	 Dynamik Shader Layout
	 This defines the resource components in a shader.
	 Mainly this defines the uniform bindings and sampler bindings.
	*/
	struct DMK_API DMKShaderLayout {
		ARRAY<DMKShaderResource> resources;
	};

	/*
	 Shader module for the Dynamik Engine
	*/
    class DMK_API DMKShaderModule {
    public:
        DMKShaderModule() {}
        DMKShaderModule(const DMKShaderLocation& sLocation, const DMKShaderCodeType& sType) : location(sLocation), codeType(sType) {}
        virtual ~DMKShaderModule() {}

		virtual void loadCode(const STRING& path);

		void addResource(DMKUniformType type, UI32 binding, UI32 offset = 0);

	public:
        ARRAY<CHR> shaderCode;
		DMKShaderLayout layout;
		DMKShaderLocation location = DMKShaderLocation::DMK_SHADER_LOCATION_ALL;
		DMKShaderCodeType codeType = DMKShaderCodeType::DMK_SHADER_CODE_TYPE_GLSL;
    };
}

#endif // !_DYNAMIK_SHADER_H
