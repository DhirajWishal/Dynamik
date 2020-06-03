#pragma once
#ifndef _DYNAMIK_CAMERA_MODULE_H
#define _DYNAMIK_CAMERA_MODULE_H

/*
 Author:	Dhiraj Wishal
 Date:		03/06/2020
*/
#include "Macros/Global.h"
#include "Math/MathTypes.h"
#include "Managers/Window/EventHandler.h"

namespace Dynamik
{
	/*
	 Camera module for the Dynamik Engine.
	*/
	class DMK_API DMKCameraModule {
	public:
		DMKCameraModule() {}
		virtual ~DMKCameraModule() {}

		virtual void update(const DMKEventBuffer& eventBuffer);

		MAT4F viewMatrix = MAT4F(0.0f);
		MAT4F projectionMatrix = MAT4F(0.0f);

		VEC3F position = { 0.0f, 0.0f, 0.0f };
		VEC3F front = { 0.0f, 0.0f, 1.0f };
		VEC3F right = { 1.0f, 0.0f, 0.0f };
		VEC3F cameraUp = { 0.0f, 1.0f, 0.0f };
		VEC3F worldUp = { 0.0f, 1.0f, 0.0f };
	};
}

#endif // !_DYNAMIK_CAMERA_H
