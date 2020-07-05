// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "MemoryFunctions.h"

#include <memory>

namespace Dynamik
{
	void DMKMemoryFunctions::moveData(VPTR destination, VPTR source, UI64 byteSize)
	{
		/* TODO: Proper memory move function */
		std::memcpy(destination, source, byteSize);
	}

	void DMKMemoryFunctions::setData(VPTR destination, BYTE byteValue, UI64 byteSize)
	{
		/* TODO: Proper memory set function */
		std::memset(destination, byteValue, byteSize);
	}
}