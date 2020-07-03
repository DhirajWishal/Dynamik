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

		/*
		 Update the camera.
		 By default, on every call, the player position is added to the camera position.
		*/
		virtual void updateCamera();

	public:		/* Player Data Store */
		Vector3F position = Vector3F(0.0f);

		/*
		 Set the player position in world space.
		*/
		void setPosition(const Vector3F& position);

		void addForwardVector(const F32& rate = 1.0f);
		void addBackwardVector(const F32& rate = 1.0f);
		void addLeftVector(const F32& rate = 1.0f);
		void addRightVector(const F32& rate = 1.0f);
		void addUpVector(const F32& rate = 1.0f);
		void addDownVector(const F32& rate = 1.0f);

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
		DMKCameraModule cameraModule;
		B1 isCameraRelative = false;

		/*
		 Set the camera position.
		*/
		void setCameraPosition(const VEC3& position);

		void setCameraParams(F32 FOV, F32 aspect, F32 fNear, F32 fFar);
		void setAspectRatio(F32 fAspect);

		void makeCameraRelative();
		void makeCameraStationary();

		/*
		 Get the camera module
		*/
		DMKCameraModule *getCameraModule();
	};
}

#endif // !_DYNAMIK_PLAYER_ENTITY_H
