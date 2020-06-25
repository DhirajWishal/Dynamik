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

	void DMKShaderModule::setResourceLayout(const DMKShaderResourceLayout& resourceLayout)
	{
		this->resourceLayout = resourceLayout;
	}

	void DMKShaderModule::addResource(const DMKShaderInputAttribute& inputAttribute)
	{
		resourceLayout.inputAttributes.pushBack(inputAttribute);
	}

	void DMKShaderModule::addResource(const DMKUniformDescription& uniformDescription)
	{
		resourceLayout.uniforms.pushBack(uniformDescription);
	}

	const DMKShaderResourceLayout DMKShaderModule::getResourceLayout() const
	{
		return this->resourceLayout;
	}
}