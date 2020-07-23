// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "Uniform.h"

namespace Dynamik
{
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

	void DMKUniformBufferObject::initialize()
	{
		if (!uByteSize)
		{
			DMK_ERROR("The buffer is not initialized! Make sure to add all the attributes prior to calling this function!");
			return;
		}

		if (pUniformBufferStorage)
		{
			if (uByteSize)
			{
				DMK_WARN("The buffer is already allocated! Reallocating the buffer.");
				StaticAllocator<VPTR>::deallocate(pUniformBufferStorage, uByteSize);
			}
		}

		pUniformBufferStorage = StaticAllocator<BYTE>::allocate(uByteSize);
	}

	void DMKUniformBufferObject::setData(const STRING& name, VPTR data, const UI64& offset)
	{
		auto attribute = attributeMap[name];
		DMKMemoryFunctions::copyData(IncrementPointer(pUniformBufferStorage, attribute.offset + offset), data, attribute.byteSize);
	}

	void DMKUniformBufferObject::setData(VPTR data)
	{
		DMKMemoryFunctions::copyData(pUniformBufferStorage, data, uByteSize);
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

	void DMKUniformBufferObject::setBindingLocation(const UI32& binding)
	{
		bindingLocation = binding;
	}

	UI64 DMKUniformBufferObject::getBindingLocation() const
	{
		return bindingLocation;
	}

	void DMKUniformBufferObject::setUniformType(const DMKUniformType& uniformType)
	{
		type = uniformType;
	}

	DMKUniformType DMKUniformBufferObject::getUniformType() const
	{
		return type;
	}
}