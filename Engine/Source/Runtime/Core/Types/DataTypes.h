#pragma once
#ifndef _DYNAMIK_DATA_TYPES_H
#define _DYNAMIK_DATA_TYPES_H

#include <cstdint>

/*
 Dynamik Data Types.
 These data types are in the global scope and the engine and the studio will use these types.

 Author:    Dhiraj Wishal
 Date:      13/05/2020
 IDE:       MS Visual Studio 2019
*/

typedef unsigned char UI8;			// unsigned 8 bit integer
typedef unsigned short UI16;		// unsigned 16 bit integer
typedef unsigned int UI32;			// unsigned 32 bit integer
typedef unsigned long long UI64;	// unsigned 64 bit integer

typedef signed char SI8;			// signed 8 bit integer
typedef signed short SI16;			// signed 16 bit integer
typedef signed int SI32;			// signed 32 bit integer
typedef signed long long SI64;		// signed 64 bit integer

typedef signed char I8;				// 8 bit integer
typedef short I16;					// 16 bit integer
typedef int I32;					// 32 bit integer
typedef long long I64;				// 64 bit integer

typedef bool B1;					// bool
typedef float F32;					// float
typedef double D64;					// double
typedef long double LD64;			// long double

typedef void* VPTR;					// void pointer
typedef char* CPTR;					// char pointer
typedef wchar_t* WCPTR;				// char pointer
typedef const char* CCPTR;			// const char pointer
typedef unsigned char* UCPTR;		// unsigned char pointer
typedef const wchar_t* CWCPTR;		// const char pointer

typedef char CHR;					// char (ASCII)
typedef wchar_t WCHR;				// wide char (UTF-8)

typedef UI8 BYTE;					// byte of data
typedef BYTE* BPTR;					// byte pointer

typedef unsigned char UCHR;			// unsigned char

#endif // !_DYNAMIK_DATA_TYPES_H
