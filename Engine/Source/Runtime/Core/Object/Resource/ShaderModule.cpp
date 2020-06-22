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

	void DMKShaderModule::setLocation(const DMKShaderLocation& location)
	{
		this->location = location;
	}

	void DMKShaderModule::setResourceMap(const DMKShaderResourceMap& resourceMap)
	{
		this->resourceMap = resourceMap;
	}

	void DMKShaderModule::addResource(const DMKVertexAttribute& inputAttribute)
	{
		resourceMap.inputAttributes.pushBack(inputAttribute);
	}

	void DMKShaderModule::addResource(const DMKUniformDescription& uniformDescription)
	{
		resourceMap.uniforms.pushBack(uniformDescription);
	}

	const DMKShaderResourceMap DMKShaderModule::getResourceMap() const
	{
		return this->resourceMap;
	}
}