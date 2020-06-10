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

	UI64 DMKUniformDescription::getUniformSize()
	{
		UI64 _size = 0;
		for (auto _attribute : attributes)
			_size += ((UI64)_attribute.dataType * _attribute.dataCount);

		return _size;
	}

	UI32 DMKVertexBufferDescriptor::getVertexSize()
	{
		UI32 _size = 0;
		for (auto _attribute : attributes)
			_size += ((UI64)_attribute.dataType * _attribute.dataCount);

		return _size;
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
		nextPointer = uniformBufferStorage;
	}

	void DMKUniformBufferObject::initialize(const DMKUniformDescription& description)
	{
		myDescription = description;
		uniformBufferStorage = StaticAllocator<UI32>::allocateArr(myDescription.getUniformSize());
		nextPointer = uniformBufferStorage;
	}

	void DMKUniformBufferObject::setData(const VPTR& data, const UI32& byteSize, const UI32& location, const UI32& arrayIndex)
	{
		if (location < myDescription.attributes.size())
		{
			if ((UI32)myDescription.attributes[location].dataType != byteSize)
				DMK_FATAL("Invalid data size bound! Possibly because your binding the wront data.");

			if (location)
			{
				if (arrayIndex < (UI32)myDescription.attributes[location - 1].dataCount)
				{
					nextPointer = (VPTR)(((UI64)nextPointer) + (UI64)myDescription.attributes[location - 1].dataType * (arrayIndex + 1));
				}
				else
				{
					DMK_ERROR("Invalid array location in the uniform element at: " +
						std::to_string(location) +
						". Niglecting the array location and binding to the data to the given location.");

					nextPointer = (VPTR)(((UI64)nextPointer) + (UI64)myDescription.attributes[location - 1].dataType);
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
		nextPointer = uniformBufferStorage;
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
		_description.usage = DMKUniformBufferUsage::DMK_UNIFORM_BUFFER_USAGE_CUSTOM;

		DMKUniformAttribute _attribute1;
		_attribute1.attributeType = DMKUniformAttributeType::DMK_UNIFORM_ATTRIBUTE_TYPE_MODEL;
		_attribute1.dataCount = 1;
		_attribute1.dataType = DMKDataType::DMK_DATA_TYPE_MAT4;
		_description.attributes.pushBack(_attribute1);

		return _description;
	}
}
