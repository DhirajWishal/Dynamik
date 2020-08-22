// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "Module00.h"
#include "../../Worlds/DefaultWorld.h"

void Module00::onInitialize()
{
	/* Load the default game world. */
	createUserGameWorld<DefaultWorld>();
}
