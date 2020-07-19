// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "Compiler.h"

#include "Services/RuntimeSystems/ToolsRegistry.h"
#include <sstream>

namespace Dynamik
{
	ARRAY<UI32> GLSLCompiler::getSPIRV(const STRING& file, DMKShaderLocation location, DMKShaderCodeType codeType)
	{
		std::stringstream stream;
		stream << DMKToolsRegistry::getTool("GLSL_VALIDATOR_EXE") << " -V " << file << " -o " << (file + ".spv");

		system(stream.str().c_str());

		return ARRAY<UI32>();
	}
}
