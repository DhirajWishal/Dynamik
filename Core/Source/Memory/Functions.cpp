// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "Core/Memory/Functions.h"

#include <memory>

namespace DMK
{
	namespace MemoryFunctions
	{
		void MoveData(void* destination, const void* source, UI64 byteSize)
		{
			std::memmove(destination, source, byteSize);
		}

		void CopyData(void* destination, const void* source, UI64 byteSize)
		{
			std::memcpy(destination, source, byteSize);
		}

		void SetData(void* destination, BYTE byteValue, UI64 byteSize)
		{
			std::memset(destination, byteValue, byteSize);
		}
	}
}