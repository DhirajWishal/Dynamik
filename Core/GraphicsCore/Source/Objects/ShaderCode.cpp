// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "GraphicsCore/Objects/ShaderCode.h"
#include "Core/ErrorHandler/Logger.h"

#include "ShaderTools/SPIR-V/Reflection.h"

#include <fstream>

namespace DMK
{
	namespace GraphicsCore
	{
		void ShaderCode::LoadCode(const char* pAsset, ShaderCodeType mType, ShaderLocation mLocation)
		{
			this->mType = mType;
			this->mLocation = mLocation;

			// Open the required file.
			std::ifstream file(pAsset, std::ios::ate | std::ios::binary);

			// Check if the shader file was loaded.
			if (!file.is_open())
			{
				Logger::LogError(TEXT("Failed to load the requested shader code! Make sure that the shader file exists and the provided path is valid."));
				return;
			}

			// Load data to the vector.
			I64 fileSize = (I64)file.tellg();
			mShaderCode.resize(fileSize);
			file.seekg(0);
			file.read(reinterpret_cast<char*>(mShaderCode.data()), fileSize);

			// Close the shader file.
			file.close();
		}

		void ShaderCode::PerformReflection()
		{
			// Create the reflection digest object.
			ShaderTools::ReflectionDigest mReflectionDigest = {};

			switch (mType)
			{
			case DMK::GraphicsCore::ShaderCodeType::UNDEFINED:
				break;
			case DMK::GraphicsCore::ShaderCodeType::SPIR_V:
			{
				// Create and perform SPIR-V Reflection.
				ShaderTools::SPIRVReflection mReflection;
				mReflectionDigest = std::move(mReflection.Reflect(*this));
				break;
			}
			case DMK::GraphicsCore::ShaderCodeType::GLSL:
				break;
			case DMK::GraphicsCore::ShaderCodeType::HLSL:
				break;
			default:
				break;
			}

			this->mUniforms = std::move(mReflectionDigest.mUniforms);
			this->mInputAttributes = std::move(mReflectionDigest.mInputAttributes);
			this->mOutputAttributes = std::move(mReflectionDigest.mOutputAttributes);
		}
	}
}