// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "GraphicsCore/Objects/ShaderCode.h"
#include "Core/ErrorHandler/Logger.h"
#include "Core/Hash/Hasher.h"

#include "ShaderTools/SPIR-V/Reflection.h"

#include <fstream>

namespace DMK
{
	namespace GraphicsCore
	{
		ShaderCode::ShaderCode(const ShaderCode& other)
			: mType(other.mType), mLocation(other.mLocation), mInputAttributes(other.mInputAttributes),
			mOutputAttributes(other.mOutputAttributes), mShaderCode(other.mShaderCode), mUniforms(other.mUniforms)
		{
		}

		ShaderCode::ShaderCode(ShaderCode&& other) noexcept
			: mType(other.mType), mLocation(other.mLocation), mInputAttributes(std::move(other.mInputAttributes)),
			mOutputAttributes(std::move(other.mOutputAttributes)), mShaderCode(std::move(other.mShaderCode)), mUniforms(std::move(other.mUniforms))
		{
		}

		UI64 ShaderCode::Hash() const
		{
			return Hasher::GetHash(mShaderCode.data(), mShaderCode.size() * sizeof(UI32));
		}

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

			// Perform code reflection.
			PerformReflection();
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

		ShaderCode& ShaderCode::operator=(const ShaderCode& other)
		{
			this->mType = other.mType;
			this->mLocation = other.mLocation;
			this->mInputAttributes = other.mInputAttributes;
			this->mOutputAttributes = other.mOutputAttributes;
			this->mShaderCode = other.mShaderCode;
			this->mUniforms = other.mUniforms;

			return *this;
		}

		ShaderCode& ShaderCode::operator=(ShaderCode&& other) noexcept
		{
			this->mType = other.mType;
			this->mLocation = other.mLocation;
			this->mInputAttributes = std::move(other.mInputAttributes);
			this->mOutputAttributes = std::move(other.mOutputAttributes);
			this->mShaderCode = std::move(other.mShaderCode);
			this->mUniforms = std::move(other.mUniforms);

			return *this;
		}
	}
}