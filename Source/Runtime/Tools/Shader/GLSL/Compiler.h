// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GLSL_COMPILER_H
#define _DYNAMIK_GLSL_COMPILER_H

#include "Core/Types/Array.h"
#include "Core/Objects/Resources/ShaderModule.h"

namespace Tools
{
	/*
	 GLSL shader compiler
	*/
	class DMK_API GLSLCompiler {
	public:
		GLSLCompiler() {}
		~GLSLCompiler() {}

		/*
		 GLSL code to SPIRV code converter.

		 @param file: GLSL file path.
		 @param location: Shader code location.
		 @param codeType: The input code type.
		*/
		DMKShaderModule getSPIRV(const STRING& file, DMKShaderLocation location);
	};
}

#endif // !_DYNAMIK_GLSL_COMPILER_H
