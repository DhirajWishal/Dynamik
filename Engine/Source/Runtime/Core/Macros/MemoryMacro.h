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

#endif // !_DYNAMIK_MEMORY_MACRO_H
