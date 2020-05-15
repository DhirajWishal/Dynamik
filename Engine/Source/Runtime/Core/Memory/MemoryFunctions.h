#pragma once
#ifndef _DYNAMIK_MEMORY_FUNCTIONS_H
#define _DYNAMIK_MEMORY_FUNCTIONS_H

/*
 Memory Functions for the Dynamik Engine.
 This contains a set of functions which can be used to manipulate data.

 Author:    Dhiraj Wishal
 Date:      13/05/2020
*/

#include "Object/Object.h"

namespace Dynamik
{
    /*
     This class contains all the necessary memory functions for the Dynamik Engine.
    */
    DMK_ALIGN class DMK_API MemoryFunctions
    {
    private:                                                
        MemoryFunctions() {}
        ~MemoryFunctions() {}
        
    public:													
        MemoryFunctions(const MemoryFunctions&) = delete;
        MemoryFunctions(MemoryFunctions&&) = delete;
        MemoryFunctions& operator=(const MemoryFunctions&) = delete;
        MemoryFunctions& operator=(MemoryFunctions&&) = delete;

        static void moveData(VPTR destination, VPTR source, UI32 byteSize);
        static void setData(VPTR destination, BYTE byteValue, UI32 byteSize);
    };
}

#endif // !_DYNAMIK_MEMORY_FUNCTIONS_H
