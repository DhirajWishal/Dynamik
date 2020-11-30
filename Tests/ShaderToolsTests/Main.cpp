// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "ShaderTools/SPIR-V/Reflection.h"
#include "ShaderTools/SPIR-V/Transpiler.h"

int main()
{
	DMK::GraphicsCore::ShaderCode mShaderCode;
	mShaderCode.LoadCode("..\\..\\Assets\\Shaders\\SkyBox\\Cinematic\\vert.spv", DMK::GraphicsCore::ShaderCodeType::SPIR_V, DMK::GraphicsCore::ShaderLocation::VERTEX);

	DMK::ShaderTools::SPIRVReflection mTranspiler;
	mTranspiler.Reflect(mShaderCode);

	return 0;
}