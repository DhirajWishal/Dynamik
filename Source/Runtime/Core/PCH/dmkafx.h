// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_PCH
#define _DYNAMIK_PCH

/*
 Dynamik Engine Precompiled Header File.

 Author:    Dhiraj Wishal
 Date:      13/05/2020

 @warn: Include files that are required by all the source files.
*/

#ifdef DMK_PLATFORM_WINDOWS
#include "Core/Error/ErrorManager.h"

#include "Core/Memory/MemoryFunctions.h"

#include "Core/Types/Utilities.h"
#include "Core/Types/DataTypes.h"

#include "Core/Macros/Assert.h"
#include "Core/Macros/Global.h"

#endif // DMK_PLATFORM_WINDOWS

#endif // !_DYNAMIK_PCH
