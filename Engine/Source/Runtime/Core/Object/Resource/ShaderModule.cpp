// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "ShaderModule.h"

#include <fstream>

namespace Dynamik
{
	void DMKShaderModule::loadCode(const STRING& path)
	{
		std::ifstream file(path, std::ios::ate | std::ios::binary);

		if (!file.is_open())
			DMK_ERROR_BOX("Failed to load the specified shader at location (" + path + ")!");

		I64 fileSize = (I64)file.tellg();
		shaderCode.resize(fileSize);
		file.seekg(0);
		file.read((CPTR)shaderCode.data(), fileSize);

		file.close();
	}
	
	void DMKShaderModule::addResource(DMKUniformType type, UI32 binding, UI32 offset)
	{
		DMKShaderResource _resource;
		_resource.type = type;
		_resource.binding = binding;
		_resource.offset = offset;

		layout.resources.pushBack(_resource);
	}
}