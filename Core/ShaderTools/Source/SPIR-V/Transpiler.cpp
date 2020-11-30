// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "ShaderTools/SPIR-V/Transpiler.h"
#include "ShaderTools/SPIR-V/Utilities.h"
#include "Core/ErrorHandler/Logger.h"
#include "Core/Memory/Functions.h"

#include <spirv_glsl.hpp>
#include <spirv_hlsl.hpp>

namespace DMK
{
	namespace ShaderTools
	{
		void SPIRVTranspiler::Initialize(GraphicsCore::ShaderCode* pShaderCode)
		{
			// Check if the shader code type is correct.
			if (pShaderCode->GetCodeType() != GraphicsCore::ShaderCodeType::SPIR_V)
			{
				Logger::LogError(TEXT("Invalid shader code type sent to the SPIR-V Transpiler! Make sure that the code type is SPIR-V."));
				return;
			}

			this->pShaderCode = pShaderCode;
		}

		GraphicsCore::ShaderCode SPIRVTranspiler::GetGLSL()
		{
			// Create and initialize the shader code.
			GraphicsCore::ShaderCode mShaderCode = {};
			mShaderCode.mLocation = pShaderCode->GetLocation();
			mShaderCode.mType = GraphicsCore::ShaderCodeType::GLSL;

			// Check if the shader code object is set.
			if (!pShaderCode)
			{
				Logger::LogError(TEXT("Shader code is not set! Make sure to initialize the SPIR-V Transpiler with the shader code pointer."));
				return mShaderCode;
			}

			// Create the compiler.
			spirv_cross::CompilerGLSL mCompiler(std::move(Utilities::ResolvePadding(pShaderCode->mShaderCode)));
			
			// Compile to GLSL and get the byte size of it.
			auto mGLSl = mCompiler.compile();
			UI64 mSize = mGLSl.size() * sizeof(char);

			// Resize the vector.
			mShaderCode.mShaderCode.resize(mSize / sizeof(UI32));

			// Move data from the string to the shader code and return it.
			MemoryFunctions::MoveData(mShaderCode.mShaderCode.data(), mGLSl.data(), mSize);
			return mShaderCode;
		}
		
		GraphicsCore::ShaderCode SPIRVTranspiler::GetHLSL()
		{
			// Create and initialize the shader code.
			GraphicsCore::ShaderCode mShaderCode = {};
			mShaderCode.mLocation = pShaderCode->GetLocation();
			mShaderCode.mType = GraphicsCore::ShaderCodeType::HLSL;

			// Check if the shader code object is set.
			if (!pShaderCode)
			{
				Logger::LogError(TEXT("Shader code is not set! Make sure to initialize the SPIR-V Transpiler with the shader code pointer."));
				return mShaderCode;
			}

			// Create the compiler.
			spirv_cross::CompilerHLSL mCompiler(std::move(Utilities::ResolvePadding(pShaderCode->mShaderCode)));

			// Compile to GLSL and get the byte size of it.
			auto mHLSL = mCompiler.compile();
			UI64 mSize = mHLSL.size() * sizeof(char);

			// Resize the vector.
			mShaderCode.mShaderCode.resize(mSize / sizeof(UI32));

			// Move data from the string to the shader code and return it.
			MemoryFunctions::MoveData(mShaderCode.mShaderCode.data(), mHLSL.data(), mSize);
			return mShaderCode;
		}
	}
}