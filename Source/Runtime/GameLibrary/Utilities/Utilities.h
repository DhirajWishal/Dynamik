// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GAME_LIBRARY_UTILITIES_H
#define _DYNAMIK_GAME_LIBRARY_UTILITIES_H

#include "Renderer/Renderer.h"
#include "../Mechanics/PlayerController.h"

#include "Services/SystemLocator.h"

namespace Dynamik
{
	class DMK_API DMKRenderer;
	class DMK_API DMKPlayerController;

	/*
	 Get the currently active renderer. 
	*/
	DMKRenderer* GetRenderer();

	/*
	 Get the currently active player controller.
	*/
	DMKPlayerController* GetPlayerController();
}

#endif // !_DYNAMIK_GAME_LIBRARY_UTILITIES_H
