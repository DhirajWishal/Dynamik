// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "Primitives.h"

namespace Dynamik
{
	UI64 DMKConstantBlockDescription::getBlockSize()
	{
		UI64 _size = 0;
		for (auto _attribute : attributes)
			_size += ((UI64)_attribute.dataType * _attribute.dataCount);

		return _size;
	}

	UI64 DMKUniformDescription::getUniformSize() const
	{
		UI64 _size = 0;
		for (auto _attribute : attributes)
			_size += ((UI64)_attribute.dataType * _attribute.dataCount);

		return _size;
	}

	const UI64 DMKVertexLayout::getVertexSize() const
	{
		UI64 _size = 0;
		for (auto _attribute : attributes)
			_size += ((UI64)_attribute.dataType * _attribute.dataCount);

		return _size;
	}

	DMKVertexLayout DMKVertexLayout::createBasic()
	{
		DMKVertexLayout layout;
		DMKVertexAttribute attribute;
		attribute.dataCount = 1;

		attribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_POSITION;
		attribute.dataType = DMKDataType::DMK_DATA_TYPE_VEC3;
		layout.attributes.pushBack(attribute);

		attribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_COLOR_0;
		layout.attributes.pushBack(attribute);

		attribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_0;
		attribute.dataType = DMKDataType::DMK_DATA_TYPE_VEC2;
		layout.attributes.pushBack(attribute);

		return layout;
	}

	DMKVertexLayout DMKVertexLayout::createAnimated()
	{
		DMKVertexLayout layout;
		DMKVertexAttribute attribute;
		attribute.dataCount = 1;

		attribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_POSITION;
		attribute.dataType = DMKDataType::DMK_DATA_TYPE_VEC3;
		layout.attributes.pushBack(attribute);

		attribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_NORMAL;
		layout.attributes.pushBack(attribute);

		attribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_UV_COORDINATES;
		attribute.dataType = DMKDataType::DMK_DATA_TYPE_VEC2;
		layout.attributes.pushBack(attribute);

		attribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_COLOR_0;
		attribute.dataType = DMKDataType::DMK_DATA_TYPE_VEC3;
		layout.attributes.pushBack(attribute);

		attribute.dataCount = 4;
		attribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_BONE_WEIGHT;
		attribute.dataType = DMKDataType::DMK_DATA_TYPE_F32;
		layout.attributes.pushBack(attribute);

		attribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_BONE_ID;
		attribute.dataType = DMKDataType::DMK_DATA_TYPE_UI32;
		layout.attributes.pushBack(attribute);

		return layout;
	}

	B1 DMKVertexLayout::operator==(const DMKVertexLayout& other) const
	{
		if (this->attributes.size() != other.attributes.size())
			return false;

		for (UI32 index = 0; index < this->attributes.size(); index++)
			if (
				(this->attributes[index].attributeType != other.attributes[index].attributeType) ||
				(this->attributes[index].dataCount != other.attributes[index].dataCount) ||
				(this->attributes[index].dataType != other.attributes[index].dataType))
				return false;

		return true;
	}

	I64 DMKUniformBufferDescriptor::operator()()
	{
		auto descriptorCount = this->uniformBufferObjects.size();
		I64 _ID = 0;

		for (auto _object : this->uniformBufferObjects)
		{

		}

		return _ID;
	}

	DMKUniformBufferObject::~DMKUniformBufferObject()
	{
		StaticAllocator<VPTR>::deallocate(uniformBufferStorage, myDescription.getUniformSize());
		uniformBufferStorage = nullptr;
		nextPointer = (BYTE*)uniformBufferStorage;
	}

	void DMKUniformBufferObject::initialize(const DMKUniformDescription& description)
	{
		myDescription = description;
		uniformBufferStorage = StaticAllocator<UI32>::allocateArr(myDescription.getUniformSize());
		nextPointer = (BYTE*)uniformBufferStorage;
	}

	void DMKUniformBufferObject::setData(const VPTR& data, const UI32& byteSize, const UI32& location, const UI32& arrayIndex)
	{
		if (location < myDescription.attributes.size())
		{
			if ((UI32)myDescription.attributes[location].dataType != byteSize)
				DMK_FATAL("Invalid data size bound! Possibly because your binding the wrong data.");

			if (location)
			{
				if (arrayIndex < (UI32)myDescription.attributes[location - 1].dataCount)
				{
					nextPointer = (BYTE*)(((UI64)nextPointer) + (UI64)myDescription.attributes[location - 1].dataType * (arrayIndex + 1));
				}
				else
				{
					DMK_ERROR("Invalid array location in the uniform element at: " +
						std::to_string(location) +
						". Neglecting the array location and binding to the data to the given location.");

					nextPointer = (BYTE*)(((UI64)nextPointer) + (UI64)myDescription.attributes[location - 1].dataType);
				}
				DMKMemoryFunctions::moveData(nextPointer, data, byteSize);
			}
			else
				DMKMemoryFunctions::moveData(uniformBufferStorage, data, byteSize);
		}
		else
			DMK_FATAL("Invalid data location bound!");
	}

	void DMKUniformBufferObject::clear()
	{
		DMKMemoryFunctions::setData(uniformBufferStorage, 0, myDescription.getUniformSize());
		nextPointer = (BYTE*)uniformBufferStorage;
	}

	VPTR DMKUniformBufferObject::getUniformData() const
	{
		return uniformBufferStorage;
	}

	UI64 DMKUniformBufferObject::getUniformSize() const
	{
		return myDescription.getUniformSize();
	}

	DMKUniformDescription DMKUniformBufferObject::createUniformCamera(UI32 binding, DMKShaderLocation location)
	{
		DMKUniformDescription _description;
		_description.destinationBinding = binding;
		_description.offset = 0;
		_description.shaderLocation = location;
		_description.type = DMKUniformType::DMK_UNIFORM_TYPE_UNIFORM_BUFFER;
		_description.usage = DMKUniformBufferUsage::DMK_UNIFORM_BUFFER_USAGE_CAMERA;

		DMKUniformAttribute _attribute1;
		_attribute1.attributeType = DMKUniformAttributeType::DMK_UNIFORM_ATTRIBUTE_TYPE_VIEW;
		_attribute1.dataCount = 1;
		_attribute1.dataType = DMKDataType::DMK_DATA_TYPE_MAT4;
		_description.attributes.pushBack(_attribute1);

		DMKUniformAttribute _attribute2;
		_attribute2.attributeType = DMKUniformAttributeType::DMK_UNIFORM_ATTRIBUTE_TYPE_PROJECTION;
		_attribute2.dataCount = 1;
		_attribute2.dataType = DMKDataType::DMK_DATA_TYPE_MAT4;
		_description.attributes.pushBack(_attribute2);

		return _description;
	}

	DMKUniformDescription DMKUniformBufferObject::createUniformModel(UI32 binding, DMKShaderLocation location)
	{
		DMKUniformDescription _description;
		_description.destinationBinding = binding;
		_description.offset = 0;
		_description.shaderLocation = location;
		_description.type = DMKUniformType::DMK_UNIFORM_TYPE_UNIFORM_BUFFER;
		_description.usage = DMKUniformBufferUsage::DMK_UNIFORM_BUFFER_USAGE_MODEL;

		DMKUniformAttribute _attribute1;
		_attribute1.attributeType = DMKUniformAttributeType::DMK_UNIFORM_ATTRIBUTE_TYPE_MODEL;
		_attribute1.dataCount = 1;
		_attribute1.dataType = DMKDataType::DMK_DATA_TYPE_MAT4;
		_description.attributes.pushBack(_attribute1);

		return _description;
	}
}
