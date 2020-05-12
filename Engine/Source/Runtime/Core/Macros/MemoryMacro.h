#pragma once
#ifndef _DYNAMIK_MEMORY_MACRO_H
#define _DYNAMIK_MEMORY_MACRO_H

/* 
 Memory Macros for the Dynamik Engine.
 By default Dynamik engine aligns all of its objects and structures for a 64 bit alignment.

 Author:    Dhiraj Wishal
 Date:      13/05/2020
*/

/* Default alignment */
#define DMK_ALIGNMENT	64

/* Alignment macro */
#define DMK_ALIGN alignof(DMK_ALIGNMENT)

#endif // !_DYNAMIK_MEMORY_MACRO_H
