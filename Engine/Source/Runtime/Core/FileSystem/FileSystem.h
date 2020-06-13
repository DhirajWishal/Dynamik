// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_FILE_SYSTEM_H
#define _DYNAMIK_FILE_SYSTEM_H

/*
 Author:    Dhiraj Wishal
 Date:      20/05/2020
*/
#include "Types/DataTypes.h"

namespace Dynamik
{
	/*
	 File System based functions for the Dynamik Engine
	*/
	class DMK_API DMKFileSystem {
	public:
		/* Get the path of the executable */
		static STRING getExecutablePath();

	};
}

#endif // !_DYNAMIK_FILE_SYSTEM_H
