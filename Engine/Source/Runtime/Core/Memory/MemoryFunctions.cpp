#include "dmkafx.h"
#include "MemoryFunctions.h"

#include <memory>

namespace Dynamik
{
	void DMKMemoryFunctions::moveData(VPTR destination, VPTR source, UI64 byteSize)
	{
		/* TODO: Proper memory move function */
		std::memmove(destination, source, byteSize);
	}

	void DMKMemoryFunctions::setData(VPTR destination, BYTE byteValue, UI64 byteSize)
	{
		/* TODO: Proper memory set function */
		std::memset(destination, byteValue, byteSize);
	}

}