// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_SHADER_MODULE_H
#define _DYNAMIK_SHADER_MODULE_H

#include "Core/Types/Array.h"
#include "UniformBuffer.h"

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
		DMKShaderInputAttribute(DMKFormat format, UI32 dataCount) 
			: dataFormat(format), dataCount(dataCount) {}
		virtual ~DMKShaderInputAttribute() = default;

		DMKFormat dataFormat = DMKFormat::DMK_FORMAT_UNDEFINED;
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

	 Shader uniforms (only the uniforms which the users are allowed to submit data from) are managed by the
	 shader module itself. Users are required to provide the shader module with the uniforms it contains
	 and creating and updating uniform buffers are required to be done by the user. Initialization, 
	 termination and maintenance is done by the module.
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

		/*
		 Add an uniform to the shader.

		 @param uniform: The uniform buffer object.
		*/
		void addUniform(const DMKUniformBuffer& uniform);

		/*
		 Get a uniform buffer object at a given index.

		 @param index: The index of the required index buffer;
		*/
		DMKUniformBuffer& getUniform(I64 index);

		/*
		 Get all the uniforms of the current shader.
		*/
		ARRAY<DMKUniformBuffer>& getUniforms();

		/*
		 This defines the inputs which the shader requires. 
		 This is only needed if the shader location is Vertex.

		 @param attribute: The input attribute.
		*/
		void addInputAttribute(const DMKShaderInputAttribute& attribute);

		/*
		 Set all the input attributes.

		 @param attributes: All the input attributes..
		*/
		void setInputAttributes(ARRAY<DMKShaderInputAttribute> attributes);

		/*
		 Get a stored shader attribute.

		 @param index: The index of the attribute.
		*/
		DMKShaderInputAttribute getAttribute(I64 index) const;

		/*
		 Get the whole attribute array.
		*/
		ARRAY<DMKShaderInputAttribute>& getAttributes();

	public:
		ARRAY<DMKUniformBuffer> uniforms;
		ARRAY<DMKShaderInputAttribute> inputAttributes;
        ARRAY<UI32> shaderCode;
		DMKShaderLocation location = DMKShaderLocation::DMK_SHADER_LOCATION_ALL;
		DMKShaderCodeType codeType = DMKShaderCodeType::DMK_SHADER_CODE_TYPE_GLSL;
    };
}

#endif // !_DYNAMIK_SHADER_H
