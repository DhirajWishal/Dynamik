// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_SHADER_FACTORY_H
#define _DYNAMIK_SHADER_FACTORY_H

/*
 Author:	Dhiraj Wishal
 Date:		22/06/2020
*/
#include "ShaderModule.h"

namespace Dynamik
{
	/* SINGLETON
	 Dynamik Shader Factory
	*/
	class DMK_API DMKShaderFactory {
		DMKShaderFactory() {}
		~DMKShaderFactory() {}

		static DMKShaderFactory instance;

	public:
		DMKShaderFactory(const DMKShaderFactory&) = delete;
		DMKShaderFactory(DMKShaderFactory&&) = delete;
		DMKShaderFactory& operator=(const DMKShaderFactory&) = delete;
		DMKShaderFactory& operator=(DMKShaderFactory&&) = delete;

	public:
		/*
		 This function is used internally.
		 Set the working directory of the executable. 

		 @param path: Directory.
		*/
		static void setWorkingDirectory(const STRING& path);

	public:
		/*
		 Create a shader resource map by scanning the shader code.

		 @warn: Currently works only with SPIR-V format.
		 @param path: Shader path.
		 @param location: Shader location.
		*/
		static DMKShaderResourceLayout createResourceMap(const STRING& path, const DMKShaderLocation& location);

	public:
		/*
		 Create a basic shader module from external file.

		 @param filePath: File path of the shader code.
		 @param location: Shader location (Vertex, Tessellation, Geometry, Fragment).
		 @param resourceLayout: Shader resource map.
		 @param codeType: Type of the code (language: GLSL, HLSL, SPIRV).
		*/
		static DMKShaderModule createModule(const STRING& filePath, const DMKShaderLocation& location, const DMKShaderResourceLayout& resourceLayout, const DMKShaderCodeType& codeType);

	private:
		STRING myWorkingDir = DMK_TEXT("");
	};
}

#endif // !_DYNAMIK_SHADER_FACTORY_H
