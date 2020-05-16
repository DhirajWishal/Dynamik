#pragma once
#ifndef _DYNAMIK_MEMORY_MACRO_H
#define _DYNAMIK_MEMORY_MACRO_H

/*
 Memory Macros for the Dynamik Engine.
 By default Dynamik engine aligns all of its objects and structures for a 32 bit alignment.

 Author:    Dhiraj Wishal
 Date:      13/05/2020
*/

/* Default alignment */

#ifdef DMK_ALIGN_64_BIT
    #define DMK_ALIGNMENT	64

#else 
    #define DMK_ALIGNMENT	32  

#endif // DMK_ALIGN_64_BIT


/* Alignment macro */
#define DMK_ALIGN __declspec(align(DMK_ALIGNMENT))

/* 
 Alignment macros for Vector and Matrix classes.
 Name Convention: DMK_ALIGN_<Data type><Primitive type (float = F, double = D)>
*/
#define DMK_ALIGN_VEC2F      __declspec(align(8))
#define DMK_ALIGN_VEC2D      __declspec(align(16))

#define DMK_ALIGN_VEC3F      __declspec(align(16))
#define DMK_ALIGN_VEC3D      __declspec(align(32))

#define DMK_ALIGN_VEC4F      __declspec(align(16))
#define DMK_ALIGN_VEC4D      __declspec(align(32))

#define DMK_ALIGN_MAT2F      __declspec(align(16))
#define DMK_ALIGN_MAT2D      __declspec(align(32))

#define DMK_ALIGN_MAT3F      __declspec(align(36))
#define DMK_ALIGN_MAT3D      __declspec(align(62))

#define DMK_ALIGN_MAT4F      __declspec(align(64))
#define DMK_ALIGN_MAT4D      __declspec(align(128))

#endif // !_DYNAMIK_MEMORY_MACRO_H
