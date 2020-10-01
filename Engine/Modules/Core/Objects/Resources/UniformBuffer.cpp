// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "UniformBuffer.h"

void DMKUniformBuffer::addAttribute(const STRING& name, const UI64& attribSize)
{
	Attribute newAttribute;
	newAttribute.byteSize = attribSize;
	newAttribute.offset = uByteSize;
	attributeMap[name] = newAttribute;

	uByteSize += attribSize;
}

std::vector<DMKUniformBuffer::UniformBufferAttribute> DMKUniformBuffer::getAttributes() const
{
	std::vector<DMKUniformBuffer::UniformBufferAttribute> attributes;
	for (auto attribute : attributeMap)
	{
		DMKUniformBuffer::UniformBufferAttribute _attribute;
		_attribute.byteSize = attribute.second.byteSize;
		_attribute.offset = attribute.second.offset;
		_attribute.name = attribute.first;

		attributes.push_back(_attribute);
	}

	return attributes;
}

void DMKUniformBuffer::initialize()
{
	if (!uByteSize)
	{
		DMK_WARN("The buffer is not initialized! Make sure to add all the attributes prior to calling this function!");
		return;
	}

	if (pUniformBufferStorage)
	{
		if (uByteSize)
		{
			DMK_WARN("The buffer is already allocated! Reallocating the buffer.");
			StaticAllocator<void*>::deallocate(pUniformBufferStorage, uByteSize);
		}
	}

	pUniformBufferStorage = StaticAllocator<BYTE>::allocate(uByteSize);
}

void DMKUniformBuffer::setData(const STRING& name, void* data, const UI64& offset)
{
	auto attribute = attributeMap[name];
	DMKMemoryFunctions::copyData(IncrementPointer(pUniformBufferStorage, attribute.offset + offset), data, attribute.byteSize);
}

void DMKUniformBuffer::setData(void* data)
{
	DMKMemoryFunctions::copyData(pUniformBufferStorage, data, uByteSize);
}

void* DMKUniformBuffer::getData(const STRING& name, const UI64& offset)
{
	auto attribute = attributeMap[name];
	return IncrementPointer(pUniformBufferStorage, attribute.offset + offset);
}

void DMKUniformBuffer::setZero()
{
	DMKMemoryFunctions::setData(pUniformBufferStorage, 0, uByteSize);
}

void DMKUniformBuffer::clear()
{
	StaticAllocator<void*>::deallocate(pUniformBufferStorage, uByteSize);

	pUniformBufferStorage = nullptr;
	uByteSize = 0;
	attributeMap.clear();
}

void* DMKUniformBuffer::data() const
{
	return pUniformBufferStorage;
}

UI64 DMKUniformBuffer::byteSize() const
{
	return this->uByteSize;
}

void DMKUniformBuffer::setBindingLocation(const UI32& binding)
{
	bindingLocation = binding;
}

UI64 DMKUniformBuffer::getBindingLocation() const
{
	return bindingLocation;
}

void DMKUniformBuffer::setUniformType(const DMKUniformType& uniformType)
{
	type = uniformType;
}

DMKUniformType DMKUniformBuffer::getUniformType() const
{
	return type;
}
