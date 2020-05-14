#pragma once
#ifndef _DYNAMIK_MEMORY_FUNCTIONS_H
#define _DYNAMIK_MEMORY_FUNCTIONS_H

/*
 Memory Functions for the Dynamik Engine.
 This contains a set of functions which can be used to manipulate data.

 Author:    Dhiraj Wishal
 Date:      13/05/2020
*/

#include "DataTypes.h"
#include "Macros/Global.h"
#include "Object/Object.h"

namespace Dynamik
{
    /*
     This class contains all the necessary memory functions for the Dynamik Engine.
    */
    class DMK_API MemoryFunctions
    {
        DMK_CLASS_FUNCTIONAL(MemoryFunctions)

        static void moveData(VPTR destination, VPTR source, UI32 byteSize);
        static void setData(VPTR destination, BYTE byteValue, UI32 byteSize);
    };
}

#endif // !_DYNAMIK_MEMORY_FUNCTIONS_H
