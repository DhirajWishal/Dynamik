// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "Uniform.h"

namespace Dynamik
{
	UI64 DMKUniformDescription::getUniformSize() const
	{
		UI64 _size = 0;
		for (auto _attribute : attributes)
			_size += ((UI64)_attribute.dataType * _attribute.dataCount);

		return _size;
	}

	I64 DMKUniformBufferDescriptor::operator()()
	{
		auto descriptorCount = this->uniformBufferObjects.size();
		I64 _ID = 0;

		return _ID;
	}

	void DMKUniformBufferObject::setDescription(const DMKUniformDescription& description)
	{
		initialize(description);
	}

	void DMKUniformBufferObject::initialize(const DMKUniformDescription& description)
	{
		myDescription = description;
		pUniformBufferStorage = StaticAllocator<UI32>::allocateArr(myDescription.getUniformSize());
		nextPointer = (BYTE*)pUniformBufferStorage;
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
				DMKMemoryFunctions::moveData(pUniformBufferStorage, data, byteSize);
		}
		else
			DMK_FATAL("Invalid data location bound!");
	}

	void DMKUniformBufferObject::setData(const VPTR& data)
	{
		DMKMemoryFunctions::moveData(pUniformBufferStorage, data, myDescription.getUniformSize());
	}

	void DMKUniformBufferObject::clear()
	{
		StaticAllocator<VPTR>::deallocate(pUniformBufferStorage, myDescription.getUniformSize());
		pUniformBufferStorage = nullptr;
		nextPointer = (BYTE*)pUniformBufferStorage;
	}

	VPTR DMKUniformBufferObject::data() const
	{
		return pUniformBufferStorage;
	}

	UI64 DMKUniformBufferObject::byteSize() const
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

		DMKUniformAttribute _attribute1;
		_attribute1.dataCount = 1;
		_attribute1.dataType = DMKDataType::DMK_DATA_TYPE_MAT4;
		_description.attributes.pushBack(_attribute1);

		DMKUniformAttribute _attribute2;
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

		DMKUniformAttribute _attribute1;
		_attribute1.dataCount = 1;
		_attribute1.dataType = DMKDataType::DMK_DATA_TYPE_MAT4;
		_description.attributes.pushBack(_attribute1);

		return _description;
	}
}