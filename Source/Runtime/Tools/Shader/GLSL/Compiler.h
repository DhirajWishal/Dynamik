// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GLSL_COMPILER_H
#define _DYNAMIK_GLSL_COMPILER_H

#include "Core/Types/Array.h"
#include "Core/Objects/Resources/ShaderModule.h"

namespace Dynamik
{
	/*
	 GLSL shader compiler
	*/
	class DMK_API GLSLCompiler {
	public:
		GLSLCompiler() {}
		~GLSLCompiler() {}

		ARRAY<UI32> getSPIRV(const STRING& file, DMKShaderLocation location, DMKShaderCodeType codeType);
	};
}

#endif // !_DYNAMIK_GLSL_COMPILER_H
