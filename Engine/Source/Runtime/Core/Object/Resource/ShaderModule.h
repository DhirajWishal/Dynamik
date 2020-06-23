// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

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
	/* Shader Code Type */
	enum class DMK_API DMKShaderCodeType {
		DMK_SHADER_CODE_TYPE_GLSL,
		DMK_SHADER_CODE_TYPE_HLSL,
		DMK_SHADER_CODE_TYPE_SPIRV,
	};

	/*
	 Shader resource map
	 This describes all the resources and inputs the shader code needs.
	*/
	struct DMK_API DMKShaderResourceMap {
		ARRAY<DMKUniformDescription> uniforms;
		ARRAY<DMKShaderInputAttribute> inputAttributes;
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
	 Shader module for the Dynamik Engine
	*/
    class DMK_API DMKShaderModule {
    public:
        DMKShaderModule() {}
        DMKShaderModule(const DMKShaderLocation& sLocation, const DMKShaderCodeType& sType) : location(sLocation), codeType(sType) {}
        ~DMKShaderModule() {}

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
		 Set shader resource map.

		 @param resourceMap: Shader resource map.
		*/
		void setResourceMap(const DMKShaderResourceMap& resourceMap);

		/*
		 Add input attribute resource to the map.
		*/
		void addResource(const DMKShaderInputAttribute& inputAttribute);

		/*
		 Add uniform description resource to the map.
		*/
		void addResource(const DMKUniformDescription& uniformDescription);

		/*
		 Get the stored resource map.
		*/
		const DMKShaderResourceMap getResourceMap() const;

	public:
		DMKShaderResourceMap resourceMap;
        ARRAY<UI32> shaderCode;
		DMKShaderLocation location = DMKShaderLocation::DMK_SHADER_LOCATION_ALL;
		DMKShaderCodeType codeType = DMKShaderCodeType::DMK_SHADER_CODE_TYPE_GLSL;
    };
}

#endif // !_DYNAMIK_SHADER_H
