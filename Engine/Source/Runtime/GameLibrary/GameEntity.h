// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GAME_ENTITY_H
#define _DYNAMIK_GAME_ENTITY_H

/*
 Game Entiry for the Dynamik Engine.

 Author:    Dhiraj Wishal
 Date:      17/05/2020
*/
#include "ComponentSystem/ComponentManager.h"

namespace Dynamik
{
	/*
	 The entity class is the component which the user directly interact with. Player character and other
	 input based characters are derived from this.
	 Basically, Game Entities are of two types,

	 You can imagine entities as a soul. You are required to control it. 
	*/
	class DMK_API DMKGameEntity {
	public:
		DMKGameEntity() {}
		virtual ~DMKGameEntity() {}

		/*
		 Initialize the entity
		*/
		virtual void initialize() {}

		/*
		 Setup camera module
		 Camera modules are added to the renderable components after initializing the entity.
		 Shaders will have the uniform buffer of the camera at the last binding. by default view and 
		 projection matrixes are passed respectively.
		*/
		virtual void setupCamera(const POINTER<DMKCameraModule>& cModule);

		/* Component Manager */
		DMKComponentManager componentManager;
	};
}

#endif // !_DYNAMIK_GAME_ENTITY_H
