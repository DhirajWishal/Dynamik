// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_MEMORY_FUNCTIONS_H
#define _DYNAMIK_MEMORY_FUNCTIONS_H

/*
 Memory Functions for the Dynamik Engine.
 This contains a set of functions which can be used to manipulate data.
*/

/*
 This class contains all the necessary memory functions for the Dynamik Engine.
*/
class DMK_API DMKMemoryFunctions
{
private:
	DMKMemoryFunctions() {}
	~DMKMemoryFunctions() {}

public:
	DMKMemoryFunctions(const DMKMemoryFunctions&) = delete;
	DMKMemoryFunctions(DMKMemoryFunctions&&) = delete;
	DMKMemoryFunctions& operator=(const DMKMemoryFunctions&) = delete;
	DMKMemoryFunctions& operator=(DMKMemoryFunctions&&) = delete;

	static void moveData(VPTR destination, VPTR source, UI64 byteSize);
	static void copyData(VPTR destination, VPTR source, UI64 byteSize);
	static void setData(VPTR destination, BYTE byteValue, UI64 byteSize);
};

#endif // !_DYNAMIK_MEMORY_FUNCTIONS_H
