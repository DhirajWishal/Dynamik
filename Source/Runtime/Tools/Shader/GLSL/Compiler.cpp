// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "Compiler.h"

#include "Services/RuntimeSystems/ToolsRegistry.h"
#include "Core/Utilities/ShaderFactory.h"
#include <sstream>
#include <Windows.h>

namespace Dynamik
{
	namespace Tools
	{
		DMKShaderModule GLSLCompiler::getSPIRV(const STRING& file, DMKShaderLocation location)
		{
			std::stringstream stream;

			STRING fileCommand = "\"";
			fileCommand.append(file);
			fileCommand.append("\"");

			STRING outputCommand = "\"";
			outputCommand.append(file + ".spv\"");

			stream << " -V " << fileCommand << " -o " << outputCommand;

			/* Create the process */
			{
				STARTUPINFOA si;
				PROCESS_INFORMATION pi;

				ZeroMemory(&si, sizeof(si));
				si.cb = sizeof(si);
				ZeroMemory(&pi, sizeof(pi));

				// start the program up
				auto check = CreateProcessA
				(
					DMKToolsRegistry::getTool("GLSL_VALIDATOR_EXE").c_str(),
					(CPTR)stream.str().c_str(),
					NULL,
					NULL,
					FALSE,
					NULL,
					NULL,
					NULL,
					&si,
					&pi
				);

				CloseHandle(pi.hProcess);
				CloseHandle(pi.hThread);

				/* Wait for a second till the shader is compiled. */
				Sleep(500);
			}

			return DMKShaderFactory::createModule(file + STRING(".spv"), location, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV);
		}
	}
}
