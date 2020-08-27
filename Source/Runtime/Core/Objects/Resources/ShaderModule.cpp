// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "ShaderModule.h"

#include <fstream>

DMKShaderModule::DMKShaderModule(const STRING& path, const DMKShaderLocation& sLocation, const DMKShaderCodeType& sType)
	: location(sLocation), codeType(sType)
{
	loadCode(path);
}

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

void DMKShaderModule::addUniform(const DMKUniformBuffer& uniform)
{
	uniforms.pushBack(uniform);
}

DMKUniformBuffer& DMKShaderModule::getUniform(I64 index)
{
	return uniforms[index];
}

ARRAY<DMKUniformBuffer>& DMKShaderModule::getUniforms()
{
	return uniforms;
}

void DMKShaderModule::addInputAttribute(const DMKShaderInputAttribute& attribute)
{
	inputAttributes.pushBack(attribute);
}

void DMKShaderModule::setInputAttributes(ARRAY<DMKShaderInputAttribute> attributes)
{
	this->inputAttributes = attributes;
}

DMKShaderInputAttribute DMKShaderModule::getAttribute(I64 index) const
{
	return inputAttributes[index];
}

ARRAY<DMKShaderInputAttribute>& DMKShaderModule::getAttributes()
{
	return inputAttributes;
}
