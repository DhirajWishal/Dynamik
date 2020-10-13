// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_SYSTEM_H
#define _DYNAMIK_SYSTEM_H

#include "Core/Macros/Global.h"
#include <thread>

/*
 Dynamik System object
 The Dynamik Engine is made up of multiple systems interconnected to work with each other. All these systems
 are centrally managed by either the Engine or by the Studio.
 These systems are:
 * Rendering Engine
 * Physics Engine
 * Audio Engine
*/
class DMK_API DMKSystem {
public:
	DMKSystem() {}
	virtual ~DMKSystem() {}

	virtual void initializeInternals() = 0;
	virtual void terminateInternals() = 0;
};

#endif // !_DYNAMIK_SYSTEM_H
