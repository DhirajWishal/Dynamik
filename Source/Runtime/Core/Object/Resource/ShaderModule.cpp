// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "ShaderModule.h"

#include <fstream>

namespace Dynamik
{
	DMKShaderResourceLayout DMKShaderResourceLayout::createDefault(const DMKShaderLocation& location)
	{
		DMKShaderResourceLayout layout;
		DMKUniformDescription uniform;
		uniform.shaderLocation = location;

		switch (location)
		{
		case Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX:
		{
			/* Initialize Input Attributes */
			DMKShaderInputAttribute inputAttribute;
			inputAttribute.dataCount = 1;

			inputAttribute.dataType = DMKDataType::DMK_DATA_TYPE_VEC3;
			layout.inputAttributes.pushBack(inputAttribute);
			layout.inputAttributes.pushBack(inputAttribute);

			inputAttribute.dataType = DMKDataType::DMK_DATA_TYPE_VEC2;
			layout.inputAttributes.pushBack(inputAttribute);

			/* Initialize Uniforms */
			uniform.type = DMKUniformType::DMK_UNIFORM_TYPE_UNIFORM_BUFFER;
			uniform.usage = DMKUniformBufferUsage::DMK_UNIFORM_BUFFER_USAGE_MODEL;
			uniform.destinationBinding = 0;

			DMKUniformAttribute uniformAttribute;
			uniformAttribute.dataCount = 1;
			uniformAttribute.dataType = DMKDataType::DMK_DATA_TYPE_MAT4;

			uniformAttribute.attributeType = DMKUniformAttributeType::DMK_UNIFORM_ATTRIBUTE_TYPE_MODEL;
			uniform.attributes.pushBack(uniformAttribute);
			layout.uniforms.pushBack(uniform);
			uniform.attributes.clear();

			uniform.destinationBinding = 0;
			uniform.usage = DMKUniformBufferUsage::DMK_UNIFORM_BUFFER_USAGE_CAMERA;

			uniformAttribute.attributeType = DMKUniformAttributeType::DMK_UNIFORM_ATTRIBUTE_TYPE_VIEW;
			uniformAttribute.dataType = DMKDataType::DMK_DATA_TYPE_MAT4;
			uniform.attributes.pushBack(uniformAttribute);

			uniformAttribute.attributeType = DMKUniformAttributeType::DMK_UNIFORM_ATTRIBUTE_TYPE_PROJECTION;
			uniformAttribute.dataType = DMKDataType::DMK_DATA_TYPE_MAT4;
			uniform.attributes.pushBack(uniformAttribute);
			layout.uniforms.pushBack(uniform);
		}
		break;
		case Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_TESSELLATION:
			break;
		case Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_GEOMETRY:
			break;
		case Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_FRAGMENT:
		{
			uniform.destinationBinding = 0;
			uniform.type = DMKUniformType::DMK_UNIFORM_TYPE_SAMPLER_2D;
			uniform.usage = DMKUniformBufferUsage::DMK_UNIFORM_BUFFER_USAGE_SAMPLER;
			layout.uniforms.pushBack(uniform);
		}
			break;
		default:
			DMK_ERROR_BOX("Invalid location! This function supports Vertex, Tessellation, Geometry and Fragment!");
			break;
		}

		return layout;
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