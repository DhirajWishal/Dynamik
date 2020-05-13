#pragma once
#ifndef _DYNAMIK_MEMORY_PADDING_H
#define _DYNAMIK_MEMORY_PADDING_H

/*
 Memory Padding object for the Dynamik Engine
 The engine aligns all of its objects and structures to fit a pre defined alignment.

 Author:    Dhiraj Wishal
 Date:      13/05/2020
 IDE:       MS Visual Studio Community 2019
*/

#include "../Types/DataTypes.h"
#include "Macros/Global.h"
#include "Macros/MemoryMacro.h"

/*
 TEMPLATED CLASS
 Dynamik Memory Padding Object.

 This object is used to fill memory alignment gaps in any object/ structure.
 The required padding must be passed via the template argument.

 Including this object inside "private:" would make better interface.
 Alignment must be provided in bits.
*/
template<UI32 alignment = DMK_ALIGNMENT>
class DMK_ALIGN DMK_API DMKMemoryPadding
{
    /* Check for the template input before compiling. */
    static_assert((alignment / 8), "Invalid memory alignment. You might have given in bytes. Template argument is required in bits.");

    /* Padding variable constant. */
	const BYTE __pad[(alignment / 8)] = { 0 };
};

#endif // !_DYNAMIK_MEMORY_PADDING_H
