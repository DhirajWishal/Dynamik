#include "dmkafx.h"
#include "MemoryFunctions.h"

#include <memory>

void MemoryFunctions::moveData(VPTR destination, VPTR source, UI32 byteSize)
{
	/* TODO: Proper memory move function */
	std::memmove(destination, source, byteSize);
}

void MemoryFunctions::setData(VPTR destination, BYTE byteValue, UI32 byteSize)
{
	/* TODO: Proper memory set function */
	std::memset(destination, byteValue, byteSize);
}
