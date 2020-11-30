// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "GraphicsCore/Objects/ShaderCode.h"

int main()
{
	DMK::GraphicsCore::ShaderCode mShaderCode;
	mShaderCode.LoadCode("..\\..\\Assets\\Shaders\\SkyBox\\Cinematic\\vert.spv", DMK::GraphicsCore::ShaderCodeType::SPIR_V, DMK::GraphicsCore::ShaderLocation::VERTEX);

	return 0;
}