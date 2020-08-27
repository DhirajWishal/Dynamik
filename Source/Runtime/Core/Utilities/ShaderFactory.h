// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_SHADER_FACTORY_H
#define _DYNAMIK_SHADER_FACTORY_H

#include "Core/Objects/Resources/ShaderModule.h"

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
	 Create a basic shader module from external file.

	 @param filePath: File path of the shader code.
	 @param location: Shader location (Vertex, Tessellation, Geometry, Fragment).
	 @param codeType: Type of the code (language: GLSL, HLSL, SPIRV).
	*/
	static DMKShaderModule createModule(const STRING& filePath, const DMKShaderLocation& location, const DMKShaderCodeType& codeType);

private:
	STRING myWorkingDir = TEXT("");
};

#endif // !_DYNAMIK_SHADER_FACTORY_H
