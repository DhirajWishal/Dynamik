// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "GraphicsCore/Backend/Common/ShaderModule.h"
#include "Core/ErrorHandler/Logger.h"

#include <fstream>

namespace DMK
{
	namespace GraphicsCore
	{
		void ShaderModule::Initialize(const wchar* pAsset, ShaderLocation location)
		{
			// Open the shader code file.
			std::wifstream inputFile(pAsset, std::ios::binary, std::ios::ate);

			// Check if the shader code is opened.
			if (!inputFile.is_open())
			{
				Logger::LogError(TEXT("Failed to open the required shader module!"));
				return;
			}

			// Load the shader code from the file to a vector.
			UI64 fileSize = static_cast<UI32>(inputFile.tellg());
			std::vector<UI32> shaderCode(fileSize);
			inputFile.seekg(0);
			inputFile.read(reinterpret_cast<wchar*>(shaderCode.data()), fileSize);

			// Close the input file.
			inputFile.close();

			// Initialize the shader code.
			InitializeShaderModule(GetBackendData(), shaderCode);
		}

		void ShaderModule::Terminate()
		{
			TerminateShaderModule(GetBackendData());
		}
	}
}