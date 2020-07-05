// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GLOBAL_MACROS_H
#define _DYNAMIK_GLOBAL_MACROS_H

/*
 This header contains all the global macros for the engine.
*/

#ifdef DMK_PLATFORM_WINDOWS
	#ifdef DMK_DLL
		#ifdef DMK_BUILD_DLL
			#define DMK_API		__declspec(dllexport)
		#else 
			#define DMK_API		__declspec(dllimport)

		#endif // DMK_BUILD_DLL

	#else 
		#define DMK_API

	#endif // DMK_DLL  

#else
	#error Dynamik Engine currently supports Windows!

#endif // DMK_PLATFORM_WINDOWS

#define BIT_SHIFT(count)	(1 << count)

#define DMK_FORCEINLINE		__forceinline

#define DMK_ENGINE_VERSION	"00001-00000-00000"


#endif // !_DYNAMIK_GLOBAL_MACROS_H
