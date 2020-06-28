// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_PLAYER_OBJECT_H
#define _DYNAMIK_PLAYER_OBJECT_H

/*
 Author:	Dhiraj Wishal
 Date:		13/06/2020
*/
#include "Camera/CameraModule.h"
#include "ComponentSystem/ComponentManager.h"

namespace Dynamik
{
	/*
	 Dynamik Player Object
	 This object is the user controlled character in the game.
	*/
	class DMK_API DMKPlayerObject {
	public:
		DMKPlayerObject() {}
		virtual ~DMKPlayerObject() {}

		/*
		 On initialize method
		*/
		virtual void onInitialize() {}

	public:		/* Component manager */
		DMKComponentManager componentManager;

		/*
		 Create a new component and return its address.
		*/
		template<class COMPONENT>
		COMPONENT* createComponent()
		{
			return componentManager.createComponent<COMPONENT>();
		}

	public:		/* Camera Module */
		DMKCameraModule* cameraModule;

		/*
		 Get the camera module
		*/
		virtual DMKCameraModule* getCameraModule() { return cameraModule; }
	};
}

#endif // !_DYNAMIK_PLAYER_ENTITY_H
