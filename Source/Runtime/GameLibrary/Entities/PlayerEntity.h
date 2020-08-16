// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_PLAYER_OBJECT_H
#define _DYNAMIK_PLAYER_OBJECT_H

#include "Core/Types/ComplexTypes.h"
#include "../Camera/CameraModule.h"
#include "../Mechanics/PlayerController.h"

namespace Dynamik
{
	/*
	 Dynamik Player Object
	 This object is the user controlled character in the game. 
	*/
	class DMK_API DMKPlayerEntity {
	public:
		DMKPlayerEntity() {}
		virtual ~DMKPlayerEntity() {}

		/*
		 On initialize method
		*/
		virtual void onInitializePlayer() {}

		/*
		 Update the camera.
		 By default, on every call, the player position is added to the camera position.
		*/
		virtual void updateCamera();

		/*
		 Setup the player controller. 
		 This enables this object to be used in specific events.
		*/
		virtual void setupPlayerControls(DMKPlayerController* pPlayerController) {}

		/* Event Handling	*/
	public:
		/* On move forward event. */
		virtual void onMoveForward() {}

		/* On move backward event. */
		virtual void onMoveBackward() {}

		/* On move left event. */
		virtual void onMoveLeft() {}

		/* On move right event. */
		virtual void onMoveRight() {}

		/* On jump event */
		virtual void onJump() {}

		/* On crouch event */
		virtual void onCrouch() {}

		/* On sprint event */
		virtual void onSprint() {}

		/* On slide event */
		virtual void onSlide() {}

		/* On aim event */
		virtual void onAim() {}

		/* On trigger event */
		virtual void onTrigger() {}

		/* On reload event */
		virtual void onReload() {}

		/* On look at event */
		virtual void onLookAt() {}	/* eg: Looking at a scene. */

		/* On view event */
		virtual void onView() {}	/* eg: Looking at a gun. */

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

		void addRotationX(F32 pitch);
		void addRotationY(F32 yaw);
		void addRotationZ(F32 roll);

		void processMouseControl(DMKExtent2D position, F32 sensitivity = 0.1f, B1 refresh = false, B1 flipAxises = false);

		void setCameraViewPort(DMKExtent2D extent);

	public:		/* Camera Module */
		DMKCameraModule cameraModule;
		B1 isCameraRelative = false;

		/*
		 Set the camera position.
		*/
		void setCameraPosition(const VEC3& position);
		void setCameraAndWorldUp(const VEC3& cameraUp, const VEC3& worldUp);

		void setCameraParams(F32 FOV, F32 aspect, F32 fNear, F32 fFar);
		void setAspectRatio(F32 fAspect);

		void makeCameraRelative();
		void makeCameraStationary();

		/*
		 Get the camera module
		*/
		DMKCameraModule *getCameraModule();

	private:
		DMKExtent2D lastPosition;
		F32 firstInput = true;
	};
}

#endif // !_DYNAMIK_PLAYER_ENTITY_H
