// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "IndexBuffer.h"

void DMKIndexBuffer::setIndexSize(UI64 size)
{
	indexSize = size;
}

const UI64 DMKIndexBuffer::getIndexSize() const
{
	return indexSize;
}

void DMKIndexBuffer::initialize(UI64 indexCount)
{
	if (!indexCount)
	{
		DMK_WARN("The index count submitted to initialize the index buffer is invalid!");
		return;
	}

	if (!indexSize)
	{
		DMK_WARN("The index size is not set!");
		return;
	}

	if (pDataStore)
	{
		DMK_WARN("The buffer is already allocated! Reallocating the buffer with the new size will clear all the stored data!");
		clear();
	}

	this->indexCount = indexCount;

	pDataStore = StaticAllocator<BYTE>::allocate(byteSize());
	lastAllocationSize = size();
}

void DMKIndexBuffer::clear()
{
	StaticAllocator<BYTE>::deallocate(pDataStore, lastAllocationSize);

	pDataStore = nullptr;
	lastAllocationSize = 0;
	indexCount = 0;
}

void DMKIndexBuffer::add(const UI64& index)
{
	if (((indexCount + 1) * indexSize) > lastAllocationSize)
		_growBuffer(indexSize);

	DMKMemoryFunctions::moveData(at(-1), Cast<void*>(&index), indexSize);

	indexCount++;
}

void DMKIndexBuffer::set(const void* data, UI64 size, UI64 offset)
{
	DMKMemoryFunctions::copyData(IncrementPointer(pDataStore, offset), data, size);
}

void* DMKIndexBuffer::data() const
{
	return pDataStore;
}

const UI64 DMKIndexBuffer::size() const
{
	return indexCount;
}

const UI64 DMKIndexBuffer::byteSize() const
{
	return indexSize * indexCount;
}

const UI64 DMKIndexBuffer::typeSize() const
{
	return indexSize;
}

void DMKIndexBuffer::resize(UI64 newIndexSize)
{
	if (indexSize)
	{
		if (pDataStore)
		{
			/* Allocate a new buffer with the data */

		}
	}
	else
	{
		indexSize = newIndexSize;
	}
}

void* DMKIndexBuffer::at(I64 index)
{
	if (index < 0 && indexCount == 0)
		return pDataStore;

	if (index < 0)
		index = indexCount + index;

	if (index > Cast<I64>(indexCount) || index < 0)
	{
		DMK_ERROR("Invalid index buffer index!");
		return nullptr;
	}

	return IncrementPointer(pDataStore, indexSize * index);
}

const void* DMKIndexBuffer::at(I64 index) const
{
	if (index < 0)
		index = indexCount - index;

	if (index > Cast<I64>(indexCount))
	{
		DMK_ERROR("Invalid index buffer index!");
		return nullptr;
	}

	return IncrementPointer(pDataStore, indexSize * index);
}

void DMKIndexBuffer::_growBuffer(UI64 byteSize)
{
	void* newBuffer = StaticAllocator<BYTE>::allocate(lastAllocationSize + byteSize);
	DMKMemoryFunctions::moveData(newBuffer, pDataStore, lastAllocationSize);

	StaticAllocator<BYTE>::deallocate(pDataStore, lastAllocationSize);

	pDataStore = newBuffer;
	lastAllocationSize += byteSize;
}