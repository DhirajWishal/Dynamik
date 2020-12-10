// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "GraphicsCore/Backend/Buffer.h"

namespace DMK
{
	namespace GraphicsCore
	{
		void Buffer::CopyData(Device* pDevice, const void* pData, UI64 size, UI64 offset)
		{
			// Check if the size, buffer and buffer memory are valid.
			if (!mSize || !size || (size + offset) > mSize)
				return;

			auto pDataStore = MapMemory(pDevice, size, offset);
			std::memcpy(pDataStore, pData, size);
			UnmapMemory(pDevice);
		}

		void Buffer::MoveData(Device* pDevice, const void* pData, UI64 size, UI64 offset)
		{
			// Check if the size, buffer and buffer memory are valid.
			if (!mSize || !size || (size + offset) > mSize)
				return;

			auto pDataStore = MapMemory(pDevice, size, offset);
			std::memmove(pDataStore, pData, size);
			UnmapMemory(pDevice);
		}
	}
}