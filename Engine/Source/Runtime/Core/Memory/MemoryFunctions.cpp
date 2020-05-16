#include "dmkafx.h"
#include "MemoryFunctions.h"

#include <memory>

namespace Dynamik
{
	void MemoryFunctions::moveData(VPTR destination, VPTR source, UI64 byteSize)
	{
		/* TODO: Proper memory move function */
		std::memmove(destination, source, byteSize);
	}

	void MemoryFunctions::setData(VPTR destination, BYTE byteValue, UI64 byteSize)
	{
		/* TODO: Proper memory set function */
		std::memset(destination, byteValue, byteSize);
	}

}