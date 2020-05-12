#pragma once
#ifndef _DYNAMIK_ASSERT_H
#define _DYNAMIK_ASSERT_H

/*
 Assertion macros for the Dynamik Engine.

 Author:    Dhiraj Wishal
 Date:      13/05/2020
*/

#define DMK_ASSERT(condition, msg)	if(condition) 
#define DMK_CONDITIONAL_ASSERT(condition, expected, msg) if(condition == expected)

#endif // !_DYNAMIK_ERROR_MACRO_H
