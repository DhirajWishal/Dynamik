// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_ASSERT_H
#define _DYNAMIK_ASSERT_H

/*
 Assertion macros for the Dynamik Engine.
*/

#define DMK_ASSERT(condition, msg)	if(condition) 
#define DMK_CONDITIONAL_ASSERT(condition, expected, msg) if(condition == expected)

#endif // !_DYNAMIK_ERROR_MACRO_H
