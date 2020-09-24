// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GLOBAL_MACROS_H
#define _DYNAMIK_GLOBAL_MACROS_H

/*
 This header contains all the global macros for the engine.
*/

#define BIT_SHIFT(count)	(1 << count)

#define DMK_FORCEINLINE		__forceinline

#define DMK_ENGINE_VERSION	"00001-00000-00000"


#ifdef DMK_SHARED
	#if defined(DMK_PLATFORM_WINDOWS)
		#ifdef DMK_BUILD_SHARED
			#define DMK_API __declspec(dllexport)
		#else 
			#define DMK_API __declspec(dllimport)
		#endif
	#elif defined(DMK_PLATFORM_LINUX)
		#ifdef DMK_BUILD_SHARED
			#define DMK_API 
		#else 
			#define DMK_API 
		#endif
	#elif defined(DMK_PLATFORM_MAC)
		#ifdef DMK_BUILD_SHARED
			#define DMK_API 
		#else 
			#define DMK_API 
		#endif
	#else
		#error "Invalid Platform Macro!"
	#endif
#else
	#define DMK_API

#endif

#define DMK_SETUP_GETTER(className) className* get##className() const { return this; }

#endif // !_DYNAMIK_GLOBAL_MACROS_H
