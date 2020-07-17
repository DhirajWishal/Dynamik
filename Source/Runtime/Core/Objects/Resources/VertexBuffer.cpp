// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VertexBuffer.h"

namespace Dynamik
{
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

	DMKVertexLayout DMKVertexLayout::createBoundingBox()
	{
		DMKVertexLayout layout;
		DMKVertexAttribute attribute;
		attribute.dataCount = 1;

		attribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_POSITION;
		attribute.dataType = DMKDataType::DMK_DATA_TYPE_VEC3;
		layout.attributes.pushBack(attribute);

		attribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_COLOR_0;
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

	void DMKVertexBuffer::initialize(UI64 dataCount)
	{
		initialize(dataCount, layout);
	}

	void DMKVertexBuffer::initialize(UI64 dataCount, DMKVertexLayout layout)
	{
		/* Check if the vertex buffer is already initialized */
		if (pDataStore || _allocationSize)
		{
			DMK_WARN("The vertex buffer is already initialized! Clearing the buffer and re-initializing.");

			clear();
		}

		this->layout = layout;

		_allocationSize = layout.getVertexSize() * dataCount;
		pDataStore = StaticAllocator<BYTE>::allocate(_allocationSize);
	}

	void DMKVertexBuffer::setLayout(const DMKVertexLayout& layout)
	{
		this->layout = layout;
	}

	DMKVertexLayout DMKVertexBuffer::getLayout() const
	{
		return layout;
	}

	UI64 DMKVertexBuffer::size() const
	{
		return _allocationSize / layout.getVertexSize();
	}

	UI64 DMKVertexBuffer::stride() const
	{
		return layout.getVertexSize();
	}

	UI64 DMKVertexBuffer::byteSize() const
	{
		return _allocationSize;
	}

	void DMKVertexBuffer::clear()
	{
		StaticAllocator<BYTE>::deallocate(pDataStore, _allocationSize);

		pDataStore = nullptr;
		_allocationSize = 0;
	}

	VPTR DMKVertexBuffer::data() const
	{
		return pDataStore;
	}

	void DMKVertexBuffer::addData(const VPTR source, const UI64& byteCount, const UI64& offset)
	{
		DMKMemoryFunctions::moveData(IncrementPointer(pDataStore, offset), source, byteCount);
	}

	void DMKVertexBuffer::setData(const VPTR source)
	{
		DMKMemoryFunctions::moveData(pDataStore, source, _allocationSize);
	}

	void DMKVertexBuffer::setNull(const UI64& byteSize, const UI64& offset)
	{
		DMKMemoryFunctions::setData(IncrementPointer(pDataStore, offset), 0, byteSize);
	}

	void DMKVertexBuffer::updateVertex(const UI64& index, const VPTR data)
	{
		UI64 offset = layout.getVertexSize() * index;

		DMKMemoryFunctions::moveData(IncrementPointer(pDataStore, offset), data, stride());
	}

	void DMKVertexBuffer::updateVertexAttribute(const UI64& index, const VPTR data, const DMKVertexAttributeType& attribute)
	{
		UI64 offset = layout.getVertexSize() * index;
		offset += _findAttributeOffset(attribute);

		DMKMemoryFunctions::moveData(IncrementPointer(pDataStore, offset), data, _getAttributeSize(attribute));
	}

	UI64 DMKVertexBuffer::_findAttributeOffset(DMKVertexAttributeType attributeType)
	{
		UI64 _offset = 0;
		for (auto attribtue : layout.attributes)
		{
			if (attributeType == attribtue.attributeType)
				break;

			_offset += (UI64)attribtue.dataCount * (UI64)attribtue.dataType;
		}

		return _offset;
	}

	UI64 DMKVertexBuffer::_getAttributeSize(DMKVertexAttributeType attributeType)
	{
		for (auto attribtue : layout.attributes)
			if (attributeType == attribtue.attributeType)
				return attribtue.dataCount * (UI64)attribtue.dataType;

		DMK_ERROR("Attribute type is not available in the layout!");
		return UI64();
	}
}