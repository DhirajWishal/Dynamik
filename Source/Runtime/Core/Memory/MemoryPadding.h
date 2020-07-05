// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_MEMORY_PADDING_H
#define _DYNAMIK_MEMORY_PADDING_H

/*
 Memory Padding object for the Dynamik Engine
 The engine aligns all of its objects and structures to fit a pre defined alignment.
*/

#include "../Types/DataTypes.h"
#include "Core/Macros/Global.h"
#include "Core/Macros/MemoryMacro.h"

namespace Dynamik
{
	/*
	 TEMPLATED CLASS
	 Dynamik Memory Padding Object.

	 This object is used to fill memory alignment gaps in any object/ structure.
	 The required padding must be passed via the template argument.

	 Including this object inside "private:" would make better interface.
	 Alignment must be provided in bits.
	*/
	template<UI32 alignment = DMK_ALIGNMENT>
	class DMK_API DMKMemoryPadding
	{
		/* Check for the template input before compiling. */
		static_assert((alignment / 8), "Invalid memory alignment. You might have given in bytes. Template argument is required in bits.");

		/* Padding variable constant. */
		const BYTE __pad[(alignment / 8)] = { 0 };
	};
}

#endif // !_DYNAMIK_MEMORY_PADDING_H
