// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_EXPERIMENTAL_GAME_PACKAGE_H
#define _DYNAMIK_EXPERIMENTAL_GAME_PACKAGE_H

#include "Core/Macros/Global.h"

namespace Dynamik
{
	namespace Experimental
	{
		/*
		 Dynamik Game Package
		 The game package defines an actual game instance. All the game data passed to the engine is passed through 
		 this object. It also contains additional information and systems the game might require. 
		*/
		class DMK_API DMKGamePackage {
		public:
			DMKGamePackage() {}
			virtual ~DMKGamePackage() {}
		};
	}
}

#endif // !_DYNAMIK_EXPERIMENTAL_GAME_PACKAGE_H
