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

	void DMKUniformBufferObject::addAttribute(const STRING& name, const UI64& attribSize)
	{
		Attribute newAttribute;
		newAttribute.byteSize = attribSize;
		newAttribute.offset = uByteSize;
		attributeMap[name] = newAttribute;

		uByteSize += attribSize;
	}

	ARRAY<DMKUniformBufferObject::UniformBufferAttribute> DMKUniformBufferObject::getAttributes() const
	{
		ARRAY<DMKUniformBufferObject::UniformBufferAttribute> attributes;
		for (auto attribute : attributeMap)
		{
			DMKUniformBufferObject::UniformBufferAttribute _attribute;
			_attribute.byteSize = attribute.second.byteSize;
			_attribute.offset = attribute.second.offset;
			_attribute.name = attribute.first;

			attributes.pushBack(_attribute);
		}

		return attributes;
	}

	void DMKUniformBufferObject::setData(const STRING& name, VPTR data, const UI64& offset)
	{
		auto attribute = attributeMap[name];
		DMKMemoryFunctions::copyData(IncrementPointer(pUniformBufferStorage, attribute.offset + offset), data, attribute.byteSize);
	}

	VPTR DMKUniformBufferObject::getData(const STRING& name, const UI64& offset)
	{
		auto attribute = attributeMap[name];
		return IncrementPointer(pUniformBufferStorage, attribute.offset + offset);
	}

	void DMKUniformBufferObject::setZero()
	{
		DMKMemoryFunctions::setData(pUniformBufferStorage, 0, uByteSize);
	}

	void DMKUniformBufferObject::clear()
	{
		StaticAllocator<VPTR>::deallocate(pUniformBufferStorage, uByteSize);
		pUniformBufferStorage = nullptr;
	}

	VPTR DMKUniformBufferObject::data() const
	{
		return pUniformBufferStorage;
	}

	UI64 DMKUniformBufferObject::byteSize() const
	{
		return this->uByteSize;
	}

	void DMKUniformBufferObject::setBindingLocation(const UI64& binding)
	{
		bindingLocation = binding;
	}

	UI64 DMKUniformBufferObject::getBindingLocation() const
	{
		return bindingLocation;
	}

	void DMKUniformBufferObject::setLocation(const DMKShaderLocation& location)
	{
		this->location = location;
	}

	DMKShaderLocation DMKUniformBufferObject::getLocation() const
	{
		return location;
	}
}