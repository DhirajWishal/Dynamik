// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_SHADER_MODULE_H
#define _DYNAMIK_SHADER_MODULE_H

/*
 Author:    Dhiraj Wishal
 Date:      29/05/2020
*/
#include "Core/Macros/Global.h"
#include "Core/Types/Array.h"
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
	struct DMK_API DMKShaderResourceLayout {
		ARRAY<DMKUniformDescription> uniforms;
		ARRAY<DMKShaderInputAttribute> inputAttributes;
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
			 
		/*
		 Set shader resource map.

		 @param resourceLayout: Shader resource map.
		*/
		void setResourceLayout(const DMKShaderResourceLayout& resourceLayout);

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
		const DMKShaderResourceLayout getResourceLayout() const;

	public:
		DMKShaderResourceLayout resourceLayout;
        ARRAY<UI32> shaderCode;
		DMKShaderLocation location = DMKShaderLocation::DMK_SHADER_LOCATION_ALL;
		DMKShaderCodeType codeType = DMKShaderCodeType::DMK_SHADER_CODE_TYPE_GLSL;
    };
}

#endif // !_DYNAMIK_SHADER_H
