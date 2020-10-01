// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VertexBuffer.h"

void DMKVertexLayout::addAttribute(const DMKVertexAttribute& attribute)
{
	attributes.push_back(attribute);
}

const UI64 DMKVertexLayout::getVertexSize() const
{
	UI64 _size = 0;
	for (auto _attribute : attributes)
		_size += FormatSize(_attribute.dataFormat) * _attribute.dataCount;

	return _size;
}

std::vector<DMKShaderInputAttribute> DMKVertexLayout::getInputAttributes() const
{
	std::vector<DMKShaderInputAttribute> inputAttributes;

	for (auto attribute : attributes)
		inputAttributes.push_back(DMKShaderInputAttribute(attribute.dataFormat, attribute.dataCount));

	return inputAttributes;
}

DMKVertexLayout DMKVertexLayout::createBasic()
{
	DMKVertexLayout layout;
	DMKVertexAttribute attribute;
	attribute.dataFormat = DMKFormat::DMK_FORMAT_RGBA_32_SF32;
	attribute.dataCount = 1;

	attribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_POSITION;
	layout.attributes.push_back(attribute);

	attribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_COLOR_0;
	layout.attributes.push_back(attribute);

	attribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES_0;
	attribute.dataFormat = DMKFormat::DMK_FORMAT_RG_32_SF32;
	layout.attributes.push_back(attribute);

	return layout;
}

DMKVertexLayout DMKVertexLayout::createBasicIBL()
{
	DMKVertexLayout layout;
	DMKVertexAttribute attribute;
	attribute.dataFormat = DMKFormat::DMK_FORMAT_RGBA_32_SF32;
	attribute.dataCount = 1;

	attribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_POSITION;
	layout.attributes.push_back(attribute);

	attribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_NORMAL;
	layout.attributes.push_back(attribute);

	attribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_UV_COORDINATES;
	attribute.dataFormat = DMKFormat::DMK_FORMAT_RG_32_SF32;
	layout.attributes.push_back(attribute);

	return layout;
}

DMKVertexLayout DMKVertexLayout::createAnimated()
{
	DMKVertexLayout layout;
	DMKVertexAttribute attribute;
	attribute.dataFormat = DMKFormat::DMK_FORMAT_RGBA_32_SF32;
	attribute.dataCount = 1;

	attribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_POSITION;
	layout.attributes.push_back(attribute);

	attribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_NORMAL;
	layout.attributes.push_back(attribute);

	attribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_UV_COORDINATES;
	attribute.dataFormat = DMKFormat::DMK_FORMAT_RG_32_SF32;
	layout.attributes.push_back(attribute);

	attribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_COLOR_0;
	attribute.dataFormat = DMKFormat::DMK_FORMAT_RGBA_32_SF32;
	layout.attributes.push_back(attribute);

	attribute.dataCount = 4;
	attribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_BONE_WEIGHT;
	attribute.dataFormat = DMKFormat::DMK_FORMAT_R_32_SF32;
	layout.attributes.push_back(attribute);

	attribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_BONE_ID;
	attribute.dataFormat = DMKFormat::DMK_FORMAT_R_32_SF32;
	layout.attributes.push_back(attribute);

	return layout;
}

DMKVertexLayout DMKVertexLayout::createBoundingBox()
{
	DMKVertexLayout layout;
	DMKVertexAttribute attribute;
	attribute.dataFormat = DMKFormat::DMK_FORMAT_RGBA_32_SF32;
	attribute.dataCount = 1;

	attribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_POSITION;
	layout.attributes.push_back(attribute);

	attribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_COLOR_0;
	layout.attributes.push_back(attribute);

	return layout;
}

DMKVertexLayout DMKVertexLayout::createBasicSkybox()
{
	DMKVertexLayout layout;
	DMKVertexAttribute attribute;
	attribute.dataCount = 1;
	attribute.dataFormat = DMKFormat::DMK_FORMAT_RGBA_32_SF32;
	attribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_POSITION;
	layout.attributes.push_back(attribute);

	return layout;
}

bool DMKVertexLayout::operator==(const DMKVertexLayout& other) const
{
	if (this->attributes.size() != other.attributes.size())
		return false;

	for (UI32 index = 0; index < this->attributes.size(); index++)
		if (
			(this->attributes[index].attributeType != other.attributes[index].attributeType) ||
			(this->attributes[index].dataCount != other.attributes[index].dataCount) ||
			(this->attributes[index].dataFormat != other.attributes[index].dataFormat))
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

void* DMKVertexBuffer::data() const
{
	return pDataStore;
}

void DMKVertexBuffer::addData(const void* source, const UI64& byteCount, const UI64& offset)
{
	DMKMemoryFunctions::moveData(IncrementPointer(pDataStore, offset), source, byteCount);
}

void DMKVertexBuffer::setData(const void* source)
{
	DMKMemoryFunctions::moveData(pDataStore, source, _allocationSize);
}

void DMKVertexBuffer::setNull(const UI64& byteSize, const UI64& offset)
{
	DMKMemoryFunctions::setData(IncrementPointer(pDataStore, offset), 0, byteSize);
}

void DMKVertexBuffer::updateVertex(const UI64& index, const void* data)
{
	UI64 offset = layout.getVertexSize() * index;

	DMKMemoryFunctions::moveData(IncrementPointer(pDataStore, offset), data, stride());
}

void DMKVertexBuffer::updateVertexAttribute(const UI64& index, const void* data, const DMKVertexAttributeType& attribute)
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

		_offset += (UI64)attribtue.dataCount * FormatSize(attribtue.dataFormat);
	}

	return _offset;
}

UI64 DMKVertexBuffer::_getAttributeSize(DMKVertexAttributeType attributeType)
{
	for (auto attribtue : layout.attributes)
		if (attributeType == attribtue.attributeType)
			return attribtue.dataCount * FormatSize(attribtue.dataFormat);

	DMK_ERROR("Attribute type is not available in the layout!");
	return UI64();
}
