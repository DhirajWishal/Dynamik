// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "MemoryFunctions.h"

#include <memory>

void DMKMemoryFunctions::moveData(void* destination, const void* source, UI64 byteSize)
{
	/* TODO: Proper memory move function */
	std::memmove(destination, source, byteSize);
}

void DMKMemoryFunctions::copyData(void* destination, const void* source, UI64 byteSize)
{
	/* TODO: Proper memory copy function */
	std::memcpy(destination, source, byteSize);
}

void DMKMemoryFunctions::setData(void* destination, BYTE byteValue, UI64 byteSize)
{
	/* TODO: Proper memory set function */
	std::memset(destination, byteValue, byteSize);
}
