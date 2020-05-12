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

#include "DataTypes.h"

/*
 TEMPLATED CLASS
 Dynamik Memory Padding Object.

 This object is used to fill memory alignment gaps in any object/ structure.
 The required padding must be passed via the template argument.

 Including this object inside "private:" would make better interface.
*/
template<UI32 alignment = 1U>
class MemoryPadding
{
	BYTE __pad[alignment] = { 0 };
};

#endif // !_DYNAMIK_MEMORY_PADDING_H
