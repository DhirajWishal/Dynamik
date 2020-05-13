#pragma once
#ifndef _DYNAMIK_GLOBAL_MACROS_H
#define _DYNAMIK_GLOBAL_MACROS_H

/*
 This header contains all the global macros for the engine.

 Author:	Dhiraj Wishal
 Date:		13/05/2020
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


#endif // !_DYNAMIK_GLOBAL_MACROS_H
